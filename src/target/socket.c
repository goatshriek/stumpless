// SPDX-License-Identifier: Apache-2.0

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
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/socket.h"

static size_t next_socket_number = 0;

void
stumpless_close_socket_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty(  );
    return;
  }

  destroy_socket_target( target->id );
  free_mem( target->name );
  free_mem( target );
}

struct stumpless_target *
stumpless_open_socket_target( const char *name,
                              const char *local_socket,
                              int options,
                              int default_facility ) {
  struct stumpless_target *target;
  size_t name_len, local_socket_len;
  char default_socket[15];

  clear_error(  );

  if( !name ) {
    raise_argument_empty(  );
    goto fail;
  }

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  name_len = strlen( name );

  if( !local_socket ) {
    default_socket[0] = 's';
    default_socket[1] = 't';
    default_socket[2] = 'u';
    default_socket[3] = 'm';
    default_socket[4] = 'p';
    default_socket[5] = 'l';
    default_socket[6] = 'e';
    default_socket[7] = 's';
    default_socket[8] = 's';
    default_socket[9] = '-';
    default_socket[10] = ( ( next_socket_number >> 12 ) & 0xf ) + 97;
    default_socket[11] = ( ( next_socket_number >> 8 ) & 0xf ) + 97;
    default_socket[12] = ( ( next_socket_number >> 4 ) & 0xf ) + 97;
    default_socket[13] = ( next_socket_number & 0xf ) + 97;
    default_socket[14] = '\0';
    next_socket_number++;
    target->id = new_socket_target( name, name_len, default_socket, 15 );
  } else { 
    local_socket_len = strlen( local_socket );
    target->id = new_socket_target( name, name_len, local_socket, local_socket_len );
  }

  if( !target->id ) {
    goto fail_id;
  }

  target->name = alloc_mem( name_len + 1 );
  if( !target->name ) {
    goto fail_name;
  }

  memcpy( target->name, name, name_len );
  target->name[name_len] = '\0';
  target->type = STUMPLESS_SOCKET_TARGET;
  target->options = options;
  target->default_prival =
    get_prival( default_facility, STUMPLESS_SEVERITY_INFO );

  stumpless_set_current_target( target );
  return target;

fail_name:
  destroy_socket_target( target->id );
fail_id:
  free_mem( target );
fail:
  return NULL;
}


/* private definitions */

void
destroy_socket_target( struct socket_target *trgt ) {
  if( !trgt ) {
    return;
  }

  close( trgt->local_socket );
  unlink( trgt->local_addr.sun_path );
  free_mem( trgt );
}

struct socket_target *
new_socket_target( const char *dest, size_t dest_len,
                   const char *source, size_t source_len ) {
  struct socket_target *trgt;

  trgt = alloc_mem( sizeof( *trgt ) );
  if( !trgt ) {
    return NULL;
  }

  trgt->target_addr.sun_family = AF_UNIX;
  memcpy( &trgt->target_addr.sun_path, dest, dest_len );
  trgt->target_addr.sun_path[dest_len] = '\0';

  trgt->local_addr.sun_family = AF_UNIX;
  memcpy( &trgt->local_addr.sun_path, source, source_len );
  trgt->local_addr.sun_path[source_len] = '\0';

  trgt->local_socket = socket( trgt->local_addr.sun_family, SOCK_DGRAM, 0 );
  if( trgt->local_socket < 0 ) {
    free_mem( trgt );
    return NULL;
  }

  if( bind
      ( trgt->local_socket, ( struct sockaddr * ) &trgt->local_addr,
        sizeof( trgt->local_addr ) ) < 0 ) {
    free_mem( trgt );
    raise_socket_bind_failure(  );
    return NULL;
  }

  trgt->target_addr_len = sizeof( trgt->target_addr );

  return trgt;
}

int
sendto_socket_target( const struct socket_target *target, const char *msg ) {
  return sendto( target->local_socket, msg, strlen( msg ) + 1, 0,
                 ( struct sockaddr * ) &target->target_addr,
                 target->target_addr_len );
}
