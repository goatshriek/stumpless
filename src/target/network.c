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
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/strhelper.h"
#include "private/target.h"
#include "private/target/network.h"

static
void
destroy_ipv4( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      config_close_tcp4_target( &target->details.tcp4 );
      break;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      config_close_udp4_target( &target->details.udp4 );
      break;

    default:
      return;

  }
}

static
void
destroy_ipv6( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      config_close_tcp6_target( &target->details.tcp6 );
      break;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      config_close_udp6_target( &target->details.udp6 );
      break;

    default:
      return;

  }
}

static
const char *
get_ipv4_transport_port( const struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return target->details.tcp4.port;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return target->details.udp4.port;

    default:
      raise_target_incompatible( "transport port is not valid for this"
                                 " network target" );
      return NULL;

  }
}

static
const char *
get_ipv6_transport_port( const struct network_target *target ) {
  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return target->details.tcp6.port;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return target->details.udp6.port;

    default:
      raise_target_incompatible( "transport port is not valid for this"
                                 " network target" );
      return NULL;

  }
}

static
void *
init_ipv4( enum stumpless_transport_protocol transport,
           struct network_target *target ) {

  switch( transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      config_init_tcp4( &target->details.tcp4 );
      return &target->details.tcp4;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      config_init_udp4( &target->details.udp4 );
      return &target->details.udp4;

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

  }
}

static
void *
init_ipv6( enum stumpless_transport_protocol transport,
           struct network_target *target ) {

  switch( transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      config_init_tcp6( &target->details.tcp6 );
      return &target->details.tcp6;

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      config_init_udp6( &target->details.udp6 );
      return &target->details.udp6;

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

  }
}

static
int
ipv4_is_open( const struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_tcp4_is_open( &target->details.tcp4 );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_udp4_is_open( &target->details.udp4 );

    default:
      return 0;

  }
}

static
int
ipv6_is_open( const struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_tcp6_is_open( &target->details.tcp6 );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_udp6_is_open( &target->details.udp6 );

    default:
      return 0;

  }
}

static
void *
open_ipv4_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_open_tcp4_target( target );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_open_udp4_target( target );,

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

    }
}

static
void *
open_ipv6_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_open_tcp6_target( target );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_open_udp6_target( target );,

    default:
      raise_transport_protocol_unsupported(  );
      return NULL;

    }
}

static
void *
reopen_ipv4_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_reopen_tcp4_target( target );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_reopen_udp4_target( target );

    default:
      raise_target_incompatible( "destination is not valid for this network"
                                 " target" );
      return NULL;

  }
}

static
void *
reopen_ipv6_target( struct network_target *target ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_reopen_tcp6_target( target );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_reopen_udp6_target( target );

    default:
      raise_target_incompatible( "destination is not valid for this network"
                                 " target" );
      return NULL;

  }
}

static
void *
set_ipv4_port( struct network_target *target, const char *port ) {

  switch( target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_set_tcp4_port( &target->details.tcp4,
                                   target->destination,
                                   port );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_set_udp4_port( &target->details.udp4,
                                   target->destination,
                                   port );

    default:
      raise_target_incompatible( "transport port is not valid for this network"
                                 " target" );
      return NULL;

  }
}

static
void *
set_ipv6_port( struct network_target *net_target, const char *port ) {

  switch( net_target->transport ) {

    case STUMPLESS_TCP_TRANSPORT_PROTOCOL:
      return config_set_tcp6_port( &net_target->details.tcp6,
                                   net_target->destination,
                                   port );

    case STUMPLESS_UDP_TRANSPORT_PROTOCOL:
      return config_set_udp6_port( &net_target->details.udp6,
                                   net_target->destination,
                                   port );

    default:
      raise_target_incompatible( "transport port is not valid for this network"
                                 " target" );
      return NULL;

  }
}

/* public definitions */

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

const char *
stumpless_get_destination( const struct stumpless_target *target ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "destination is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  return net_target->destination;

fail:
  return NULL;
}

const char *
stumpless_get_transport_port( const struct stumpless_target *target ) {
  struct network_target *net_target;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "transport port is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  switch( net_target->network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      return get_ipv4_transport_port( net_target );

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      return get_ipv6_transport_port( net_target );

    default:
      raise_network_protocol_unsupported(  );
      goto fail;

  }

