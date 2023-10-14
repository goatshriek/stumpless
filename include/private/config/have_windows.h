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

#ifndef __STUMPLESS_PRIVATE_CONFIG_HAVE_WINDOWS_H
#  define __STUMPLESS_PRIVATE_CONFIG_HAVE_WINDOWS_H

#  include "private/windows_wrapper.h"

#  include <stdbool.h>
#  include <stddef.h>

bool
windows_compare_exchange_bool( LONG volatile *b,
                               LONG expected,
                               LONG replacement );

bool
windows_compare_exchange_ptr( PVOID volatile *p,
                              const void *expected,
                              PVOID replacement );

/**
 * Creates a copy of a NULL terminated multibyte string in wide string format.
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
 * @param str A multibyte string to copy, in UTF-8 format.
 *
 * @param copy_length The length of the copy including the NULL terminator, in
 * characters (_not_ bytes). If this is NULL or the function fails, then it is
 * ignored.
 *
 * @return A copy of the given string in wide string format, or NULL if an
 * error is encountered.
 */
LPWSTR
windows_copy_cstring_to_lpwstr( LPCSTR str, int *copy_length );

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
windows_copy_wstring_to_cstring( const wchar_t *str, int *copy_size );

void
windows_destroy_mutex( const CRITICAL_SECTION *mutex );

int
windows_gethostname( char *buffer, size_t namelen );

size_t
windows_getpagesize( void );

int
windows_getpid( void );

void
windows_init_mutex( LPCRITICAL_SECTION mutex );

void
windows_lock_mutex( const CRITICAL_SECTION *mutex );

void
windows_unlock_mutex( const CRITICAL_SECTION *mutex );

#endif /* __STUMPLESS_PRIVATE_CONFIG_HAVE_WINDOWS_H */
