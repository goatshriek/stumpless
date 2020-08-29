/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2018-2020 Joel E. Anderson
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


/* definition of network target functions */
#  ifdef HAVE_SYS_SOCKET_H
#    define config_socket_handle_t int
#    include "private/config/have_sys_socket.h"
#    define config_close_tcp4_target sys_socket_close_network_target
#    define config_close_tcp6_target sys_socket_close_network_target
#    define config_close_udp4_target sys_socket_close_network_target
#    define config_close_udp6_target sys_socket_close_network_target
#    define config_init_tcp4 sys_socket_init_network_target
#    define config_init_tcp6 sys_socket_init_network_target
#    define config_init_udp4 sys_socket_init_network_target
#    define config_init_udp6 sys_socket_init_network_target
#    define config_network_cleanup() ( ( void ) 0 )
#    define config_open_tcp4_target sys_socket_open_tcp4_target
#    define config_open_tcp6_target sys_socket_open_tcp6_target
#    define config_open_udp4_target sys_socket_open_udp4_target
#    define config_open_udp6_target sys_socket_open_udp6_target
#    define config_reopen_tcp4_target sys_socket_reopen_tcp4_target
#    define config_reopen_tcp6_target sys_socket_reopen_tcp6_target
#    define config_reopen_udp4_target sys_socket_reopen_udp4_target
#    define config_reopen_udp6_target sys_socket_reopen_udp6_target
#    define config_sendto_tcp4_target sys_socket_sendto_target
#    define config_sendto_tcp6_target sys_socket_sendto_target
#    define config_sendto_udp4_target sys_socket_sendto_target
#    define config_sendto_udp6_target sys_socket_sendto_target
#    define config_tcp4_is_open sys_socket_network_target_is_open
#    define config_tcp6_is_open sys_socket_network_target_is_open
#    define config_udp4_is_open sys_socket_network_target_is_open
#    define config_udp6_is_open sys_socket_network_target_is_open
#  elif HAVE_WINSOCK2_H
#    include <winsock2.h>
#    define config_socket_handle_t SOCKET
#    include "private/config/have_winsock2.h"
#    define config_close_tcp4_target winsock2_close_network_target
#    define config_close_tcp6_target winsock2_close_network_target
#    define config_close_udp4_target winsock2_close_network_target
#    define config_close_udp6_target winsock2_close_network_target
#    define config_init_tcp4 winsock2_init_network_target
#    define config_init_tcp6 winsock2_init_network_target
#    define config_init_udp4 winsock2_init_network_target
#    define config_init_udp6 winsock2_init_network_target
#    define config_network_cleanup() winsock2_cleanup()
#    define config_open_tcp4_target winsock2_open_tcp4_target
#    define config_open_tcp6_target winsock2_open_tcp6_target
#    define config_open_udp4_target winsock2_open_udp4_target
#    define config_open_udp6_target winsock2_open_udp6_target
#    define config_reopen_tcp4_target winsock2_reopen_tcp4_target
#    define config_reopen_tcp6_target winsock2_reopen_tcp6_target
#    define config_reopen_udp4_target winsock2_reopen_udp4_target
#    define config_reopen_udp6_target winsock2_reopen_udp6_target
#    define config_sendto_tcp4_target winsock2_sendto_target
#    define config_sendto_tcp6_target winsock2_sendto_target
#    define config_sendto_udp4_target winsock2_sendto_target
#    define config_sendto_udp6_target winsock2_sendto_target
#    define config_tcp4_is_open winsock2_network_target_is_open
#    define config_tcp6_is_open winsock2_network_target_is_open
#    define config_udp4_is_open winsock2_network_target_is_open
#    define config_udp6_is_open winsock2_network_target_is_open
#  endif


