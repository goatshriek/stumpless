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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_WSTRING_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_WSTRING_H

#  include "private/config.h"

/* definition of config_copy_wstring_to_cstring */
#  ifdef HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_copy_wstring_to_cstring  windows_copy_wstring_to_cstring
#  elif !defined HAVE_WCSRTOMBS_S
#    include "private/config/no_wcsrtombs_s.h"
#    define config_copy_wstring_to_cstring no_wcsrtombs_s_copy_wstring_to_cstring
#  else
#    include "private/config/fallback.h"
#    define config_copy_wstring_to_cstring  fallback_copy_wstring_to_cstring
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_WSTRING_H */
