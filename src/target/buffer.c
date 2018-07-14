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
#include "private/id.h"
#include "private/memory.h"
#include "private/target.h"
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

  destroy_buffer_target( get_priv_target( target->id ) );
  unregister_priv_target( target->id );
}

struct stumpless_target *
stumpless_open_buffer_target( const char *name, char *buffer, size_t size,
                              int options, int default_facility ) {
  struct stumpless_target *pub_target;
  struct buffer_target *priv_target;
  size_t name_len;

  clear_error(  );

  if( !name || !buffer ) {
    raise_argument_empty(  );
    return NULL;
  }

  pub_target = alloc_mem( sizeof( *pub_target ) );
  if( !pub_target ) {
    goto fail;
  }

  priv_target = new_buffer_target( buffer, size );
  if( !priv_target ) {
    goto fail_priv_target;
  }

  name_len = strlen( name );
  pub_target->name = alloc_mem( name_len + 1 );
  if( !pub_target->name ) {
    goto fail_pub_name;
  }

  memcpy( pub_target->name, name, name_len );
  pub_target->name[name_len] = '\0';
  pub_target->type = STUMPLESS_BUFFER_TARGET;
  pub_target->options = options;
  pub_target->default_prival =
    get_prival( default_facility, STUMPLESS_SEVERITY_INFO );
  pub_target->id = register_priv_target( priv_target );
  pub_target->default_app_name = NULL;
  pub_target->default_app_name_length = 0;
  pub_target->default_msgid = NULL;
  pub_target->default_msgid_length = 0;

  stumpless_set_current_target( pub_target );
  return pub_target;

fail_pub_name:
  free_mem( priv_target );
fail_priv_target:
  free_mem( pub_target );
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
sendto_buffer_target( struct buffer_target *target, const char *msg ) {
  size_t msg_len;
  size_t buffer_remaining;

  msg_len = strlen( msg );

  if( msg_len >= target->size ) {
    raise_argument_too_big(  );
    return -1;
  }

  buffer_remaining = target->size - target->position;

  if( buffer_remaining > msg_len ) {
    memcpy( target->buffer + target->position, msg, msg_len );
    target->position = msg_len + 1;
  } else {
    memcpy( target->buffer + target->position, msg, buffer_remaining );
    memcpy( target->buffer, msg + buffer_remaining,
            msg_len - buffer_remaining );
    target->position = msg_len - buffer_remaining + 1;
  }

  target->buffer[target->position - 1] = '\0';

  return msg_len + 1;
}
