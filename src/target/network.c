// SPDX-License-Identifier: Apache-2.0

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

#include <stddef.h>
#include <stumpless/target.h>
#include <stumpless/target/network.h>
#include "private/target/network.h"

void
stumpless_close_network_target( struct stumpless_target *target );

struct stumpless_target *
stumpless_open_network_target( const char *name,
                               const char *target,
                               enum stumpless_network_protocol network,
                               enum stumpless_transport_protocol transport,
                               int options,
                               int default_facility ) {
  return NULL;
}

struct stumpless_target *
stumpless_open_tcp4_target( const char *name,
                            const char *target,
                            int options,
                            int default_facility ) {
  return stumpless_open_network_target( name,
                                        target,
                                        STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                        STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );
}

struct stumpless_target *
stumpless_open_udp4_target( const char *name,
                            const char *target,
                            int options,
                            int default_facility ) {
  return stumpless_open_network_target( name,
                                        target,
                                        STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                        STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );
}

/* private definitions */

void
destroy_network_target( struct network_target *target ) {
  return;
}

struct network_target *
new_network_target( const char *target,
                    enum stumpless_network_protocol network,
                    enum stumpless_transport_protocol transport ) {
  return NULL;
}

int
sendto_network_target( struct network_target *target,
                       const char *msg,
                       size_t msg_length ) {
  return -1;
}
