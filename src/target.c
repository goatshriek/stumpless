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

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/facility.h>
#include <stumpless/filter.h>
#include <stumpless/option.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/error.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/file.h>
#include <stumpless/target/function.h>
#include <stumpless/target/stream.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper.h"
#include "private/config/wrapper/journald.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/formatter.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/severity.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/target.h"
#include "private/target/buffer.h"
#include "private/target/file.h"
#include "private/target/function.h"
#include "private/target/stream.h"
#include "private/validate.h"

/* global static variables */
static config_atomic_ptr_t current_target = config_atomic_ptr_initializer;
static config_atomic_ptr_t default_target = config_atomic_ptr_initializer;
static config_atomic_ptr_t cons_stream = config_atomic_ptr_initializer;
static config_atomic_bool_t cons_stream_free = config_atomic_bool_true;
static config_atomic_bool_t cons_stream_valid = config_atomic_bool_false;

/* per-thread static variables */
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_entry *cached_entry = NULL;
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_entry *cached_trace = NULL;

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

int
stump_trace( const char *file,
             int line,
             const char *func,
             const char *message, ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstump_trace( file, line, func, message, subs );
  va_end( subs );

  return result;
}

int
stumpless_add_entry( struct stumpless_target *target,
                     const struct stumpless_entry *entry ) {
  stumpless_filter_func_t filter;
  struct strbuilder *builder;
  size_t builder_length;
  const char *buffer = NULL;
  int result;
  FILE *error_stream;

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

  filter = stumpless_get_target_filter( target );
  if( filter && !filter( target, entry ) ) {
    return 0;
  }
 
  if( stumpless_get_option( target, STUMPLESS_OPTION_PERROR ) ){
    // setting is_log_formatted true concludes that STUMPLESS_OPTION_PERROR
    // option is set, thus only checking this flag is enough for further checks
    // NOTE : Calling the format_entry twice because if the buffer is for target
    // who require unformatted entry would need not to call format_entry.
    builder = format_entry( entry, target );
    if( !builder ) {
      return -1;
    }
    buffer = strbuilder_get_buffer( builder, &builder_length );
    error_stream = stumpless_get_error_stream();
    if( fwrite( buffer, 1, builder_length, error_stream) != builder_length ){
      return -1;
    }
  }

  // function targets are not formatted
  if( target->type == STUMPLESS_FUNCTION_TARGET ) {
    return send_entry_to_function_target( target, entry );
  }

  // journald targets are not formatted
  if( target->type == STUMPLESS_JOURNALD_TARGET ) {
    return config_send_entry_to_journald_target( target, entry );
  }

  // windows targets are not formatted in code
  // instead their formatting comes from message text files
  if( target->type == STUMPLESS_WINDOWS_EVENT_LOG_TARGET ) {
    return config_send_entry_to_wel_target( target->id, entry );
  }

  // entry was not formatted before
  if( buffer == NULL ){
    builder = format_entry( entry, target );
    if( !builder ) {
      return -1;
    }
    buffer = strbuilder_get_buffer( builder, &builder_length );

  }
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

    case STUMPLESS_FUNCTION_TARGET:
      stumpless_close_function_target( target );
      break;

    case STUMPLESS_JOURNALD_TARGET:
      config_close_journald_target( target );
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

  result = config_read_ptr( &current_target );
  if( result ) {
    return result;
  }

  result = stumpless_get_default_target(  );
  config_compare_exchange_ptr( &current_target, NULL, result );

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

  result = config_read_ptr( &default_target );

  while( !result ) {
    result = config_open_default_target(  );

    if( !config_compare_exchange_ptr( &default_target, NULL, result ) ) {
      config_close_default_target( result );
      result = config_read_ptr( &default_target );
    }
  }

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

  VALIDATE_ARG_NOT_NULL( target );
  clear_error(  );

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

  VALIDATE_ARG_NOT_NULL( target );
  clear_error(  );

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

stumpless_filter_func_t
stumpless_get_target_filter( const struct stumpless_target *target ) {
  stumpless_filter_func_t filter;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return 0;
  }

  lock_target( target );
  filter = target->filter;
  unlock_target( target );

  clear_error(  );
  return filter;
}

int
stumpless_get_target_mask( const struct stumpless_target *target ) {
  int mask;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return 0;
  }

  lock_target( target );
  mask = target->mask;
  unlock_target( target );

  clear_error(  );
  return mask;
}

