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

#ifndef __STUMPLESS_PRIVATE_CONFIG_FALLBACK_H
#  define __STUMPLESS_PRIVATE_CONFIG_FALLBACK_H

#include <stddef.h>

/**
 * Creates a copy of a NULL terminated wide character string in UTF-8 multibyte
 * format.
 *
 * **Thread Safety: MT-Safe race:str**
 * This function is thread safe, of course assuming that the string is not
 * changed during operation.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the copy.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @param str A wide character string to copy, in UTF-16 format.
 *
 * @param copy_size The size of the copy including the NULL terminator, in
 * bytes. If this is NULL or the function fails, then it is ignored.
 *
 * @return A copy of the given string in wide string format, or NULL if an
 * error is encountered.
 */
char *
windows_copy_wstring_to_cstring( wchar_t *str, int *copy_size );

int
fallback_gethostname( char *buffer, size_t namelen );

size_t
fallback_getpagesize( void );

int
fallback_getpid( void );

#endif /* __STUMPLESS_PRIVATE_CONFIG_FALLBACK_H */
