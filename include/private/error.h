/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_ERROR_H
#  define __STUMPLESS_PRIVATE_ERROR_H

#  include <stddef.h>
#  include <stumpless/error.h>
#  include "private/config.h"

void
clear_error( void );

COLD_FUNCTION
void
raise_address_failure( const char *message, int code, const char *code_type );

COLD_FUNCTION
void
raise_argument_empty( const char *message );

/**
 * Raises an error indicating that an argument was too big to process.
 *
 * If the size is too big to represent in an int, then it is capped to INT_MAX.
 *
 * @param message A localized message describing the overall error.
 *
 * @param arg_size The size of the offending argument.
 *
 * @param arg_type A localized description of the argument that was too big.
 */
COLD_FUNCTION
void
raise_argument_too_big( const char *message,
                        size_t arg_size,
                        const char *arg_type );

COLD_FUNCTION
void
raise_duplicate_element( void );

COLD_FUNCTION
void
raise_element_not_found( void );

COLD_FUNCTION
void
raise_error( enum stumpless_error_id id,
             const char *message,
             int code,
             const char *code_type );

COLD_FUNCTION
void
raise_file_open_failure( void );

COLD_FUNCTION
void
raise_file_write_failure( void );

COLD_FUNCTION
void
raise_function_target_failure( int code );

COLD_FUNCTION
void
raise_gethostname_failure( const char *message,
                           int code,
                           const char *code_type );

COLD_FUNCTION
void
raise_index_out_of_bounds( const char *message, size_t index );

COLD_FUNCTION
void
raise_invalid_encoding( const char* message );

COLD_FUNCTION
void
raise_invalid_facility( int facility );

COLD_FUNCTION
void
raise_invalid_id( void );

COLD_FUNCTION
void
raise_invalid_severity( int severity );

COLD_FUNCTION
void
raise_journald_failure( int code );

/**
 * Raises an error indicating that a conversion from a multibyte string to a
 * wide character string failed.
 *
 * @param code The result of GetLastError after the failed conversion.
 */
COLD_FUNCTION
void
raise_mb_conversion_failure( int code );

COLD_FUNCTION
void
raise_memory_allocation_failure( void );

COLD_FUNCTION
void
raise_network_protocol_unsupported( void );

COLD_FUNCTION
void
raise_param_not_found( void );

COLD_FUNCTION
void
raise_socket_bind_failure( const char *message,
                           int code,
                           const char *code_type );

COLD_FUNCTION
void
raise_socket_connect_failure( const char *message,
                              int code,
                              const char *code_type );

COLD_FUNCTION
void
raise_socket_failure( const char *message, int code, const char *code_type );

COLD_FUNCTION
void
raise_socket_send_failure( const char *message,
                           int code,
                           const char *code_type );

COLD_FUNCTION
void
raise_stream_write_failure( void );

COLD_FUNCTION
void
raise_target_incompatible( const char *message );

COLD_FUNCTION
void
raise_target_unsupported( const char *message );

COLD_FUNCTION
void
raise_transport_protocol_unsupported( void );

COLD_FUNCTION
void
raise_wel_close_failure( void );

COLD_FUNCTION
void
raise_wel_open_failure( void );

/**
 * Raises an error indicating that a conversion from a wide string to a
 * multibyte string failed.
 *
 * @param code The result of GetLastError after the failed conversion.
 */
COLD_FUNCTION
void
raise_wide_conversion_failure( int code );

#endif /* __STUMPLESS_PRIVATE_ERROR_H */
