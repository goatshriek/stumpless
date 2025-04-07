/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2022 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_PARAM_H
#  define __STUMPLESS_PRIVATE_PARAM_H

#  include <stddef.h>
#  include <stumpless/param.h>

void
lock_param( const struct stumpless_param *param );

/**
 * Does the same as stumpless_load_param, but without performing any validation
 * or NULL checks.
 *
 * **Thread Safety: MT-Safe race:param race:name race:value**
 * This function is thread safe, assuming that the param, name, and value are
 * not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap lock**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the param's value as well as the use of
 * a mutex initialization routine.
 *
 * **Async Cancel Safety: AC-Unsafe heap lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions and a mutex
 * initialization routine.
 *
 * @param param The struct to load with the given values.
 *
 * @param name The name of the param.
 *
 * @param name_length The length of the name in bytes, not including the NULL
 * terminator.
 *
 * @param value The value of the param. This pointer will be stored and used
 * over the lifetime of the param, and must be valid until
 * `stumpless_unload_param` is called on this loaded param.
 *
 * @return A pointer to the loaded param, if no error is encountered. If an
 * error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
struct stumpless_param *
unchecked_load_param( struct stumpless_param *param,
                      const char *name,
                      size_t name_length,
                      const char *value );

/**
 * Retrieves the size required to store the parameter as a string.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it doesn't use any synchronization
 * or locking mechanisms while accessing shared resources.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 *
 * @param param The param to retrieve the size required to store the 
 * parameter as a string.
 *
 * @return The size required to store the parameter as a string.
 */
size_t
locked_get_param_string_size( const struct stumpless_param *param );

/**
 * Writes the parameter as a string into the buffer provided.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it doesn't use any synchronization
 * or locking mechanisms while accessing shared resources.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers due to the use of
 * memory functions.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory functions that could leave the
 * memory in undefined state.
 *
 * @param entry The param to write as a string.
 *
 * @param buffer The buffer to write in.
 *
 * @param buffer_size The size of the buffer.
 *
 * @return The number of bytes written in the buffer.
 */
size_t
locked_param_into_buffer( const struct stumpless_param *param,
                        char *buffer, size_t buffer_size );

void
unlock_param( const struct stumpless_param *param );

#endif /* __STUMPLESS_PRIVATE_PARAM_H */
