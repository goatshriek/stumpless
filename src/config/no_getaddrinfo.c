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

#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "private/config/no_getaddrinfo.h"
#include "private/config/locale/wrapper.h"
#include "private/error.h"

int
no_getaddrinfo_int_connect( const char *destination,
                            const char *port,
                            int domain,
                            int type,
                            int protocol ) {
  int handle;
  struct sockaddr_in addr;
  int port_num;
  int result;

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

  if( inet_addr( destination ) == -1 ) {
    raise_address_failure( "inet_aton failure", // TODO failure
                           errno,
                           L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail_addr;
  }

  addr.sin_family = domain;
  addr.sin_port = ntohs( port_num );
  addr.sin_addr.s_addr = inet_addr( destination );

  result = connect( handle,
                    ( struct sockaddr * ) &addr,
                    sizeof( addr ) );
  if( result == -1 ) {
    goto fail_addr;
  }

  return handle;

fail_addr:
  close( handle );
fail:
  return -1;
}
