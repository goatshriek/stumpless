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

#include <stddef.h>
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/buffer.h"
#include "private/validate.h"

void
stumpless_close_buffer_target( const struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_BUFFER_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  clear_error(  );

  destroy_buffer_target( target->id );
  destroy_target( target );
}

struct stumpless_target *
stumpless_open_buffer_target( const char *name,
                              char *buffer,
                              size_t size ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( buffer );

  target = new_target( STUMPLESS_BUFFER_TARGET, name );

  if( !target ) {
    goto fail;
  }

  target->id = new_buffer_target( buffer, size );
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

size_t
stumpless_read_buffer( struct stumpless_target *target,
                       char *buffer,
                       size_t max_length ) {
  struct buffer_target *buffer_target;
  size_t read_position;
  size_t out_position = 0;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return 0;
  }

  if( !buffer || max_length == 0 ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "buffer" ) );
    return 0;
  }

  buffer_target = ( struct buffer_target * ) target->id;

  config_lock_mutex( &buffer_target->buffer_mutex );

  read_position = buffer_target->read_position;
  while( read_position != buffer_target->write_position &&
         out_position < max_length - 1 ) {
    buffer[out_position] = buffer_target->buffer[read_position];
    read_position = ( read_position + 1 ) % buffer_target->size;

    if( buffer[out_position] == '\0' ) {
      goto cleanup_and_return;
    }

    out_position++;
  }

  buffer[out_position] = '\0';

cleanup_and_return:
  buffer_target->read_position = read_position;
  config_unlock_mutex( &buffer_target->buffer_mutex );
  return out_position + 1;
}

/* private definitions */

void
destroy_buffer_target( const struct buffer_target *target ) {
  config_destroy_mutex( &target->buffer_mutex );
  free_mem( target );
}

struct buffer_target *
new_buffer_target( char *buffer, size_t size ) {
  struct buffer_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    return NULL;
  }

  config_init_mutex( &target->buffer_mutex );
  target->buffer = buffer;
  target->size = size;
  target->read_position = 0;
  target->write_position = 0;

  return target;
}

int
sendto_buffer_target( struct buffer_target *target,
                      const char *msg,
                      size_t msg_length ) {
  size_t write_start;
  size_t buffer_remaining;
  size_t free_space_left;

  // leave off the newline
  msg_length--;

  if( msg_length >= target->size ) {
    raise_argument_too_big( L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE,
                            msg_length,
                            L10N_MESSAGE_SIZE_ERROR_CODE_TYPE );
    return -1;
  }

  config_lock_mutex( &target->buffer_mutex );
  write_start = target->write_position;
  buffer_remaining = target->size - write_start;

  if( buffer_remaining > msg_length ) {
    // the entire message will fit into the buffer without wrapping around
    memcpy( target->buffer + write_start, msg, msg_length );
    target->write_position += msg_length + 1;

  } else {
    // we need to split the message and wrap it around to the beginning
    memcpy( target->buffer + write_start, msg, buffer_remaining );
    memcpy( target->buffer,
            msg + buffer_remaining,
            msg_length - buffer_remaining );
    target->write_position = msg_length - buffer_remaining + 1;
  }

  target->buffer[target->write_position - 1] = '\0';

  // checking to see if we have overwritten older messages and need to adjust
  // the read position to reflect this
  if( target->read_position > write_start ) {
    free_space_left = target->read_position - write_start;
  } else {
    free_space_left = ( target->size - write_start ) + target->read_position;
  }

  if( free_space_left <= msg_length ) {
    target->read_position = ( target->write_position + 1 ) % target->size;

    if( target->buffer[target->read_position] == '\0' ) {
      target->read_position = ( target->read_position + 1 ) % target->size;
    }
  }

  config_unlock_mutex( &target->buffer_mutex );

  return cap_size_t_to_int( msg_length + 1 );
}
