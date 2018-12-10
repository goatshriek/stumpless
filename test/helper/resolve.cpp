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

#include "test/helper/resolve.hpp"
#include <stdio.h>
#ifdef _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <errno.h>
#  include <netdb.h>
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <unistd.h>
#endif

bool
name_resolves( const char *name ) {
#ifdef _WIN32
  int result;
  PADDRINFOA addr_result;
  WSADATA wsa_data;

  result = getaddrinfo( name, "514", NULL, &addr_result );
  if( result == WSANOTINITIALISED ) {
    WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
    result = getaddrinfo( name, "514", NULL, &addr_result );
  }

  if( result != 0 ) {
    return false;
  }

  freeaddrinfo( addr_result );
  return true;

#else
  struct addrinfo *addr_result;
  int result;

  result = getaddrinfo( name, "514", NULL, &addr_result );
  freeaddrinfo( addr_result );

  return result == 0;

#endif
}
