/* SPDX-License-Identifier: Apache-2.0 */

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

/**
 * Raises an error indicating an issue in the current thread of execution.
 *
 * Errors are thread-specific, and so will be save to check without worrying
 * about thread safety. However, reentrant code will need to signal issues in
 * other ways, as it cannot safely modify the thread-global error structure.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store the error.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store the error.
 *
 * @param id The type of error to raise.
 *
 * @param message The message to assign to the error.
 *
 * @param code A more specific subtype of the error, or a secondary error code
 * provided by the failing call or operation.
 *
 * @param code_type A description of what the code signifies.
 */
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

/**
 * Raises an error indicating that some field had an invalid encoding. This
 * could mean that something was an invalid UTF-8 or 16 character, wasn't
 * terminated or otherwise formatted properly, or something similar.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors.
 *
 * @param message The message to assign to the error.
 */
COLD_FUNCTION
void
raise_invalid_encoding( const char *message );

COLD_FUNCTION
void
raise_invalid_facility( int facility );

COLD_FUNCTION
void
raise_invalid_id( void );

COLD_FUNCTION
void
raise_invalid_param( void );

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
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors.
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

/**
 * Raises an error indicating an issue in resolving a hostname.
 *
 * This assumes that the resolution failed with both gethostbyname[2] and
 * inet_pton.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store the error.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store the error.
 *
 * @param message The message to assign to the error.
 */
COLD_FUNCTION
void
raise_resolve_hostname_failure( const char *message );

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
 * @param code The error code.
 *
 * @param code_type A localized description of the error code.
 */
COLD_FUNCTION
void
raise_wide_conversion_failure( int code, const char *code_type );

/**
 * Raises an error indicating a general failure of a Windows API call. Details
 * on what call failed and why must be provided.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * a thread-global structure to store errors.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a thread-global structure to store errors.
 *
 * @param message A localized description of the failure that occurred,
 * including a function name or operation type that failed.
 *
 * @param code An error code.
 *
 * @param code_type A localized description of what the code type is.
 */
COLD_FUNCTION
void
raise_windows_failure( const char *message, int code, const char *code_type );

/**
 * Writes a message to the error stream. This is ignored if the error stream
 * is NULL.
 *
 * This function does not update or modify the per-thread error code. Failures
 * are silently ignored.
 *
 * **Thread Safety: MT-Safe race:prefix**
 * This function is thread safe. A lock is used to coordinate writes to the
 * error stream.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers, as it uses a
 * non-reentrant lock to synchronize access to the error stream.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the lock used to control access to the error stream may not
 * be released after a cancellation.
 *
 * @since v2.1.0.
 *
 * @param msg The message to be written to the error stream.
 *
 * @param msg_size The size of the message to be written in bytes.
 */
void
write_to_error_stream( const char *msg, size_t msg_size );

#endif /* __STUMPLESS_PRIVATE_ERROR_H */
