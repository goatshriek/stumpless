/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2018 Joel E. Anderson
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


/* definition of config_sendto_network_target and config_network_free_all */
#  ifdef STUMPLESS_NETWORK_TARGETS_SUPPORTED
#    include "private/target/network.h"
#    define config_sendto_network_target sendto_network_target
#    ifdef HAVE_SYS_SOCKET_H
#      include "private/config/have_sys_socket.h"
#      define config_network_free_all() sys_socket_free_all()
#    elif HAVE_WINSOCK2_H
#      include "private/config/have_winsock2.h"
#      define config_network_free_all() winsock2_free_all()
#    endif
#  else
#    include "private/target.h"
#    define config_sendto_network_target sendto_unsupported_target
#    define config_network_free_all() ( ( void ) 0 )
#  endif


/* definition of config_sendto_socket_target */
#  ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include "private/target/socket.h"
#    define config_sendto_socket_target sendto_socket_target
#  else
#    include "private/target.h"
#    define config_sendto_socket_target sendto_unsupported_target
#  endif


/* definition of config_sendto_wel_target */
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include "private/config/wel_supported.h"
#    include "private/target/wel.h"
#    define config_send_entry_to_wel_target send_entry_to_wel_target
#    define config_destroy_insertion_params destroy_insertion_params
#    define config_initialize_insertion_params initialize_insertion_params
#    define config_set_entry_wel_type set_entry_wel_type
#  else
#    include "private/target.h"
#    define config_send_entry_to_wel_target send_entry_to_unsupported_target
#    define config_destroy_insertion_params( ENTRY ) ( ( void ) 0 )
#    define config_initialize_insertion_params( ENTRY ) ( ( void ) 0 )
#    define config_set_entry_wel_type( ENTRY, SEVERITY ) ( ( void ) 0 )
#  endif


/* definition of config_fopen */
#  ifdef HAVE_FOPEN_S
#    include "private/config/have_fopen_s.h"
#    define config_fopen fopen_s_fopen
#  else
#    include <stdio.h>
#    define config_fopen fopen
#  endif


/* definition of config_get_now */
#  ifdef HAVE_GMTIME_R
#    include "private/config/have_gmtime_r.h"
#    define config_get_now gmtime_r_get_now
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_get_now windows_get_now
#  endif


/* definition of config_gethostname */
#  ifdef HAVE_UNISTD_H
#    include "private/config/have_unistd.h"
#    define config_gethostname(buffer, namelen) unistd_gethostname((buffer), (namelen))
#  elif HAVE_WINSOCK2_H
#    include "private/config/have_winsock2.h"
#    define config_gethostname(buffer, namelen) winsock2_gethostname((buffer), (namelen))
#  endif


/* definition of config_getpagesize */
#  ifdef HAVE_UNISTD_H
#    include "private/config/have_unistd.h"
#    define config_getpagesize unistd_getpagesize
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_getpagesize windows_getpagesize
#  endif


/* definition of config_getpid */
#  ifdef HAVE_UNISTD_H
#    include "private/config/have_unistd.h"
#    define config_getpid unistd_getpid
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_getpid windows_getpid
#  endif


/* definition of network target functions */
#  ifdef HAVE_SYS_SOCKET_H
#    include "private/config/have_sys_socket.h"
#    define config_close_tcp4_target sys_socket_close_tcp4_target
#    define config_close_udp4_target sys_socket_close_udp4_target
#    define config_open_tcp4_target sys_socket_open_tcp4_target
#    define config_open_udp4_target sys_socket_open_udp4_target
#    define config_reopen_tcp4_target sys_socket_reopen_tcp4_target
#    define config_reopen_udp4_target sys_socket_reopen_udp4_target
#    define config_sendto_tcp4_target sys_socket_sendto_tcp4_target
#    define config_sendto_udp4_target sys_socket_sendto_udp4_target
#    define config_set_tcp4_port sys_socket_set_tcp4_port
#    define config_set_udp4_port sys_socket_set_udp4_port
#  elif HAVE_WINSOCK2_H
#    include "private/config/have_winsock2.h"
#    define config_close_tcp4_target winsock2_close_tcp4_target
#    define config_close_udp4_target winsock2_close_udp4_target
#    define config_open_tcp4_target winsock2_open_tcp4_target
#    define config_open_udp4_target winsock2_open_udp4_target
#    define config_reopen_tcp4_target winsock2_reopen_tcp4_target
#    define config_reopen_udp4_target winsock2_reopen_udp4_target
#    define config_sendto_tcp4_target winsock2_sendto_tcp4_target
#    define config_sendto_udp4_target winsock2_sendto_udp4_target
#    define config_set_tcp4_port winsock2_set_tcp4_port
#    define config_set_udp4_port winsock2_set_udp4_port
#  endif


#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H */