const char *
stumpless_get_target_name( const struct stumpless_target *target ) {
  char *name_copy;

  VALIDATE_ARG_NOT_NULL( target );

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
  struct stumpless_target *result;

  VALIDATE_ARG_NOT_NULL( target );
  clear_error(  );

  lock_target( target );
  if( target->type != STUMPLESS_NETWORK_TARGET ) {
    unlock_target( target );
    raise_target_incompatible( L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE );
    return NULL;
  }

  result = config_open_network_target( target );
  unlock_target( target );

  return result;
}

void
stumpless_set_current_target( struct stumpless_target *target ) {
  clear_error(  );
  config_write_ptr( &current_target, target );
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

  if( !validate_app_name_length( app_name ) ||
      !validate_printable_ascii( app_name ) ) {
    return NULL;
  }

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

  if( !validate_msgid_length( msgid ) || !validate_printable_ascii( msgid ) ) {
      return NULL;
  }

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

struct stumpless_target *
stumpless_set_target_filter( struct stumpless_target *target,
                             stumpless_filter_func_t filter ) {
  VALIDATE_ARG_NOT_NULL( target );

  lock_target( target );
  target->filter = filter;
  unlock_target( target );

  clear_error(  );
  return target;
}

struct stumpless_target *
stumpless_set_target_mask( struct stumpless_target *target, int mask ) {
  VALIDATE_ARG_NOT_NULL( target );

  lock_target( target );
  target->mask = mask;
  unlock_target( target );

  clear_error(  );
  return target;
}

const struct stumpless_target *
stumpless_target_is_open( const struct stumpless_target *target ) {
  int is_open = 1;

  VALIDATE_ARG_NOT_NULL( target );
  clear_error(  );

  lock_target( target );
  if( target->type == STUMPLESS_NETWORK_TARGET ) {
    is_open = config_network_target_is_open( target );
  }
  unlock_target( target );

  return is_open ? target : NULL;
}

int
stumpless_trace_entry( struct stumpless_target *target,
                       struct stumpless_entry *entry,
                       const char *file,
                       int line,
                       const char *func ) {
  char digits[MAX_INT_SIZE];
  char *line_str;

  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return -1;
  }

  if( !file ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "file" ) );
    return -1;
  }

  if( !func ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "file" ) );
    return -1;
  }

  digits[MAX_INT_SIZE-1] = '\0';
  line_str = digits + MAX_INT_SIZE - 1;
  if( line == 0 ) {
    line_str--;
    *line_str = '0';
  } else {
    while( line != 0 ) {
      line_str--;
      *line_str = ( line % 10 ) + 48;
      line /= 10;
    }
  }

  stumpless_set_entry_param_value_by_name( entry, "trace", "file", file );
  if( stumpless_has_error(  ) ) {
    return -1;
  }

  stumpless_set_entry_param_value_by_name( entry, "trace", "line", line_str );
  if( stumpless_has_error(  ) ) {
    return -1;
  }

  stumpless_set_entry_param_value_by_name( entry, "trace", "function", func );
  if( stumpless_has_error(  ) ) {
    return -1;
  }

  return stumpless_add_entry( target, entry );
}

int
stumpless_trace_log( struct stumpless_target *target,
                     int priority,
                     const char *file,
                     int line,
                     const char *func,
                     const char *message,
                     ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstumpless_trace_log( target,
                                 priority,
                                 file,
                                 line,
                                 func,
                                 message,
                                 subs );
  va_end( subs );

  return result;
}

int
stumpless_trace_message( struct stumpless_target *target,
                         const char *file,
                         int line,
                         const char *func,
                         const char *message,
                         ... ) {
  int result;
  va_list subs;

  va_start( subs, message );
  result = vstumpless_trace_message( target, file, line, func, message, subs );
  va_end( subs );

  return result;
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

void
stumplog( int priority, const char *message, ... ) {
  va_list subs;

  va_start( subs, message );
  vstumplog( priority, message, subs );
  va_end( subs );
}

int
stumplog_set_mask( int mask ) {
  struct stumpless_target *target;
  int old_mask;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return 0;
  }

  lock_target( target );
  old_mask = target->mask;
  target->mask = mask;
  unlock_target( target );

  return old_mask;
}

