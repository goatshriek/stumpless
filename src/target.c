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
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/config/wrapper.h"
#include "private/error.h"
#include "private/formatter.h"
#include "private/memory.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/target.h"
#include "private/target/buffer.h"

static struct stumpless_target *current_target = NULL;
static struct id_map *priv_targets = NULL;
static struct stumpless_entry *cached_entry = NULL;

int
stumpless( const char *message ) {
  struct stumpless_target *target;
  int result, severity, facility;

  clear_error(  );

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  if( !cached_entry ) {
    cached_entry = stumpless_new_entry( 0, 0, "-", "-", message );
    if( !cached_entry ) {
      return -1;
    }

    cached_entry->prival = current_target->default_prival;

    if( target->default_app_name ) {
      cached_entry->app_name = alloc_mem( target->default_app_name_length );
      if( !cached_entry->app_name ) {
        return -1;
      }

      memcpy( cached_entry->app_name, target->default_app_name,
              target->default_app_name_length );
      cached_entry->app_name_length = target->default_app_name_length;
    }

    if( target->default_msgid ) {
      cached_entry->msgid = alloc_mem( target->default_msgid_length );
      if( !cached_entry->msgid ) {
        return -1;
      }

      memcpy( cached_entry->msgid, target->default_msgid,
              target->default_msgid_length );
      cached_entry->msgid_length = target->default_msgid_length;
    }

  }

  stumpless_set_entry_message( cached_entry, message );

  result = stumpless_add_entry( target, cached_entry );
  return result;
}

int
stumpless_add_entry( struct stumpless_target *target,
                     struct stumpless_entry *entry ) {
  struct strbuilder *builder;
  size_t builder_length;
  const char *buffer;
  int result;

  clear_error(  );

  if( !target || !entry ) {
    raise_argument_empty(  );
    return -1;
  }

  if( !target->id ) {
    raise_invalid_id(  );
    return -1;
  }

  builder = format_entry( target, entry );
  if( !builder ) {
    return -1;
  }

  buffer = strbuilder_get_buffer( builder, &builder_length );

  switch ( target->type ) {
    case STUMPLESS_SOCKET_TARGET:
      result =
        config_sendto_socket_target( target->id, buffer, builder_length );
      break;
    case STUMPLESS_BUFFER_TARGET:
      result = sendto_buffer_target( target->id, buffer, builder_length );
      break;
    default:
      result = target_unsupported( target, buffer, builder_length );
  }

  strbuilder_destroy( builder );
  return result;
}

struct stumpless_target *
stumpless_get_current_target( void ) {
  clear_error(  );

  return current_target;
}

void
stumpless_set_current_target( struct stumpless_target *target ) {
  current_target = target;
}

struct stumpless_target *
stumpless_set_target_default_app_name( struct stumpless_target *target,
                                       const char *app_name ) {
  size_t *app_name_length;
  char *sized_name;

  clear_error(  );

  app_name_length = &( target->default_app_name_length );
  sized_name = cstring_to_sized_string( app_name, app_name_length );
  if( !sized_name ) {
    return NULL;

  } else {
    target->default_app_name = sized_name;
    return target;

  }
}

struct stumpless_target *
stumpless_set_target_default_msgid( struct stumpless_target *target,
                                    const char *msgid ) {
  size_t *msgid_length;
  char *sized_msgid;

  clear_error(  );

  msgid_length = &( target->default_msgid_length );
  sized_msgid = cstring_to_sized_string( msgid, msgid_length );
  if( !sized_msgid ) {
    return NULL;

  } else {
    target->default_msgid = sized_msgid;
    return target;

  }
}

/* private definitions */

int
target_unsupported( const struct stumpless_target *target,
                    const char *msg, size_t msg_length ) {
  raise_target_unsupported(  );
  return -1;
}
