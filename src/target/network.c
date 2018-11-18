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

#include "private/config/wrapper.h"

#include <stddef.h>
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/target/network.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/network.h"

void
stumpless_close_network_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return;
  }

  destroy_network_target( target->id );
  destroy_target( target );
}
size_t
stumpless_get_udp_max_message_size( struct stumpless_target *target ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "max message size is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  if( net_target->transport != STUMPLESS_UDP_TRANSPORT_PROTOCOL ) {
    raise_target_incompatible( "max message size is only valid for UDP targets" );
    goto fail;
  }

  return net_target->max_msg_size;

fail:
  return 0;
}

struct stumpless_target *
stumpless_open_network_target( const char *name,
                               const char *destination,
                               enum stumpless_network_protocol network,
                               enum stumpless_transport_protocol transport,
                               int options,
                               int default_facility ) {
  struct stumpless_target *target;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  if( !destination ) {
    raise_argument_empty( "destination is NULL" );
    goto fail;
  }

  target = new_target( STUMPLESS_NETWORK_TARGET,
                       name,
                       strlen( name ),
                       options,
                       default_facility );

  if( !target ) {
    goto fail;
  }

  target->id = new_network_target( destination, network, transport );
  if( !target->id ) {
    goto fail_id;
  }

  stumpless_set_current_target( target );
  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
}

struct stumpless_target *
stumpless_open_tcp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {
  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                        STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );
}

struct stumpless_target *
stumpless_open_udp4_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {
  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                        STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );
}

struct stumpless_target *
stumpless_set_udp_max_message_size( struct stumpless_target *target,
                                    size_t max_msg_size ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "max message size is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  if( net_target->transport != STUMPLESS_UDP_TRANSPORT_PROTOCOL ) {
    raise_target_incompatible( "max message size is only valid for UDP targets" );
    goto fail;
  }

  net_target = target->id;
  net_target->max_msg_size = max_msg_size;

  return target;

fail:
  return NULL;
}

/* private definitions */

void
destroy_network_target( struct network_target *target ) {

  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
    config_close_tcp4_target( &target->details.tcp4 );

  } else {
    config_close_udp4_target( &target->details.udp4 );

  }

  free_mem( target );
}

struct network_target *
new_network_target( const char *destination,
                    enum stumpless_network_protocol network,
                    enum stumpless_transport_protocol transport ) {
  struct network_target *target;
  struct tcp4_details *tcp4_result;
  struct udp4_details *udp4_result;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  if( network != STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
    raise_network_protocol_unsupported(  );
    goto fail_details;
  }

  switch( transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      tcp4_result = config_open_tcp4_target( &target->details.tcp4,
                                             destination );
      if( !tcp4_result ) {
        goto fail_details;
      }
      break;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      udp4_result = config_open_udp4_target( &target->details.udp4,
                                             destination );
      if( !udp4_result ) {
        goto fail_details;
      }
      break;

    default:
      raise_transport_protocol_unsupported(  );
      goto fail_details;

  }

  target->network = network;
  target->transport = transport;
  target->max_msg_size = STUMPLESS_DEFAULT_UDP_MAX_MESSAGE_SIZE;
  return target;

fail_details:
  free_mem( target );
fail:
  return NULL;
}

int
sendto_network_target( struct network_target *target,
                       const char *msg,
                       size_t msg_length ) {
  if( target->transport == STUMPLESS_TCP_TRANSPORT_PROTOCOL ) {
    return config_sendto_tcp4_target( &target->details.tcp4, msg, msg_length );

  } else {
    return config_sendto_udp4_target( &target->details.udp4, msg, msg_length );

  }
}
