// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2021 Joel E. Anderson
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

#include <cstddef>
#include <cstring>
#include "test/helper/resolve.hpp"
#ifdef _WIN32
#  include <ws2tcpip.h>
#else
#  include <netdb.h>
#endif

bool
name_resolves( const char *name, int domain ) {
#ifdef _WIN32
  int result;
  ADDRINFOA hints;
  PADDRINFOA addr_result;
  PADDRINFOA next;
  WSADATA wsa_data;

  memset( &hints, 0, sizeof( hints ) );
  hints.ai_flags = 0;
  hints.ai_addrlen = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = domain;

  result = getaddrinfo( name, "514", &hints, &addr_result );
  if( result == WSANOTINITIALISED ) {
    WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
    result = getaddrinfo( name, "514", NULL, &addr_result );
  }

  if( result != 0 ) {
    return false;
  }

  next = addr_result;
  while( next != NULL ) {
    next = next->ai_next;
  }

  freeaddrinfo( addr_result );
  return true;

#else
  struct addrinfo *addr_result;
  struct addrinfo hints;
  int result;

  memset( &hints, 0, sizeof( hints ) );
  hints.ai_flags = 0;
  hints.ai_addrlen = 0;
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = domain;
  result = getaddrinfo( name, "514", &hints, &addr_result );

  if( result != 0 ) {
    return false;
  }

  freeaddrinfo( addr_result );
  return true;

#endif
}
