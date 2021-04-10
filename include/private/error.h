/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_ERROR_H
#  define __STUMPLESS_PRIVATE_ERROR_H

// Generate error enum strings array in src/error.c
#define STUMPLESS_GENERATE_STRING(STRING, INDEX) #STRING,

#  include <stddef.h>
#  include <stumpless/error.h>

void
clear_error( void );

void
raise_address_failure( const char *message, int code, const char *code_type );

void
raise_argument_empty( const char *message );

void
raise_argument_too_big( const char *message, int code, const char *code_type );

void
raise_duplicate_element( void );

void
raise_element_not_found( void );

void
raise_error( enum stumpless_error_id id,
             const char *message,
             int code,
             const char *code_type );

void
raise_file_open_failure( void );

void
raise_file_write_failure( void );

void
raise_function_target_failure( int code );

void
raise_gethostname_failure( const char *message,
                           size_t code,
                           const char *code_type );

void
raise_index_out_of_bounds( const char *message, size_t index );

void
raise_invalid_facility( int facility );

void
raise_invalid_id( void );

void
raise_invalid_severity( int severity );

void
raise_memory_allocation_failure( void );

void
raise_network_protocol_unsupported( void );

void
raise_param_not_found( void );

void
raise_socket_bind_failure( const char *message,
                           int code,
                           const char *code_type );

void
raise_socket_connect_failure( const char *message,
                              int code,
                              const char *code_type );

void
raise_socket_failure( const char *message, int code, const char *code_type );

void
raise_socket_send_failure( const char *message,
                           int code,
                           const char *code_type );

void
raise_stream_write_failure( void );

void
raise_target_incompatible( const char *message );

void
raise_target_unsupported( const char *message );

void
raise_transport_protocol_unsupported( void );

void
raise_wel_close_failure( void );

void
raise_wel_open_failure( void );

void
raise_invalid_encoding( const char *message );

#endif /* __STUMPLESS_PRIVATE_ERROR_H */
