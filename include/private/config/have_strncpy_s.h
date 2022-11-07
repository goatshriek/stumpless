/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2022 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_HAVE_STRNCPY_S_H
#  define __STUMPLESS_PRIVATE_CONFIG_HAVE_STRNCPY_S_H

#  include <stddef.h>

/**
 * Copies the NULL-terminated string from src into dest. The dest will always
 * be NULL-terminated, even if count is less than the size of the source.
 *
 * @since release v2.1.0
 *
 * @param dest The buffer to copy the string into.
 *
 * @param src The string to copy.
 *
 * @param count The maximum number of characters to copy into dest.
 *
 * @return dest on success, or NULL on failure.
 */
char *
strncpy_s_strncpy( char *dest, const char *src, size_t count );

#endif /* __STUMPLESS_PRIVATE_CONFIG_HAVE_STRNCPY_S_H */
