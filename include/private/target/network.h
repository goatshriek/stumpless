/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2019-2020 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_TARGET_NETWORK_H
#  define __STUMPLESS_PRIVATE_TARGET_NETWORK_H


#  include <stddef.h>
#  include <stumpless/target.h>
#  include <stumpless/target/network.h>
#  include "private/config.h"
#  include "private/config/wrapper.h"
#  include "private/config/wrapper/thread_safety.h"

struct network_target {
  const char *destination;
  enum stumpless_network_protocol network;
  enum stumpless_transport_protocol transport;
  size_t max_msg_size;
  const char *port;
  config_socket_handle_t handle;
#if defined( STUMPLESS_THREAD_SAFETY_SUPPORTED ) \
    && !defined( HAVE_SYS_SOCKET_H ) \
    && defined( HAVE_WINSOCK2_H )
/**
 * A mutex to coordinate writes to this target's socket. This is only needed in
 * winsock-based network targets, where the send function is not thread-safe
 * with the same descriptor on stream-oriented targets, which can lead to
 * message interleaving.
 */
  config_mutex_t socket_mutex;
#endif
};

void
destroy_network_target( const struct network_target *target );

void
network_free_all( void );

int
network_target_is_open( const struct stumpless_target *target );

struct network_target *
new_network_target( enum stumpless_network_protocol network,
                    enum stumpless_transport_protocol transport );

struct stumpless_target *
open_network_target( struct stumpless_target *target );

struct network_target *
open_new_network_target( const char *destination,
                         enum stumpless_network_protocol network,
                         enum stumpless_transport_protocol transport );

int
sendto_network_target( struct network_target *target,
                       const char *msg,
                       size_t msg_length );

#endif /* __STUMPLESS_PRIVATE_TARGET_NETWORK_H */
