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

#include <pthread.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/entry.h>
#include <stumpless/facility.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/file.h>
#include <stumpless/target/stream.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/formatter.h"
#include "private/memory.h"
#include "private/severity.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/target.h"
#include "private/target/buffer.h"
#include "private/target/file.h"
#include "private/target/stream.h"
#include "private/validate.h"

/* global static variables */
static struct stumpless_target *current_target = NULL;
static pthread_mutex_t current_target_mutex = PTHREAD_MUTEX_INITIALIZER;

static struct stumpless_target *default_target = NULL;
static pthread_mutex_t default_target_mutex = PTHREAD_MUTEX_INITIALIZER;

/* per-thread static variables */
static __thread struct stumpless_entry *cached_entry = NULL;

static
void
close_unsupported_target( const struct stumpless_target *target ) {
  ( void ) target;

  raise_target_unsupported( L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE );
}

int
stump( const char *message, ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstump( message, subs );
  va_end( subs );

  return result;
}

void
stumplog( int priority, const char *message, ... ) {
  va_list subs;

  va_start( subs, message );
  vstumplog( priority, message, subs );
  va_end( subs );
}

int
stumpless_add_entry( struct stumpless_target *target,
                     const struct stumpless_entry *entry ) {
  struct strbuilder *builder;
  size_t builder_length;
  const char *buffer;
  int result;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return -1;
  }

  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return -1;
  }

  if( !target->id ) {
    raise_invalid_id(  );
    return -1;
  }

  clear_error(  );

  // windows targets are not formatted in code
  // instead their formatting comes from message text files
  if( target->type == STUMPLESS_WINDOWS_EVENT_LOG_TARGET ) {
    return config_send_entry_to_wel_target( target->id, entry );
  }

  builder = format_entry( entry, target );
  if( !builder ) {
    return -1;
  }

  buffer = strbuilder_get_buffer( builder, &builder_length );

  switch ( target->type ) {

    case STUMPLESS_BUFFER_TARGET:
      result = sendto_buffer_target( target->id, buffer, builder_length );
      break;

    case STUMPLESS_FILE_TARGET:
      result = sendto_file_target( target->id, buffer, builder_length );
      break;

    case STUMPLESS_NETWORK_TARGET:
      result = config_sendto_network_target( target->id,
                                             buffer,
                                             builder_length );
      break;

    case STUMPLESS_SOCKET_TARGET:
      result = config_sendto_socket_target( target->id,
                                            buffer,
                                            builder_length );
      break;

    case STUMPLESS_STREAM_TARGET:
      result = sendto_stream_target( target->id, buffer, builder_length );
      break;

    default:
      result = sendto_unsupported_target( target, buffer, builder_length );
  }

  strbuilder_destroy( builder );
  return result;
}

int
stumpless_add_log( struct stumpless_target *target,
                   int priority,
                   const char *message,
                   ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstumpless_add_log( target, priority, message, subs );
  va_end( subs );

  return result;
}

int
stumpless_add_message( struct stumpless_target *target,
                       const char *message,
                       ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstumpless_add_message( target, message, subs );
  va_end( subs );

  return result;
}

void
stumpless_close_target( struct stumpless_target *target ) {
  clear_error(  );

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  switch( target->type ) {
    case STUMPLESS_BUFFER_TARGET:
      stumpless_close_buffer_target( target );
      break;

    case STUMPLESS_FILE_TARGET:
      stumpless_close_file_target( target );
      break;

    case STUMPLESS_NETWORK_TARGET:
      config_close_network_target( target );
      break;

    case STUMPLESS_SOCKET_TARGET:
      config_close_socket_target( target );
      break;

    case STUMPLESS_STREAM_TARGET:
      stumpless_close_stream_target( target );
      break;

    case STUMPLESS_WINDOWS_EVENT_LOG_TARGET:
      config_close_wel_target( target );
      break;

    default:
      raise_target_unsupported( L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE );

  }
}

struct stumpless_target *
stumpless_get_current_target( void ) {
  struct stumpless_target *result;

  clear_error(  );

  pthread_mutex_lock( &current_target_mutex );
  result = current_target;
  pthread_mutex_unlock( &current_target_mutex );

  if( result ) {
    return result;
  }

  result = stumpless_get_default_target(  );

  pthread_mutex_lock( &current_target_mutex );
  if( !current_target ) {
    current_target = result;
  } else {
    result = current_target;
  }
  pthread_mutex_unlock( &current_target_mutex );

  return result;
}

int
stumpless_get_default_facility( const struct stumpless_target *target ) {
  int prival;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return -1;
  }

  lock_target( target );
  prival = target->default_prival;
  unlock_target( target );

  clear_error(  );
  return get_facility( prival );
}

