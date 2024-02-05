/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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

#  include <stddef.h>
#  include "private/target/network.h"

void
winsock2_close_network_target( const struct network_target *target );

/**
 * TODO
 */
void
winsock2_free_all( void );

struct network_target *
winsock2_init_network_target( struct network_target *target );

struct network_target *
winsock2_open_tcp4_target( struct network_target *target );

struct network_target *
winsock2_open_tcp6_target( struct network_target *target );

struct network_target *
winsock2_open_udp4_target( struct network_target *target );

struct network_target *
winsock2_open_udp6_target( struct network_target *target );

struct network_target *
winsock2_reopen_tcp4_target( struct network_target *target );

struct network_target *
winsock2_reopen_tcp6_target( struct network_target *target );

struct network_target *
winsock2_reopen_udp4_target( struct network_target *target );

struct network_target *
winsock2_reopen_udp6_target( struct network_target *target );

int
winsock2_sendto_tcp_target( struct network_target *target,
                            const char *msg,
                            size_t msg_length );

int
winsock2_sendto_udp_target( struct network_target *target,
                            const char *msg,
                            size_t msg_length );

struct network_target *
winsock2_set_network_port( struct network_target *target, const char *port );

int
winsock2_network_target_is_open( const struct network_target *target );

#endif /* __STUMPLESS_PRIVATE_CONFIG_HAVE_WINSOCK2_H */
