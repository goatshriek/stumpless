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
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/journald.h>
#include <sys/uio.h>
#include <systemd/sd-journal.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/memory.h"
#include "private/severity.h"
#include "private/target.h"
#include "private/target/journald.h"
#include "private/validate.h"

/* per-thread static variables */
static CONFIG_THREAD_LOCAL_STORAGE char *message_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE size_t message_buffer_length = 0;
static CONFIG_THREAD_LOCAL_STORAGE char *priority_buffer = NULL;
static CONFIG_THREAD_LOCAL_STORAGE char *facility_buffer = NULL;

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

void
journald_free_thread( void ) {
  free_mem( message_buffer );
  message_buffer = NULL;
  message_buffer_length = 0;
  free_mem( priority_buffer );
  priority_buffer = NULL;
  free_mem( facility_buffer );
  facility_buffer = NULL;
}

int
send_entry_to_journald_target( const struct stumpless_target *target,
                               const struct stumpless_entry *entry ) {
  char *new_message_buffer;
  struct iovec fields[3];
  int facility_val;

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

  lock_entry( entry );

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

  unlock_entry( entry );

  fields[0].iov_base = message_buffer;
  fields[1].iov_base = priority_buffer;
  fields[1].iov_len = 10;
  fields[2].iov_base = facility_buffer;

  return sd_journal_sendv( fields, 3 );
}
