// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2023 Joel E. Anderson
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
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/strhelper.h"

/* global static variables */
static config_atomic_ptr_t error_stream = config_atomic_ptr_initializer;
static config_atomic_bool_t error_stream_free = config_atomic_bool_true;
static config_atomic_bool_t error_stream_valid = config_atomic_bool_false;

static const char *error_enum_to_string[] = {
  STUMPLESS_FOREACH_ERROR( GENERATE_STRING )
};

/* per-thread static variables */
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_error last_error;
static CONFIG_THREAD_LOCAL_STORAGE bool error_valid = false;

const struct stumpless_error *
stumpless_get_error( void ) {
  if( error_valid )
    return &last_error;
  else
    return NULL;
}

enum stumpless_error_id
stumpless_get_error_id( const struct stumpless_error *err ) {
  return err->id;
}

const char *
stumpless_get_error_id_string( enum stumpless_error_id id) {
  int error_id_upper_bound = sizeof( error_enum_to_string ) / sizeof( char * );
  if ( id >= 0 && id < error_id_upper_bound ) {
    return error_enum_to_string[id];
  }

  return "NO_SUCH_ERROR_ID";
}

FILE *
stumpless_get_error_stream( void ) {
  if( config_read_bool( &error_stream_valid ) ) {
    return config_read_ptr( &error_stream );
  } else {
    return stderr;
  }
}

bool
stumpless_has_error( void ) {
  return error_valid;
}

void
stumpless_perror( const char *prefix ) {
  FILE *stream;
  bool locked;

  stream = stumpless_get_error_stream(  );

  if( stream && error_valid ) {

    do {
      locked = config_compare_exchange_bool( &error_stream_free, true, false );
    } while( !locked );

    if( prefix ) {
      fputs( prefix, stream );
      fputc( ':', stream );
      fputc( ' ', stream );
    }

    fputs( stumpless_get_error_id_string(last_error.id), stream );
    fputc( ':', stream );
    fputc( ' ', stream );

    fputs( last_error.message, stream );

    if( last_error.code_type ) {
      fprintf( stream, " (%s: %d)", last_error.code_type, last_error.code );
    }

    fputc( '\n', stream );
  }

  config_write_bool( &error_stream_free, true );
}

void
stumpless_set_error_stream( FILE *stream ) {
  config_write_ptr( &error_stream, stream );
  config_write_bool( &error_stream_valid, true );
}

/* private functions */

/**
 * Clears the internal error state. This must be called at some point in all
 * public functions to make sure that residual errors don't stick around.
 *
 * If a public function calls another public function internally, it can skip
 * calling this function as the called public function will clear the error if
 * it succeeds, and should pass the error on if not.
 *
 * Ideally, this should be called directly after the last possible failure point
 * in the function to avoid unnecessary clears, but before other code in case a
 * non-fatal error is raised and needs to be visible upon return.
 */
