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

#include "private/config/have_winsock2.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/strhelper.h"
#include "private/target/network.h"

static char *tcp_send_buffer = NULL;
static size_t tcp_send_buffer_length = 0;

static
SOCKET
winsock_open_socket( const char *destination,
                     const char *port,
                     int af,
                     int type,
                     int protocol ) {
  SOCKET handle;
  ADDRINFOA hints;
  PADDRINFOA addr_result;
  WSADATA wsa_data;
  int result;

  handle = socket( af, type, protocol );

  if( handle == INVALID_SOCKET ) {
    if( WSAGetLastError(  ) == WSANOTINITIALISED ) {
      WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
      handle = socket( af, type, protocol );
      if( handle == INVALID_SOCKET ) {
        goto fail;
      }
    }
  }

  hints.ai_flags = 0;
  hints.ai_family = af;
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
                           "Windows Socket error code" );
    goto fail;
  }

  result = connect( handle,
                    addr_result->ai_addr,
                    cap_size_t_to_int( addr_result->ai_addrlen ) );

  if( result == SOCKET_ERROR ) {
    raise_socket_connect_failure( "connect failed on winsock2 socket",
                                  WSAGetLastError(  ),
                                  "WSAGetLastError after the failed call" );
    goto fail_socket;
  }

  freeaddrinfo( addr_result );
  return handle;

fail_socket:
  freeaddrinfo( addr_result );
fail:
  return INVALID_SOCKET;
}

void
winsock2_close_tcp4_target( struct tcp4_details *details ) {
  free_mem( ( void * ) details->port );
  closesocket( details->handle );
}

void
winsock2_close_udp4_target( struct udp4_details *details ) {
  free_mem( ( void * ) details->port );
  closesocket( details->handle );
}

void
winsock2_free_all( void ) {
  free_mem( tcp_send_buffer );
  tcp_send_buffer_length = 0;

  WSACleanup(  );
}

int
winsock2_gethostname( char *buffer, size_t namelen ) {
  int capped_namelen;
  int result;
  WSADATA wsa_data;

  capped_namelen = cap_size_t_to_int( namelen );

  result = gethostname( buffer, capped_namelen );

  if( result == SOCKET_ERROR ) {
    if( WSAGetLastError(  ) == WSANOTINITIALISED ) {
      WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
      result = gethostname( buffer, capped_namelen );
    }
  }

  return result;
}

struct tcp4_details *
winsock2_open_tcp4_target( struct tcp4_details *details,
                           const char *destination,
                           const char *port ) {
  char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    goto fail;
  }

  details->handle = winsock_open_socket( destination,
                                         port,
                                         AF_INET,
                                         SOCK_STREAM,
                                         IPPROTO_TCP );

  if( details->handle == INVALID_SOCKET ) {
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
winsock2_open_udp4_target( struct udp4_details *details,
                           const char *destination,
                           const char *port ) {
  char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    goto fail;
  }

  details->handle = winsock_open_socket( destination,
                                         port,
                                         AF_INET,
                                         SOCK_DGRAM,
                                         IPPROTO_UDP );

  if( details->handle == INVALID_SOCKET ) {
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
winsock2_reopen_tcp4_target( struct tcp4_details *details,
                             const char *destination ) {
  closesocket( details->handle );

  details->handle = winsock_open_socket( destination,
                                         details->port,
                                         AF_INET,
                                         SOCK_STREAM,
                                         IPPROTO_TCP );

  if( details->handle == INVALID_SOCKET ) {
    return NULL;

  } else {
    return details;

  }
}

struct udp4_details *
winsock2_reopen_udp4_target( struct udp4_details *details,
                             const char *destination ) {
  closesocket( details->handle );

  details->handle = winsock_open_socket( destination,
                                         details->port,
                                         AF_INET,
                                         SOCK_DGRAM,
                                         IPPROTO_UDP );

  if( details->handle == INVALID_SOCKET ) {
    return NULL;

  } else {
    return details;

  }

}

int
winsock2_sendto_tcp4_target( struct tcp4_details *details,
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
                 cap_size_t_to_int( int_length + msg_length ),
                 0 );

  if( result == SOCKET_ERROR ) {
    raise_socket_send_failure( "send failed with IPv4/TCP socket",
                               WSAGetLastError(  ),
                               "WSAGetLastError after the failed call" );
    return -1;
  }

  return result;
}

int
winsock2_sendto_udp4_target( struct udp4_details *details,
                             const char *msg,
                             size_t msg_length ) {
  int result;

  result = send( details->handle,
                 msg,
                 cap_size_t_to_int( msg_length ),
                 0 );

  if( result == SOCKET_ERROR ) {
    raise_socket_send_failure( "send failed with IPv4/UDP socket",
                               WSAGetLastError(  ),
                               "WSAGetLastError after the failed call" );
    return -1;
  }

  return result;
}

struct tcp4_details *
winsock2_set_tcp4_port( struct tcp4_details *details,
                        const char *destination,
                        const char *port ) {
  char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    return NULL;
  }

  free_mem( ( void * ) details->port );
  details->port = port_copy;
  return winsock2_reopen_tcp4_target( details, destination );
}

struct udp4_details *
winsock2_set_udp4_port( struct udp4_details *details,
                        const char *destination,
                        const char *port ) {
  char *port_copy;

  port_copy = copy_cstring( port );
  if( !port_copy ) {
    return NULL;
  }

  free_mem( ( void * ) details->port );
  details->port = port_copy;
  return winsock2_reopen_udp4_target( details, destination );
}
