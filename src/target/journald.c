// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// keeps systemd from showing stumpless itself as the source of the entries
#define SD_JOURNAL_SUPPRESS_LOCATION 1

#include <stddef.h>
#include <string.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/param.h>
#include <stumpless/target.h>
#include <stumpless/target/journald.h>
#include <sys/uio.h>
#include <systemd/sd-journal.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/getpid.h"
#include "private/config/wrapper/get_now.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/element.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/formatter.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/param.h"
#include "private/severity.h"
#include "private/target.h"
#include "private/target/journald.h"
#include "private/validate.h"

#define PRIORITY_PREFIX_SIZE 9
#define FACILITY_PREFIX_SIZE 16
#define TIMESTAMP_PREFIX_SIZE 17
#define IDENTIFIER_PREFIX_SIZE 18
#define PID_PREFIX_SIZE 11
#define MSGID_PREFIX_SIZE 13
#define MESSAGE_PREFIX_SIZE 8
#define SD_FIELDS_OFFSET 7

/**
 * Holds journald fields that are always present and have a fixed maximum
 * length.
 */
struct fixed_fields {
  char priority[PRIORITY_PREFIX_SIZE + 1];
  char facility[FACILITY_PREFIX_SIZE + 2];
  char timestamp[TIMESTAMP_PREFIX_SIZE + RFC_5424_TIMESTAMP_BUFFER_SIZE];
  char identifier[IDENTIFIER_PREFIX_SIZE + STUMPLESS_MAX_APP_NAME_LENGTH];
  char pid[PID_PREFIX_SIZE + MAX_INT_SIZE];
  char msgid[MSGID_PREFIX_SIZE + STUMPLESS_MAX_MSGID_LENGTH];
};

/* per-thread static variables */
static CONFIG_THREAD_LOCAL_STORAGE struct iovec *fields = NULL;
static CONFIG_THREAD_LOCAL_STORAGE size_t fields_length = 0;
static CONFIG_THREAD_LOCAL_STORAGE struct fixed_fields *fixed_fields = NULL;
static CONFIG_THREAD_LOCAL_STORAGE char *message_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE size_t message_buffer_length = 0;
static CONFIG_THREAD_LOCAL_STORAGE char *sd_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE size_t sd_buffer_size = 0;

void
stumpless_close_journald_target( const struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_JOURNALD_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_target( target );
  clear_error(  );
}

  size_t
  stumpless_flatten_element_name( const struct stumpless_entry *entry,
                                 size_t element_index,
                                 char *destination,
                                 size_t size ) {
  const struct stumpless_element *element;
  size_t required_size;
  size_t used_size;

  element = entry->elements[element_index];
  required_size = element->name_length;

  if( required_size > size ) {
    return required_size;
  }

  return get_journald_field_name( destination, element->name, element->name_length );
}

size_t
stumpless_flatten_param_name( const struct stumpless_entry *entry,
                              size_t element_index,
                              size_t param_index,
                              char *destination,
                              size_t size ) {
  const struct stumpless_element *element;
  const struct stumpless_param *param;
  size_t required_size;
  size_t used_size;

  element = entry->elements[element_index];
  param = element->params[param_index];

  required_size = element->get_journald_name( entry, element_index, NULL, 0 )
                  + 1 + param->name_length;

  if( required_size > size ) {
    return required_size;
  }

  used_size = element->get_journald_name( entry, element_index, destination,
                                          required_size );
  destination[used_size++] = '_';
  used_size += get_journald_field_name( destination + used_size,
                                        param->name, param->name_length );
  return used_size;
}

struct stumpless_target *
stumpless_open_journald_target( const char *name ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_JOURNALD_TARGET, name );
  if( !target ) {
    return NULL;
  }

  target->id = target;

  stumpless_set_current_target( target );
  return target;
}

/* private definitions */

size_t
get_journald_field_name( char *flattened, const char *raw, size_t size ) {
  unsigned char current;
  size_t raw_i = 0;
  size_t flattened_i = 0;

  while( raw_i < size ) {
    current = raw[raw_i];
    if( ( current >= 48 && current <= 57 ) // digit
        || ( current >= 65 && current <= 90 ) ) { // uppercase letter
      flattened[flattened_i] = current;
    } else if( current >= 97 && current <= 122 ) { // lowercase letter
      flattened[flattened_i] = current - 32;
    } else {
      flattened[flattened_i] = '_';
    }

    // skip over utf-8 multibyte characters
    while( current >= 128 ) {
      raw_i++;
    }

    raw_i++;
    flattened_i++;
  }

  return flattened_i;
}

