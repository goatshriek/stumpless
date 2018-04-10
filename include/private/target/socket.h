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

#ifndef __STUMPLESS_PRIVATE_TARGET_SOCKET_H
#define __STUMPLESS_PRIVATE_TARGET_SOCKET_H
 
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stumpless/target.h>
 
struct socket_target {
  struct sockaddr_un target_addr;
  socklen_t target_addr_len;
  struct sockaddr_un local_addr;
  int local_socket;
};

void destroy_socket_target(struct socket_target *trgt);
struct socket_target *new_socket_target(const char *dest, size_t dest_len);
int sendto_socket_target(const struct stumpless_target *trgt, const char *msg);

#endif /* __STUMPLESS_PRIVATE_TARGET_SOCKET_H */
