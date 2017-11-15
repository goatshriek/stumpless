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

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "private/target.h"

struct target *new_target(const char *dest, size_t dest_len){
  struct target *trgt;
  
  trgt = malloc(sizeof(struct target));
  if( !trgt ){
    return NULL;
  }
  
  trgt->target_addr.sun_family = AF_UNIX;
  // todo need to check dest_len before this memcpy happens
  memcpy(&trgt->target_addr.sun_path, dest, dest_len);
  trgt->target_addr.sun_path[dest_len] = '\0';
  
  trgt->local_addr.sun_family = AF_UNIX;
  memcpy(&trgt->local_addr.sun_path, "\0/stmplss-tst", 14);
  
  trgt->local_socket = socket(trgt->local_addr.sun_family, SOCK_DGRAM, 0);
  if(trgt->local_socket < 0){
    free(trgt);
    return NULL;
  }
  
  if( bind(trgt->local_socket, (struct sockaddr *) &trgt->local_addr, sizeof(trgt->local_addr)) < 0 ){
    free(trgt);
    return NULL;
  }
  
  trgt->target_addr_len = sizeof(trgt->target_addr);
  
  return trgt;
}

void destroy_target(struct target *trgt){
  if( !trgt ){
    return;
  }
  
  close(trgt->local_socket);
  free(trgt);
}

ssize_t sendto_target(const struct target *trgt, const char *msg){
  if(!trgt || !msg){
    return 0;
  }
  
  return sendto(trgt->local_socket, msg, strlen(msg)+1, 0, (struct sockaddr *) &trgt->target_addr, trgt->target_addr_len);
}