fail:
  return NULL;
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
stumpless_new_network_target( const char *name,
                              enum stumpless_network_protocol network,
                              enum stumpless_transport_protocol transport ) {
  struct stumpless_target *target;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  target = new_target( STUMPLESS_NETWORK_TARGET,
                       name,
                       strlen( name ),
                       0,
                       STUMPLESS_FACILITY_USER );
  if( !target ) {
    goto fail;
  }

  target->id = new_network_target( network, transport );
  if( !target->id ) {
    goto fail_id;
  }

  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
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

  if( facility_is_invalid( default_facility ) ) {
    raise_invalid_facility(  );
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

  target->id = open_network_target( destination, network, transport );
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
stumpless_open_tcp6_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {

  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV6_NETWORK_PROTOCOL,
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
stumpless_open_udp6_target( const char *name,
                            const char *destination,
                            int options,
                            int default_facility ) {

  return stumpless_open_network_target( name,
                                        destination,
                                        STUMPLESS_IPV6_NETWORK_PROTOCOL,
                                        STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                        options,
                                        default_facility );

}

struct stumpless_target *
stumpless_set_destination( struct stumpless_target *target,
                           const char *destination ) {
  const char *new_destination;
  struct network_target *net_target;
  void *result;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( !destination ) {
    raise_argument_empty( "destination is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "transport port is only valid for network"
                               " targets" );
    goto fail;
  }

  new_destination = copy_cstring( destination );
  if( !new_destination ) {
    goto fail;
  }

  net_target = target->id;
  switch( net_target->network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      result = reopen_ipv4_target( net_target, new_destination );
      break;

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      result = reopen_ipv6_target( net_target, new_destination );
      break;

    default:
      raise_network_protocol_unsupported(  );
      goto fail_reopen;

  }

  if( !result ) {
    goto fail_reopen;
  }

  net_target->destination = new_destination;
  return target;

fail_reopen:
  free_mem( ( void * ) new_destination );
fail:
  return NULL;
}

struct stumpless_target *
stumpless_set_transport_port( struct stumpless_target *target,
                              const char *port ) {
  struct network_target *net_target;
  void *result;

  clear_error(  );

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    goto fail;
  }

  if( !port ) {
    raise_argument_empty( "port is NULL" );
    goto fail;
  }

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( "transport port is only valid for network"
                               " targets" );
    goto fail;
  }

  net_target = target->id;
  switch( net_target->network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      result = set_ipv4_port( net_target, port );
      break;

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      result = set_ipv6_port( net_target, port );
      break;

    default:
      raise_network_protocol_unsupported(  );
      goto fail;

  }

  if( !result ) {
    goto fail;
  }

  return target;

fail:
  return NULL;
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

  switch( target->network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      destroy_ipv4( target );
      break;

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      destroy_ipv6( target );
      break;

  }

  free_mem( ( void * ) target->destination );
  free_mem( ( void * ) target->port );
  free_mem( target );
}

int
network_target_is_open( const struct stumpless_target *target ) {
  const struct network_target *net_target;

  net_target = ( const struct network_target * ) target->id;

  switch( net_target->network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      return ipv4_is_open( net_target );

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      return ipv6_is_open( net_target );

    default:
      raise_network_protocol_unsupported(  );
      return 0;
      
  }
}

struct network_target *
new_network_target( enum stumpless_network_protocol network,
                    enum stumpless_transport_protocol transport ) {
  struct network_target *target;
  void *result;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  switch( network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      result = init_ipv4( transport, target );
      break;

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      result = init_ipv6( transport, target );
      break;

    default:
      raise_network_protocol_unsupported(  );
      goto fail_transport;

  }

  if( !result ) {
    goto fail_transport;
  }

  target->destination = NULL;
  target->port = NULL;
  target->network = network;
  target->transport = transport;

  return target;

fail_transport:
  free_mem( target );
fail:
  return NULL;
}

struct network_target *
open_network_target( const char *destination,
                     enum stumpless_network_protocol network,
                     enum stumpless_transport_protocol transport ) {
  struct network_target *target;
  const char *destination_copy;
  const char *port_copy;
  void *result;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  destination_copy = copy_cstring( destination );
  if( !destination_copy ) {
    goto fail_destination;
  }

  port_copy = copy_cstring( DEFAULT_PORT );
  if( !port_copy ) {
    goto fail_port;
  }

  target->network = network;
  target->transport = transport;
  target->max_msg_size = STUMPLESS_DEFAULT_UDP_MAX_MESSAGE_SIZE;
  target->destination = destination_copy;
  target->port = port_copy;

  switch( network ) {

    case STUMPLESS_IPV4_NETWORK_PROTOCOL:
      result = open_ipv4_target( target );
      break;

    case STUMPLESS_IPV6_NETWORK_PROTOCOL:
      result = open_ipv6_target( target );
      break;

    default:
      raise_network_protocol_unsupported(  );
      goto fail_protocol;

  }

  if( !result ) {
    goto fail_protocol;
  }

  return target;

fail_protocol:
  free_mem( ( void * ) port_copy );
fail_port:
  free_mem( ( void * ) destination_copy );
fail_destination:
  free_mem( target );
fail:
  return NULL;
}

struct network_target *
reopen_network_target( struct network_target *target ) {

  if( target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
    return reopen_ipv4_target( target );

  } else {
    return reopen_ipv6_target( target );

  }
}

int
sendto_network_target( struct network_target *target,
                       const char *msg,
                       size_t msg_length ) {
  size_t effective_length;

  if( target->transport == STUMPLESS_UDP_TRANSPORT_PROTOCOL ) {

    if( msg_length > target->max_msg_size ) {
      effective_length = target->max_msg_size;
      raise_argument_too_big( "message is too large to be sent in a single datagram",
                              cap_size_t_to_int( msg_length ),
                              "size of the message that is too large" );
    } else {
      effective_length = msg_length;
    }

    if( target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
      return config_sendto_udp4_target( &target->details.udp4, msg, effective_length );
    } else {
      return config_sendto_udp6_target( &target->details.udp6, msg, effective_length );
    }

  } else {

    if( target->network == STUMPLESS_IPV4_NETWORK_PROTOCOL ) {
      return config_sendto_tcp4_target( &target->details.tcp4, msg, msg_length );
    } else {
      return config_sendto_tcp6_target( &target->details.tcp6, msg, msg_length );
    }

  }
}