/* definition of network target support */
#  ifdef STUMPLESS_NETWORK_TARGETS_SUPPORTED
#    include <stumpless/target/network.h>
#    include "private/target/network.h"
#    define config_close_network_target stumpless_close_network_target
#    define config_network_free_all network_free_all
#    define config_network_target_is_open network_target_is_open
#    define config_open_network_target open_network_target
#    define config_sendto_network_target sendto_network_target
#  else
#    include "private/target.h"
#    define config_close_network_target close_unsupported_target
#    define config_network_free_all() ( ( void ) 0 )
#    define config_network_target_is_open unsupported_target_is_open
#    define config_open_network_target open_unsupported_target
#    define config_sendto_network_target sendto_unsupported_target
#  endif


/* definition of config_open_default_target */
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include "private/config/wel_supported.h"
#    define config_open_default_target wel_open_default_target
#    define config_close_default_target stumpless_close_wel_target
#  elif STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include "private/config/socket_supported.h"
#    define config_open_default_target socket_open_default_target
#    define config_close_default_target stumpless_close_socket_target
#  else
#    include <stumpless/target/file.h>
#    include "private/target/file.h"
#    define config_open_default_target file_open_default_target
#    define config_close_default_target stumpless_close_file_target
#  endif


/* definition of config_sendto_socket_target */
#  ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
#    include <stumpless/target/socket.h>
#    include "private/target/socket.h"
#    define config_close_socket_target stumpless_close_socket_target
#    define config_sendto_socket_target sendto_socket_target
#  else
#    include "private/target.h"
#    define config_close_socket_target close_unsupported_target
#    define config_sendto_socket_target sendto_unsupported_target
#  endif


/* definition of wel functions */
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include <stumpless/target/wel.h>
#    include "private/config/wel_supported.h"
#    include "private/target/wel.h"
#    define config_close_wel_target stumpless_close_wel_target
#    define config_send_entry_to_wel_target send_entry_to_wel_target
#    define config_copy_wel_data copy_wel_data
#    define config_destroy_wel_data destroy_wel_data
#    define config_initialize_wel_data initialize_wel_data
#    define config_set_entry_wel_type set_entry_wel_type
#  else
#    include <stdbool.h>
#    include "private/target.h"
#    define config_close_wel_target close_unsupported_target
#    define config_send_entry_to_wel_target send_entry_to_unsupported_target
#    define config_copy_wel_data( DESTINATION, SOURCE ) ( DESTINATION )
#    define config_destroy_wel_data( ENTRY ) ( ( void ) 0 )
#    define config_initialize_wel_data( ENTRY ) ( true )
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


/* definition of config_format_string */
#  ifdef HAVE_VSNPRINTF_S
#    include "private/config/have_vsnprintf_s.h"
#    define config_format_string vsnprintf_s_format_string
#  else
#    include "private/config/no_vsnprintf_s.h"
#    define config_format_string no_vsnprintf_s_format_string
#  endif


/* definition of config_get_now */
#  ifdef HAVE_GMTIME_R
#    include "private/config/have_gmtime_r.h"
#    define config_get_now gmtime_r_get_now
#  elif SUPPORT_WINDOWS_GET_NOW
#    include "private/config/support_windows_get_now.h"
#    define config_get_now windows_get_now
#  endif


/* definition of config_gethostname */
#  ifdef HAVE_UNISTD_GETHOSTNAME
#    include "private/config/have_unistd_gethostname.h"
#    define config_gethostname(buffer, namelen) unistd_gethostname((buffer), (namelen))
#  elif HAVE_WINSOCK2_H
#    include "private/config/have_winsock2.h"
#    define config_gethostname(buffer, namelen) winsock2_gethostname((buffer), (namelen))
#  else
#    include "private/config/fallback.h"
#    define config_gethostname(buffer, namelen) fallback_gethostname((buffer), (namelen))
#  endif


/* definition of config_getpagesize */
#  ifdef SUPPORT_UNISTD_SYSCONF_GETPAGESIZE
#    include "private/config/support_unistd_sysconf_getpagesize.h"
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


/* definition of config_getpid */
#  ifdef HAVE_UNISTD_H
#    include "private/config/have_unistd.h"
#    define config_getpid unistd_getpid
#  elif HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    define config_getpid windows_getpid
#  else
#    include "private/config/fallback.h"
#    define config_getpid fallback_getpid
#  endif


#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_H */
