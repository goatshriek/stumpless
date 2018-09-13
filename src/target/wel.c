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

struct stumpless_entry *
stumpless_add_wel_insertion_string( struct stumpless_entry *entry,
                                    LPCSTR str ) {
  LPSTR *new_strings;
  LPSTR str_copy;
  size_t str_length;
  size_t old_size;
  size_t new_size;

  clear_error(  );

  if( !entry || !str ) {
    raise_argument_empty(  );
    goto fail;
  }

  str_length = strlen( str );
  str_copy = alloc_mem( str_length );
  if( !str_copy ) {
    goto fail;
  }

  old_size = sizeof( LPCSTR ) * entry->wel_insertion_count;
  new_size = old_size + sizeof( LPCSTR );

  new_strings = realloc_mem( entry->wel_insertion_strings, new_size );
  if( !new_strings ) {
    goto fail_realloc;
  }

  memcpy( str_copy, str, str_length );
  str_copy[str_length] = '\0';
  new_strings[entry->wel_insertion_count] = str_copy;

  entry->wel_insertion_strings = new_strings;
  entry->wel_insertion_count++;
  return entry;


fail_realloc:
  free_mem( str_copy );
fail:
  return NULL;
}

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
sendto_wel_target( const struct wel_target *target,
                   const struct stumpless_entry *entry ) {
  BOOL success;

  success = ReportEventA(
    target->handle,
    0, //  WORD   wType - need to translate (or accept from custom function)
    0, //  WORD   wCategory - defined by user
    0, //  DWORD  dwEventID - defined by user
    NULL,
    0, //  WORD   wNumStrings, - same as the entry element count
    0,
    NULL,//  LPCSTR *lpStrings - use the element names - will need to build list separately
    NULL
  );

  return -1;
}
