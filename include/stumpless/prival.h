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

/** @file
 * Prival codes for function to create severity and facility string from prival int value.  
 */

#ifndef __STUMPLESS_PRIVAL_H
#  define __STUMPLESS_PRIVAL_H

#  include <stumpless/config.h>

#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    include <syslog.h>
#  endif

/**
 * Gets the string corresponding to the given int prival value.
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
 * @since release v2.2.0.
 * 
 * @param prival The prival name to get the string from.
 * 
 * @return The string representation of the severity and facility from the given prival.
*/
STUMPLESS_PUBLIC_FUNCTION
const char * 
stumpless_get_prival_string( int prival );

#  ifdef __cplusplus
} /* extern "C" */
#  endif

#endif /* __STUMPLESS_PRIVAL_H */
