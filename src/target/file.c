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
#include <stdio.h>
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/target/file.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target/file.h"

void
stumpless_close_file_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty(  );
    return;
  }

  destroy_file_target( target->id );
  free_mem( target->name );
  free_mem( target );
}

struct stumpless_target *
stumpless_open_file_target( const char *name,
                            int options, int default_facility ) {
  struct stumpless_target *target;
  size_t name_len;

  clear_error(  );

  if( !name ) {
    raise_argument_empty(  );
    return NULL;
  }

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->id = new_file_target( name );
  if( !target->id ) {
    goto fail_id;
  }

  name_len = strlen( name );
  target->name = alloc_mem( name_len + 1 );
  if( !target->name ) {
    goto fail_name;
  }

  memcpy( target->name, name, name_len );
  target->name[name_len] = '\0';
  target->type = STUMPLESS_FILE_TARGET;
  target->options = options;
  target->default_prival =
    get_prival( default_facility, STUMPLESS_SEVERITY_INFO );
  target->default_app_name = NULL;
  target->default_app_name_length = 0;
  target->default_msgid = NULL;
  target->default_msgid_length = 0;

  stumpless_set_current_target( target );
  return target;

fail_name:
  destroy_file_target( target->id );
fail_id:
  free_mem( target );
fail:
  return NULL;
}

/* private definitions */

void
destroy_file_target( struct file_target *target ) {
  fclose( target->stream );
  free_mem( target );
}

struct file_target *
new_file_target( const char *filename ) {
  struct file_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->stream = fopen( filename, "a" );
  if( !target->stream ) {
    raise_file_open_failure(  );
    goto fail_stream;
  }

  return target;

fail_stream:
  free_mem( target );
fail:
  return NULL;
}

int
sendto_file_target( struct file_target *target,
                    const char *msg, size_t msg_length ) {
  return fwrite( msg, sizeof( char ), msg_length, target->stream );
}
