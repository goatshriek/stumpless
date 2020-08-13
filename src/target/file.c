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
#include <stumpless/facility.h>
#include <stumpless/option.h>
#include <stumpless/target.h>
#include <stumpless/target/file.h>
#include "private/config/wrapper.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/file.h"

void
stumpless_close_file_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return;
  }

  destroy_file_target( target->id );
  destroy_target( target );
}

struct stumpless_target *
stumpless_open_file_target( const char *name,
                            int options, int default_facility ) {
  struct stumpless_target *target;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    return NULL;
  }

  target = new_target(
    STUMPLESS_FILE_TARGET,
    name,
    options,
    default_facility
  );

  if( !target ) {
    goto fail;
  }

  target->id = new_file_target( name );
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
destroy_file_target( struct file_target *target ) {
  pthread_mutex_destroy( &target->stream_mutex );
  fclose( target->stream );
  free_mem( target );
}

struct stumpless_target *
file_open_default_target( void ) {
  return stumpless_open_file_target( STUMPLESS_DEFAULT_FILE,
                                     STUMPLESS_OPTION_NONE,
                                     STUMPLESS_FACILITY_USER );
}

struct file_target *
new_file_target( const char *filename ) {
  struct file_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->stream = config_fopen( filename, "a" );
  if( !target->stream ) {
    raise_file_open_failure(  );
    goto fail_stream;
  }

  pthread_mutex_init( &target->stream_mutex, NULL );

  return target;

fail_stream:
  free_mem( target );
fail:
  return NULL;
}

int
sendto_file_target( struct file_target *target,
                    const char *msg,
                    size_t msg_length ) {
  size_t fwrite_result;
  int putc_result;

  pthread_mutex_lock( &target->stream_mutex );

  fwrite_result = fwrite( msg, sizeof( char ), msg_length, target->stream );
  if( fwrite_result != msg_length ) {
    goto write_failure;
  }

  putc_result = fputc( '\n', target->stream );
  if( putc_result != '\n' ) {
    goto write_failure;
  }

  pthread_mutex_unlock( &target->stream_mutex );

  return cap_size_t_to_int( fwrite_result + 1 );

write_failure:
  pthread_mutex_unlock( &target->stream_mutex );
  raise_file_write_failure(  );
  return -1;
}
