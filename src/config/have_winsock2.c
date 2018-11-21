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
#include <winsock2.h>
#include <ws2tcpip.h>
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target/network.h"

void
winsock2_close_tcp4_target( struct tcp4_details *details ) {
  closesocket( details->handle );
}

void
winsock2_close_udp4_target( struct udp4_details *details ) {
  closesocket( details->handle );
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
                           const char *destination ) {
  SOCKET handle;
  PADDRINFOA addr_result;
  WSADATA wsa_data;
  int result;

  handle = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

  if( handle == INVALID_SOCKET ) {
    if( WSAGetLastError(  ) == WSANOTINITIALISED ) {
      WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
      handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
      if( handle == INVALID_SOCKET ) {
        goto fail;
      }
    }
  }

  result = getaddrinfo( destination, DEFAULT_TCP_PORT, NULL, &addr_result );
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
    raise_socket_connect_failure( "connect failed with IPv4/UDP socket",
                                  WSAGetLastError(  ),
                                  "WSAGetLastError after the failed call" );
    goto fail_socket;
  }

  freeaddrinfo( addr_result );
  details->port = DEFAULT_TCP_PORT;
  details->handle = handle;
  return details;

fail_socket:
  freeaddrinfo( addr_result );
fail:
  return NULL;
}

struct udp4_details *
winsock2_open_udp4_target( struct udp4_details *details,
                           const char *destination ) {
  SOCKET handle;
  PADDRINFOA addr_result;
  WSADATA wsa_data;
  int result;

  handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

  if( handle == INVALID_SOCKET ) {
    if( WSAGetLastError(  ) == WSANOTINITIALISED ) {
      WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
      handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
      if( handle == INVALID_SOCKET ) {
        goto fail;
      }
    }
  }

  result = getaddrinfo( destination, DEFAULT_UDP_PORT, NULL, &addr_result );
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
    raise_socket_connect_failure( "connect failed with IPv4/UDP socket",
                                  WSAGetLastError(  ),
                                  "WSAGetLastError after the failed call" );
    goto fail_socket;
  }

  freeaddrinfo( addr_result );
  details->port = DEFAULT_UDP_PORT;
  details->handle = handle;
  return details;

fail_socket:
  freeaddrinfo( addr_result );
fail:
  return NULL;
}

int
winsock2_sendto_tcp4_target( struct tcp4_details *details,
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
                 cap_size_t_to_int( int_length + msg_length ),
                 0 );
  free_mem( buffer );

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
