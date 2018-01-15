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
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/error.h"
#include "private/id.h"
#include "private/memory.h"
#include "private/target/socket.h"

static struct id_map *targets=NULL;

void
stumpless_close_socket_target(struct stumpless_target *target){
  clear_error();
  
  if(target && targets){
    destroy_socket_target(get_by_id(targets, target->id));
  }
  
  // todo need to clean up the id list
}

struct stumpless_target *
stumpless_open_socket_target(const char *name, int options, int facility){
  struct stumpless_target *pub_target;
  struct socket_target *priv_target;
  size_t name_len;

  clear_error();
  
  if(!targets){
    targets = new_id_map();
    if(!targets){
      goto fail;
    }
  }

  pub_target = alloc_mem(sizeof(struct stumpless_target));
  if( !pub_target ){
    goto fail;
  }
  
  name_len = strlen(name) ;
  priv_target = new_socket_target(name, name_len);
  if( !priv_target ){
    goto fail_priv_target;
  }

  pub_target->name = alloc_mem(name_len);
  if( !pub_target->name ){
    goto fail_pub_name;
  }

  memcpy(pub_target->name, name, name_len);
  pub_target->name[name_len] = '\0';
  pub_target->type = STUMPLESS_SOCKET_TARGET;
  pub_target->options = options;
  pub_target->facility = facility;
  pub_target->severity = 6; // todo change this from a hardcoded value
  pub_target->id = add_to_id_map(targets, priv_target);

  stumpless_set_current_target(pub_target);
  return pub_target;

fail_pub_name:
  free_mem(priv_target);
fail_priv_target:
  free_mem(pub_target);
fail:
  return NULL;
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
  
  priv_trgt = get_by_id(targets, target->id);

  return sendto(priv_trgt->local_socket, msg, strlen(msg)+1, 0, (struct sockaddr *) &priv_trgt->target_addr, priv_trgt->target_addr_len);
}
