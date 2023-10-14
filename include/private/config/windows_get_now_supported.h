/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2023 Joel E. Anderson
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
 * Functionality to get the current time, based on Windows functions.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_WINDOWS_GET_NOW_SUPPORTED_H
#  define __STUMPLESS_PRIVATE_CONFIG_WINDOWS_GET_NOW_SUPPORTED_H

#  include <stddef.h>

/**
 * Gets the current time as a string and places it into the given buffer.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not safe to call from signal handlers, due to the use of
 * sprintf_s.
 *
 * **Async Cancel Safety: AC-Unsafe**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of sprintf_s.
 *
 * @param buffer The buffer to write the string into.
 *
 * @return The number of characters written into the buffer. If an error is
 * encountered, then 0 is returned.
 */
size_t
windows_get_now( char *buffer );

#endif /* __STUMPLESS_PRIVATE_CONFIG_WINDOWS_GET_NOW_SUPPORTED_H */