void
stumplog_trace( int priority,
                const char *file,
                int line,
                const char *func,
                const char *message, ... ) {
  va_list subs;

  va_start( subs, message );
  vstumplog_trace( priority, file, line, func, message, subs );
  va_end( subs );
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

int
vstump_trace( const char *file,
              int line,
              const char *func,
              const char *message,
              va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return -1;
  }

  return vstumpless_trace_message( target, file, line, func, message, subs );
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

int
vstumpless_trace_log( struct stumpless_target *target,
                      int priority,
                      const char *file,
                      int line,
                      const char *func,
                      const char *message,
                      va_list subs ) {
  const struct stumpless_entry *set_result;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return -1;
  }

  if( !cached_trace ) {
    cached_trace = vstumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
                                         target->default_app_name,
                                         target->default_msgid,
                                         message,
                                         subs );
    if( !cached_trace ) {
      return -1;
    }

  } else {
    set_result = vstumpless_set_entry_message( cached_trace,
                                               message,
                                               subs );
    if( !set_result ) {
      return -1;
    }

    set_result = stumpless_set_entry_app_name( cached_trace,
                                               target->default_app_name );
    if( !set_result ) {
      return -1;
    }

    set_result = stumpless_set_entry_msgid( cached_trace,
                                            target->default_msgid );
    if( !set_result ) {
      return -1;
    }

  }

  cached_trace->prival = priority;

  return stumpless_trace_entry( target, cached_trace, file, line, func );
}

int
vstumpless_trace_message( struct stumpless_target *target,
                          const char *file,
                          int line,
                          const char *func,
                          const char *message,
                          va_list subs ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return -1;
  }

  return vstumpless_trace_log( target,
                               target->default_prival,
                               file,
                               line,
                               func,
                               message,
                               subs );
}

void
vstumplog( int priority, const char *message, va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  vstumpless_add_log( target, priority, message, subs );
}

void
vstumplog_trace( int priority,
                 const char * file,
                 int line,
                 const char *func,
                 const char *message,
                 va_list subs ) {
  struct stumpless_target *target;

  target = stumpless_get_current_target(  );
  if( !target ) {
    return;
  }

  vstumpless_trace_log( target, priority, file, line, func, message, subs );
}

/* private definitions */

void
destroy_target( const struct stumpless_target *target ) {
  config_compare_exchange_ptr( &current_target, target, NULL );

  config_destroy_cached_mutex( target->mutex );
  free_mem( target->default_app_name );
  free_mem( target->default_msgid );
  free_mem( target->name );
  free_mem( target );
}

void
lock_target( const struct stumpless_target *target ) {
  config_lock_mutex( target->mutex );
}

struct stumpless_target *
new_target( enum stumpless_target_type type, const char *name ) {
  struct stumpless_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  target->name = copy_cstring_with_length( name, &target->name_length );
  if( !target->name ) {
    goto fail_name;
  }

  config_assign_cached_mutex( target->mutex );
  if( !config_check_mutex_valid( target->mutex ) ) {
    goto fail_mutex;
  }

  target->type = type;
  target->options = STUMPLESS_OPTION_NONE;
  target->default_prival = get_prival( STUMPLESS_DEFAULT_FACILITY,
                                       STUMPLESS_DEFAULT_SEVERITY );
  target->default_app_name = NULL;
  target->default_app_name_length = 0;
  target->default_msgid = NULL;
  target->default_msgid_length = 0;
  target->mask = STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_DEBUG_VALUE );
  target->filter = stumpless_mask_filter;

  return target;

fail_mutex:
  free_mem( target->name );
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
  config_close_default_target( config_read_ptr( &default_target ) );
  config_write_ptr( &default_target, NULL );
}

void
target_free_thread( void ) {
  stumpless_destroy_entry_and_contents( cached_entry );
  cached_entry = NULL;

  stumpless_destroy_entry_and_contents( cached_trace );
  cached_trace = NULL;
}

void
unlock_target( const struct stumpless_target *target ) {
  config_unlock_mutex( target->mutex );
}

int
unsupported_target_is_open( const struct stumpless_target *target ) {
  ( void ) target;

  raise_target_unsupported( L10N_UNSUPPORTED_TARGET_IS_OPEN_ERROR_MESSAGE );
  return 0;
}

FILE *
stumpless_get_cons_stream( void ) {
  if( config_read_bool( &cons_stream_valid ) ) {
    return config_read_ptr( &cons_stream );
  } else {
    return stdout;
  }
}

void
stumpless_set_cons_stream( FILE *stream) {
  config_write_ptr( &cons_stream, stream );
  config_write_bool( &cons_stream_valid, true );
}
