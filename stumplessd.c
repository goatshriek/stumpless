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
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

int main(void){
  // create and open pipe
  int log_socket;
  struct sockaddr_un log_socket_addr;
  struct sockaddr_un from_addr;
  ssize_t msg_len;
  socklen_t size;
  char buf[1024];

  log_socket_addr.sun_family = AF_UNIX;
  memcpy(&log_socket_addr.sun_path, "/dev/stumpless", 15);

  log_socket = socket(log_socket_addr.sun_family, SOCK_DGRAM, 0);
  if(log_socket < 0){
    perror("could not create socket: ");
    return EXIT_FAILURE;
  }

  if( bind(log_socket, (struct sockaddr *) &log_socket_addr, sizeof(log_socket_addr.sun_family)+15) < 0 ){
    perror("could not bind socket: ");
    return EXIT_FAILURE;
  }

  size = 100;
  msg_len = recvfrom(log_socket, buf, 1024, 0, (struct sockaddr *) &from_addr, &size);
  if(msg_len < 0){
    perror("message recieve failure: ");
  }

  printf("%s\n", buf);

  return EXIT_SUCCESS;
}
