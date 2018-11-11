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

#include <stdio.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
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
  struct sockaddr_in *cast_addr_in;

  handle = socket( AF_INET, SOCK_STREAM, 0 );

  cast_addr_in = ( struct sockaddr_in * ) &details->target_addr;
  cast_addr_in->sin_family = AF_INET;
  inet_pton( AF_INET, destination, &cast_addr_in->sin_addr.s_addr );
  cast_addr_in->sin_port = htons( 601 );

  details->handle = handle;
  return details;

fail:
  return NULL;
}

struct udp4_details *
sys_socket_open_udp4_target( struct udp4_details *details,
                             const char *destination ) {
  int handle;
  struct sockaddr_in *cast_addr_in;

  handle = socket( PF_INET, SOCK_DGRAM, 0 );

  memset( &details->target_addr, '\0', sizeof( struct sockaddr_storage ) );
  cast_addr_in = ( struct sockaddr_in * ) &details->target_addr;
  cast_addr_in->sin_family = PF_INET;
  inet_pton( PF_INET, destination, &cast_addr_in->sin_addr.s_addr );
  cast_addr_in->sin_port = htons( 514 );

  if( connect( handle,
               ( struct sockaddr * ) &details->target_addr,
               sizeof( struct sockaddr_storage ) ) == -1 ){
    perror("connect failed");
    goto fail;
           }

  details->handle = handle;
  return details;

fail:
  return NULL;
}

int
sys_socket_sendto_tcp4_target( struct tcp4_details *details,
                               const char *msg,
                               size_t msg_length ) {
  return sendto( details->handle,
                 msg,
                 msg_length,
                 0,
                 ( struct sockaddr * ) &details->target_addr,
                 sizeof( details->target_addr ) );
}

int
sys_socket_sendto_udp4_target( struct udp4_details *details,
                               const char *msg,
                               size_t msg_length ) {
  int result;

  result = send( details->handle,
                 msg,
                 msg_length,
                 0);

  if( result == -1 ){
    perror("send failed");
  }

  return result;
}
