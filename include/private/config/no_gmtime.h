/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2024 Joel E. Anderson
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
 * Fallback functionality for getting the current time.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_NO_GMTIME_H
#define __STUMPLESS_PRIVATE_CONFIG_NO_GMTIME_H

#include <stddef.h>

/**
 * Writes an RFC 5424 NILVALUE to the provided buffer and returns its size.
 *
 * This function is used to get the time if no other suitable time function is
 * available.
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
 * @since release v2.2.0
 *
 * @param buffer The buffer to write the string into.
 *
 * @return The number of characters written into the buffer.
 */
size_t
no_gmtime_get_now( char *buffer );

#endif /* __STUMPLESS_PRIVATE_CONFIG_NO_GMTIME_H */
