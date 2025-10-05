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
 * @brief Stringifies the first argument and appends a comma.
 *
 * This macro ignores the second argument. It is primarily used in
 * FOREACH macros when defining enumerations, especially for
 * converting enum values to strings.
 *
 * @param STRING The value to stringify.
 * @param INDEX  Ignored parameter, typically used in FOREACH macros.
 */
#  define GENERATE_STRING( STRING, INDEX ) #STRING,

/**
 * @brief Creates a copy of a null-terminated C string.
 *
 * Allocates memory for a new string and copies the contents of the
 * provided string into it.
 *
 * @param str The original null-terminated string to copy.
 * @return A pointer to the newly allocated copy of the string,
 *         or NULL if memory allocation fails.
 */
char *
copy_cstring( const char *str );

/**
 * @brief Creates a copy of a C string and optionally returns its length.
 *
 * Allocates memory for a new string, copies the contents of the
 * provided string, and if the `length` pointer is provided, stores
 * the length of the copied string.
 *
 * @param str    The original null-terminated string to copy.
 * @param length Optional pointer to store the length of the copied string.
 * @return A pointer to the newly allocated copy of the string,
 *         or NULL if memory allocation fails.
 */
char *
copy_cstring_with_length( const char *str, size_t *length );

/**
 * @brief Compares two strings ignoring case, up to a given number of characters.
 *
 * Works similarly to the standard `strncasecmp`, but is a custom implementation.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n  Maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2.
 */
int
strncasecmp_custom( const char *s1, const char *s2, size_t n );

#endif /* __STUMPLESS_PRIVATE_STRHELPER_H */
