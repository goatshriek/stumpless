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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GET_NOW_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GET_NOW_H

/* definition of config_get_now */
#  ifdef HAVE_GMTIME_R
#    include "private/config/have_gmtime_r.h"
#    define config_get_now gmtime_r_get_now
#  elif SUPPORT_WINDOWS_GET_NOW
#    include "private/config/windows_get_now_supported.h"
#    define config_get_now windows_get_now
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GET_NOW_H */
