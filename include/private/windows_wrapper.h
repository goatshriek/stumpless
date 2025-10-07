/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020 Joel E. Anderson
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

/**
 * @file private_windows_wrapper.h
 * @brief Safe inclusion wrapper for Windows-specific headers.
 *
 * This header acts as a **single inclusion point** for `windows.h`,
 * `winsock2.h`, and `ws2tcpip.h`, ensuring that they are included in the
 * correct order to prevent compilation conflicts.
 *
 * Windows headers have known ordering dependencies — for example, including
 * `windows.h` before `winsock2.h` can lead to symbol redefinitions and other
 * errors.  
 * This wrapper handles these dependencies automatically for internal use.
 *
 * @note This header should **only be included by internal Stumpless files**
 * that need Windows APIs.
 *
 * @since release v2.0.0
 */

#ifndef __STUMPLESS_PRIVATE_WINDOWS_WRAPPER_H
#  define __STUMPLESS_PRIVATE_WINDOWS_WRAPPER_H

#  include "private/config.h"

/**
 * @defgroup windows_wrapper Internal Windows Header Management
 * @ingroup internal_headers
 * @brief Safely manages inclusion of Windows API headers.
 *
 * This group ensures that all Windows-specific includes are handled in a
 * consistent and safe manner throughout the library.
 * @{
 */

#  ifdef HAVE_WINSOCK2_H
  /**
   * @brief Includes Windows socket API headers if available.
   *
   * These headers provide definitions for networking operations,
   * sockets, and related structures used internally by Stumpless.
   */
#    include <winsock2.h>
#    include <ws2tcpip.h>
#  endif

#  ifdef HAVE_WINDOWS_H
  /**
   * @brief Includes the main Windows API header if available.
   *
   * Provides access to system-level APIs such as file handling,
   * synchronization, and process management.
   */
#    include <windows.h>
#  endif

/** @} */ /* end of windows_wrapper group */

#endif /* __STUMPLESS_PRIVATE_WINDOWS_WRAPPER_H */
