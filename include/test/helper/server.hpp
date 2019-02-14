/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2019 Joel E. Anderson
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

#ifndef __STUMPLESS_TEST_HELPER_SERVER_HPP
#  define __STUMPLESS_TEST_HELPER_SERVER_HPP

#  ifdef _WIN32
#  include <winsock2.h>
#    define BAD_HANDLE INVALID_SOCKET
typedef SOCKET socket_handle_t;
#  else
#    define BAD_HANDLE -1
typedef int socket_handle_t;
#  endif

socket_handle_t
open_tcp_server_socket( int af, const char *dest, const char *port );

socket_handle_t
open_udp_server_socket( int af, const char *dest, const char *port );

socket_handle_t
accept_tcp_connection( socket_handle_t handle );

#  ifdef _WIN32
void
recv_from_handle( socket_handle_t handle, char *buff, int buff_len );
#  else
void
recv_from_handle( socket_handle_t handle, char *buff, size_t buff_len );
#endif

void
close_server_socket( socket_handle_t handle );

#endif /* __STUMPLESS_TEST_HELPER_SERVER_HPP */
