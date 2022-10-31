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

#  include "private/config.h"


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

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H */
