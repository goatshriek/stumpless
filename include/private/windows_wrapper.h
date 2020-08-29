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
 
/** @file
 * Serves as a single inclusion point for windows.h, winsock2.h, and
 * ws2tcpip.h. Windows headers have ordering dependencies that can cause
 * compilation errors, and as such need to be done carefully.
 */

#ifndef __STUMPLESS_PRIVATE_WINDOWS_WRAPPER_H
#  define __STUMPLESS_PRIVATE_WINDOWS_WRAPPER_H

#  include "private/config.h"

#  ifdef HAVE_WINSOCK2_H
#    include <winsock2.h>
#    include <ws2tcpip.h>
#  endif

#  ifdef HAVE_WINDOWS_H
#    include <windows.h>
#  endif

#endif /* __STUMPLESS_PRIVATE_WINDOWS_WRAPPER_H */
