// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/facility.h>
#include <stumpless/filter.h>
#include <stumpless/option.h>
#include <stumpless/param.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/error.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/file.h>
#include <stumpless/target/function.h>
#include <stumpless/target/stream.h>
#include "private/config.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/chain.h"
#include "private/config/wrapper/open_default_target.h"
#include "private/config/wrapper/wel.h"
#include "private/config/wrapper/journald.h"
#include "private/config/wrapper/network_supported.h"
#include "private/config/wrapper/fopen.h"
#include "private/config/wrapper/socket.h"
#include "private/config/wrapper/sqlite3.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/element.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/formatter.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/param.h"
#include "private/prival.h"
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
static const char *target_type_enum_to_string[] = {
  STUMPLESS_FOREACH_TARGET_TYPE( GENERATE_STRING )
};
static config_atomic_int_t default_option = STUMPLESS_OPTION_NDELAY;
static config_atomic_ptr_t current_target = config_atomic_ptr_initializer;
static config_atomic_ptr_t default_target = config_atomic_ptr_initializer;
static config_atomic_ptr_t cons_stream = config_atomic_ptr_initializer;
static config_atomic_bool_t cons_stream_free = config_atomic_bool_true;
static config_atomic_bool_t cons_stream_valid = config_atomic_bool_false;

/* per-thread static variables */
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_entry cached_entry;
static CONFIG_THREAD_LOCAL_STORAGE bool cached_entry_valid = false;
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_entry cached_trace;
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_element trace_element;
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_param trace_file;
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_param trace_line;
static CONFIG_THREAD_LOCAL_STORAGE struct stumpless_param trace_function;
static CONFIG_THREAD_LOCAL_STORAGE bool cached_trace_valid = false;


/* static functions */

/**
 * Adds the element with the trace params to the entry used for trace calls.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap lock**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation routines and mutex initializers.
 *
 * **Async Cancel Safety: AC-Unsafe heap lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use memory allocation routines and mutex initializers.
 *
 * @return Returns the trace entry upon success, or NULL if an error was
 * encountered.
 */
static
struct stumpless_entry *
add_trace_element( void ) {
    if( unlikely( !unchecked_load_param( &trace_file, "file", 4, "-" ) ) ) {
      goto fail;
    }

    if( unlikely( !unchecked_load_param( &trace_line, "line", 4, "-") ) ) {
      goto fail_line;
    }

    if( unlikely( !unchecked_load_param( &trace_function,
                                         "function",
                                         8,
                                         "-" ) ) ) {
      goto fail_function;
    }

    if( unlikely( !unchecked_load_element( &trace_element, "trace", 5 ) ) ) {
      goto fail_element;
    }

    if( unlikely( !stumpless_add_param( &trace_element, &trace_file ) ) ) {
      goto fail_add;
    }

    if( unlikely( !stumpless_add_param( &trace_element, &trace_line ) ) ) {
      goto fail_add;
    }

    if( unlikely( !stumpless_add_param( &trace_element, &trace_function ) ) ) {
      goto fail_add;
    }

    if( unlikely( !stumpless_add_element( &cached_trace, &trace_element ) ) ) {
      goto fail_add;
    }

    return &cached_trace;

fail_add:
    unchecked_unload_element( &trace_element );
fail_element:
    stumpless_unload_param( &trace_function );
fail_function:
    stumpless_unload_param( &trace_line );
fail_line:
    stumpless_unload_param( &trace_file );
fail:
    return NULL;
}

/* public definitions */

const char *
stumpless_get_target_type_string( enum stumpless_target_type target_type ){
  size_t upper_bound;

  upper_bound = sizeof( target_type_enum_to_string ) / sizeof( const char * );
  if ( target_type >= 0 && target_type < cap_size_t_to_int( upper_bound ) ) {
    return target_type_enum_to_string[target_type];
  } else {
    return "NO_SUCH_TARGET_TYPE";
  }
}

static
void
close_unsupported_target( const struct stumpless_target *target ) {
  ( void ) target;

  raise_target_unsupported( L10N_CLOSE_UNSUPPORTED_TARGET_ERROR_MESSAGE );
}

