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
#include <netdb.h>
#include <stddef.h>
#include <unistd.h>
#include "private/config/have_getaddrinfo.h"
#include "private/config/locale/wrapper.h"
#include "private/error.h"

int
getaddrinfo_int_connect( const char *destination,
                         const char *port,
                         int domain,
                         int type,
                         int protocol ) {
  int handle;
  struct addrinfo hints = { .ai_flags = 0,
                            .ai_addrlen = 0,
                            .ai_canonname = NULL,
                            .ai_addr = NULL,
                            .ai_next = NULL };
  struct addrinfo *addr_result;
  int result;

  handle = socket( domain, type, protocol );
  if( handle == -1 ) {
    raise_socket_failure( L10N_SOCKET_FAILED_ERROR_MESSAGE,
                          errno,
                          L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail;
  }

  hints.ai_family = domain;
  hints.ai_socktype = type;
  hints.ai_protocol = protocol;

  result = getaddrinfo( destination, port, &hints, &addr_result );
  if( result != 0 ) {
    raise_address_failure( L10N_GETADDRINFO_FAILURE_ERROR_MESSAGE,
                           result,
                           L10N_GETADDRINFO_RETURN_ERROR_CODE_TYPE );
    goto fail_addr;
  }

  result = connect( handle,
                    addr_result->ai_addr,
                    addr_result->ai_addrlen );

  if( result == -1 ) {
    raise_socket_connect_failure( L10N_CONNECT_SYS_SOCKET_FAILED_ERROR_MESSAGE,
                                  errno,
                                  L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail_connect;
  }

  freeaddrinfo( addr_result );
  return handle;

fail_connect:
  freeaddrinfo( addr_result );
fail_addr:
  close( handle );
fail:
  return -1;
}
