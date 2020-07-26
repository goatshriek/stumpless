// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stumpless/error.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/socket.h"

void
stumpless_close_socket_target( const struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return;
  }

  destroy_socket_target( target->id );
  destroy_target( target );

  clear_error(  );
}

struct stumpless_target *
stumpless_open_socket_target( const char *name,
                              const char *local_socket,
                              int options,
                              int default_facility ) {
  struct stumpless_target *target;
  size_t name_len;
  size_t local_socket_len;
  char temp_name[16];
  int temp_fd;

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  target = new_target(
    STUMPLESS_SOCKET_TARGET,
    name,
    options,
    default_facility
  );

  if( !target ) {
    goto fail;
  }

  name_len = strlen( name );

  if( !local_socket ) {
    memcpy( temp_name, "stumplessXXXXXX", 16 );
    temp_fd = mkstemp( temp_name );
    if( temp_fd == -1 ) {
      raise_error( STUMPLESS_FILE_OPEN_FAILURE,
                   "could not create a file with the chosen local socket name",
                   errno,
                   "errno after the failed call to mkstemp" );
      goto fail_id;
    }

    close( temp_fd );
    unlink( temp_name );
    target->id = new_socket_target( name, name_len, temp_name, 16 );
  } else {
    local_socket_len = strlen( local_socket );
    target->id =
      new_socket_target( name, name_len, local_socket, local_socket_len );
  }

  if( !target->id ) {
    goto fail_id;
  }

  stumpless_set_current_target( target );
  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
}


/* private definitions */

void
destroy_socket_target( const struct socket_target *trgt ) {
  if( !trgt ) {
    return;
  }

  close( trgt->local_socket );
  unlink( trgt->local_addr.sun_path );
  free_mem( trgt );
}

struct socket_target *
new_socket_target( const char *dest,
                   size_t dest_len,
                   const char *source,
                   size_t source_len ) {
  struct socket_target *target;
  int bind_result;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->target_addr.sun_family = AF_UNIX;
  memcpy( &target->target_addr.sun_path, dest, dest_len );
  target->target_addr.sun_path[dest_len] = '\0';

  target->local_addr.sun_family = AF_UNIX;
  memcpy( &target->local_addr.sun_path, source, source_len );
  target->local_addr.sun_path[source_len] = '\0';

  target->local_socket = socket( target->local_addr.sun_family, SOCK_DGRAM, 0 );
  if( target->local_socket < 0 ) {
    raise_socket_failure( "could not create a local unix socket",
                          errno,
                          "errno after the failed call to socket" );
    goto fail_socket;
  }

  bind_result= bind( target->local_socket,
                     ( struct sockaddr * ) &target->local_addr,
                     sizeof( target->local_addr ) );

  if( bind_result < 0 ) {
    raise_socket_bind_failure( "could not bind to the local unix socket",
                               errno,
                               "errno after the failed called to bind" );
    goto fail_socket;
  }

  target->target_addr_len = sizeof( target->target_addr );

  return target;

fail_socket:
  free_mem( target );
fail:
  return NULL;
}

int
sendto_socket_target( const struct socket_target *target,
                      const char *msg, size_t msg_length ) {
  int result;

 result = sendto( target->local_socket,
                  msg,
                  msg_length,
                  0,
                  ( const struct sockaddr * ) &target->target_addr,
                  target->target_addr_len );

  if( result == -1 ) {
    raise_socket_send_failure( "sendto failed with unix socket",
                               errno,
                               "errno after the failed call to sendto" );
  }

  return result;
}
