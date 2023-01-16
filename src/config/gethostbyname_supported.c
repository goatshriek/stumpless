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
#include <limits.h>
#include <netdb.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "private/config/gethostbyname_supported.h"
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/gethostbyname.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"

/** Used to synchronize access to gethostbyname return values. */
static config_atomic_bool_t gethostbyname_free = config_atomic_bool_true;

int
gethostbyname_int_connect( const char *destination,
                           const char *port,
                           int domain,
                           int type,
                           int protocol ) {
  int handle;
  struct sockaddr_in addr4;
  struct sockaddr_in6 addr6;
  void *domain_address;
  unsigned long port_ul;
  int port_i;
  int result;
  bool locked;
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

  port_ul = strtoul( port, NULL, 0 );
  port_i = ( port_ul > INT_MAX ) ? INT_MAX : ( int ) port_ul;

  if( domain == AF_INET ) {
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons( port_i );
    domain_address = &( addr4.sin_addr );
    addr = ( struct sockaddr * ) &addr4;
    addrlen = sizeof( addr4 );
  } else {
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons( port_i );
    addr6.sin6_flowinfo = 0;
    addr6.sin6_scope_id = 0;
    domain_address = &( addr6.sin6_addr );
    addr = ( struct sockaddr * ) &addr6;
    addrlen = sizeof( addr6 );
  }

  do {
    locked = config_compare_exchange_bool( &gethostbyname_free, true, false );
  } while( !locked );

  host = config_gethostbyname( destination, domain );
  if( host && host->h_addrtype == domain && host->h_addr_list[0] ) {
    memcpy( domain_address, host->h_addr_list[0], host->h_length );
  } else {
    if( inet_pton( domain, destination, domain_address ) != 1 ) {
      raise_resolve_hostname_failure( L10N_NAME_RESOLUTION_FAILED_ERROR_MESSAGE );
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

  config_write_bool( &gethostbyname_free, true );
  return handle;

fail_addr:
  config_write_bool( &gethostbyname_free, true );
  close( handle );
fail:
  return -1;
}
