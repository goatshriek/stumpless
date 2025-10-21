/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2025 Michael Hinz
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

/** @file
 * Fallback functionality for comparing two strings ignoring case.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_NO_STRNCASECMP_H
#define __STUMPLESS_PRIVATE_CONFIG_NO_STRNCASECMP_H

#include <stddef.h>

/**
 * Implements the POSIX 1-2008 function to compare two strings ignoring case
 *
 * FIXME: check these:
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v3.0.0
 *
 * @param s1    The first string.
 * @param s2    The second string.
 * @param n     The maximum number of characters to be compared.
 *
 * @return      an integer less than, equal to, or greater than zero if s1 is found, respectively, to
 *              be less than, to match, or be greater than s2.
 */

int strncasecmp_custom(const char *s1, const char *s2, size_t n);

#endif /* __STUMPLESS_PRIVATE_CONFIG_NO_STRNCASECMP_H */