struct stumpless_target *
stumpless_get_default_target( void ) {
  struct stumpless_target *result;

  clear_error(  );

  pthread_mutex_lock( &default_target_mutex );
  if( !default_target ) {
    default_target = config_open_default_target(  );
  }
  result = default_target;
  pthread_mutex_unlock( &default_target_mutex );

  return result;
}

int
stumpless_get_option( const struct stumpless_target *target, int option ) {
  int options;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return 0;
  }

  lock_target( target );
  options = target->options;
  unlock_target( target );

  clear_error(  );
  return options & option;
}

const char *
stumpless_get_target_default_app_name( const struct stumpless_target *target ) {
  char *name_copy = NULL;

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  lock_target( target );
  if( !target->default_app_name ) {
    goto cleanup_and_return;
  }


  name_copy = alloc_mem( target->default_app_name_length + 1 );
  if( !name_copy ) {
    goto cleanup_and_return;
  }

  memcpy( name_copy,
          target->default_app_name,
          target->default_app_name_length + 1 );
  clear_error(  );

cleanup_and_return:
  unlock_target( target );
  return name_copy;
}

const char *
stumpless_get_target_default_msgid( const struct stumpless_target *target ) {
  char *msgid_copy = NULL;

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  lock_target( target );
  if( !target->default_msgid ) {
    goto cleanup_and_return;
  }

  msgid_copy = alloc_mem( target->default_msgid_length + 1 );
  if( !msgid_copy ) {
    goto cleanup_and_return;
  }

  memcpy( msgid_copy, target->default_msgid, target->default_msgid_length + 1 );
  clear_error(  );

cleanup_and_return:
  unlock_target( target );
  return msgid_copy;
}

const char *
stumpless_get_target_name( const struct stumpless_target *target ) {
  char *name_copy;

  if( !target ) {
    raise_argument_empty( "target is NULL" );
    return NULL;
  }

  lock_target( target );
  name_copy = alloc_mem( target->name_length + 1 );
  if( !name_copy ) {
    goto cleanup_and_return;
  }
  memcpy( name_copy, target->name, target->name_length + 1 );
  clear_error(  );

cleanup_and_return:
  unlock_target( target );
  return name_copy;
}

struct stumpless_target *
stumpless_open_target( struct stumpless_target *target ) {

  VALIDATE_ARG_NOT_NULL( target );

  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    raise_target_incompatible( L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE );
    return NULL;

  }
  clear_error(  );
  return config_open_network_target( target );
}

void
stumpless_set_current_target( struct stumpless_target *target ) {
  clear_error(  );

  pthread_mutex_lock( &current_target_mutex );
  current_target = target;
  pthread_mutex_unlock( &current_target_mutex );
}

struct stumpless_target *
stumpless_set_default_facility( struct stumpless_target *target,
                                int default_facility ) {
  int old_severity;

  VALIDATE_ARG_NOT_NULL( target );

  if( facility_is_invalid( default_facility ) ) {
    raise_invalid_facility( default_facility );
    return NULL;
  }

  lock_target( target );
  old_severity = get_severity( target->default_prival );
  target->default_prival = default_facility + old_severity;
  unlock_target( target );

  clear_error(  );
  return target;
}

struct stumpless_target *
stumpless_set_option( struct stumpless_target *target, int option ) {
  VALIDATE_ARG_NOT_NULL( target );

  lock_target( target );
  target->options |= option;
  unlock_target( target );

  clear_error(  );
  return target;
}

struct stumpless_target *
stumpless_set_target_default_app_name( struct stumpless_target *target,
                                       const char *app_name ) {
  size_t new_length;
  char *new_name;
  const char *old_name;

  VALIDATE_ARG_NOT_NULL( target );
  VALIDATE_ARG_NOT_NULL( app_name );

  new_name = copy_cstring_with_length( app_name, &new_length );
  if( !new_name ) {
    return NULL;

  }

  lock_target( target );
  old_name = target->default_app_name;
  target->default_app_name = new_name;
  target->default_app_name_length = new_length;
  unlock_target( target );

  free_mem( old_name );
  clear_error(  );
  return target;
}

struct stumpless_target *
stumpless_set_target_default_msgid( struct stumpless_target *target,
                                    const char *msgid ) {
  size_t new_length;
  char *new_msgid;
  const char *old_msgid;

  VALIDATE_ARG_NOT_NULL( target );
  VALIDATE_ARG_NOT_NULL( msgid );

  new_msgid = copy_cstring_with_length( msgid, &new_length );
  if( !new_msgid ) {
    return NULL;

  }

  lock_target( target );
  old_msgid = target->default_msgid;
  target->default_msgid = new_msgid;
  target->default_msgid_length = new_length;
  unlock_target( target );

  free_mem( old_msgid );
  clear_error(  );
  return target;
}

