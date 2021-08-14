/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_JOURNALD_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_JOURNALD_H

#  include <stumpless/config.h>

#  ifdef STUMPLESS_JOURNALD_TARGETS_SUPPORTED
#    include <stumpless/target/journald.h>
#    include "private/config/journald_supported.h"
#    include "private/target/journald.h"
#    define config_close_journald_target stumpless_close_journald_target
#    define config_init_journald_element journald_init_journald_element
#    define config_init_journald_param journald_init_journald_param
#    define config_journald_free_thread journald_free_thread
#    define config_send_entry_to_journald_target send_entry_to_journald_target
#  else
#    include "private/target.h"
#    define config_close_journald_target close_unsupported_target
#    define config_init_journald_element( ELEMENT ) ( ( void ) 0 )
#    define config_init_journald_param( PARAM ) ( ( void ) 0 )
#    define config_journald_free_thread(  ) ( ( void ) 0 )
#    define config_send_entry_to_journald_target send_entry_to_unsupported_target
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_JOURNALD_H */
