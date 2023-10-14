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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_WEL_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_WEL_H

#  include <stumpless/config.h>

#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include <stumpless/target/wel.h>
#    include "private/config/wel_supported.h"
#    include "private/target/wel.h"
#    define config_close_wel_target stumpless_close_wel_target
#    define config_sendto_wel_target sendto_wel_target
#    define config_copy_wel_data copy_wel_data
#    define config_destroy_wel_data destroy_wel_data
#    define config_initialize_wel_data initialize_wel_data
#    define config_set_entry_wel_type set_entry_wel_type
#  else
#    include <stdbool.h>
#    include "private/target.h"
#    define config_close_wel_target close_unsupported_target
#    define config_sendto_wel_target send_entry_and_msg_to_unsupported_target
#    define config_copy_wel_data( DESTINATION, SOURCE ) ( DESTINATION )
#    define config_destroy_wel_data( ENTRY ) ( ( void ) 0 )
#    define config_initialize_wel_data( ENTRY ) ( true )
#    define config_set_entry_wel_type( ENTRY, SEVERITY ) ( ( void ) 0 )
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_WEL_H */