void
init_fields( size_t field_count ) {
  struct iovec *new_fields;

  new_fields = realloc_mem( fields, sizeof( *fields ) * field_count );
  if( !new_fields ) {
    return;
  }

  fields = new_fields;
  fields_length = field_count;
  set_field_bases(  );
}

void
init_fixed_fields( void ){
  fixed_fields = alloc_mem( sizeof( *fixed_fields ) );
  if( !fixed_fields ) {
    return;
  }

  memcpy( fixed_fields->priority, "PRIORITY=", PRIORITY_PREFIX_SIZE );
  memcpy( fixed_fields->facility, "SYSLOG_FACILITY=", FACILITY_PREFIX_SIZE );
  memcpy( fixed_fields->timestamp, "SYSLOG_TIMESTAMP=", TIMESTAMP_PREFIX_SIZE );
  memcpy( fixed_fields->identifier, "SYSLOG_IDENTIFIER=",
          IDENTIFIER_PREFIX_SIZE );
  memcpy( fixed_fields->pid, "SYSLOG_PID=", PID_PREFIX_SIZE );
  memcpy( fixed_fields->msgid, "SYSLOG_MSGID=", MSGID_PREFIX_SIZE );

  if( fields ) {
    set_field_bases(  );
  }

}

void
journald_free_thread( void ) {
  free_mem( fields );
  fields = NULL;
  fields_length = 0;

  free_mem( fixed_fields );
  fixed_fields = NULL;

  free_mem( message_buffer );
  message_buffer = NULL;
  message_buffer_length = 0;

  free_mem( sd_buffer );
  sd_buffer = NULL;
  sd_buffer_size = 0;
}

void
load_facility( const struct stumpless_entry *entry ) {
  int facility_val;

  facility_val = get_facility( entry->prival ) >> 3;
  if( facility_val <= 9 ) {
    fixed_fields->facility[FACILITY_PREFIX_SIZE] = facility_val + 48;
    fields[1].iov_len = 17;
  } else {
    fixed_fields->facility[FACILITY_PREFIX_SIZE] = ( facility_val / 10 ) + 48;
    fixed_fields->facility[FACILITY_PREFIX_SIZE] = ( facility_val % 10 ) + 48;
    fields[1].iov_len = 18;
  }

}

void
load_identifier( const struct stumpless_entry *entry ) {
  memcpy( fixed_fields->identifier + IDENTIFIER_PREFIX_SIZE,
          entry->app_name,
          entry->app_name_length );
  fields[3].iov_len = IDENTIFIER_PREFIX_SIZE + entry->app_name_length;
}

char *
load_message( const struct stumpless_entry *entry ) {
  char *new_message_buffer;

  fields[6].iov_len = entry->message_length + MESSAGE_PREFIX_SIZE;
  if( fields[6].iov_len > message_buffer_length ) {
    new_message_buffer = realloc_mem( message_buffer, fields[6].iov_len );
    if( !new_message_buffer ) {
      return NULL;
    }
    message_buffer = new_message_buffer;
    message_buffer_length = fields[6].iov_len;
    memcpy( message_buffer, "MESSAGE=", MESSAGE_PREFIX_SIZE );
    fields[6].iov_base = message_buffer;
  }
  memcpy( message_buffer + MESSAGE_PREFIX_SIZE,
          entry->message,
          entry->message_length );

  return message_buffer;
}

void
load_msgid( const struct stumpless_entry *entry ) {
  memcpy( fixed_fields->msgid + MSGID_PREFIX_SIZE,
          entry->msgid,
          entry->msgid_length );
  fields[5].iov_len = MSGID_PREFIX_SIZE + entry->msgid_length;
}

size_t
load_pid( void ) {
  int pid;
  char digits[MAX_INT_SIZE];
  size_t pid_size;
  size_t digit_count;

  pid = config_getpid();
  if( pid == 0 ) {
    fixed_fields->pid[PID_PREFIX_SIZE] = '0';
    pid_size = 1;
  } else {
    pid_size = 0;
    digit_count = 0;

    while( pid != 0 ) {
      digits[digit_count++] = ( pid % 10 ) + 48;
      pid /= 10;
    }

    while( digit_count > 0 ) {
      fixed_fields->pid[PID_PREFIX_SIZE + pid_size] = digits[--digit_count];
      pid_size++;
    }
  }

  return PID_PREFIX_SIZE + pid_size;
}

