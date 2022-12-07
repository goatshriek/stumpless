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
#include <stdlib.h>
#include <stumpless/target.h>
#include <stumpless/target/stream.h>
#include <stumpless/severity.h>
#include <stumpless/entry.h>
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

char *SEVERITY_COLORS_DEFAULT[] = {
  "\033[37m\033[41m", // EMERG
  "\033[36m\033[41m", // ALERT
  "\033[37m\033[41m", // CRIT
  "\033[31m", // ERR
  "\033[33m", // WARNING
  "", // NOTICE
  "\033[32m", // INFO
  "\033[36m", // DEBUG
};

struct stumpless_target *
stumpless_open_stderr_target( const char *name ) {
  struct stumpless_target *stumpless_target= stumpless_open_stream_target( name, stderr );
  
  if( !stumpless_target ) {
    goto fail;
  }

  struct stream_target *stream_target = stumpless_target->id;
  
  if( !stream_target) {
    goto fail_id;
  }

  for(int i=0; i<8; i++)
    stumpless_set_severity_color( stumpless_target, (enum stumpless_severity)i, SEVERITY_COLORS_DEFAULT[i]);
  return stumpless_target;

fail_id:
  destroy_target( stumpless_target );
fail:
  return NULL;  
}

struct stumpless_target *
stumpless_open_stdout_target( const char *name ) {
  struct stumpless_target *stumpless_target= stumpless_open_stream_target( name, stdout );

  if( !stumpless_target ) {
    goto fail;
  }

  struct stream_target *stream_target = stumpless_target->id;

  if( !stream_target) {
    goto fail_id;
  }
  
  for(int i=0; i<8; i++)
    stumpless_set_severity_color( stumpless_target, (enum stumpless_severity)i, SEVERITY_COLORS_DEFAULT[i]);
  
  return stumpless_target;

fail_id:
  destroy_target( stumpless_target );
fail:
  return NULL;  
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
  
  target->type = STUMPLESS_STREAM_TARGET;

  struct stream_target *stream_target = new_stream_target( stream );
  target->id = stream_target;
  if( !target->id ) {
    goto fail_id;
  }

  for(int i=0; i<8; i++)
    stream_target->severity_colors[i] = NULL;

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
  for(int i=0;i<8;i++)
    if( target->severity_colors[i] )
      free_mem( target->severity_colors[i] );
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

  for(int i=0; i<8; i++)
    target->severity_colors[i] = NULL;

  return target;
}

int
sendto_stream_target( struct stream_target *target,
                      const struct stumpless_entry * entry,
                      const char *msg,
                      size_t msg_length ) {
  size_t fwrite_result=0, escapecode_fwrite_result=0;
  enum stumpless_severity severity;

  config_lock_mutex( &target->stream_mutex );

  severity = stumpless_get_entry_severity(entry);

  /* writing escape_code to stream */
  if( target->severity_colors[ severity ] ){
    escapecode_fwrite_result = fwrite( target->severity_colors[ severity ], sizeof( char ), strlen(target->severity_colors[ severity ]), target->stream );
    if( escapecode_fwrite_result != strlen(target->severity_colors[ severity ]))
      goto write_failure;    
  }

  fwrite_result = fwrite( msg, sizeof( char ), msg_length, target->stream );

  /* writing reset_escape_code to stream */
  if( target->severity_colors[ severity ] ){
    escapecode_fwrite_result = fwrite( "\033[0m", sizeof( char ), 4, target->stream );
    if( escapecode_fwrite_result != strlen("\033[0m"))
      goto write_failure;    
  }

  config_unlock_mutex( &target->stream_mutex );

  if( fwrite_result != msg_length ) {
    goto write_failure;
  }

  return cap_size_t_to_int( fwrite_result + 1 );

write_failure:
  raise_stream_write_failure(  );
  return -1;
}

void 
stumpless_set_severity_color( const struct stumpless_target *stumpless_target,
                              const enum stumpless_severity severity,
                              const char *escape_code ) {
                              
  struct stream_target* target = NULL;
  
  if( stumpless_target == NULL){
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "stumpless_target" ) );
    return;
  }
  if( severity < 0 || severity > 7 ){
    raise_invalid_severity(severity);
    return;
  }
  if( escape_code == NULL){
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "escape_code" ) );
    return;
  }

  target = (struct stream_target*)stumpless_target->id;

  config_lock_mutex( &target->stream_mutex );
  if( target->severity_colors[severity] )
    free_mem( target->severity_colors[severity] );
  target->severity_colors[ severity ] = (char *)alloc_mem(sizeof(char*));
  strcpy( target->severity_colors[severity], escape_code );
  config_unlock_mutex( &target->stream_mutex );
}