// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2024 Joel E. Anderson
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

#ifdef _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <netdb.h>
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <unistd.h>
#endif

#include <cstddef>
#include "test/helper/server.hpp"

socket_handle_t
open_tcp4_server_socket( const char *dest, const char *port ) {
  return open_tcp_server_socket( AF_INET, dest, port );
}

socket_handle_t
open_tcp6_server_socket( const char *dest, const char *port ) {
  return open_tcp_server_socket( AF_INET6, dest, port );
}

socket_handle_t
open_udp4_server_socket( const char *dest, const char *port ) {
  return open_udp_server_socket( AF_INET, dest, port );
}

socket_handle_t
open_udp6_server_socket( const char *dest, const char *port ) {
  return open_udp_server_socket( AF_INET6, dest, port );
}

#ifdef _WIN32
socket_handle_t
open_tcp_server_socket( int af, const char *dest, const char *port ){
  SOCKET handle;
  PADDRINFOA addr_result;
  WSADATA wsa_data;

  handle = socket( af, SOCK_STREAM, IPPROTO_TCP );
  if( WSAGetLastError(  ) == WSANOTINITIALISED ) {
    WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
    handle = socket( af, SOCK_STREAM, IPPROTO_TCP );
    if( handle == INVALID_SOCKET ) {
      return INVALID_SOCKET;
    }
  }

  if( getaddrinfo( dest, port, NULL, &addr_result ) != 0 ) {
    return INVALID_SOCKET;
  }

  bind(handle, addr_result->ai_addr, ( int ) addr_result->ai_addrlen );
  listen( handle, 1 );
  freeaddrinfo( addr_result );

  return handle;
}

socket_handle_t
open_udp_server_socket( int af, const char *dest, const char *port ){
  SOCKET handle;
  PADDRINFOA addr_result;
  WSADATA wsa_data;

  handle = socket( af, SOCK_DGRAM, IPPROTO_UDP );
  if( WSAGetLastError(  ) == WSANOTINITIALISED ) {
    WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
    handle = socket( af, SOCK_DGRAM, IPPROTO_UDP );
    if( handle == INVALID_SOCKET ) {
      return INVALID_SOCKET;
    }
  }

  if( getaddrinfo( dest, port, NULL, &addr_result ) != 0 ) {
    return INVALID_SOCKET;
  }

  bind(handle, addr_result->ai_addr, ( int ) addr_result->ai_addrlen );
  listen( handle, 1 );
  freeaddrinfo( addr_result );

  return handle;
}

socket_handle_t
accept_tcp_connection( socket_handle_t handle ) {
  struct sockaddr_storage fromaddr;
  socklen_t fromaddr_len = sizeof( struct sockaddr_storage );

  return accept( handle, ( struct sockaddr * ) &fromaddr, &fromaddr_len );
}

bool
recv_from_handle( socket_handle_t handle, char *buff, int buff_len ) {
  int msg_len;

  msg_len = recv( handle, buff, buff_len - 1, 0 );
  if( msg_len == SOCKET_ERROR || msg_len == 0 ) {
    buff[0] = '\0';
    return false;
  } else {
    buff[msg_len] = '\0';
    return true;
  }
}

void
close_server_socket( socket_handle_t handle ) {
  if( handle != BAD_HANDLE ) {
    closesocket( handle );
  }
}

#else

socket_handle_t
open_tcp_server_socket( int domain, const char *dest, const char *port ) {
  int handle;
  int reuse = 1;
  struct addrinfo *addr_result;

  handle = socket( domain, SOCK_STREAM, 0 );

  setsockopt( handle, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof( int ) );

  if( getaddrinfo( dest, port, NULL, &addr_result ) != 0 ) {
    return BAD_HANDLE;
  }

  if( bind(handle, addr_result->ai_addr, addr_result->ai_addrlen ) == -1 ){
    freeaddrinfo( addr_result );
    return BAD_HANDLE;
  }

  listen( handle, 1 );
  freeaddrinfo( addr_result );

  return handle;
}

socket_handle_t
open_udp_server_socket( int domain, const char *dest, const char *port ) {
  int handle;
  struct addrinfo *addr_result;

  handle = socket( domain, SOCK_DGRAM, 0 );

  if( getaddrinfo( dest, port, NULL, &addr_result ) != 0 ) {
    return BAD_HANDLE;
  }

  if( bind(handle, addr_result->ai_addr, addr_result->ai_addrlen ) == -1 ){
    freeaddrinfo( addr_result );
    return BAD_HANDLE;
  }

  listen( handle, 1 );
  freeaddrinfo( addr_result );

  return handle;
}

socket_handle_t
accept_tcp_connection( socket_handle_t handle ) {
  struct sockaddr_storage fromaddr;
  socklen_t fromaddr_len = sizeof( struct sockaddr_storage );

  return accept( handle, ( struct sockaddr * ) &fromaddr, &fromaddr_len );
}

bool
recv_from_handle( socket_handle_t handle, char *buff, size_t buff_len ) {
  ssize_t msg_len;

  msg_len = recv( handle, buff, buff_len - 1, 0 );
  if( msg_len <= 0 ) {
    buff[0] = '\0';
    return false;
  } else {
    buff[msg_len] = '\0';
    return true;
  }
}

void
close_server_socket( socket_handle_t handle ) {
  if( handle != BAD_HANDLE ) {
    close( handle );
  }
}
#endif
