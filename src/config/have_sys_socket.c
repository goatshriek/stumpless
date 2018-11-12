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
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "private/error.h"
#include "private/target/network.h"

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
                             const char *destination ) {
  int handle;
  struct addrinfo *addr_result;
  int result;

  handle = socket( AF_INET, SOCK_STREAM, 0 );

  result = getaddrinfo( destination, "514", NULL, &addr_result );
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
    raise_socket_connect_failure( "connect failed with IPv4/TCP socket",
                                  errno,
                                  "errno after the failed call" );
    goto fail_socket;
  }

  freeaddrinfo( addr_result );
  details->handle = handle;
  return details;


fail_socket:
  freeaddrinfo( addr_result );
fail:
  return NULL;
}

struct udp4_details *
sys_socket_open_udp4_target( struct udp4_details *details,
                             const char *destination ) {
  int handle;
  struct addrinfo *addr_result;
  int result;

  handle = socket( AF_INET, SOCK_DGRAM, 0 );

  result = getaddrinfo( destination, "514", NULL, &addr_result );
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
    raise_socket_connect_failure( "connect failed with IPv4/UDP socket",
                                  errno,
                                  "errno after the failed call" );
    goto fail_socket;
  }

  freeaddrinfo( addr_result );
  details->handle = handle;
  return details;


fail_socket:
  freeaddrinfo( addr_result );
fail:
  return NULL;
}

int
sys_socket_sendto_tcp4_target( struct tcp4_details *details,
                               const char *msg,
                               size_t msg_length ) {
  int result;

  result = send( details->handle,
                 msg,
                 msg_length,
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
