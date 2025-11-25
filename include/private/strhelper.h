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

#ifndef __STUMPLESS_PRIVATE_STRHELPER_H
#  define __STUMPLESS_PRIVATE_STRHELPER_H

#  include <stddef.h>

/**
 * Stringifies the first argument and adds a comma afterwards, and ignores the
 * second argument. Useful in FOREACH macros used to define enumerations,
 * particularly for conversion to string functionality.
 */
#  define GENERATE_STRING( STRING, INDEX ) #STRING,

/**
 * Creates a duplicate of the given C-string.
 *
 * Allocates a new buffer and copies the contents of `str` into it,
 * including the terminating NULL byte. The returned string must be freed
 * with the corresponding deallocator when no longer needed.
 *
 * **Thread Safety: MT-Safe**
 * Uses heap allocation but maintains no shared global state; safe when
 * used concurrently in multiple threads.
 *
 * **Async Signal Safety: AS-Unsafe (heap)**
 * Not safe to call from signal handlers because it may invoke memory
 * allocation routines that are not reentrant.
 *
 * **Async Cancel Safety: AC-Unsafe (heap)**
 * May leave heap state inconsistent if a thread is asynchronously
 * cancelled during allocation.
 *
 * @param str The NULL-terminated source string to copy. Must not be NULL.
 * @return A newly allocated copy of `str`, or `NULL` if allocation fails.
 */
char *
copy_cstring( const char *str );

/**
 * Creates a duplicate of the given C-string returning the length in the
 * supplied length parameter.
 *
 * Allocates a new buffer and copies the contents of `str` into it,
 * including the terminating NULL byte. The returned string must be freed
 * with the corresponding deallocator when no longer needed.
 *
 * **Thread Safety: MT-Safe**
 * Uses heap allocation but maintains no shared global state; safe when
 * used concurrently in multiple threads.
 *
 * **Async Signal Safety: AS-Unsafe (heap)**
 * Not safe to call from signal handlers because it may invoke memory
 * allocation routines that are not reentrant.
 *
 * **Async Cancel Safety: AC-Unsafe (heap)**
 * May leave heap state inconsistent if a thread is asynchronously
 * cancelled during allocation.
 *
 * @param str The NULL-terminated source string to copy. Must not be NULL.
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 * @return A newly allocated copy of `str`, or `NULL` if allocation fails.
 */
char *
copy_cstring_with_length( const char *str, size_t *length );

#endif /* __STUMPLESS_PRIVATE_STRHELPER_H */
