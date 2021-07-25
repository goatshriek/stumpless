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
#include "private/config/wrapper.h"
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

/* per-thread static variables */
static CONFIG_THREAD_LOCAL_STORAGE struct iovec *fields = NULL;
static CONFIG_THREAD_LOCAL_STORAGE size_t fields_length = 0;
static CONFIG_THREAD_LOCAL_STORAGE char *sd_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE size_t sd_buffer_size = 0;
static CONFIG_THREAD_LOCAL_STORAGE char *message_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE size_t message_buffer_length = 0;
static CONFIG_THREAD_LOCAL_STORAGE char *priority_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE char *facility_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE char *timestamp_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE char *pid_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE char *app_name_buffer = NULL;

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

  required_size = element->name_length + param->name_length + param->value_length + 2;

  if( required_size > size ) {
    return required_size;
  }

  used_size = get_journald_field_name( destination, element->name, element->name_length );
  destination[used_size++] = '_';
  used_size += get_journald_field_name( destination + used_size, param->name, param->name_length );
  destination[used_size++] = '=';
  memcpy( destination + used_size, param->value, param->value_length );
  return used_size + param->value_length;
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
journald_free_thread( void ) {
  free_mem( fields );
  fields = NULL;
  fields_length = 0;
  free_mem( sd_buffer );
  sd_buffer = NULL;
  sd_buffer_size = 0;
  free_mem( message_buffer );
  message_buffer = NULL;
  message_buffer_length = 0;
  free_mem( priority_buffer );
  priority_buffer = NULL;
  free_mem( facility_buffer );
  facility_buffer = NULL;
  free_mem( timestamp_buffer );
  timestamp_buffer = NULL;
  free_mem( pid_buffer );
  pid_buffer = NULL;
}

