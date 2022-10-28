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

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/target/stream.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/stream.h"
#include "private/validate.h"

void
stumpless_close_stream_target( const struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_STREAM_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  clear_error(  );
  destroy_stream_target( target->id );
  destroy_target( target );
}

struct stumpless_target *
stumpless_open_stderr_target( const char *name ) {
  struct stumpless_target *stumpless_target= stumpless_open_stream_target( name, stderr );
  struct stream_target *stream_target = stumpless_target->id;
  // ? dynamically get number of possible severiy
  stream_target->severity_colors = (char **)alloc_mem( sizeof(char *)*8 );
  // TODO use predefined array and loop over to init color confs
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_EMERG, "\033[37m\033[41m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_ALERT, "\033[36m\033[41m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_CRIT, "\033[37m\033[41m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_ERR, "\033[31m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_WARNING, "\033[33m");
  // stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_NOTICE, "\033[3m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_INFO, "\033[32m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_DEBUG, "\033[36m");
  return stumpless_target;
}

struct stumpless_target *
stumpless_open_stdout_target( const char *name ) {
  struct stumpless_target *stumpless_target= stumpless_open_stream_target( name, stdout );
  struct stream_target *stream_target = stumpless_target->id;
  // ? dynamically get number of possible severiy
  stream_target->severity_colors = (char **)alloc_mem( sizeof(char *)*8 );
  // TODO use predefined array and loop over to init color confs
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_EMERG, "\033[37m\033[41m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_ALERT, "\033[36m\033[41m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_CRIT, "\033[37m\033[41m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_ERR, "\033[31m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_WARNING, "\033[33m");
  // stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_NOTICE, "\033[3m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_INFO, "\033[32m");
  stumpless_set_severity_color( stream_target, STUMPLESS_SEVERITY_DEBUG, "\033[36m");
  return stumpless_target;
}

struct stumpless_target *
stumpless_open_stream_target( const char *name, FILE *stream ) {
  struct stumpless_target *target;

  clear_error(  );

  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( stream );

  target = new_target( STUMPLESS_STREAM_TARGET, name );

  if( !target ) {
    goto fail;
  }

  struct stream_target *stream_target = new_stream_target( stream );
  target->id = stream_target;
  if( !target->id ) {
    goto fail_id;
  }

  stream_target->severity_colors = NULL;

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
  config_destroy_mutex( &target->stream_mutex );
  // ? severity_colors deletion method
  // for(int i=0;i<8;i++)
  //   if( target->severity_colors[i] )
  //     free_mem( target->severity_colors[i] );
  // free_mem( target->severity_colors );
  free_mem( target );
}

struct stream_target *
new_stream_target( FILE *stream ) {
  struct stream_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    return NULL;
  }

  config_init_mutex( &target->stream_mutex );
  target->stream = stream;

  return target;
}

int
sendto_stream_target( struct stream_target *target,
                      const struct stumpless_entry * entry,
                      const char *msg,
                      size_t msg_length ) {
  size_t fwrite_result;
  enum stumpless_severity severity;

  if( target->severity_colors ){
    config_lock_mutex( &target->stream_mutex );
    severity = stumpless_get_entry_severity(entry);
    if( target->severity_colors[ severity ] )
      fwrite_result = fwrite( target->severity_colors[ severity ], sizeof( char ), strlen(target->severity_colors[ severity ]), target->stream );
    fwrite_result = fwrite( msg, sizeof( char ), msg_length, target->stream );
    if( target->severity_colors[ severity ] )
      fwrite_result = fwrite( "\033[0m", sizeof( char ), 4, target->stream );
    config_unlock_mutex( &target->stream_mutex );
  }
  else{
    config_lock_mutex( &target->stream_mutex );
    fwrite_result = fwrite( msg, sizeof( char ), msg_length, target->stream );
    config_unlock_mutex( &target->stream_mutex );
  }

  if( fwrite_result != msg_length ) {
    goto write_failure;
  }

  return cap_size_t_to_int( fwrite_result + 1 );

write_failure:
  raise_stream_write_failure(  );
  return -1;
}

void 
stumpless_set_severity_color( struct stream_target *target,
                              const enum stumpless_severity severity,
                              const char *escape_code ) {
                              
  if( target == NULL)
    return;
  if( escape_code == NULL)
    return;

  config_lock_mutex( &target->stream_mutex );
  if( target->severity_colors[severity] )
    free_mem( target->severity_colors[severity] );
  target->severity_colors[ severity ] = (char *)alloc_mem(sizeof(char*));
  strcpy( target->severity_colors[severity], escape_code );
  config_unlock_mutex( &target->stream_mutex );
}