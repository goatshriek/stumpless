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

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stumpless/error.h>
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"

static FILE *error_stream = NULL;
static int error_stream_valid = 0;
static struct stumpless_error *last_error = NULL;
static bool error_valid = false;

struct stumpless_error *
stumpless_get_error( void ) {
  if( error_valid )
    return last_error;
  else
    return NULL;
}

enum stumpless_error_id
stumpless_get_error_id( const struct stumpless_error *err ) {
  return err->id;
}

FILE *
stumpless_get_error_stream( void ) {
  if( !error_stream_valid ) {
    error_stream = stderr;
    error_stream_valid = 1;
  }

  return error_stream;
}

bool
stumpless_has_error( void ) {
  return error_valid;
}

void
stumpless_perror( const char *prefix ) {

  if( !error_stream_valid ) {
    error_stream = stderr;
    error_stream_valid = 1;
  }

  if( error_stream && error_valid ) {

    if( prefix ) {
      fputs( prefix, error_stream );
      fputc( ':', error_stream );
      fputc( ' ', error_stream );
    }

    fputs( last_error->message, error_stream );

    if( last_error->code_type ) {
      fprintf( error_stream, " (%s: %d)", last_error->code_type, last_error->code );
    }

    fputc( '\n', error_stream );
  }
}

void
stumpless_set_error_stream( FILE *stream ) {
  error_stream = stream;
  error_stream_valid = 1;
}

/* private functions */

void
clear_error( void ) {
  error_valid = false;
}

void
error_free_all( void ) {
  free_mem( last_error );
  last_error = NULL;
}

void
raise_address_failure( const char *message, int code, const char *code_type ) {
  raise_error( STUMPLESS_ADDRESS_FAILURE, message, code, code_type );
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
raise_duplicate_element( void ) {
  raise_error( STUMPLESS_DUPLICATE_ELEMENT,
               "an element with the provided name is already present in this" \
               " entry",
               0,
               NULL );
}

void
raise_element_not_found( void ) {
  raise_error( STUMPLESS_ELEMENT_NOT_FOUND,
               "an element with the specified characteristics could not be" \
               " found",
               0,
               NULL );
}

void
raise_error( enum stumpless_error_id id,
             const char *message,
             int code,
             const char *code_type ) {
  if( !last_error ) {
    last_error = alloc_mem( sizeof( struct stumpless_error ) );
    if( !last_error ) {
      error_valid = false;
      return;
    }
  }

  last_error->id = id;
  last_error->message = message;
  last_error->code = code;
  last_error->code_type = code_type;
  error_valid = true;
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
raise_index_out_of_bounds( const char *message, size_t index ) {
  raise_error( STUMPLESS_INDEX_OUT_OF_BOUNDS,
               message,
               size_t_to_int( index ),
               "the invalid index, or -1 if it is too large to represent as"
               " an int" );
}

void
raise_invalid_facility( int facility ) {
  raise_error( STUMPLESS_INVALID_FACILITY,
               "facility codes must be defined in accordance with RFC 5424, "
               "after the multiplication by 8",
               facility,
               "the invalid facility" );
}

void
raise_invalid_id( void ) {
  raise_error( STUMPLESS_INVALID_ID, NULL, 0, NULL );
}

void
raise_invalid_severity( int severity ) {
  raise_error( STUMPLESS_INVALID_SEVERITY,
               "severity codes must be defined in accordance with RFC 5424: "
               "values between 0 and 7 inclusive",
               severity,
               "the invalid severity" );
}

void
raise_memory_allocation_failure( void ) {
  if( !last_error ) {
    return;
  }

  raise_error( STUMPLESS_MEMORY_ALLOCATION_FAILURE, NULL, 0, NULL );
}

void
raise_network_protocol_unsupported( void ) {
  raise_error( STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED, NULL, 0, NULL );
}

void
raise_param_not_found( void ) {
  raise_error( STUMPLESS_PARAM_NOT_FOUND,
               "a param with the specified characteristics could not be found",
               0,
               NULL );
}

void
raise_socket_bind_failure( const char *message, int code, const char *code_type ) {
  raise_error( STUMPLESS_SOCKET_BIND_FAILURE, message, code, code_type );
}

void
raise_socket_connect_failure( const char *message,
                              int code,
                              const char *code_type ) {
  raise_error( STUMPLESS_SOCKET_CONNECT_FAILURE, message, code, code_type );
}

void
raise_socket_failure( const char *message, int code, const char *code_type ) {
  raise_error( STUMPLESS_SOCKET_FAILURE, message, code, code_type );
}

void
raise_socket_send_failure( const char *message,
                           int code,
                           const char *code_type ) {
  raise_error( STUMPLESS_SOCKET_SEND_FAILURE, message, code, code_type );
}

void
raise_stream_write_failure( void ) {
  raise_error( STUMPLESS_STREAM_WRITE_FAILURE, NULL, 0, NULL );
}

void
raise_target_incompatible( const char *message ) {
  raise_error( STUMPLESS_TARGET_INCOMPATIBLE, message, 0, NULL );
}

void
raise_target_unsupported( const char *message ) {
  raise_error( STUMPLESS_TARGET_UNSUPPORTED, message, 0, NULL );
}

void
raise_transport_protocol_unsupported( void ) {
  raise_error( STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED, NULL, 0, NULL );
}

void
raise_wel_close_failure( void ) {
  raise_error( STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE, NULL, 0, NULL );
}

void
raise_wel_open_failure( void ) {
  raise_error( STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE, NULL, 0, NULL );
}
