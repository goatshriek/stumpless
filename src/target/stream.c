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

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stumpless/target.h>
#include <stumpless/target/stream.h>
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/stream.h"

void
stumpless_close_stream_target( const struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return;
  }

  clear_error(  );
  destroy_stream_target( target->id );
  destroy_target( target );
}

struct stumpless_target *
stumpless_open_stderr_target( const char *name,
                              int options,
                              int default_facility ) {
  return stumpless_open_stream_target( name,
                                       stderr,
                                       options,
                                       default_facility );
}

struct stumpless_target *
stumpless_open_stdout_target( const char *name,
                              int options,
                              int default_facility ) {
  return stumpless_open_stream_target( name,
                                       stdout,
                                       options,
                                       default_facility );

}

struct stumpless_target *
stumpless_open_stream_target( const char *name,
                              FILE *stream,
                              int options,
                              int default_facility ) {
  struct stumpless_target *target;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    return NULL;
  }

  if( !stream ) {
    raise_argument_empty( "stream is NULL" );
    return NULL;
  }

  target = new_target(
    STUMPLESS_STREAM_TARGET,
    name,
    options,
    default_facility
  );

  if( !target ) {
    goto fail;
  }

  target->id = new_stream_target( stream );
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
destroy_stream_target( const struct stream_target *target ) {
  pthread_mutex_destroy( ( pthread_mutex_t * ) &target->stream_mutex );
  free_mem( target );
}

struct stream_target *
new_stream_target( FILE *stream ) {
  struct stream_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    return NULL;
  }

  pthread_mutex_init( &target->stream_mutex, NULL );
  target->stream = stream;

  return target;
}

int
sendto_stream_target( struct stream_target *target,
                      const char *msg,
                      size_t msg_length ) {
  size_t fwrite_result;

  pthread_mutex_lock( &target->stream_mutex );

  fwrite_result = fwrite( msg, sizeof( char ), msg_length, target->stream );
  if( fwrite_result != msg_length ) {
    goto write_failure;
  }

  pthread_mutex_unlock( &target->stream_mutex );

  return cap_size_t_to_int( fwrite_result + 1 );

write_failure:
  pthread_mutex_unlock( &target->stream_mutex );
  raise_stream_write_failure(  );
  return -1;
}
