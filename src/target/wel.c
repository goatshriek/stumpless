// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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

#include <stddef.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/wel.h>
#include <string.h>
#include <windows.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/wel.h"

void
stumpless_close_wel_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return;
  }

  destroy_wel_target( target->id );
  destroy_target( target );
}

struct stumpless_target *
stumpless_open_local_wel_target( const char *name,
                                 int options ) {
  struct stumpless_target *target;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  target = new_target( STUMPLESS_WINDOWS_EVENT_LOG_TARGET,
                       name,
                       strlen( name ),
                       options,
                       0 );

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
stumpless_open_remote_wel_target( const char *server,
                                  const char *name,
                                  int options ) {
   struct stumpless_target *target;

   clear_error(  );

   if( !name ) {
     raise_argument_empty( "name is NULL" );
     goto fail;
   }

   target = new_target( STUMPLESS_WINDOWS_EVENT_LOG_TARGET,
                        name,
                        strlen( name ),
                        options,
                        0 );

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

void
destroy_wel_target( struct wel_target *target ) {
  BOOL success;

  success = DeregisterEventSource( target->handle );
  if( !success ) {
    raise_wel_close_failure(  );
  }

  free_mem( target );
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

  for( i = 0; i < entry->wel_insertion_count; i++ ) {
    if( entry->wel_insertion_params[i] ) {
      entry->wel_insertion_strings[i] = entry->wel_insertion_params[i]->value;
    } else {
      entry->wel_insertion_strings[i] = NULL;
    }
  }

  success = ReportEvent( target->handle,
                         entry->wel_type,
                         entry->wel_category,
                         entry->wel_event_id,
                         NULL,
                         entry->wel_insertion_count,
                         0,
                         entry->wel_insertion_strings,
                         NULL );

  if( success ) {
    return 1;
  } else {
    return -1;
  }
}
