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


#ifndef __STUMPLESS_PRIVATE_CONFIG_HAVE_WINSOCK2_H
#  define __STUMPLESS_PRIVATE_CONFIG_HAVE_WINSOCK2_H

#  include "private/target/network.h"

void
winsock2_close_tcp4_target( struct tcp4_details *details );

void
winsock2_close_udp4_target( struct udp4_details *details );

int winsock2_gethostname( char *buffer, size_t namelen );

struct tcp4_details *
winsock2_open_tcp4_target( struct tcp4_details *details,
                           const char *destination,
                           const char *port );

struct udp4_details *
winsock2_open_udp4_target( struct udp4_details *details,
                           const char *destination,
                           const char *port );

int
winsock2_sendto_tcp4_target( struct tcp4_details *details,
                             const char *msg,
                             size_t msg_length );

int
winsock2_sendto_udp4_target( struct udp4_details *details,
                             const char *msg,
                             size_t msg_length );

struct tcp4_details *
winsock2_set_tcp4_port( struct tcp4_details *details,
                        const char *destination,
                        const char *port );

struct udp4_details *
winsock2_set_udp4_port( struct udp4_details *details,
                        const char *destination,
                        const char *port );

#endif /* __STUMPLESS_PRIVATE_CONFIG_HAVE_WINSOCK2_H */
