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

#ifndef __STUMPLESS_TARGET_H
#define __STUMPLESS_TARGET_H
 
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
 
struct target {
  struct sockaddr_un target_addr;
  socklen_t target_addr_len;
  struct sockaddr_un local_addr;
  int local_socket;
};

struct target *new_target(const char *dest, size_t dest_len);
void destroy_target(struct target *trgt);
ssize_t sendto_target(const struct target *trgt, const char *msg);

#endif /* __STUMPLESS_TARGET_H */