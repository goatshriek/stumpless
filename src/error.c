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
#include <stdlib.h>
#include <stumpless/error.h>
#include "private/error.h"

static struct stumpless_error *last_error = NULL;
static short error_valid = 0;

struct stumpless_error *
stumpless_get_error( void ) {
  if( error_valid )
    return last_error;
  else
    return NULL;
}

/* private functions */

void
clear_error( void ) {
  error_valid = 0;
}

void
raise_argument_empty( const char *message ) {
  raise_error( STUMPLESS_ARGUMENT_EMPTY, message, 0, NULL );
}

void
raise_argument_too_big( const char *message, int code, const char *code_type ) {
  raise_error( STUMPLESS_ARGUMENT_TOO_BIG, message, code, code_type );
}

void
raise_error( enum stumpless_error_id id,
             const char *message,
             int code,
             const char *code_type ) {
  if( !last_error ) {
    last_error = malloc( sizeof( struct stumpless_error ) );
    if( !last_error ) {
      error_valid = 0;
      return;
    }
  }

  last_error->id = id;
  last_error->message = message;
  last_error->code = code;
  last_error->code_type = code_type;
  error_valid = 1;
}

void
raise_file_open_failure( void ) {
  raise_error( STUMPLESS_FILE_OPEN_FAILURE, NULL, 0, NULL );
}

void
raise_file_write_failure( void ) {
  raise_error( STUMPLESS_FILE_WRITE_FAILURE, NULL, 0, NULL );
}

void
raise_invalid_id( void ) {
  raise_error( STUMPLESS_INVALID_ID, NULL, 0, NULL );
}

void
raise_memory_allocation_failure( void ) {
  raise_error( STUMPLESS_MEMORY_ALLOCATION_FAILURE, NULL, 0, NULL );
}

void
raise_network_protocol_unsupported( void ) {
  raise_error( STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED );
}

void
raise_socket_bind_failure( void ) {
  raise_error( STUMPLESS_SOCKET_BIND_FAILURE, NULL, 0, NULL );
}

void
raise_stream_write_failure( void ) {
  raise_error( STUMPLESS_STREAM_WRITE_FAILURE, NULL, 0, NULL );
}

void
raise_target_unsupported( void ) {
  raise_error( STUMPLESS_TARGET_UNSUPPORTED, NULL, 0, NULL );
}

void
raise_transport_protocol_unsupported( void ) {
  raise_error( STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED );
}

void
raise_wel_close_failure( void ) {
  raise_error( STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE, NULL, 0, NULL );
}

void
raise_wel_open_failure( void ) {
  raise_error( STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE, NULL, 0, NULL );
}
