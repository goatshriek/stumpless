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
#include <sys/socket.h>
#include <sys/un.h>

int main(void){
  // create and open pipe
  int log_socket;
  struct sockaddr_un log_socket_addr;

  log_socket_addr.sun_family = AF_UNIX;
  memcpy(&log_socket_addr.sun_data, "/dev/stumpless", 15);

  log_socket = socket(log_socket_addr.sun_family, SOCK_DGRAM, 0);
  if(s < 0){
    perror("could not create socket: ");
    return EXIT_FAILURE;
  }

  if( bind(log_socket, log_socket_addr, sizeof(log_socket_addr.sun_family)+15) < 0 ){
    perror("could not bind socket: ");
    return EXIT_FAILURE;
  }

  while(1){
    // use recvfrom
  }

  return EXIT_SUCCESS;
}