int
stumpless_add_entry( struct stumpless_target *target,
                     const struct stumpless_entry *entry ) {
  stumpless_filter_func_t filter;
  struct strbuilder *builder = NULL;
  size_t builder_length;
  const char *buffer = NULL;
  int result;
  FILE *current_cons_stream;
  bool locked;
  int options;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );
  VALIDATE_ARG_NOT_NULL_INT_RETURN( entry );

  if( unlikely( !target->id ) ) {
    raise_invalid_id(  );
    return -1;
  }

  options = target->options;
  if ( ( options & STUMPLESS_OPTION_ODELAY ) ) {
    target = stumpless_open_target( target );
    if ( !target ) {
      return -1;
    }
  }

  filter = stumpless_get_target_filter( target );
  if( filter && !filter( target, entry ) ) {
    return 0;
  }

  if( stumpless_get_option( target, STUMPLESS_OPTION_PERROR ) ){
    builder = format_entry( entry, target );
    if( !builder ) {
      return -1;
    }
    buffer = strbuilder_get_buffer( builder, &builder_length );
    write_to_error_stream( buffer, builder_length );
  }

  // chain targets simply pass the entry on
  if( target->type == STUMPLESS_CHAIN_TARGET ) {
    result = config_send_entry_to_chain_target( target->id, entry );
    goto finish;
  }

  // function targets are not formatted
  if( target->type == STUMPLESS_FUNCTION_TARGET ) {
    result = send_entry_to_function_target( target, entry );
    goto finish;
  }

  // journald targets are not formatted
  if( target->type == STUMPLESS_JOURNALD_TARGET ) {
    result = config_send_entry_to_journald_target( target, entry );
    goto finish;
  }

  // sqlite3 targets are not formatted
  if( target->type == STUMPLESS_SQLITE3_TARGET ) {
    result = config_send_entry_to_sqlite3_target( target, entry );
    goto finish;
  }

  // entry was not formatted before
  if( !buffer ){
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
      result = sendto_stream_target( target->id, buffer, builder_length, entry );
      break;

    case STUMPLESS_WINDOWS_EVENT_LOG_TARGET:
      result = config_sendto_wel_target( target->id,
                                         entry,
                                         buffer,
                                         builder_length );
      break;

    default:
      result = sendto_unsupported_target( target, buffer, builder_length );
  }

  /* STUMPLESS_OPTION_CONS: if target write fails, write to system console.
   * Important: use unchecked_ to preserve the error from the failed target.
   * Ignore any further errors; more important to return the original result.
   */
  if ( result < 0 && unchecked_get_option( target, STUMPLESS_OPTION_CONS ) ) {
    current_cons_stream = stumpless_get_cons_stream(  );
    if ( current_cons_stream ) {
      do {
        locked = config_compare_exchange_bool( &cons_stream_free, true, false );
      } while( !locked );

      fwrite( buffer, sizeof( char ), builder_length, current_cons_stream );

      config_write_bool( &cons_stream_free, true );
    }
  }

