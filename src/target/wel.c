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
#include <stumpless/target.h>
#include <stumpless/target/wel.h>
#include <string.h>
#include <windows.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target/wel.h"

void
stumpless_close_wel_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty(  );
    return;
  }

  destroy_wel_target( target->id );
  free_mem( target->name );
  free_mem( target );
}

struct stumpless_target *
stumpless_open_local_wel_target( const char *name,
                                 int options,
                                 int default_facility ) {
  struct stumpless_target *target;
  size_t name_len;

  clear_error(  );

  if( !name ) {
    raise_argument_empty(  );
    goto fail;
  }

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  name_len = strlen( name );

  target->id = new_wel_target( NULL, name );

  if( !target->id ) {
    goto fail_id;
  }

  target->name = alloc_mem( name_len + 1 );
  if( !target->name ) {
    goto fail_name;
  }

  memcpy( target->name, name, name_len );
  target->name[name_len] = '\0';
  target->type = STUMPLESS_WINDOWS_EVENT_LOG_TARGET;
  target->options = options;
  target->default_prival =
    get_prival( default_facility, STUMPLESS_SEVERITY_INFO );

  stumpless_set_current_target( target );
  return target;

fail_name:
  destroy_wel_target( target->id );
fail_id:
  free_mem( target );
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
new_wel_target( LPCSTR server_name, LPCSTR source_name ){
  struct wel_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->handle = RegisterEventSourceA( server_name, source_name );
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

  success = ReportEventA(
    target->handle,
    entry->wel_type,
    0, //  WORD   wCategory - defined by user
    0, //  DWORD  dwEventID - defined by user
    NULL,
    entry->wel_insertion_count,
    0,
    entry->wel_insertion_strings,
    NULL
  );

  return -1;
}
