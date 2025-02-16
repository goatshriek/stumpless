// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
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

/* this must be included first to avoid errors */
#include "private/windows_wrapper.h"

#include <stddef.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/wel.h>
#include "private/config/have_windows.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wel_supported.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/wel.h"
#include "private/validate.h"

void
stumpless_close_wel_target( struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_WINDOWS_EVENT_LOG_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  if( !destroy_wel_target( target->id ) ) {
    return;
  }

  clear_error(  );
  destroy_target( target );
}

struct stumpless_target *
stumpless_open_local_wel_target( const char *name ) {
  return stumpless_open_remote_wel_target( NULL, name );
}


struct stumpless_target *
stumpless_open_remote_wel_target( const char *server, const char *name ) {
   struct stumpless_target *target;

   clear_error(  );

   VALIDATE_ARG_NOT_NULL( name );

   target = new_target( STUMPLESS_WINDOWS_EVENT_LOG_TARGET, name );

   if( !target ) {
     goto fail;
   }

   target->id = new_wel_target( server, name );

   if( !target->id ) {
     goto fail_id;
   }

   stumpless_set_current_target( target );
   return target;

 fail_id:
   destroy_target( target );
 fail:
   return NULL;
}

/* private definitions */

BOOL
destroy_wel_target( struct wel_target *target ) {
  BOOL success;

  success = DeregisterEventSource( target->handle );
  if( !success ) {
    raise_wel_close_failure(  );
  } else {
    free_mem( target );
  }

  return success;
}

struct wel_target *
new_wel_target( LPCSTR server_name, LPCSTR source_name ) {
  struct wel_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->handle = RegisterEventSource( server_name, source_name );
  if( !target->handle ) {
    raise_wel_open_failure(  );
    goto fail_handle;
  }

  return target;

fail_handle:
  free_mem( target );
fail:
  return NULL;
}

int
sendto_wel_target( const struct wel_target *target,
                   const struct stumpless_entry *entry,
                   const char *msg,
                   size_t msg_size ) {
  BOOL success = FALSE;
  WORD i;
  struct wel_data *data;
  LPCWSTR insertion_str;
  int prival;
  WORD category;
  WORD type;
  DWORD event_id;
  WORD insertion_string_count;
  LPCWSTR msg_insertion_strings[1];
  LPCWSTR *insertion_strings;

  data = entry->wel_data;
  lock_wel_data( data );

  for( i = 0; i < data->insertion_count; i++ ) {
    if( data->insertion_params[i] ) {
      insertion_str = copy_param_value_to_lpwstr( data->insertion_params[i] );
      if( !insertion_str ) {
        goto cleanup_and_return;
      }

      // We drop the const qualifier here so that the param's value can be set
      // as the insertion string. This doesn't modify the effective value of the
      // entry, but does require dropping the const to make internal changes.
      if( !locked_swap_wel_insertion_string( ( struct stumpless_entry * ) entry,
                                             i,
                                             insertion_str ) ) {
        goto cleanup_and_return;
      }
    }
  }

  prival = stumpless_get_entry_prival( entry );

  if( data->type_set ) {
    type = data->type;
  } else {
    type = get_type( prival );
  }

  if( data->category_set ) {
    category = data->category;
  } else {
    category = get_category( prival );
  }

  if( data->event_id_set ) {
    event_id = data->event_id;
    insertion_string_count = data->insertion_count;
    insertion_strings = data->insertion_strings;
  } else {
    event_id = get_event_id( prival );
    insertion_string_count = 1;
    lock_entry( entry );
    msg_insertion_strings[0] = windows_copy_cstring_to_lpwstr( entry->message,
                                                               NULL );
    unlock_entry( entry );
    insertion_strings = msg_insertion_strings;
  }

  success = ReportEventW( target->handle,
                          type,
                          category,
                          event_id,
                          NULL,
                          insertion_string_count,
                          cap_size_t_to_int( msg_size ),
                          insertion_strings,
                          ( LPVOID ) msg );

cleanup_and_return:
  unlock_wel_data( data );
  if( insertion_strings == msg_insertion_strings ) {
    free_mem( msg_insertion_strings[0] );
  }
  if( success ) {
    return 1;
  } else {
    return -1;
  }
}
