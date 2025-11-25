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

#ifndef __STUMPLESS_PRIVATE_STRBUILDER_H
#define __STUMPLESS_PRIVATE_STRBUILDER_H

#include <stddef.h>

struct strbuilder {
  char *buffer;
  char *position;
  char *buffer_end;
};

/**
 * Appends a character buffer.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the potential
 * use of memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the potential use of memory management functions.
 *
 * @param builder The strbuilder to append the characters to.
 *
 * @param buffer The character buffer to append to the string.
 * @param size The number of bytes to copy from the character buffer.
 *
 * @return The modified builder if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct strbuilder *
strbuilder_append_buffer( struct strbuilder *builder,
                          const char *buffer, size_t size );

/**
 * Appends a char value.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the potential
 * use of memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the potential use of memory management functions.
 *
 * @param builder The strbuilder to append the characters to.
 *
 * @param c The character to append to the string.
 *
 * @return The modified builder if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct strbuilder *
strbuilder_append_char( struct strbuilder *builder, char c );

/**
 * Appends an int value. The value is assumed to be greater than or equal to
 * zero. If it is negative, a negative sign is NOT included in the sequence of
 * appended characters.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the potential
 * use of memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the potential use of memory management functions.
 *
 * @param builder The strbuilder to append the characters to.
 *
 * @param i The zero or positive value to append.
 *
 * @return The modified builder if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct strbuilder *
strbuilder_append_positive_int( struct strbuilder *builder, int i );

/**
 * Appends a string.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the potential
 * use of memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the potential use of memory management functions.
 *
 * @param builder The strbuilder to append the characters to.
 *
 * @param str The NULL terminated string to append to the buffer.
 *
 * @return The modified builder if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct strbuilder *
strbuilder_append_string( struct strbuilder *builder,
                          const char *str );

/**
 * Frees all memory associated with any string builders that have been created.
 * Releases memory associated with the cache and also any buffers within each
 * item in the cache (via the teardown function).
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the potential
 * use of memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the potential use of memory management functions.
 */
void
strbuilder_free_all( void );

/**
 * Gets the buffer output from the string builder, returning the length of the
 * buffer in the supplied length parameter.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * Mostly AS-Safe but there is an opportunity for tearing which could result
 * in a nonsensical length.
 *
 * **Async Cancel Safety: AC-Safe**
 *
 * @param builder The strbuilder to append the characters to.
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return A pointer to the complete buffer.
 */
char *
strbuilder_get_buffer( struct strbuilder *builder, size_t *length );

/**
 * Destroys a specific string builder but does not free the associated memory.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock and possibly memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of a lock that could be left locked and the possible
 * use of memory management functions.
 *
 * @param builder The strbuilder to destroy.
 */
void
strbuilder_destroy( const struct strbuilder *builder );

/**
 * Creates a string builder.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock and possibly memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of a lock that could be left locked and the possible
 * use of memory management functions.
 *
 * @return The new string builder.
 */
struct strbuilder *
strbuilder_new( void );

/**
 * Resets the strbuilder to be empty, without giving up memory resources.
 *
 * @since release v2.2.0
 *
 * @param builder The strbuilder to reset. If this is NULL, then this function
 * does nothing.
 *
 * @return The reset builder.
 */
struct strbuilder *
strbuilder_reset( struct strbuilder *builder );

/**
 * Converts a string builder to a NULL terminated string.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe.
 *
* **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the potential
 * use of memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the potential use of memory management functions.
 *
 * @return The new string builder.
 */
char *
strbuilder_to_string( const struct strbuilder *builder );

#endif /* __STUMPLESS_PRIVATE_STRBUILDER_H */
