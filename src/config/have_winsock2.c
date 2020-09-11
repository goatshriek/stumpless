// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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

/* this must be included first to avoid errors */
#include "private/windows_wrapper.h"

#include <stddef.h>
#include "private/config/have_winsock2.h"
#include "private/config/locale/wrapper.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/target/network.h"

static
SOCKET
winsock_open_socket( const char *destination,
                     const char *port,
                     int af,
                     int type,
                     int protocol ) {
  SOCKET handle;
  ADDRINFOA hints = { .ai_flags = 0,
                      .ai_addrlen = 0,
                      .ai_canonname = NULL,
                      .ai_addr = NULL,
                      .ai_next = NULL };
  PADDRINFOA addr_result;
  WSADATA wsa_data;
  int result;

  handle = socket( af, type, protocol );

  if( handle == INVALID_SOCKET ) {
    if( WSAGetLastError(  ) == WSANOTINITIALISED ) {
      WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
      handle = socket( af, type, protocol );
    }

    if( handle == INVALID_SOCKET ) {
      raise_socket_failure( L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE,
                            WSAGetLastError(  ),
                            L10N_WSAGETLASTERROR_ERROR_CODE_TYPE );
      goto fail;
    }
  }

  hints.ai_family = af;
  hints.ai_socktype = type;
  hints.ai_protocol = protocol;

  result = getaddrinfo( destination, port, &hints, &addr_result );
  if( result != 0 ) {
    raise_address_failure( L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE,
                           result,
                           L10N_WINDOWS_SOCKET_ERROR_CODE_TYPE );
    goto fail_addr;
  }

  result = connect( handle,
                    addr_result->ai_addr,
                    cap_size_t_to_int( addr_result->ai_addrlen ) );

  if( result == SOCKET_ERROR ) {
    raise_socket_connect_failure( L10N_CONNECT_WIN_SOCKET_FAILED_ERROR_MESSAGE,
                                  WSAGetLastError(  ),
                                  L10N_WSAGETLASTERROR_ERROR_CODE_TYPE );
    goto fail_connect;
  }

  freeaddrinfo( addr_result );
  return handle;

fail_connect:
  freeaddrinfo( addr_result );
fail_addr:
  closesocket( handle );
fail:
  return INVALID_SOCKET;
}

void
winsock2_close_network_target( const struct network_target *target ) {
  closesocket( target->handle );
}

void
winsock2_cleanup( void ) {
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

void
winsock2_init_network_target( struct network_target *target ) {
  target->handle = INVALID_SOCKET;
}

struct network_target *
winsock2_open_tcp4_target( struct network_target *target ) {

  target->handle = winsock_open_socket( target->destination,
                                        target->port,
                                        AF_INET,
                                        SOCK_STREAM,
                                        IPPROTO_TCP );

  if( target->handle == INVALID_SOCKET ) {
    return NULL;

  }

  return target;
}

struct network_target *
winsock2_open_tcp6_target( struct network_target *target ) {

  target->handle = winsock_open_socket( target->destination,
                                        target->port,
                                        AF_INET6,
                                        SOCK_STREAM,
                                        IPPROTO_TCP );

  if( target->handle == INVALID_SOCKET ) {
    return NULL;

  }

  return target;
}

struct network_target *
winsock2_open_udp4_target( struct network_target *target ) {

  target->handle = winsock_open_socket( target->destination,
                                        target->port,
                                        AF_INET,
                                        SOCK_DGRAM,
                                        IPPROTO_UDP );

  if( target->handle == INVALID_SOCKET ) {
    return NULL;

  }

  return target;
}

struct network_target *
winsock2_open_udp6_target( struct network_target *target ) {

  target->handle = winsock_open_socket( target->destination,
                                        target->port,
                                        AF_INET6,
                                        SOCK_DGRAM,
                                        IPPROTO_UDP );

  if( target->handle == INVALID_SOCKET ) {
    return NULL;

  }

  return target;
}

struct network_target *
winsock2_reopen_tcp4_target( struct network_target *target ) {

  winsock2_close_network_target( target );
  return winsock2_open_tcp4_target( target );

}

struct network_target *
winsock2_reopen_tcp6_target( struct network_target *target ) {

  winsock2_close_network_target( target );
  return winsock2_open_tcp6_target( target );

}

struct network_target *
winsock2_reopen_udp4_target( struct network_target *target ) {

  winsock2_close_network_target( target );
  return winsock2_open_udp4_target( target );

}

struct network_target *
winsock2_reopen_udp6_target( struct network_target *target ) {

  winsock2_close_network_target( target );
  return winsock2_open_udp6_target( target );

}

int
winsock2_sendto_target( struct network_target *target,
                        const char *msg,
                        size_t msg_length ) {
  int result;

  result = send( target->handle,
                 msg,
                 cap_size_t_to_int( msg_length ),
                 0 );

  if( result == SOCKET_ERROR ) {
    raise_socket_send_failure( L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE,
                               WSAGetLastError(  ),
                               L10N_WSAGETLASTERROR_ERROR_CODE_TYPE );
    return -1;
  }

  return result;
}

int
winsock2_network_target_is_open( const struct network_target *target ) {
  return target->handle != SOCKET_ERROR;
}
