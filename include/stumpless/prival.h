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

#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    include <syslog.h>
#  endif

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Gets the string representation of the given prival.
 *
 * This is a string literal that should not be modified or freed by the caller.
 *
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
