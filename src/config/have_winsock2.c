// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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

#include <stdbool.h>
#include <stddef.h>
#include <winsock2.h>
#include "private/config/have_winsock2.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/target/network.h"

/* global static variables */
static WSADATA wsa_data;
static config_atomic_bool_t wsa_data_free = config_atomic_bool_true;
static config_atomic_bool_t wsa_initialized = config_atomic_bool_false;

/**
 * Runs WSAStartup if WSA hasn't been initialized yet.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers as some targets make
 * use of non-reentrant locks to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of lock schemes that may be left locked.
 *
 * @return The return code from WSAStartup.
 */
static
int
init_wsa( void ) {
  bool locked;
  int result = 0;

  if( config_read_bool( &wsa_initialized ) ) {
    return 0;
  }

  do {
    locked = config_compare_exchange_bool( &wsa_data_free, true, false );
  } while( !locked );

  // check to see if it was initialized while waiting on the lock
  if( config_read_bool( &wsa_initialized ) ) {
    goto cleanup_and_return;
  }

  result = WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
  if( result == 0 ) {
    config_write_bool( &wsa_initialized, true );
  }

cleanup_and_return:
  config_write_bool( &wsa_data_free, true );
  return result;
}

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
  int result;

  handle = socket( af, type, protocol );

  if( handle == INVALID_SOCKET ) {
    raise_socket_failure( L10N_WINSOCK2_SOCKET_FAILED_ERROR_MESSAGE,
                          WSAGetLastError(  ),
                          L10N_WSAGETLASTERROR_ERROR_CODE_TYPE );
    goto fail;
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
  if( target->handle != INVALID_SOCKET ) {
    closesocket( target->handle );
  }

  config_destroy_mutex( &target->mutex );
}

int
winsock2_free_all( void ) {
  bool locked;
  int result;

  do {
    locked = config_compare_exchange_bool( &wsa_data_free, true, false );
  } while( !locked );

  result = WSACleanup();
  if( result != 0 ) {
    config_write_bool( &wsa_initialized, false );
  }

  config_write_bool( &wsa_data_free, true );

  return result;
}

struct network_target *
winsock2_init_network_target( struct network_target *target ) {
  if( init_wsa() != 0 ) {
    return NULL;
  }

  target->handle = INVALID_SOCKET;
  config_init_mutex( &target->mutex );

  return target;
}

struct network_target *
winsock2_open_tcp4_target( struct network_target *target ) {
  SOCKET result;

  lock_network_target( target );
  result = winsock_open_socket( target->destination,
                                target->port,
                                AF_INET,
                                SOCK_STREAM,
                                IPPROTO_TCP );
  target->handle = result;
  unlock_network_target( target );

  return result == INVALID_SOCKET ? NULL : target;
}

struct network_target *
winsock2_open_tcp6_target( struct network_target *target ) {
  SOCKET result;

  lock_network_target( target );
  result = winsock_open_socket( target->destination,
                                target->port,
                                AF_INET6,
                                SOCK_STREAM,
                                IPPROTO_TCP );
  target->handle = result;
  unlock_network_target( target );

  return result == INVALID_SOCKET ? NULL : target;
}

struct network_target *
winsock2_open_udp4_target( struct network_target *target ) {
  SOCKET result;

  lock_network_target( target );
  result = winsock_open_socket( target->destination,
                                target->port,
                                AF_INET,
                                SOCK_DGRAM,
                                IPPROTO_UDP );
  target->handle = result;
  unlock_network_target( target );

  return result == INVALID_SOCKET ? NULL : target;
}

struct network_target *
winsock2_open_udp6_target( struct network_target *target ) {
  SOCKET result;

  lock_network_target( target );
  result = winsock_open_socket( target->destination,
                                target->port,
                                AF_INET6,
                                SOCK_DGRAM,
                                IPPROTO_UDP );
  target->handle = result;
  unlock_network_target( target );

  return result == INVALID_SOCKET ? NULL : target;
}

struct network_target *
winsock2_reopen_tcp4_target( struct network_target *target ) {
  lock_network_target( target );

  if( winsock2_network_target_is_open( target ) ) {
    closesocket( target->handle );
    target->handle = winsock_open_socket( target->destination,
                                          target->port,
                                          AF_INET,
                                          SOCK_STREAM,
                                          IPPROTO_TCP );
  }

  unlock_network_target( target );
  return target;
}

struct network_target *
winsock2_reopen_tcp6_target( struct network_target *target ) {
  lock_network_target( target );

  if( winsock2_network_target_is_open( target ) ) {
  closesocket( target->handle );
    target->handle = winsock_open_socket( target->destination,
                                          target->port,
                                          AF_INET6,
                                          SOCK_STREAM,
                                          IPPROTO_TCP );
  }

  unlock_network_target( target );
  return target;
}

struct network_target *
winsock2_reopen_udp4_target( struct network_target *target ) {
  lock_network_target( target );

  if( winsock2_network_target_is_open( target ) ) {
    closesocket( target->handle );
    target->handle = winsock_open_socket( target->destination,
                                          target->port,
                                          AF_INET,
                                          SOCK_DGRAM,
                                          IPPROTO_UDP );
  }

  unlock_network_target( target );
  return target;
}

struct network_target *
winsock2_reopen_udp6_target( struct network_target *target ) {
  lock_network_target( target );

  if( winsock2_network_target_is_open( target ) ) {
    closesocket( target->handle );
    target->handle = winsock_open_socket( target->destination,
                                          target->port,
                                          AF_INET6,
                                          SOCK_DGRAM,
                                          IPPROTO_UDP );
  }

  unlock_network_target( target );
  return target;
}

int
winsock2_sendto_tcp_target( const struct network_target *target,
                            const char *msg,
                            size_t msg_size ) {
  int send_result;
  size_t sent_bytes = 0;
  int remaining_size;

  lock_network_target( target );

  while( sent_bytes < msg_size ) {
    // sys/socket.h network targets can check for a FIN message using recv
    // winsock doesn't provide MSG_DONTWAIT, making this strategy not viable
    // using non-blocking connections is one potential solution to this problem

    remaining_size = cap_size_t_to_int( msg_size - sent_bytes );
    send_result = send( target->handle, msg, remaining_size, 0 );

    if( send_result == SOCKET_ERROR ) {
      unlock_network_target( target );
      raise_socket_send_failure( L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE,
                                 WSAGetLastError(  ),
                                 L10N_WSAGETLASTERROR_ERROR_CODE_TYPE );
      return -1;
    }

    sent_bytes += send_result;
  }

  unlock_network_target( target );
  return 1;
}

int
winsock2_sendto_udp_target( const struct network_target *target,
                            const char *msg,
                            size_t msg_size ) {
  int send_result;

  lock_network_target( target );
  send_result = send( target->handle,
                      msg,
                      cap_size_t_to_int( msg_size ),
                      0 );
  unlock_network_target( target );

  if( send_result == SOCKET_ERROR ) {
    raise_socket_send_failure( L10N_SEND_WIN_SOCKET_FAILED_ERROR_MESSAGE,
                               WSAGetLastError(  ),
                               L10N_WSAGETLASTERROR_ERROR_CODE_TYPE );
    return -1;
  }

  return send_result;
}

int
winsock2_network_target_is_open( const struct network_target *target ) {
  return target->handle != SOCKET_ERROR;
}
