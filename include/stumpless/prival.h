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

/** @file
 * Function for converting prival from int to string
 */

#ifndef __STUMPLESS_PRIVAL_H
#  define __STUMPLESS_PRIVAL_H

#  include <stumpless/config.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Gets the string representation of the given prival.
 *
 * The string returned must be freed by the caller when it is no longer
 * needed to avoid memory leaks.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled due to the use of memory management functions.
 *
 * @since release v2.2.0
 *
 * @param prival int to get the string from.
 *
 * @return The string representation of the given prival.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_prival_string( int prival );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_PRIVAL_H */
