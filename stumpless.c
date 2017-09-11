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
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "stumpless.h"

int stumpless(const char *message){
  int my_socket;
  struct sockaddr_un log_socket_addr, my_addr;
  ssize_t msg_len;
  socklen_t size;
  size=100;

  log_socket_addr.sun_family = AF_UNIX;
  memcpy(&log_socket_addr.sun_path, "/dev/stumpless", 15);

  my_addr.sun_family = AF_UNIX;
  memcpy(&my_addr.sun_path, "\0/stumpless-test", 17);

  my_socket = socket(my_addr.sun_family, SOCK_DGRAM, 0);
  if(my_socket < 0){
    perror("could not create socket: ");
    return -1;
  }

  if( bind(my_socket, (struct sockaddr *) &my_addr, sizeof(my_addr.sun_family)+17) < 0 ){
    perror("could not bind socket: ");
    return -1;
  }

  msg_len = sendto(my_socket, message, strlen(message)+1, 0, (struct sockaddr *) &log_socket_addr, size);
  if(msg_len > 0){
    printf("message sent");
  } else {
    perror("could not send message: ");
  }

  return 0;
}
