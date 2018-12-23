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
#include "private/strhelper.h"
#include "private/target/network.h"

static char *tcp_send_buffer = NULL;
static size_t tcp_send_buffer_length = 0;

static
int
sys_socket_open_socket( const char *destination,
                        const char *port,
                        int domain,
                        int type,
                        int protocol ) {
  int handle;
  struct addrinfo hints;
  struct addrinfo *addr_result;
  int result;

  handle = socket( domain, type, protocol );

  hints.ai_flags = 0;
  hints.ai_family = domain;
  hints.ai_socktype = type;
  hints.ai_protocol = protocol;
  hints.ai_addrlen = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;

  result = getaddrinfo( destination, port, &hints, &addr_result );
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
  free_mem( ( void * ) details->port );
  close( details->handle );
}

void
sys_socket_close_udp4_target( struct udp4_details *details ) {
  free_mem( ( void * ) details->port );
  close( details->handle );
}

void
sys_socket_free_all( void ) {
  free_mem( tcp_send_buffer );
  tcp_send_buffer_length = 0;
}

struct tcp4_details *
sys_socket_open_tcp4_target( struct tcp4_details *details,
                             const char *destination,
                             const char *port ) {
  int handle;
  char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    goto fail;
  }

  handle = sys_socket_open_socket( destination,
                                   port,
                                   AF_INET,
                                   SOCK_STREAM,
                                   0 );
  details->handle = handle;

  if( handle == -1 ) {
    goto fail_open;
  }

  details->port = port_copy;
  return details;

fail_open:
  free_mem( port_copy );
fail:
  details->port = NULL;
  return NULL;
}

struct udp4_details *
sys_socket_open_udp4_target( struct udp4_details *details,
                             const char *destination,
                             const char *port ) {
  int handle;
  char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    goto fail;
  }

  handle = sys_socket_open_socket( destination,
                                   port,
                                   AF_INET,
                                   SOCK_DGRAM,
                                   0 );
  details->handle = handle;
  if( handle == -1 ) {
    goto fail_open;

  }

  details->port = port_copy;
  return details;

fail_open:
  free_mem( port_copy );
fail:
  details->port = NULL;
  return NULL;
}

struct tcp4_details *
sys_socket_reopen_tcp4_target( struct tcp4_details *details,
                               const char *destination ) {
  close( details->handle );

  details->handle = sys_socket_open_socket( destination,
                                            details->port,
                                            AF_INET,
                                            SOCK_STREAM,
                                            0 );

  if( details->handle == -1 ) {
    return NULL;

  } else {
    return details;

  }
}

struct udp4_details *
sys_socket_reopen_udp4_target( struct udp4_details *details,
                               const char *destination ) {
  close( details->handle );

  details->handle = sys_socket_open_socket( destination,
                                            details->port,
                                            AF_INET,
                                            SOCK_DGRAM,
                                            0 );

  if( details->handle == -1 ) {
    return NULL;

  } else {
    return details;

  }
  
}

int
sys_socket_sendto_tcp4_target( struct tcp4_details *details,
                               const char *msg,
                               size_t msg_length ) {
  int result;
  size_t int_length;
  size_t required_length;
  char *new_buffer;

  required_length = msg_length + 50;
  if( tcp_send_buffer_length < required_length ) {
    new_buffer = realloc_mem( tcp_send_buffer, required_length );

    if( !new_buffer ) {
      return -1;

    } else {
      tcp_send_buffer = new_buffer;
      tcp_send_buffer_length = required_length;

    }
  }

  snprintf( tcp_send_buffer, 50, "%zd ", msg_length );
  int_length = strlen( tcp_send_buffer );
  memcpy( tcp_send_buffer + int_length, msg, msg_length );

  result = send( details->handle,
                 tcp_send_buffer,
                 int_length + msg_length,
                 0 );

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
  const char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    return NULL;
  }

  free_mem( ( void * ) details->port );
  details->port = port_copy;
  return sys_socket_reopen_tcp4_target( details, destination );
}

struct udp4_details *
sys_socket_set_udp4_port( struct udp4_details *details,
                          const char *destination,
                          const char *port ) {
  const char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    return NULL;
  }

  free_mem( ( void * ) details->port );
  details->port = port_copy;
  return sys_socket_reopen_udp4_target( details, destination );
}
