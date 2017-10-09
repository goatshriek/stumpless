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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stumpless.h>
#include "target.h"

static struct target **targets=NULL;
static stumpless_id_t current_target=0;

int stumpless(const char *message){
  struct target *target;
  ssize_t msg_len;

  if( current_target == 0 ){
    stumpless_open_target(STUMPLESS_PIPE_NAME, 0, 0);
    if( current_target == 0 ){
      return -1;
    }
  }

  target = targets[current_target-1];
  
  msg_len = sendto(target->local_socket, message, strlen(message)+1, 0, (struct sockaddr *) &target->target_addr, target->target_addr_len);
  if(msg_len <= 0){
    perror("could not send message");
    return -1;
  }

  return 0;
}

struct stumpless_target *
stumpless_open_target(const char *name, int options, int facility){
  struct stumpless_target *pub_target;
  struct target *priv_target;
  size_t name_len;

  if( current_target == STUMPLESS_MAX_TARGET_COUNT-1 ){
    return NULL;
  }

  if(!targets){
    targets = malloc(sizeof(struct stumpless_target *) * STUMPLESS_MAX_TARGET_COUNT);
    if(!targets)
      return NULL;
  }

  pub_target = malloc(sizeof(struct stumpless_target));
  if( !pub_target ){
    return NULL;
  }
  
  priv_target = malloc(sizeof(struct target));
  if( !priv_target ){
    free(pub_target);
    return NULL;
  }

  name_len = strlen(name) + 1;
  pub_target->name = malloc(name_len);
  if( !pub_target->name ){
    free(pub_target);
    free(priv_target);
    return NULL;
  }

  memcpy(pub_target->name, name, name_len);

  pub_target->id = current_target++;
  pub_target->options = options;
  pub_target->facility = facility;

  priv_target->target_addr.sun_family = AF_UNIX;
  memcpy(&priv_target->target_addr.sun_path, name, name_len);

  priv_target->local_addr.sun_family = AF_UNIX;
  memcpy(&priv_target->local_addr.sun_path, "\0/stumpless-test", 17);

  priv_target->local_socket = socket(priv_target->local_addr.sun_family, SOCK_DGRAM, 0);
  if(priv_target->local_socket < 0){
    perror("could not create socket");
    free(pub_target->name);
    free(pub_target);
    free(priv_target);
    return NULL;
  }

  if( bind(priv_target->local_socket, (struct sockaddr *) &priv_target->local_addr, sizeof(priv_target->local_addr.sun_family)+17) < 0 ){
    perror("could not bind socket");
    free(pub_target->name);
    free(pub_target);
    free(priv_target);
    return NULL;
  }

  priv_target->target_addr_len = sizeof(priv_target->target_addr);
  targets[pub_target->id] = priv_target;
  
  return pub_target;
}

void
stumpless_close_target(struct stumpless_target *target){
  struct target *priv_target;
  
  if(!target || !targets){
    return;
  }
  
  priv_target = targets[target->id];
  
  close(priv_target->local_socket);
  free(priv_target);
  
  // todo need to clean up the id list
}
