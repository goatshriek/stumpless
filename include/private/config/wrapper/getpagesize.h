
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETPAGESIZE_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETPAGESIZE_H

#  include "private/config.h"


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

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETPAGESIZE_H */
