// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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
#include <stumpless/config.h>
#include <stumpless/option.h>
#include <stumpless/target.h>
#include <stumpless/target/file.h>
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/file.h"
#include "private/validate.h"
#include "private/config/wrapper/fopen.h"

void
stumpless_close_file_target( struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_FILE_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_file_target( target->id );
  destroy_target( target );
  clear_error(  );
}

struct stumpless_target *
stumpless_open_file_target( const char *name ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_FILE_TARGET, name );

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
  config_destroy_mutex( &target->stream_mutex );
  fclose( target->stream );
  free_mem( target );
}

struct stumpless_target *
file_open_default_target( void ) {
  return stumpless_open_file_target( STUMPLESS_DEFAULT_FILE );
}

struct file_target *
new_file_target( const char *filename ) {
  struct file_target *target;
  int options;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  options = stumpless_get_default_options(  );
  target->stream = NULL;
  if ( !( options & STUMPLESS_OPTION_ODELAY ) ) {
    target->stream = config_fopen( filename, "a" );
    if( !target->stream ) {
      raise_file_open_failure(  );
      goto fail_stream;
    }
  }

  config_init_mutex( &target->stream_mutex );

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

  config_lock_mutex( &target->stream_mutex );
  fwrite_result = fwrite( msg, sizeof( char ), msg_length, target->stream );
  config_unlock_mutex( &target->stream_mutex );

  if( fwrite_result != msg_length ) {
    goto write_failure;
  }

  return cap_size_t_to_int( fwrite_result + 1 );

write_failure:
  raise_file_write_failure(  );
  return -1;
}
