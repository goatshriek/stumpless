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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H

#  include <stumpless/config.h>
#  include "private/config.h"


/* definition of config_open_default_target */
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include "private/config/wel_supported.h"
#    include "stumpless/target/wel.h"
#    define config_open_default_target wel_open_default_target
#    define config_close_default_target stumpless_close_wel_target
#  elif STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include <stumpless/target/socket.h>
#    include "private/config/socket_supported.h"
#    define config_open_default_target socket_open_default_target
#    define config_close_default_target stumpless_close_socket_target
#  else
#    include <stumpless/target/file.h>
#    include "private/target/file.h"
#    define config_open_default_target file_open_default_target
#    define config_close_default_target stumpless_close_file_target
#  endif


/* definition of config_fopen */
#  ifdef HAVE_FOPEN_S
#    include "private/config/have_fopen_s.h"
#    define config_fopen fopen_s_fopen
#  else
#    include <stdio.h>
#    define config_fopen fopen
#  endif


/* definition of config_format_string */
#  ifdef HAVE_VSNPRINTF_S
#    include "private/config/have_vsnprintf_s.h"
#    define config_format_string vsnprintf_s_format_string
#  else
#    include "private/config/no_vsnprintf_s.h"
#    define config_format_string no_vsnprintf_s_format_string
#  endif


/* definition of config_get_now */
#  ifdef HAVE_GMTIME_R
#    include "private/config/have_gmtime_r.h"
#    define config_get_now gmtime_r_get_now
#  elif SUPPORT_WINDOWS_GET_NOW
#    include "private/config/windows_get_now_supported.h"
#    define config_get_now windows_get_now
#  endif


/* definition of config_gethostname */
#  ifdef HAVE_UNISTD_GETHOSTNAME
#    include "private/config/have_unistd_gethostname.h"
#    define config_gethostname(buffer, namelen) unistd_gethostname((buffer), (namelen))
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_gethostname(buffer, namelen) windows_gethostname((buffer), (namelen))
#  else
#    include "private/config/fallback.h"
#    define config_gethostname(buffer, namelen) fallback_gethostname((buffer), (namelen))
#  endif


/* definition of config_getpagesize */
#  ifdef SUPPORT_UNISTD_SYSCONF_GETPAGESIZE
#    include "private/config/unistd_sysconf_getpagesize_supported.h"
#    define config_getpagesize unistd_sysconf_getpagesize
#  elif HAVE_UNISTD_GETPAGESIZE
#    include "private/config/have_unistd_getpagesize.h"
#    define config_getpagesize unistd_getpagesize
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_getpagesize windows_getpagesize
#  else
#    include "private/config/fallback.h"
#    define config_getpagesize fallback_getpagesize
#  endif


/* definition of config_getpid */
#  ifdef HAVE_UNISTD_H
#    include "private/config/have_unistd.h"
#    define config_getpid unistd_getpid
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_getpid windows_getpid
#  else
#    include "private/config/fallback.h"
#    define config_getpid fallback_getpid
#  endif


#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H */
