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

#include "private/config/have_sys_socket.h"

#include <errno.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/target/network.h"

static
int
sys_socket_open_socket( const char *destination,
                        const char *port,
                        int domain,
                        int type,
                        int protocol ) {
  int handle;
  struct addrinfo *addr_result;
  int result;

  handle = socket( domain, type, protocol );

  result = getaddrinfo( destination, port, NULL, &addr_result );
  if( result != 0 ) {
    raise_address_failure( "getaddrinfo failed on name",
                           result,
                           "return code from getaddrinfo" );
    goto fail;
  }

  result = connect( handle,
                    addr_result->ai_addr,
                    addr_result->ai_addrlen );

  if( result == -1 ) {
    raise_socket_connect_failure( "connect failed with socket",
                                  errno,
                                  "errno after the failed call" );
    goto fail_socket;
  }

  return handle;


fail_socket:
  freeaddrinfo( addr_result );
fail:
  return -1;
}

void
sys_socket_close_tcp4_target( struct tcp4_details *details ) {
  close( details->handle );
}

void
sys_socket_close_udp4_target( struct udp4_details *details ) {
  close( details->handle );
}

struct tcp4_details *
sys_socket_open_tcp4_target( struct tcp4_details *details,
                             const char *destination,
                             const char *port ) {
  int handle;
  handle = sys_socket_open_socket( destination,
                                   port,
                                   AF_INET,
                                   SOCK_STREAM,
                                   0 );
  details->handle = handle;

  if( handle == -1 ) {
    details->port = NULL;
    return NULL;

  } else {
    details->port = port;
    return details;
  }
}

struct udp4_details *
sys_socket_open_udp4_target( struct udp4_details *details,
                             const char *destination,
                             const char *port ) {
  int handle;
  handle = sys_socket_open_socket( destination,
                                   port,
                                   AF_INET,
                                   SOCK_DGRAM,
                                   0 );
  details->handle = handle;

  if( handle == -1 ) {
    details->port = NULL;
    return NULL;

  } else {
    details->port = port;
    return details;
  }
}

int
sys_socket_sendto_tcp4_target( struct tcp4_details *details,
                               const char *msg,
                               size_t msg_length ) {
  int result;
  char *buffer;
  size_t int_length;

  buffer = alloc_mem( msg_length + 50 );
  if( !buffer ) {
    return -1;
  }

  snprintf( buffer, 50, "%zd ", msg_length );
  int_length = strlen( buffer );
  memcpy( buffer + int_length, msg, msg_length );

  result = send( details->handle,
                 buffer,
                 int_length + msg_length,
                 0 );
  free_mem( buffer );

  if( result == -1 ){
    raise_socket_send_failure( "send failed with IPv4/TCP socket",
                               errno,
                               "errno after the failed call");
  }

  return result;
}

int
sys_socket_sendto_udp4_target( struct udp4_details *details,
                               const char *msg,
                               size_t msg_length ) {
  int result;

  result = send( details->handle,
                 msg,
                 msg_length,
                 0 );

  if( result == -1 ){
    raise_socket_send_failure( "send failed with IPv4/UDP socket",
                               errno,
                               "errno after the failed call to send");
  }

  return result;
}

struct tcp4_details *
sys_socket_set_tcp4_port( struct tcp4_details *details,
                          const char *destination,
                          const char *port ) {
  sys_socket_close_tcp4_target( details );
  return sys_socket_open_tcp4_target( details, destination, port );
}

struct udp4_details *
sys_socket_set_udp4_port( struct udp4_details *details,
                          const char *destination,
                          const char *port ) {
  sys_socket_close_udp4_target( details );
  return sys_socket_open_udp4_target( details, destination, port );
}
