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
#include <winsock2.h>
#include <ws2tcpip.h>
#include "private/config/have_winsock2.h"
#include "private/inthelper.h"
#include "private/target/network.h"

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
  SOCKADDR_STORAGE local_addr;
  PSOCKADDR_IN cast_addr_in;
  WSADATA wsa_data;
  int bind_result;

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

  cast_addr_in = ( PSOCKADDR_IN ) &local_addr;
  cast_addr_in->sin_family = AF_INET;
  inet_pton( AF_INET, "127.0.0.1", &cast_addr_in->sin_addr.s_addr );
  cast_addr_in->sin_port = htons( 27015 );
  bind_result = bind( handle, ( PSOCKADDR ) &local_addr, sizeof( local_addr ) );
  if( bind_result == SOCKET_ERROR ) {
    goto fail_bind;
  }

  cast_addr_in = ( PSOCKADDR_IN ) &details->target_addr;
  cast_addr_in->sin_family = AF_INET;
  inet_pton( AF_INET, destination, &cast_addr_in->sin_addr.s_addr );
  cast_addr_in->sin_port = htons( 601 );

  details->handle = handle;
  return details;

fail_bind:
  closesocket( handle );
fail:
  return NULL;
}

struct udp4_details *
winsock2_open_udp4_target( struct udp4_details *details,
                           const char *destination ) {
  SOCKET handle;
  SOCKADDR_STORAGE local_addr;
  PSOCKADDR_IN local_addr_in;
  WSADATA wsa_data;
  int bind_result;

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

  local_addr_in = ( PSOCKADDR_IN ) &local_addr;
  local_addr_in->sin_family = AF_INET;
  inet_pton( AF_INET, "127.0.0.1", &local_addr_in->sin_addr.s_addr );
  local_addr_in->sin_port = htons( 27015 );
  bind_result = bind( handle, ( PSOCKADDR ) &local_addr, sizeof( local_addr ) );
  if( bind_result == SOCKET_ERROR ) {
    goto fail_bind;
  }

  details->handle = handle;
  return details;

fail_bind:
  closesocket( handle );
fail:
  return NULL;
}

int
winsock2_sendto_tcp4_target( struct tcp4_details *details,
                             const char *msg,
                             size_t msg_length ) {
  return -1;
}

int
winsock2_sendto_udp4_target( struct udp4_details *details,
                             const char *msg,
                             size_t msg_length ) {
  return -1;
}
