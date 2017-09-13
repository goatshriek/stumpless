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

#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "stumpless.h"

static struct stumpless_target *current_target;
static struct sockaddr_un target_socket_addr, my_socket_addr;
static int my_socket;

int stumpless(const char *message){
  ssize_t msg_len;
  socklen_t size;
  size=100;

  if( !current_target ){
    current_target = stumpless_open_target("/dev/stumpless", 0, 0);
    if( !current_target ){
      return -1;
    }
  }

  msg_len = sendto(my_socket, message, strlen(message)+1, 0, (struct sockaddr *) &target_socket_addr, size);
  if(msg_len > 0){
    printf("message sent");
  } else {
    perror("could not send message: ");
  }

  return 0;
}

struct stumpless_target *
stumpless_open_target(const char *name, int options, int facility){
  struct stumpless_target *target;
  size_t name_len;

  target = malloc(sizeof(struct stumpless_target));
  if( !target ){
    return NULL;
  }

  name_len = strlen(name) + 1;
  target->name = malloc(name_len);
  if( !target->name ){
    free(target);
    return NULL;
  }

  memcpy(target->name, name, name_len);

  target->options = options;
  target->facility = facility;

  target_socket_addr.sun_family = AF_UNIX;
  memcpy(&target_socket_addr.sun_path, name, name_len);

  my_socket_addr.sun_family = AF_UNIX;
  memcpy(&my_socket_addr.sun_path, "\0/stumpless-test", 17);

  my_socket = socket(my_socket_addr.sun_family, SOCK_DGRAM, 0);
  if(my_socket < 0){
    perror("could not create socket: ");
    free(target->name);
    free(target);
    return NULL;
  }

  if( bind(my_socket, (struct sockaddr *) &my_socket_addr, sizeof(my_socket_addr.sun_family)+17) < 0 ){
    perror("could not bind socket: ");
    free(target->name);
    free(target);
    return NULL;
  }

  current_target = target;
  return target;
}
