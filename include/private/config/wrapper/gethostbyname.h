/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2023 Joel E. Anderson
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
 * A wrapper for either gethostbyname or gethostbyname2.
 */

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETHOSTBYNAME_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETHOSTBYNAME_H

#  include "private/config.h"

/* definition of config_gethostbyname */
#  ifdef HAVE_GETHOSTBYNAME2
#    include <netdb.h>
#    define config_gethostbyname gethostbyname2
#  elif HAVE_GETHOSTBYNAME
#    include <netdb.h>
#    define config_gethostbyname( NAME, DOMAIN ) gethostbyname( ( NAME ) )
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_GETHOSTBYNAME_H */
