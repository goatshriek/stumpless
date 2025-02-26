// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
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
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stumpless/option.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/socket.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/socket.h"
#include "private/validate.h"

void
stumpless_close_socket_target( const struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  if( target->type != STUMPLESS_SOCKET_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_socket_target( target->id );
  destroy_target( target );

  clear_error(  );
}

struct stumpless_target *
stumpless_open_socket_target( const char *name,
                              const char *local_socket ) {
  struct stumpless_target *target;
  size_t name_len;
  size_t local_socket_len;
  char temp_name[18];
  size_t temp_name_len;

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_SOCKET_TARGET, name );

  if( !target ) {
    goto fail;
  }

  name_len = strlen( name );

  if( !local_socket ) {
    temp_name_len = config_get_local_socket_name( temp_name );
    target->id = new_socket_target( name, name_len, temp_name, temp_name_len );
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

int
socket_target_is_open( const struct stumpless_target *target ) {
  return ( ( (struct socket_target *) target->id )->local_socket != -1 );
}

struct stumpless_target *
open_socket_target( struct stumpless_target *target) {
  const struct socket_target *result;

  result = open_bind_socket( target->id );
  if ( !result ) {
    return NULL;
  }

  return target;
}

struct socket_target *
open_bind_socket( struct socket_target *target ) {
  int bind_result;

  clear_error(  );

  target->local_socket = socket( target->local_addr.sun_family, SOCK_DGRAM, 0 );
  if( target->local_socket < 0 ) {
    raise_socket_failure( L10N_UNIX_SOCKET_FAILED_ERROR_MESSAGE,
                          errno,
                          L10N_ERRNO_ERROR_CODE_TYPE );
    return NULL;
  }

  bind_result= bind( target->local_socket,
                     ( struct sockaddr * ) &target->local_addr,
                     sizeof( target->local_addr ) );

  if( bind_result < 0 ) {
    raise_socket_bind_failure( L10N_BIND_UNIX_SOCKET_FAILED_ERROR_MESSAGE,
                               errno,
                               L10N_ERRNO_ERROR_CODE_TYPE );
    goto fail_bind;
  }

  return target;

fail_bind:
  close( target->local_socket );
  return NULL;
}

struct socket_target *
new_socket_target( const char *dest,
                   size_t dest_len,
                   const char *source,
                   size_t source_len ) {
  struct socket_target *target;
  struct socket_target *open_result;
  int options;

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

  target->target_addr_len = sizeof( target->target_addr );
  target->local_socket = -1;

  options = stumpless_get_default_options(  );
  if ( !( options & STUMPLESS_OPTION_ODELAY ) ) {
    open_result = open_bind_socket( target );
    if ( !open_result ) {
      goto fail_open;
    }
  }

  return target;

fail_open:
  free_mem( target );  
fail:
  return NULL;
}

int
sendto_socket_target( const struct socket_target *target,
                      const char *msg, size_t msg_length ) {
  int result;

  // leave off the newline
  msg_length--;

  result = sendto( target->local_socket,
                  msg,
                  msg_length,
                  0,
                  ( const struct sockaddr * ) &target->target_addr,
                  target->target_addr_len );

  if( result == -1 ) {
    raise_socket_send_failure( L10N_SENDTO_UNIX_SOCKET_FAILED_ERROR_MESSAGE,
                               errno,
                               L10N_ERRNO_ERROR_CODE_TYPE );
  }

  return result;
}