int
send_entry_to_journald_target( const struct stumpless_target *target,
                               const struct stumpless_entry *entry ) {
  struct iovec *new_fields;
  char *new_message_buffer;
  int facility_val;
  size_t timestamp_size;
  int pid;
  char pid_int_buffer[MAX_INT_SIZE];
  size_t pid_size;
  size_t pid_digit_count;
  int field_count = 6;
  size_t i;
  size_t j;
  size_t sd_buffer_size_needed;
  char *new_sd_buffer;
  char *sd_buffer_current;
  size_t fields_offset;

  if( !timestamp_buffer ) {
    timestamp_buffer = alloc_mem( 17 + RFC_5424_TIMESTAMP_BUFFER_SIZE );
    if( !timestamp_buffer ) {
      return -1;
    }
    memcpy( timestamp_buffer, "SYSLOG_TIMESTAMP=", 17 );
  }
  timestamp_size = config_get_now( timestamp_buffer + 17 );

  if( !priority_buffer ) {
    priority_buffer = alloc_mem( 10 );
    if( !priority_buffer ) {
      return -1;
    }
    memcpy( priority_buffer, "PRIORITY=", 9 );
  }

  if( !facility_buffer ) {
    facility_buffer = alloc_mem( 18 );
    if( !facility_buffer ) {
      return -1;
    }
    memcpy( facility_buffer, "SYSLOG_FACILITY=", 16 );
  }

  if( !app_name_buffer ) {
    app_name_buffer = alloc_mem( 18 + STUMPLESS_MAX_APP_NAME_LENGTH );
    if( !app_name_buffer ) {
      return -1;
    }
    memcpy( app_name_buffer, "SYSLOG_IDENTIFIER=", 18 );
  }

  if( !pid_buffer ) {
    pid_buffer = alloc_mem( 11 + MAX_INT_SIZE );
    if( !pid_buffer ) {
      return -1;
    }
    memcpy( pid_buffer, "SYSLOG_PID=", 11 );
  }
  pid = config_getpid();
  if( pid == 0 ) {
    pid_buffer[11] = '0';
    pid_size = 12;
  } else {
    pid_size = 11;
    pid_digit_count = 0;

    while( pid != 0 ) {
      pid_int_buffer[pid_digit_count] = ( pid % 10 ) + 48;
      pid /= 10;
      pid_digit_count++;
    }

    while( pid_digit_count > 0 ) {
      pid_digit_count--;
      pid_buffer[pid_size] = pid_int_buffer[pid_digit_count];
      pid_size++;
    }
  }

  lock_entry( entry );

  field_count = 6 + entry->element_count;
  sd_buffer_size_needed = 0;
  for( i = 0; i < entry->element_count; i++ ) {
    lock_element( entry->elements[i] );
    sd_buffer_size_needed += entry->elements[i]->name_length + 1;
    field_count += entry->elements[i]->param_count;
    for( j = 0; j < entry->elements[i]->param_count; j++ ) {
      lock_param( entry->elements[i]->params[j] );
      sd_buffer_size_needed += stumpless_flatten_param_name( entry, i, j, NULL, 0 );
    }
  }

  if( fields_length < field_count ) {
    new_fields = realloc_mem( fields, sizeof( *fields ) * field_count );
    if( !new_fields ) {
      return -1;
    }

    fields = new_fields;
    fields_length = field_count;
  }

  if( sd_buffer_size < sd_buffer_size_needed ) {
    new_sd_buffer = realloc_mem( sd_buffer, sd_buffer_size_needed );
    if( !new_sd_buffer ) {
      return -1;
    }

    sd_buffer = new_sd_buffer;
    sd_buffer_size = sd_buffer_size_needed;
  }

  fields_offset = 6;
  sd_buffer_current = sd_buffer;
  for( i = 0; i < entry->element_count; i++ ) {
    fields[fields_offset].iov_base = sd_buffer_current;
    fields[fields_offset].iov_len = entry->elements[i]->name_length + 1;
    memcpy( sd_buffer_current, entry->elements[i]->name, entry->elements[i]->name_length );
    sd_buffer_current[entry->elements[i]->name_length] = '=';
    sd_buffer_current += fields[fields_offset].iov_len;
    fields_offset++;
    for( j = 0; j < entry->elements[i]->param_count; j++ ) {
      fields[fields_offset].iov_base = sd_buffer_current;
      fields[fields_offset].iov_len = stumpless_flatten_param_name( entry, i, j, sd_buffer_current, sd_buffer_size - (sd_buffer_current - sd_buffer) );
      sd_buffer_current += fields[fields_offset].iov_len;
      fields_offset++;
      unlock_param( entry->elements[i]->params[j] );
    }
    unlock_element( entry->elements[i] );
  }

  fields[0].iov_len = entry->message_length + 8;
  if( fields[0].iov_len > message_buffer_length ) {
    new_message_buffer = realloc_mem( message_buffer, fields[0].iov_len );
    if( !new_message_buffer ) {
      unlock_entry( entry );
      return -1;
    }
    message_buffer = new_message_buffer;
    message_buffer_length = fields[0].iov_len;
    memcpy( message_buffer, "MESSAGE=", 8 );
  }
  memcpy( message_buffer + 8, entry->message, entry->message_length );

  priority_buffer[9] = get_severity( entry->prival ) + 48;

  facility_val = get_facility( entry->prival ) >> 3;
  if( facility_val <= 9 ) {
    facility_buffer[16] = facility_val + 48;
    fields[2].iov_len = 17;
  } else {
    facility_buffer[16] = ( facility_val / 10 ) + 48;
    facility_buffer[17] = ( facility_val % 10 ) + 48;
    fields[2].iov_len = 18;
  }

  memcpy( app_name_buffer + 18, entry->app_name, entry->app_name_length );
  fields[5].iov_len = entry->app_name_length + 18;

  unlock_entry( entry );

  fields[0].iov_base = message_buffer;
  fields[1].iov_base = priority_buffer;
  fields[1].iov_len = 10;
  fields[2].iov_base = facility_buffer;
  fields[3].iov_base = timestamp_buffer;
  fields[3].iov_len = timestamp_size + 17;
  fields[4].iov_base = pid_buffer;
  fields[4].iov_len = pid_size;
  fields[5].iov_base = app_name_buffer;

  return sd_journal_sendv( fields, field_count );
}
