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

#ifndef __STUMPLESS_PRIVATE_TARGET_NETWORK_H
#  define __STUMPLESS_PRIVATE_TARGET_NETWORK_H

#  include "private/config.h"

#  include <stddef.h>
#  include <stumpless/target/network.h>

#  ifdef HAVE_SYS_SOCKET_H
#    include <sys/types.h>
#    include <sys/socket.h>
#  elif HAVE_WINSOCK2_H
#    include <winsock2.h>
#  endif

struct tcp4_details {
#  ifdef HAVE_SYS_SOCKET_H
  int handle;
  struct sockaddr_storage target_addr;
#  elif HAVE_WINSOCK2_H
  SOCKET handle;
  SOCKADDR_STORAGE target_addr;
#  endif
};

struct udp4_details {
#  ifdef HAVE_SYS_SOCKET_H
  int handle;
  struct sockaddr_storage target_addr;
#  elif HAVE_WINSOCK2_H
  SOCKET handle;
  SOCKADDR_STORAGE target_addr;
#  endif
};

struct network_target {
  enum stumpless_network_protocol network;
  enum stumpless_transport_protocol transport;
  union {
    struct tcp4_details tcp4;
    struct udp4_details udp4;
  } details;
};

void
destroy_network_target( struct network_target *target );

struct network_target *
new_network_target( const char *destination,
                    enum stumpless_network_protocol network,
                    enum stumpless_transport_protocol transport );

int
sendto_network_target( struct network_target *target,
                       const char *msg,
                       size_t msg_length );

#endif /* __STUMPLESS_PRIVATE_TARGET_NETWORK_H */
