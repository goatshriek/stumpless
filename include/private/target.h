/*
 * Copyright 2017, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STUMPLESS_PRIVATE_TARGET_H
#define __STUMPLESS_PRIVATE_TARGET_H
 
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
 
struct socket_target {
  struct sockaddr_un target_addr;
  socklen_t target_addr_len;
  struct sockaddr_un local_addr;
  int local_socket;
};

void destroy_socket_target(struct socket_target *trgt);
struct socket_target *new_socket_target(const char *dest, size_t dest_len);
ssize_t sendto_socket_target(const struct socket_target *trgt, const char *msg);

#endif /* __STUMPLESS_PRIVATE_TARGET_H */
