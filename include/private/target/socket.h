/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_TARGET_SOCKET_H
#  define __STUMPLESS_PRIVATE_TARGET_SOCKET_H

#  include <stddef.h>
#  include <stumpless/target.h>
#  include <sys/socket.h>
#  include <sys/un.h>

struct socket_target {
  struct sockaddr_un target_addr;
  socklen_t target_addr_len;
  struct sockaddr_un local_addr;
  int local_socket;
};

void
destroy_socket_target( const struct socket_target *trgt );

int
socket_target_is_open( const struct stumpless_target *target );

struct stumpless_target *
open_socket_target( struct stumpless_target *target);

struct socket_target *
open_bind_socket( struct socket_target *target );

struct socket_target *
new_socket_target( const char *dest, size_t dest_len,
                   const char *source, size_t source_len );

int
sendto_socket_target( const struct socket_target *target,
                      const char *msg,
                      size_t msg_length );

#endif /* __STUMPLESS_PRIVATE_TARGET_SOCKET_H */
