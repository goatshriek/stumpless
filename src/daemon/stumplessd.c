/*
 * Copyright 2018 Joel E. Anderson
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <stumpless/target/socket.h>

static int log_socket=0;
static FILE *outfile=NULL;

void sigint_handler(int signo){
  fclose(outfile);
  close(log_socket);
  unlink(STUMPLESS_SOCKET_NAME);
  
  exit(EXIT_SUCCESS);
}

int main(void){
  struct sockaddr_un log_socket_addr;
  struct sockaddr_un from_addr;
  ssize_t msg_len;
  socklen_t size = 100;
  char buf[1024];
  
  outfile = fopen("stumplessd-out.log", "a");
  if( !outfile ){
    perror("could not open output file");
    return EXIT_FAILURE;
  }

  log_socket_addr.sun_family = AF_UNIX;
  memcpy(&log_socket_addr.sun_path, STUMPLESS_SOCKET_NAME, STUMPLESS_SOCKET_NAME_LENGTH+1);

  if(signal(SIGINT, &sigint_handler) == SIG_ERR){
    perror("could not register signal handler for SIGINT");
    return EXIT_FAILURE;
  }
  
  log_socket = socket(log_socket_addr.sun_family, SOCK_DGRAM, 0);
  if(log_socket < 0){
    perror("could not create socket");
    return EXIT_FAILURE;
  }

  if( bind(log_socket, (struct sockaddr *) &log_socket_addr, sizeof(log_socket_addr.sun_family)+STUMPLESS_SOCKET_NAME_LENGTH+1) < 0 ){
    perror("could not bind socket");
    return EXIT_FAILURE;
  }

  while(1){
    msg_len = recvfrom(log_socket, buf, 1024, 0, (struct sockaddr *) &from_addr, &size);
    if(msg_len < 0){
      perror("message recieve failure");
    } else {
      fprintf(outfile, "%s\n", buf);
      fflush(outfile);
    }
  }

  // this should never be hit
  return EXIT_FAILURE;
}
