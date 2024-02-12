/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2022-2024 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_NETWORK_SUPPORTED_H
#define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_NETWORK_SUPPORTED_H

#include <stumpless/config.h>
#include "private/config.h"


#ifndef HAVE_SYS_SOCKET_H
#  ifdef HAVE_WINSOCK2_H
#    include "private/windows_wrapper.h"
#  endif
#endif


/* definition of network target functions */
#ifdef HAVE_SYS_SOCKET_H
#  define config_socket_handle_t int
#  include "private/config/have_sys_socket.h"
#  define config_close_tcp4_target sys_socket_close_network_target
#  define config_close_tcp6_target sys_socket_close_network_target
#  define config_close_udp4_target sys_socket_close_network_target
#  define config_close_udp6_target sys_socket_close_network_target
#  define config_init_tcp4 sys_socket_init_network_target
#  define config_init_tcp6 sys_socket_init_network_target
#  define config_init_udp4 sys_socket_init_network_target
#  define config_init_udp6 sys_socket_init_network_target
#  define config_network_provider_free_all() ( ( void ) 0 )
#  define config_open_tcp4_target sys_socket_open_tcp4_target
#  define config_open_tcp6_target sys_socket_open_tcp6_target
#  define config_open_udp4_target sys_socket_open_udp4_target
#  define config_open_udp6_target sys_socket_open_udp6_target
#  define config_reopen_tcp4_target sys_socket_reopen_tcp4_target
#  define config_reopen_tcp6_target sys_socket_reopen_tcp6_target
#  define config_reopen_udp4_target sys_socket_reopen_udp4_target
#  define config_reopen_udp6_target sys_socket_reopen_udp6_target
#  define config_sendto_tcp4_target sys_socket_sendto_tcp_target
#  define config_sendto_tcp6_target sys_socket_sendto_tcp_target
#  define config_sendto_udp4_target sys_socket_sendto_udp_target
#  define config_sendto_udp6_target sys_socket_sendto_udp_target
#  define config_tcp4_is_open sys_socket_network_target_is_open
#  define config_tcp6_is_open sys_socket_network_target_is_open
#  define config_udp4_is_open sys_socket_network_target_is_open
#  define config_udp6_is_open sys_socket_network_target_is_open
#elif HAVE_WINSOCK2_H
#  define config_socket_handle_t SOCKET
#  include "private/config/have_winsock2.h"
#  define config_close_tcp4_target winsock2_close_network_target
#  define config_close_tcp6_target winsock2_close_network_target
#  define config_close_udp4_target winsock2_close_network_target
#  define config_close_udp6_target winsock2_close_network_target
#  define config_init_tcp4 winsock2_init_network_target
#  define config_init_tcp6 winsock2_init_network_target
#  define config_init_udp4 winsock2_init_network_target
#  define config_init_udp6 winsock2_init_network_target
#  define config_network_provider_free_all winsock2_free_all
#  define config_open_tcp4_target winsock2_open_tcp4_target
#  define config_open_tcp6_target winsock2_open_tcp6_target
#  define config_open_udp4_target winsock2_open_udp4_target
#  define config_open_udp6_target winsock2_open_udp6_target
#  define config_reopen_tcp4_target winsock2_reopen_tcp4_target
#  define config_reopen_tcp6_target winsock2_reopen_tcp6_target
#  define config_reopen_udp4_target winsock2_reopen_udp4_target
#  define config_reopen_udp6_target winsock2_reopen_udp6_target
#  define config_sendto_tcp4_target winsock2_sendto_tcp_target
#  define config_sendto_tcp6_target winsock2_sendto_tcp_target
#  define config_sendto_udp4_target winsock2_sendto_udp_target
#  define config_sendto_udp6_target winsock2_sendto_udp_target
#  define config_tcp4_is_open winsock2_network_target_is_open
#  define config_tcp6_is_open winsock2_network_target_is_open
#  define config_udp4_is_open winsock2_network_target_is_open
#  define config_udp6_is_open winsock2_network_target_is_open
#endif


/* definition of network target support */
#ifdef STUMPLESS_NETWORK_TARGETS_SUPPORTED
#  include <stumpless/target/network.h>
#  include "private/target/network.h"
#  define config_close_network_target stumpless_close_network_target
#  define config_network_free_all network_free_all
#  define config_network_target_is_open network_target_is_open
#  define config_open_network_target open_network_target
#  define config_sendto_network_target sendto_network_target
#else
#  include "private/target.h"
#  define config_close_network_target close_unsupported_target
#  define config_network_free_all() ( ( void ) 0 )
#  define config_network_target_is_open unsupported_target_is_open
#  define config_open_network_target open_unsupported_target
#  define config_sendto_network_target sendto_unsupported_target
#endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_NETWORK_SUPPORTED_H */
