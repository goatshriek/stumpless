// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023 Joel E. Anderson
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
#include <stumpless/target.h>
#include <stumpless/target/sqlite3.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/sqlite3.h"
#include "private/validate.h"
#include "private/config/wrapper/fopen.h"

void
stumpless_close_sqlite3_target( struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_SQLITE3_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_sqlite3_target( target->id );
  destroy_target( target );
  clear_error(  );
}

struct stumpless_target *
stumpless_open_sqlite3_target( const char *name ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_SQLITE3_TARGET, name );

  if( !target ) {
    goto fail;
  }

  target->id = new_sqlite_target( name );
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
destroy_sqlite3_target( struct sqlite3_target *target ) {
  // TODO update
  config_destroy_mutex( &target->db_mutex );
  fclose( target->stream );
  free_mem( target );
}

struct sqlite3_target *
new_sqlite3_target( const char *filename ) {
  // TODO update
  struct sqlite3_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->stream = config_fopen( filename, "a" );
  if( !target->stream ) {
    raise_file_open_failure(  );
    goto fail_stream;
  }

  config_init_mutex( &target->stream_mutex );

  return target;

fail_stream:
  free_mem( target );
fail:
  return NULL;
}

int
sendto_sqlite3_target( struct sqlite3_target *target,
                       const char *msg,
                       size_t msg_length ) {
  // TODO update
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
