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
#include "private/id.h"
#include "private/memory.h"
#include "private/target/socket.h"

static struct id_map *targets = NULL;

void
stumpless_close_socket_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty(  );
    return;
  }

  if( targets ) {
    destroy_socket_target( get_by_id( targets, target->id ) );
  }
  // todo need to clean up the id list
}

struct stumpless_target *
stumpless_open_socket_target( const char *name, int options,
                              int default_facility ) {
  struct stumpless_target *pub_target;
  struct socket_target *priv_target;
  size_t name_len;

  clear_error(  );

  if( !name ) {
    raise_argument_empty(  );
    return NULL;
  }

  if( !targets ) {
    targets = new_id_map(  );
    if( !targets ) {
      goto fail;
    }
  }

  pub_target = alloc_mem( sizeof( *pub_target ) );
  if( !pub_target ) {
    goto fail;
  }

  name_len = strlen( name );
  priv_target = new_socket_target( name, name_len );
  if( !priv_target ) {
    goto fail_priv_target;
  }

  pub_target->name = alloc_mem( name_len );
  if( !pub_target->name ) {
    goto fail_pub_name;
  }

  memcpy( pub_target->name, name, name_len );
  pub_target->name[name_len] = '\0';
  pub_target->type = STUMPLESS_SOCKET_TARGET;
  pub_target->options = options;
  pub_target->default_prival =
    get_prival( default_facility, STUMPLESS_SEVERITY_INFO );
  pub_target->id = add_to_id_map( targets, priv_target );

  stumpless_set_current_target( pub_target );
  return pub_target;

fail_pub_name:
  free_mem( priv_target );
fail_priv_target:
  free_mem( pub_target );
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
  free_mem( trgt );
}

struct socket_target *
new_socket_target( const char *dest, size_t dest_len ) {
  struct socket_target *trgt;

  trgt = alloc_mem( sizeof( *trgt ) );
  if( !trgt ) {
    return NULL;
  }

  trgt->target_addr.sun_family = AF_UNIX;
  // todo need to check dest_len before this memcpy happens
  memcpy( &trgt->target_addr.sun_path, dest, dest_len );
  trgt->target_addr.sun_path[dest_len] = '\0';

  trgt->local_addr.sun_family = AF_UNIX;
  memcpy( &trgt->local_addr.sun_path, "\0/stmplss-tst", 14 );

  trgt->local_socket = socket( trgt->local_addr.sun_family, SOCK_DGRAM, 0 );
  if( trgt->local_socket < 0 ) {
    free_mem( trgt );
    return NULL;
  }

  if( bind
      ( trgt->local_socket, ( struct sockaddr * ) &trgt->local_addr,
        sizeof( trgt->local_addr ) ) < 0 ) {
    free_mem( trgt );
    return NULL;
  }

  trgt->target_addr_len = sizeof( trgt->target_addr );

  return trgt;
}

int
sendto_socket_target( const struct stumpless_target *target, const char *msg ) {
  struct socket_target *priv_trgt;

  if( !target || !targets || !msg ) {
    return 0;
  }

  priv_trgt = get_by_id( targets, target->id );

  return sendto( priv_trgt->local_socket, msg, strlen( msg ) + 1, 0,
                 ( struct sockaddr * ) &priv_trgt->target_addr,
                 priv_trgt->target_addr_len );
}
