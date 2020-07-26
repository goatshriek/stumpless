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

#include "private/config/have_sys_socket.h"

#include <errno.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>
#include "private/error.h"
#include "private/target/network.h"

static
int
sys_socket_open_socket( const char *destination,
                        const char *port,
                        int domain,
                        int type,
                        int protocol ) {
  int handle;
  struct addrinfo hints = { .ai_flags = 0,
                            .ai_addrlen = 0,
                            .ai_canonname = NULL,
                            .ai_addr = NULL,
                            .ai_next = NULL };
  struct addrinfo *addr_result;
  int result;

  handle = socket( domain, type, protocol );
  if( handle == -1 ) {
    raise_socket_failure( "failed to open a socket",
                          errno,
                          "errno after the failed call" );
    goto fail;
  }

  hints.ai_family = domain;
  hints.ai_socktype = type;
  hints.ai_protocol = protocol;

  result = getaddrinfo( destination, port, &hints, &addr_result );
  if( result != 0 ) {
    raise_address_failure( "getaddrinfo failed on name",
                           result,
                           "return code from getaddrinfo" );
    goto fail_addr;
  }

  result = connect( handle,
                    addr_result->ai_addr,
                    addr_result->ai_addrlen );

  if( result == -1 ) {
    raise_socket_connect_failure( "connect failed with socket",
                                  errno,
                                  "errno after the failed call" );
    goto fail_connect;
  }

  return handle;

fail_connect:
  freeaddrinfo( addr_result );
fail_addr:
  close( handle );
fail:
  return -1;
}

void
sys_socket_close_network_target( const struct network_target *target ) {
  close( target->handle );
}

void
sys_socket_init_network_target( struct network_target *target ) {
  target->handle = -1;
}

struct network_target *
sys_socket_open_tcp4_target( struct network_target *target ) {

  target->handle = sys_socket_open_socket( target->destination,
                                           target->port,
                                           AF_INET,
                                           SOCK_STREAM,
                                           0 );

  if( target->handle == -1 ) {
    return NULL;

  }

  return target;
}

struct network_target *
sys_socket_open_tcp6_target( struct network_target *target ) {

  target->handle = sys_socket_open_socket( target->destination,
                                           target->port,
                                           AF_INET6,
                                           SOCK_STREAM,
                                           0 );

  if( target->handle == -1 ) {
    return NULL;

  }

  return target;
}

struct network_target *
sys_socket_open_udp4_target( struct network_target *target ) {

  target->handle = sys_socket_open_socket( target->destination,
                                           target->port,
                                           AF_INET,
                                           SOCK_DGRAM,
                                           0 );

  if( target->handle == -1 ) {
    return NULL;

  }

  return target;
}

struct network_target *
sys_socket_open_udp6_target( struct network_target *target ) {

  target->handle = sys_socket_open_socket( target->destination,
                                           target->port,
                                           AF_INET6,
                                           SOCK_DGRAM,
                                           0 );

  if( target->handle == -1 ) {
    return NULL;

  }

  return target;
}

struct network_target *
sys_socket_reopen_tcp4_target( struct network_target *target ) {

  sys_socket_close_network_target( target );
  return sys_socket_open_tcp4_target( target );

}

struct network_target *
sys_socket_reopen_tcp6_target( struct network_target *target ) {

  sys_socket_close_network_target( target );
  return sys_socket_open_tcp6_target( target );

}

struct network_target *
sys_socket_reopen_udp4_target( struct network_target *target ) {

  sys_socket_close_network_target( target );
  return sys_socket_open_udp4_target( target );

}

struct network_target *
sys_socket_reopen_udp6_target( struct network_target *target ) {

  sys_socket_close_network_target( target );
  return sys_socket_open_udp6_target( target );

}

int
sys_socket_sendto_target( struct network_target *target,
                          const char *msg,
                          size_t msg_length ) {
  int result;

  result = send( target->handle,
                 msg,
                 msg_length,
                 0 );

  if( result == -1 ){
    raise_socket_send_failure( "send failed with linux socket",
                               errno,
                               "errno after the failed call to send");
  }

  return result;
}

int
sys_socket_network_target_is_open( const struct network_target *target ) {
  return target->handle != -1;
}
