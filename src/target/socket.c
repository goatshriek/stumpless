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
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/target/socket.h"

static struct socket_target **targets=NULL;

int stumpless(const char *message){
  struct stumpless_entry *entry;
  struct stumpless_element *element;
  struct stumpless_param *param;
  struct stumpless_target *current_target;
  int result;

  clear_error();

  current_target = stumpless_get_current_target();
  if(!current_target){
    current_target = stumpless_open_socket_target(STUMPLESS_SOCKET_NAME, 0, 0);
  }

  entry = stumpless_new_entry("APP-NAME", "MSGID", message);
  if(!entry){
    return -1;
  }

  param = stumpless_new_param("name", "value");
  element = stumpless_new_element("SD-ID");
  stumpless_add_param(element, param);
  stumpless_add_element(entry, element);

  result = stumpless_add_entry(current_target, entry);
  stumpless_destroy_entry(entry);
  return result;
}

void
stumpless_close_socket_target(struct stumpless_target *target){
  clear_error();
  
  if(target && targets){
    destroy_socket_target(targets[target->id]);
  }
  
  // todo need to clean up the id list
}

struct stumpless_target *
stumpless_open_socket_target(const char *name, int options, int facility){
  struct stumpless_target *pub_target, *current_target;
  struct socket_target *priv_target;
  size_t name_len;

  clear_error();
  
  current_target = stumpless_get_current_target();
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
  priv_target = new_socket_target(name, name_len);
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

  pub_target->type = STUMPLESS_SOCKET_TARGET;
  pub_target->options = options;
  pub_target->facility = facility;

  targets[pub_target->id] = priv_target;

  stumpless_set_current_target(pub_target);
  return pub_target;
}


/* private definitions */

void destroy_socket_target(struct socket_target *trgt){
  if( !trgt ){
    return;
  }
  
  close(trgt->local_socket);
  free_mem(trgt);
}

struct socket_target *new_socket_target(const char *dest, size_t dest_len){
  struct socket_target *trgt;
  
  trgt = alloc_mem(sizeof(struct socket_target));
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

ssize_t sendto_socket_target(const struct stumpless_target *target, const char *msg){
  struct socket_target *priv_trgt;

  if(!target || !targets || !msg){
    return 0;
  }
  
  priv_trgt = targets[target->id];

  return sendto(priv_trgt->local_socket, msg, strlen(msg)+1, 0, (struct sockaddr *) &priv_trgt->target_addr, priv_trgt->target_addr_len);
}
