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

char *
copy_cstring( const char *str );

char *
copy_cstring_with_length( const char *str, size_t *length );

int
strncasecmp_custom( const char *s1, const char *s2, size_t n );

#endif /* __STUMPLESS_PRIVATE_STRHELPER_H */
