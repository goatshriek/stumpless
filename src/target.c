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
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/formatter.h"
#include "private/memory.h"
#include "private/strhelper.h"
#include "private/target.h"
#include "private/target/buffer.h"

static struct stumpless_target *current_target = NULL;

int
stumpless( const char *message ) {
  struct stumpless_entry *entry;
  struct stumpless_target *target;
  int result, severity, facility;

  clear_error(  );

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  // todo this entry creation should happen only once, not every time an event
  // is logged
  facility = get_facility(current_target->default_prival);
  severity = get_severity(current_target->default_prival);
  entry = stumpless_new_entry( facility, severity, "-", "-", message );
  if( !entry ) {
    return -1;
  }

  if( target->default_app_name ){
    entry->app_name = alloc_mem( target->default_app_name_length );
    if( !entry->app_name ){
      return -1;
    }
 
    memcpy( entry->app_name, target->default_app_name, target->default_app_name_length );
    entry->app_name_length = target->default_app_name_length;
  }

  if( target->default_msgid ){
    entry->msgid = alloc_mem( target->default_msgid_length );
    if( !entry->msgid ){
      return -1;
    }
 
    memcpy( entry->msgid, target->default_msgid, target->default_msgid_length );
    entry->msgid_length = target->default_msgid_length;
  }

  result = stumpless_add_entry( target, entry );
  stumpless_destroy_entry( entry );
  return result;
}

int
stumpless_add_entry( struct stumpless_target *target,
                     struct stumpless_entry *entry ) {
  char *message;

  clear_error(  );

  if( !target || !entry ) {
    raise_argument_empty(  );
    return -1;
  }

  message = format_entry( target, entry );

  switch ( target->type ) {
    case STUMPLESS_SOCKET_TARGET:
      return config_sendto_socket_target( target, message );
    case STUMPLESS_BUFFER_TARGET:
      if( sendto_buffer_target( target, message ) <= 0 ) {
        return -1;
      }
      break;
    default:
      return target_unsupported( target, message );
  }

  return 0;
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
                                       const char *app_name){
  size_t *app_name_length;
  char *sized_name;

  clear_error(  );

  app_name_length = &( target->default_app_name_length );
  sized_name = cstring_to_sized_string( app_name, app_name_length );
  if( !sized_name ){
    return NULL;

  } else {
    target->default_app_name = sized_name;
    return target;

  }
}

struct stumpless_target *
stumpless_set_target_default_msgid(struct stumpless_target *target,
                                   const char *msgid){
  size_t *msgid_length;
  char *sized_msgid;

  clear_error(  );

  msgid_length = &( target->default_msgid_length );
  sized_msgid = cstring_to_sized_string( msgid, msgid_length );
  if( !sized_msgid ){
    return NULL;

  } else {
    target->default_msgid = sized_msgid;
    return target;

  }
}

/* private definitions */

int
target_unsupported( const struct stumpless_target *target, const char *msg ) {
  raise_target_unsupported(  );
  return -1;
}