const struct stumpless_target *
stumpless_target_is_open( const struct stumpless_target *target ) {
  int is_open;

  clear_error(  );

  VALIDATE_ARG_NOT_NULL( target );

  if( target->type == STUMPLESS_NETWORK_TARGET ) {
    is_open = config_network_target_is_open( target );

  } else {
    is_open = 1;

  }

  if( is_open ) {
    return target;

  } else {
    return NULL;

  }
}

struct stumpless_target *
stumpless_unset_option( struct stumpless_target *target, int option ) {
  VALIDATE_ARG_NOT_NULL( target );

  lock_target( target );
  target->options &= ~option;
  unlock_target( target );

  clear_error(  );
  return target;
}

int
vstump( const char *message, va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return vstumpless_add_message( target, message, subs );
}

void
vstumplog( int priority, const char *message, va_list subs ) {
  struct stumpless_target *target;

  clear_error(  );

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  vstumpless_add_log( target, priority, message, subs );
}

int
vstumpless_add_log( struct stumpless_target *target,
                    int priority,
                    const char *message,
                    va_list subs ) {
  const struct stumpless_entry *set_result;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return -1;
  }

  if( !cached_entry ) {
    cached_entry = vstumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
                                         target->default_app_name,
                                         target->default_msgid,
                                         message,
                                         subs );
    if( !cached_entry ) {
      return -1;
    }

  } else {
    set_result = vstumpless_set_entry_message( cached_entry, message, subs );
    if( !set_result ) {
      return -1;
    }

    set_result = stumpless_set_entry_app_name( cached_entry,
                                               target->default_app_name );
    if( !set_result ) {
      return -1;
    }

    set_result = stumpless_set_entry_msgid( cached_entry,
                                            target->default_msgid );
    if( !set_result ) {
      return -1;
    }

  }

  cached_entry->prival = priority;

  return stumpless_add_entry( target, cached_entry );
}

int
vstumpless_add_message( struct stumpless_target *target,
                        const char *message,
                        va_list subs ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return -1;
  }

  return vstumpless_add_log( target, target->default_prival, message, subs );
}

/* private definitions */

void
destroy_target( const struct stumpless_target *target ) {
  if( target == current_target ) {
    current_target = NULL;
  }

  pthread_mutex_destroy( ( pthread_mutex_t * ) &target->target_mutex );
  free_mem( target->default_app_name );
  free_mem( target->default_msgid );
  free_mem( target->name );
  free_mem( target );
}

int
lock_target( const struct stumpless_target *target ) {
  return pthread_mutex_lock( ( pthread_mutex_t * ) &target->target_mutex );
}

struct stumpless_target *
new_target( enum stumpless_target_type type,
            const char *name,
            int options,
            int default_facility ) {
  struct stumpless_target *target;
  int default_prival;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->name = copy_cstring_with_length( name, &target->name_length );
  if( !target->name ) {
    goto fail_name;
  }

  pthread_mutex_init( &target->target_mutex, NULL );
  target->type = type;
  target->options = options;
  default_prival = get_prival( default_facility, STUMPLESS_SEVERITY_INFO );
  target->default_prival = default_prival;
  target->default_app_name = NULL;
  target->default_app_name_length = 0;
  target->default_msgid = NULL;
  target->default_msgid_length = 0;

  return target;

fail_name:
  free_mem( target );
fail:
  return NULL;
}

struct stumpless_target *
open_unsupported_target( struct stumpless_target *target ) {
  ( void ) target;

  raise_target_unsupported( L10N_OPEN_UNSUPPORTED_TARGET_ERROR_MESSAGE );
  return NULL;
}

int
send_entry_to_unsupported_target( const struct stumpless_target *target,
                                  const struct stumpless_entry *entry ) {
  ( void ) target;
  ( void ) entry;

  raise_target_unsupported(
    L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE
  );
  return -1;
}

int
sendto_unsupported_target( const struct stumpless_target *target,
                           const char *msg,
                           size_t msg_length ) {
  ( void ) target;
  ( void ) msg;
  ( void ) msg_length;

  raise_target_unsupported(
    L10N_SEND_MESSAGE_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE
  );
  return -1;
}

void
target_free_global( void ) {
  config_close_default_target( default_target );
  default_target = NULL;
}

void
target_free_thread( void ) {
  stumpless_destroy_entry( cached_entry );
  cached_entry = NULL;
}

int
unlock_target( const struct stumpless_target *target ) {
  return pthread_mutex_unlock( ( pthread_mutex_t * ) &target->target_mutex );
}

int
unsupported_target_is_open( const struct stumpless_target *target ) {
  ( void ) target;

  raise_target_unsupported( L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE );
  return 0;
}
