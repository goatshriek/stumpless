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
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stumpless.h>
#include <stumpless/target.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"

static struct target **targets=NULL;
static struct stumpless_target *current_target=NULL;

struct stumpless_target *
stumpless_open_socket_target(const char *name, int options, int facility){
  struct stumpless_target *pub_target;
  struct target *priv_target;
  size_t name_len;

  clear_error();
  
  if( current_target && current_target->id == STUMPLESS_MAX_TARGET_COUNT-1 ){
    return NULL;
  }

  if(!targets){
    targets = alloc_mem(sizeof(struct stumpless_target *) * STUMPLESS_MAX_TARGET_COUNT);
    if(!targets)
      return NULL;
  }

  pub_target = alloc_mem(sizeof(struct stumpless_target));
  if( !pub_target ){
    return NULL;
  }
  
  name_len = strlen(name) ;
  priv_target = new_target(name, name_len);
  if( !priv_target ){
    free_mem(pub_target);
    return NULL;
  }

  pub_target->name = alloc_mem(name_len);
  if( !pub_target->name ){
    free_mem(pub_target);
    free_mem(priv_target);
    return NULL;
  }

  memcpy(pub_target->name, name, name_len);

  if(current_target)
    pub_target->id = current_target->id+1;
  else
    pub_target->id = 0;

  pub_target->options = options;
  pub_target->facility = facility;

  targets[pub_target->id] = priv_target;

  current_target = pub_target;
  return pub_target;
}

void
stumpless_close_socket_target(struct stumpless_target *target){
  clear_error();
  
  if(target && targets){
    destroy_target(targets[target->id]);
  }
  
  // todo need to clean up the id list
}

struct target *new_target(const char *dest, size_t dest_len){
  struct target *trgt;
  
  trgt = alloc_mem(sizeof(struct target));
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
    free_mem(trgt);
    return NULL;
  }
  
  if( bind(trgt->local_socket, (struct sockaddr *) &trgt->local_addr, sizeof(trgt->local_addr)) < 0 ){
    free_mem(trgt);
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
  free_mem(trgt);
}

ssize_t sendto_target(const struct target *trgt, const char *msg){
  if(!trgt || !msg){
    return 0;
  }
  
  return sendto(trgt->local_socket, msg, strlen(msg)+1, 0, (struct sockaddr *) &trgt->target_addr, trgt->target_addr_len);
}

int stumpless_add_entry(struct stumpless_target *target, const char *message){
  clear_error();
 
  if( !target || !targets ){
    return -1;
  }
 
  if( sendto_target(targets[target->id], message) <= 0){
    perror("could not send message");
    return -1;
  }

  return 0;
}

struct stumpless_target *stumpless_get_current_target(){
  clear_error();

  return current_target;
}
