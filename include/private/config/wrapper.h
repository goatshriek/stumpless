/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2018 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H

#  include <stumpless/config.h>
#  include "private/config.h"

#  ifdef HAVE_UNISTD_H
#    include "private/config/have_unistd.h"
#  endif

#  ifdef HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#  endif

#  ifdef HAVE_WINSOCK2_H
#    include "private/config/have_winsock2.h"
#  endif

/* definition of config_socket */
#  ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include "private/target/socket.h"
#    define config_sendto_socket_target sendto_socket_target
#  else
#    define config_sendto_socket_target target_unsupported
#  endif

/* definition of config_gethostname */
#  ifdef HAVE_UNISTD_H
#    define config_gethostname(buffer, namelen) unistd_gethostname((buffer), (namelen))
#  elif HAVE_WINSOCK2_H
#    define config_gethostname(buffer, namelen) winsock2_gethostname((buffer), (namelen))
#  endif

/* definition of config_getpagesize */
#  ifdef HAVE_UNISTD_H
#    define config_getpagesize unistd_getpagesize
#  elif HAVE_WINDOWS_H
#    define config_getpagesize windows_getpagesize
#  endif

/* definition of config_getpid */
#  ifdef HAVE_UNISTD_H
#    define config_getpid unistd_getpid
#  elif HAVE_WINDOWS_H
#    define config_getpid windows_getpid
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H */