void
clear_error( void ) {
  error_valid = false;
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
raise_argument_too_big( const char *message,
                        size_t arg_size,
                        const char *arg_type ) {
  raise_error( STUMPLESS_ARGUMENT_TOO_BIG,
               message,
               cap_size_t_to_int( arg_size ),
               arg_type );
}

void
raise_duplicate_element( void ) {
  raise_error( STUMPLESS_DUPLICATE_ELEMENT,
               L10N_DUPLICATE_ELEMENT_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_element_not_found( void ) {
  raise_error( STUMPLESS_ELEMENT_NOT_FOUND,
               L10N_ELEMENT_NOT_FOUND_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_error( enum stumpless_error_id id,
             const char *message,
             int code,
             const char *code_type ) {
  last_error.id = id;
  last_error.message = message;
  last_error.code = code;
  last_error.code_type = code_type;
  error_valid = true;
}

void
raise_file_open_failure( void ) {
  raise_error( STUMPLESS_FILE_OPEN_FAILURE,
               L10N_FILE_OPEN_FAILURE_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_file_write_failure( void ) {
  raise_error( STUMPLESS_FILE_WRITE_FAILURE,
               L10N_FILE_WRITE_FAILURE_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_function_target_failure( int code ) {
  raise_error( STUMPLESS_FUNCTION_TARGET_FAILURE,
               L10N_FUNCTION_TARGET_FAILURE_ERROR_MESSAGE,
               code,
               L10N_FUNCTION_TARGET_FAILURE_CODE_TYPE );
}

void
raise_gethostname_failure( const char *message,
                           int code,
                           const char *code_type ) {
  raise_error( STUMPLESS_GETHOSTNAME_FAILURE, message, code, code_type );
}

void
raise_index_out_of_bounds( const char *message, size_t index ) {
  raise_error( STUMPLESS_INDEX_OUT_OF_BOUNDS,
               message,
               size_t_to_int( index ),
               L10N_INDEX_OUT_OF_BOUNDS_ERROR_CODE_TYPE );
}

void
raise_invalid_encoding( const char *message ) {
  raise_error( STUMPLESS_INVALID_ENCODING, message, 0, NULL );
}

void
raise_invalid_facility( int facility ) {
  raise_error( STUMPLESS_INVALID_FACILITY,
               L10N_INVALID_FACILITY_ERROR_MESSAGE,
               facility,
               L10N_INVALID_FACILITY_ERROR_CODE_TYPE );
}

void
raise_invalid_id( void ) {
  raise_error( STUMPLESS_INVALID_ID,
               L10N_INVALID_ID_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_invalid_severity( int severity ) {
  raise_error( STUMPLESS_INVALID_SEVERITY,
               L10N_INVALID_SEVERITY_ERROR_MESSAGE,
               severity,
               L10N_INVALID_SEVERITY_ERROR_CODE_TYPE );
}

void
raise_journald_failure( int code ) {
  raise_error( STUMPLESS_JOURNALD_FAILURE,
               L10N_JOURNALD_FAILURE_ERROR_MESSAGE,
               code,
               L10N_JOURNALD_FAILURE_ERROR_CODE_TYPE );
}

void
raise_mb_conversion_failure( int code ) {
  raise_error( STUMPLESS_INVALID_ENCODING,
               L10N_MB_TO_WIDE_CONVERSION_ERROR_MESSAGE,
               code,
               L10N_MB_TO_WIDE_CONVERSION_ERROR_CODE_TYPE );
}

void
raise_memory_allocation_failure( void ) {
  raise_error( STUMPLESS_MEMORY_ALLOCATION_FAILURE,
               L10N_MEMORY_ALLOCATION_FAILURE_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_network_protocol_unsupported( void ) {
  raise_error( STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED,
               L10N_NETWORK_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_param_not_found( void ) {
  raise_error( STUMPLESS_PARAM_NOT_FOUND,
               L10N_PARAM_NOT_FOUND_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_resolve_hostname_failure( const char *message ) {
  raise_error( STUMPLESS_ADDRESS_FAILURE,
               message,
               0,
               NULL );
}

void
raise_socket_bind_failure( const char *message,
                           int code,
                           const char *code_type ) {
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
  raise_error( STUMPLESS_STREAM_WRITE_FAILURE,
               L10N_STREAM_WRITE_FAILURE_ERROR_MESSAGE,
               0,
               NULL );
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
  raise_error( STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED,
               L10N_TRANSPORT_PROTOCOL_UNSUPPORTED_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_wel_close_failure( void ) {
  raise_error( STUMPLESS_WINDOWS_EVENT_LOG_CLOSE_FAILURE,
               L10N_WEL_CLOSE_FAILURE_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_wel_open_failure( void ) {
  raise_error( STUMPLESS_WINDOWS_EVENT_LOG_OPEN_FAILURE,
               L10N_WEL_OPEN_FAILURE_ERROR_MESSAGE,
               0,
               NULL );
}

void
raise_wide_conversion_failure( int code, const char *code_type ) {
  raise_error( STUMPLESS_INVALID_ENCODING,
    L10N_WIDE_TO_MB_CONVERSION_ERROR_MESSAGE,
    code,
    code_type );
}

void
raise_windows_failure( const char *message, int code, const char *code_type ) {
  raise_error( STUMPLESS_WINDOWS_FAILURE, message, code, code_type );
}

void
write_to_error_stream( const char *msg, size_t msg_size ) {
  FILE *stream;
  bool locked;

  stream = stumpless_get_error_stream(  );
  if( !stream ) {
    return;
  }

  do{
    locked = config_compare_exchange_bool( &error_stream_free, true, false );
  } while( !locked );

  fwrite( msg, sizeof( *msg ), msg_size, stream );

  config_write_bool( &error_stream_free, true );
}

void
raise_invalid_param( void ) {
  raise_error( STUMPLESS_INVALID_PARAM_STRING,
               L10N_INVALID_PARAM_ERROR_MESSAGE,
               0,
               NULL );
}
