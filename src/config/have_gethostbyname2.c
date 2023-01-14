// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023 Joel E. Anderson
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

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "private/config/have_gethostbyname2.h"
#include "private/config/locale/wrapper.h"
#include "private/error.h"

int
gethostbyname2_int_connect( const char *destination,
                            const char *port,
                            int domain,
                            int type,
                            int protocol ) {
  int handle;
  struct sockaddr_in addr4;
  struct sockaddr_in6 addr6;
  void *domain_address;
  int port_num;
  int result;
  struct hostent *host;
  struct sockaddr *addr;
  socklen_t addrlen;

  handle = socket( domain, type, protocol );
  if( handle == -1 ) {
    raise_socket_failure( L10N_SOCKET_FAILED_ERROR_MESSAGE,
                          errno,
                          L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail;
  }

  port_num = atoi( port );
  if( port_num == 0 ) {
    goto fail_addr;
  }

  if( domain == AF_INET ) {
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons( port_num );
    domain_address = &( addr4.sin_addr );
    addr = ( struct sockaddr * ) &addr4;
    addrlen = sizeof( addr4 );
  } else {
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons( port_num );
    domain_address = &( addr6.sin6_addr );
    addr = ( struct sockaddr * ) &addr6;
    addrlen = sizeof( addr6 );
  }

  host = gethostbyname2( destination, domain );
  if( host && host->h_addrtype == domain && host->h_addr_list[0] ) {
    memcpy( domain_address, host->h_addr_list[0], host->h_length );
  } else {
    if( inet_pton( domain, destination, domain_address ) != 1 ) {
      raise_address_failure( "both gethostbyname2 and inet_pton failed", // TODO localize
                             errno,
                             L10N_ERRNO_ERROR_CODE_TYPE );
      goto fail_addr;
    }
  }

  result = connect( handle, addr, addrlen );
  if( result == -1 ) {
    raise_socket_connect_failure( L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE,
                                  errno,
                                  L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail_addr;
  }

  return handle;

fail_addr:
  close( handle );
fail:
  return -1;
}
