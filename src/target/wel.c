// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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
#include "private/config/locale/wrapper.h"
#include "private/config/wel_supported.h"
#include "private/error.h"
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
  struct stumpless_target *target;

  clear_error(  );

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_WINDOWS_EVENT_LOG_TARGET, name );

  if( !target ) {
    goto fail;
  }

  target->id = new_wel_target( NULL, name );

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
send_entry_to_wel_target( const struct wel_target *target,
                          const struct stumpless_entry *entry ) {
  BOOL success;
  WORD i;
  struct wel_data *data;

  data = entry->wel_data;
  lock_wel_data( data );

  for( i = 0; i < data->insertion_count; i++ ) {
    if( data->insertion_params[i] ) {
      data->insertion_strings[i] = data->insertion_params[i]->value;
    } else {
      data->insertion_strings[i] = NULL;
    }
  }

  success = ReportEventW( target->handle,
                          data->type,
                          data->category,
                          data->event_id,
                          NULL,
                          data->insertion_count,
                          0,
                          data->insertion_strings,
                          NULL );

  unlock_wel_data( data );

  if( success ) {
    return 1;
  } else {
    return -1;
  }
}
