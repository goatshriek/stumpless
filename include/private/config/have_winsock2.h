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
 * Runs WSACleanup if WSA has already been started.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of lock schemes that may be left locked.
 *
 * @since release v2.2.0
 *
 * @return The return code from WSACleanup.
 */
int
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

/**
 * Send a message to a TCP-based network target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks that may be left locked.
 *
 * @since release v2.2.0
 *
 * @param target The network target to send the message to.
 *
 * @param msg The message to send to the target.
 *
 * @param msg_size The size of the message, in bytes.
 *
 * @return A positive value if no error was encountered, -1 otherwise. If an
 * error is encountered, an error code is set appropriately.
 */
int
winsock2_sendto_tcp_target( const struct network_target *target,
                            const char *msg,
                            size_t msg_size );

/**
 * Send a message to a UDP-based network target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of locks that may be left locked.
 *
 * @since release v2.2.0
 *
 * @param target The network target to send the message to.
 *
 * @param msg The message to send to the target.
 *
 * @param msg_size The size of the message, in bytes.
 *
 * @return A positive value if no error was encountered, -1 otherwise. If an
 * error is encountered, an error code is set appropriately.
 */
int
winsock2_sendto_udp_target( const struct network_target *target,
                            const char *msg,
                            size_t msg_size );

int
winsock2_network_target_is_open( const struct network_target *target );

#endif /* __STUMPLESS_PRIVATE_CONFIG_HAVE_WINSOCK2_H */
