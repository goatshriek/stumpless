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

/** @file
 * Priority value (PRIVAL) represents both the Facility and Severity values.
 *
 * @since release v2.2.0
 */

#ifndef __STUMPLESS_PRIORITY_H
#  define __STUMPLESS_PRIORITY_H

#  include <stumpless.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Extract PRIVAL number (Facility and Severity) from the given string with
 * the direct number or with two names divided with a period in the order:
 * facility first, then severity ("<facility_descr>.<severity_descr>").
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the target.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked..
 *
 * @since release v2.2.0
 *
 * @param string The string to extract the prival from.
 *
 * @return the PRIVAL number used for the severity and facility values of
 * the logged entry, in the event of an error it returns -1.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_prival_from_string( const char *string );

#  ifdef __cplusplus
} /* extern "C" */
#  endif

#endif /* __STUMPLESS_PRIORITY_H */
