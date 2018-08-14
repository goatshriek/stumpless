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
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target/buffer.h"

// todo need to deal with memory leak - how to clean up public targets
// and their members?
void
stumpless_close_buffer_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty(  );
    return;
  }

  destroy_buffer_target( target->id );
  free_mem( target->name );
  free_mem( target );
}

struct stumpless_target *
stumpless_open_buffer_target( const char *name, char *buffer, size_t size,
                              int options, int default_facility ) {
  struct stumpless_target *target;
  size_t name_len;

  clear_error(  );

  if( !name || !buffer ) {
    raise_argument_empty(  );
    return NULL;
  }

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->id = new_buffer_target( buffer, size );
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
  target->type = STUMPLESS_BUFFER_TARGET;
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
  destroy_buffer_target( target->id );
fail_id:
  free_mem( target );
fail:
  return NULL;
}


/* private definitions */

void
destroy_buffer_target( struct buffer_target *target ) {
  if( target ) {
    free_mem( target );
  }

}

struct buffer_target *
new_buffer_target( char *buffer, size_t size ) {
  struct buffer_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    return NULL;
  }

  target->buffer = buffer;
  target->size = size;
  target->position = 0;

  return target;
}

int
sendto_buffer_target( struct buffer_target *target,
                      const char *msg, size_t msg_length ) {
  size_t buffer_remaining;

  if( msg_length >= target->size ) {
    raise_argument_too_big(  );
    return -1;
  }

  buffer_remaining = target->size - target->position;

  if( buffer_remaining > msg_length ) {
    memcpy( target->buffer + target->position, msg, msg_length );
    target->position += msg_length + 1;
  } else {
    memcpy( target->buffer + target->position, msg, buffer_remaining );
    memcpy( target->buffer, msg + buffer_remaining,
            msg_length - buffer_remaining );
    target->position = msg_length - buffer_remaining + 1;
  }

  target->buffer[target->position - 1] = '\0';

  return msg_length + 1;
}
