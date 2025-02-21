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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_SOCKET_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_SOCKET_H

#  include <stumpless/config.h>
#  include "private/config.h"

#  ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include <stumpless/target/socket.h>
#    include "private/target/socket.h"
#    define config_close_socket_target stumpless_close_socket_target
#    define config_open_socket_target open_socket_target
#    define config_sendto_socket_target sendto_socket_target
#    define config_socket_target_is_open socket_target_is_open
#  else
#    include "private/target.h"
#    define config_close_socket_target close_unsupported_target
#    define config_open_socket_target open_unsupported_target
#    define config_sendto_socket_target sendto_unsupported_target
#    define config_socket_target_is_open unsupported_target_is_open
#  endif

#  ifdef SUPPORT_ABSTRACT_SOCKET_NAMES
#    include "private/config/abstract_socket_names_supported.h"
#    define config_get_local_socket_name abstract_socket_names_get_local_socket_name
#  else
#    include "private/config/abstract_socket_names_unsupported.h"
#    define config_get_local_socket_name no_abstract_socket_names_get_local_socket_name
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_SOCKET_H */
