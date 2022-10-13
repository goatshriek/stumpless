// SPDX-License-Identifier: Apache-2.0

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

#include <stddef.h>
#include <stumpless/target.h>
#include <stumpless/target/network.h>
#include "private/config/locale/wrapper.h"
#include "private/error.h"

void
stumpless_close_network_target( struct stumpless_target *target ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
}

const char *
stumpless_get_destination( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

const char *
stumpless_get_transport_port( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

size_t
stumpless_get_udp_max_message_size( struct stumpless_target *target ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return 0;
}

struct stumpless_target *
stumpless_new_network_target( const char *name,
                              enum stumpless_network_protocol network,
                              enum stumpless_transport_protocol transport ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_new_tcp4_target( const char *name ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_new_tcp6_target( const char *name ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_new_udp4_target( const char *name ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_new_udp6_target( const char *name ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_network_target( const char *name,
                               const char *destination,
                               enum stumpless_network_protocol network,
                               enum stumpless_transport_protocol transport,
                               int options,
                               int default_facility ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_tcp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_tcp6_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_udp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_udp6_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_set_destination( struct stumpless_target *target,
                           const char *destination ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_set_transport_port( struct stumpless_target *target,
                              const char *port ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_set_udp_max_message_size( struct stumpless_target *target,
                                    size_t max_msg_size ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return NULL;
}

enum stumpless_network_protocol
stumpless_get_network_protocol( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return -1;
}

enum stumpless_transport_protocol
stumpless_get_transport_protocol( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_NETWORK_TARGETS_UNSUPPORTED );
  return -1;
}