void
load_priority( const struct stumpless_entry *entry ) {
  char severity;

  severity = get_severity( entry->prival ) + 48;
  fixed_fields->priority[PRIORITY_PREFIX_SIZE] = severity;
}

size_t
load_sd_fields( const struct stumpless_entry *entry ) {
  size_t fields_offset = SD_FIELDS_OFFSET;
  size_t field_count;
  size_t i;
  const struct stumpless_element *element;
  size_t size_needed = 0;
  size_t j;
  const struct stumpless_param *param;
  char *new_sd_buffer;
  char *pos;
  struct iovec *vec;
  size_t size_left;

  field_count = fields_offset + entry->element_count;
  for( i = 0; i < entry->element_count; i++ ) {
    element = entry->elements[i];
    lock_element( element );
    size_needed += element->get_journald_name( entry, i, NULL, 0 ) + 1;
    field_count += element->param_count;
    for( j = 0; j < element->param_count; j++ ) {
      param = element->params[j];
      lock_param( param );
      size_needed += param->get_journald_name( entry, i, j, NULL, 0 );
      size_needed += 1 + param->value_length;
    }
  }

  if( fields_length < field_count ) {
    init_fields( field_count );
    if( fields_length < field_count ) {
      goto fail;
    }
  }

  if( sd_buffer_size < size_needed ) {
    new_sd_buffer = realloc_mem( sd_buffer, size_needed );
    if( !new_sd_buffer ) {
      goto fail;
    }

    sd_buffer = new_sd_buffer;
    sd_buffer_size = size_needed;
  }

  pos = sd_buffer;
  for( i = 0; i < entry->element_count; i++ ) {
    element = entry->elements[i];
    vec = &fields[fields_offset++];
    vec->iov_base = pos;
    size_left = sd_buffer_size - ( pos - sd_buffer );
    pos += element->get_journald_name( entry, i, pos, size_left );
    *( pos++ ) = '=';
    vec->iov_len = pos - ( char * ) vec->iov_base;
    for( j = 0; j < entry->elements[i]->param_count; j++ ) {
      param = element->params[j];
      vec = &fields[fields_offset++];
      vec->iov_base = pos;
      size_left = sd_buffer_size - ( pos - sd_buffer );
      pos += param->get_journald_name( entry, i, j, pos, size_left );
      *( pos++ ) = '=';
      memcpy( pos, param->value, param->value_length );
      pos += param->value_length;
      unlock_param( param );
      vec->iov_len = pos - ( char * ) vec->iov_base;
    }

    unlock_element( element );
  }

  return field_count;

fail:
  for( i = 0; i < entry->element_count; i++ ) {
    for( j = 0; j < entry->elements[i]->param_count; j++ ) {
      unlock_param( entry->elements[i]->params[j] );
    }

    unlock_element( entry->elements[i] );
  }

  return 0;
}

size_t
load_timestamp( void ) {
  char *timestamp;

  timestamp = fixed_fields->timestamp + TIMESTAMP_PREFIX_SIZE;
  return TIMESTAMP_PREFIX_SIZE + config_get_now( timestamp );
}

int
send_entry_to_journald_target( const struct stumpless_target *target,
                               const struct stumpless_entry *entry ) {
  size_t timestamp_size;
  size_t pid_size;
  size_t field_count;
  int sendv_result;

  if( !fixed_fields ) {
    init_fixed_fields(  );
    if( !fixed_fields ) {
      goto fail;
    }
  }

  timestamp_size = load_timestamp(  );
  pid_size = load_pid(  );

  lock_entry( entry );

  field_count = load_sd_fields( entry );
  if( field_count == 0 ) {
    goto fail_locked;
  }

  if( !load_message( entry ) ) {
    goto fail_locked;
  }

  load_priority( entry );
  load_facility( entry );
  load_identifier( entry );
  load_msgid( entry );

  unlock_entry( entry );

  fields[2].iov_len = timestamp_size;
  fields[4].iov_len = pid_size;

  sendv_result = sd_journal_sendv( fields, field_count );
  if( sendv_result != 0 ) {
    raise_journald_failure( sendv_result );
  }

  return sendv_result;

fail_locked:
  unlock_entry( entry );
fail:
  return -1;
}

void
set_field_bases( void ) {
  fields[0].iov_base = fixed_fields->priority;
  fields[0].iov_len = 10;
  fields[1].iov_base = fixed_fields->facility;
  fields[2].iov_base = fixed_fields->timestamp;
  fields[3].iov_base = fixed_fields->identifier;
  fields[4].iov_base = fixed_fields->pid;
  fields[5].iov_base = fixed_fields->msgid;
}