finish:
  if( builder ) {
    strbuilder_destroy( builder );
  }
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
stumpless_add_log_str( struct stumpless_target *target,
                       int priority,
                       const char *message ) {
  const struct stumpless_entry *result;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

  if( unlikely( !cached_entry_valid ) ) {
    result = stumpless_load_entry_str( &cached_entry,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       NULL,
                                       NULL,
                                       message );
    if( unlikely( !result ) ) {
      return -1;
    }
    cached_entry_valid = true;

  } else {
    result = stumpless_set_entry_message_str( &cached_entry, message );
    if( unlikely( !result ) ) {
      return -1;
    }
  }

  // we don't need to lock the cached entry since it is thread-local
  cached_entry.prival = priority;
  memcpy( cached_entry.app_name,
          target->default_app_name,
          target->default_app_name_length );
  cached_entry.app_name_length = target->default_app_name_length;
  memcpy( cached_entry.msgid,
          target->default_msgid,
          target->default_msgid_length );
  cached_entry.msgid_length = target->default_msgid_length;

  return stumpless_add_entry( target, &cached_entry );
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

int
stumpless_add_message_str( struct stumpless_target *target,
                           const char *message ) {
  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

  return stumpless_add_log_str( target, target->default_prival, message );
}

void
stumpless_close_target( struct stumpless_target *target ) {
  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return;
  }

  clear_error(  );

  switch( target->type ) {
    case STUMPLESS_BUFFER_TARGET:
      stumpless_close_buffer_target( target );
      break;

    case STUMPLESS_CHAIN_TARGET:
      config_close_chain_and_contents( target );
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

    case STUMPLESS_SQLITE3_TARGET:
      config_close_sqlite3_target_and_db( target );
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

FILE *
stumpless_get_cons_stream( void ) {
  if( config_read_bool( &cons_stream_valid ) ) {
    return config_read_ptr( &cons_stream );
  } else {
    return stdout;
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
stumpless_get_default_options( void ) {
  return config_read_int( &default_option );
}

int
stumpless_get_default_facility( const struct stumpless_target *target ) {
  int prival;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

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
    if( !result ) {
      return NULL;
    }

    if( !config_compare_exchange_ptr( &default_target, NULL, result ) ) {
      config_close_default_target( result );
      result = config_read_ptr( &default_target );
    }
  }

  return result;
}

int
unchecked_get_option( const struct stumpless_target *target, int option ) {
  int options;

  lock_target( target );
  options = target->options;
  unlock_target( target );

  return options & option;
}

int
stumpless_get_option( const struct stumpless_target *target, int option ) {
  int options;

  if( !target ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return 0;
  }

  options = unchecked_get_option( target, option );

  clear_error(  );
  return options;
}

const char *
stumpless_get_target_default_app_name( const struct stumpless_target *target ) {
  char *name_copy = NULL;

  VALIDATE_ARG_NOT_NULL( target );

  lock_target( target );

  name_copy = alloc_mem( target->default_app_name_length + 1 );
  if( !name_copy ) {
    goto cleanup_and_return;
  }

  memcpy( name_copy,
          target->default_app_name,
          target->default_app_name_length );
  name_copy[target->default_app_name_length] = '\0';
  clear_error(  );

cleanup_and_return:
  unlock_target( target );
  return name_copy;
}

const char *
stumpless_get_target_default_msgid( const struct stumpless_target *target ) {
  char *msgid_copy = NULL;

  VALIDATE_ARG_NOT_NULL( target );

  lock_target( target );

  msgid_copy = alloc_mem( target->default_msgid_length + 1 );
  if( !msgid_copy ) {
    goto cleanup_and_return;
  }

  memcpy( msgid_copy, target->default_msgid, target->default_msgid_length );
  msgid_copy[target->default_msgid_length] = '\0';
  clear_error(  );

cleanup_and_return:
  unlock_target( target );
  return msgid_copy;
}

stumpless_filter_func_t
stumpless_get_target_filter( const struct stumpless_target *target ) {
  stumpless_filter_func_t filter;

  VALIDATE_ARG_NOT_NULL( target );

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

  if ( !stumpless_target_is_open( target ) ) {
    lock_target( target );
    
    switch ( target->type ) {
      case STUMPLESS_FILE_TARGET:
        ( ( struct file_target * )target->id )->stream = config_fopen( target->name, "a" );
        if ( !( ( struct file_target * )target->id )->stream ) {
          goto fail;
        }
        result = target;
        break;

      case STUMPLESS_NETWORK_TARGET:
        result = config_open_network_target( target );
        if ( !result ) {
          goto fail;
        }
        break;

      case STUMPLESS_SOCKET_TARGET:
        result = config_open_socket_target( target );
        if ( !result ) {
          goto fail;
        }
        break;
      
      default:
        raise_target_incompatible( L10N_TARGET_ALWAYS_OPEN_ERROR_MESSAGE );
        result = NULL;
        break;
    }

    unlock_target( target );
  } else {
    result = target;
  }

  return result;

fail:
  unlock_target( target );
  return NULL;
}

void
stumpless_set_cons_stream( FILE *stream ) {
  config_write_ptr( &cons_stream, stream );
  config_write_bool( &cons_stream_valid, true );
}

void
stumpless_set_current_target( struct stumpless_target *target ) {
  clear_error(  );
  config_write_ptr( &current_target, target );
}

void
stumpless_set_default_options( int option ) {
  config_write_int( &default_option, option );
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

  VALIDATE_ARG_NOT_NULL( target );
  VALIDATE_ARG_NOT_NULL( app_name );

  if( unlikely( !validate_app_name( app_name, &new_length ) ) ) {
    return NULL;
  }

  clear_error(  );

  lock_target( target );
  memcpy( target->default_app_name, app_name, new_length );
  target->default_app_name_length = new_length;
  unlock_target( target );

  return target;
}

struct stumpless_target *
stumpless_set_target_default_msgid( struct stumpless_target *target,
                                    const char *msgid ) {
  size_t new_length;

  VALIDATE_ARG_NOT_NULL( target );
  VALIDATE_ARG_NOT_NULL( msgid );

  if( unlikely( !validate_msgid( msgid, &new_length ) ) ) {
    return NULL;
  }

  clear_error(  );

  lock_target( target );
  memcpy( target->default_msgid, msgid, new_length );
  target->default_msgid_length = new_length;
  unlock_target( target );

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
  switch ( target->type ) {
    case STUMPLESS_FILE_TARGET:
      is_open = ( ( (struct file_target *) target->id )->stream  != NULL );
      break;

    case STUMPLESS_NETWORK_TARGET:
      is_open = config_network_target_is_open( target );
      break;

    case STUMPLESS_SOCKET_TARGET:
      is_open = config_socket_target_is_open( target );
      break;
    
    default:
      break;
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

  VALIDATE_ARG_NOT_NULL_INT_RETURN( entry );
  VALIDATE_ARG_NOT_NULL_INT_RETURN( file );
  VALIDATE_ARG_NOT_NULL_INT_RETURN( func );

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
  if( unlikely( stumpless_has_error(  ) ) ) {
    return -1;
  }

  stumpless_set_entry_param_value_by_name( entry, "trace", "line", line_str );
  if( unlikely( stumpless_has_error(  ) ) ) {
    return -1;
  }

  stumpless_set_entry_param_value_by_name( entry, "trace", "function", func );
  if( unlikely( stumpless_has_error(  ) ) ) {
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
stumpless_trace_log_str( struct stumpless_target *target,
                         int priority,
                         const char *file,
                         int line,
                         const char *func,
                         const char *message ) {
  const struct stumpless_entry *result;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

  if( unlikely( !cached_trace_valid ) ) {
    result = stumpless_load_entry_str( &cached_trace,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       NULL,
                                       NULL,
                                       message );
    if( unlikely( !result ) ) {
      return -1;
    }

    if( !add_trace_element(  ) ) {
      unchecked_unload_entry( &cached_trace );
      return -1;
    }

    cached_trace_valid = true;

  } else {
    result = stumpless_set_entry_message_str( &cached_trace,
                                              message );
    if( unlikely( !result ) ) {
      return -1;
    }
  }

  // we don't need to lock the cached entry since it is thread-local
  cached_trace.prival = priority;
  memcpy( cached_trace.app_name,
          target->default_app_name,
          target->default_app_name_length );
  cached_trace.app_name_length = target->default_app_name_length;
  memcpy( cached_trace.msgid,
          target->default_msgid,
          target->default_msgid_length );
  cached_trace.msgid_length = target->default_msgid_length;

  return stumpless_trace_entry( target, &cached_trace, file, line, func );
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

int
stumpless_trace_message_str( struct stumpless_target *target,
                             const char *file,
                             int line,
                             const char *func,
                             const char *message ) {
  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

  return stumpless_trace_log_str( target,
                                  target->default_prival,
                                  file,
                                  line,
                                  func,
                                  message );
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
vstumpless_add_log( struct stumpless_target *target,
                    int priority,
                    const char *message,
                    va_list subs ) {
  const struct stumpless_entry *result;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

  if( unlikely( !cached_entry_valid ) ) {
    result = vstumpless_load_entry( &cached_entry,
                                    STUMPLESS_FACILITY_USER,
                                    STUMPLESS_SEVERITY_INFO,
                                    NULL,
                                    NULL,
                                    message,
                                    subs );
    if( unlikely( !result ) ) {
      return -1;
    }
    cached_entry_valid = true;

  } else {
    result = vstumpless_set_entry_message( &cached_entry, message, subs );
    if( unlikely( !result ) ) {
      return -1;
    }
  }

  // we don't need to lock the cached entry since it is thread-local
  cached_entry.prival = priority;
  memcpy( cached_entry.app_name,
          target->default_app_name,
          target->default_app_name_length );
  cached_entry.app_name_length = target->default_app_name_length;
  memcpy( cached_entry.msgid,
          target->default_msgid,
          target->default_msgid_length );
  cached_entry.msgid_length = target->default_msgid_length;

  return stumpless_add_entry( target, &cached_entry );
}

int
vstumpless_add_message( struct stumpless_target *target,
                        const char *message,
                        va_list subs ) {
  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

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
  const struct stumpless_entry *result;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

  if( unlikely( !cached_trace_valid ) ) {
    result = vstumpless_load_entry( &cached_trace,
                                    STUMPLESS_FACILITY_USER,
                                    STUMPLESS_SEVERITY_INFO,
                                    NULL,
                                    NULL,
                                    message,
                                    subs );
    if( unlikely( !result ) ) {
      return -1;
    }

    if( !add_trace_element(  ) ) {
      unchecked_unload_entry( &cached_trace );
      return -1;
    }

    cached_trace_valid = true;

  } else {
    result = vstumpless_set_entry_message( &cached_trace,
                                           message,
                                           subs );
    if( !result ) {
      return -1;
    }
  }

  // we don't need to lock the cached entry since it is thread-local
  cached_trace.prival = priority;
  memcpy( cached_trace.app_name,
          target->default_app_name,
          target->default_app_name_length );
  cached_trace.app_name_length = target->default_app_name_length;
  memcpy( cached_trace.msgid,
          target->default_msgid,
          target->default_msgid_length );
  cached_trace.msgid_length = target->default_msgid_length;

  return stumpless_trace_entry( target, &cached_trace, file, line, func );
}

int
vstumpless_trace_message( struct stumpless_target *target,
                          const char *file,
                          int line,
                          const char *func,
                          const char *message,
                          va_list subs ) {
  VALIDATE_ARG_NOT_NULL_INT_RETURN( target );

  return vstumpless_trace_log( target,
                               target->default_prival,
                               file,
                               line,
                               func,
                               message,
                               subs );
}

/* private definitions */

void
destroy_target( const struct stumpless_target *target ) {
  config_compare_exchange_ptr( &current_target, target, NULL );

  config_destroy_cached_mutex( target->mutex );
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

  target->id = NULL;
  target->type = type;
  target->options = stumpless_get_default_options(  );
  target->default_prival = get_prival( STUMPLESS_DEFAULT_FACILITY,
                                       STUMPLESS_DEFAULT_SEVERITY );
  target->default_app_name[0] = '-';
  target->default_app_name_length = 1;
  target->default_msgid[0] = '-';
  target->default_msgid_length = 1;
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
send_entry_and_msg_to_unsupported_target( const struct stumpless_target *target,
                                          const struct stumpless_entry *entry,
                                          const char *msg,
                                          size_t msg_size ) {
  ( void ) target;
  ( void ) entry;
  ( void ) msg;
  ( void ) msg_size;

  raise_target_unsupported(
    L10N_SEND_ENTRY_TO_UNSUPPORTED_TARGET_ERROR_MESSAGE
  );
  return -1;
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
  if( cached_entry_valid ) {
    stumpless_unload_entry_and_contents( &cached_entry );
    cached_entry_valid = false;
  }

  if( cached_trace_valid ) {
    stumpless_unload_entry_and_contents( &cached_trace );
    cached_trace_valid = false;
  }
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
