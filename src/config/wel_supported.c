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

/* this must be included first to avoid errors */
#include "private/windows_wrapper.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stumpless/config/wel_supported.h>
#include <stumpless/entry.h>
#include <stumpless/option.h>
#include <stumpless/param.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/wel.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wel_supported.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/strhelper.h"
#include "private/config/wrapper.h"
#include "private/validate.h"

static
struct stumpless_entry *
set_wel_insertion_string( struct stumpless_entry *entry,
                          WORD index,
                          LPCSTR str ) {
  size_t *str_length;
  struct stumpless_param *param;
  struct wel_data *data;

  param = alloc_mem( sizeof( *param ) );
  if( !param ) {
    goto fail;
  }

  str_length = &( param->value_length );
  param->value = copy_cstring_with_length( str, str_length );
  if( !param->value ) {
    goto fail_str;
  }

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      goto fail_resize;
    }
  }

  destroy_insertion_string_param( data->insertion_params[index] );

  param->name = NULL;
  param->name_length = 0;
  data->insertion_params[index] = param;
  unlock_wel_data( data );

  clear_error(  );
  return entry;


fail_resize:
  unlock_wel_data( data );
  free_mem( param->value );
fail_str:
  free_mem( param );
fail:
  return NULL;
}

LPCSTR
stumpless_get_wel_insertion_string( const struct stumpless_entry *entry,
                                    WORD index ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    raise_index_out_of_bounds(
       L10N_INVALID_INDEX_ERROR_MESSAGE( "insertion string" ),
       index
    );
    goto fail;
  }
  unlock_wel_data( data );

  clear_error();
  return data->insertion_params[index]->value;

fail:
  unlock_wel_data( data );
  return NULL;
}

struct stumpless_entry *
stumpless_set_wel_category( struct stumpless_entry *entry, WORD category ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  data->category = category;
  unlock_wel_data( data );

  clear_error();
  return entry;
}

struct stumpless_entry *
stumpless_set_wel_event_id( struct stumpless_entry *entry, DWORD event_id ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  data->event_id = event_id;
  unlock_wel_data( data );

  clear_error();
  return entry;
}

struct stumpless_entry *
stumpless_set_wel_insertion_param( struct stumpless_entry *entry,
                                   WORD index,
                                   struct stumpless_param *param ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( param );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      unlock_wel_data( data );
      return NULL;
    }
  }

  data->insertion_params[index] = param;
  unlock_wel_data( data );

  clear_error();
  return entry;
}

struct stumpless_entry *
stumpless_set_wel_insertion_string( struct stumpless_entry *entry,
                                    WORD index,
                                    LPCSTR str ) {
  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( str );

  clear_error(  );
  return set_wel_insertion_string( entry, index, str );
}

struct stumpless_entry *
stumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                     WORD count,
                                     ... ) {
  va_list insertions;
  struct stumpless_entry *result;

  va_start( insertions, count );
  result = vstumpless_set_wel_insertion_strings( entry, count, insertions );
  va_end( insertions );

  return result;
}

struct stumpless_entry *
stumpless_set_wel_type( struct stumpless_entry *entry, WORD type ) {
  struct wel_data *data;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  data->type = type;
  unlock_wel_data( data );

  clear_error();
  return entry;
}

struct stumpless_entry *
vstumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                      WORD count,
                                      va_list insertions ) {
  struct stumpless_entry *result;
  WORD i = 0;
  const char *arg;

  VALIDATE_ARG_NOT_NULL( entry );

  for( i = 0; i < count; i++ ) {
    arg = va_arg( insertions, char * );

    if( !arg ) {
      raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "insertion string" ) );
      goto fail;
    }

    result = set_wel_insertion_string( entry, i, arg );
    if( !result ) {
      goto fail;
    }
  }

  clear_error(  );
  return entry;

fail:
  return NULL;
}

/* private definitions */

struct stumpless_entry *
copy_wel_data( struct stumpless_entry *destination,
               const struct stumpless_entry *source ) {
  struct wel_data *dest_data;
  struct wel_data* source_data;
  WORD i;
  struct stumpless_param *param;
  const struct stumpless_entry *result;

  if( !config_initialize_wel_data( destination ) ) {
    goto fail;
  }

  dest_data = destination->wel_data;
  source_data = destination->wel_data;

  dest_data->type = source_data->type;
  dest_data->category = source_data->category;
  dest_data->event_id = source_data->event_id;

  dest_data->insertion_strings = alloc_mem( sizeof( LPCSTR ) * source_data->insertion_count );
  if( !dest_data->insertion_strings) {
    goto fail;
  }

  dest_data->insertion_params = alloc_mem( sizeof( struct stumpless_param * ) * source_data->insertion_count );
  if( !dest_data->insertion_params) {
    goto fail_params;
  }

  dest_data->insertion_count = source_data->insertion_count;
  for( i = 0; i < source_data->insertion_count; i++ ) {
    dest_data->insertion_params[i] = NULL;
  }

  for( i = 0; i < source_data->insertion_count; i++ ) {
    param = source_data->insertion_params[i];
    if( param && !param->value ) {
      result = set_wel_insertion_string( destination, i, param->value );
      if( !result ) {
        goto fail_set_string;
      }

    } else {
      dest_data->insertion_params[i] = param;
    }
  }

  return destination;

fail_set_string:
  destroy_insertion_params( destination );
fail_params:
  free_mem( dest_data->insertion_strings );
fail:
  return NULL;
}

void
destroy_wel_data(const struct stumpless_entry* entry) {
  struct wel_data *data;
  data = ( struct wel_data * ) entry->wel_data;

  config_destroy_mutex( &data->mutex );
  destroy_insertion_params( entry );
  free_mem( data );
}

void
destroy_insertion_params( const struct stumpless_entry *entry ) {
  struct wel_data *data;
  WORD i;

  data = ( struct wel_data * ) entry->wel_data;
  for( i = 0; i < data->insertion_count; i++ ) {
    destroy_insertion_string_param( data->insertion_params[i] );
  }

  free_mem( data->insertion_params );
}

void
destroy_insertion_string_param( const struct stumpless_param *param ) {
  if( param && !param->name ) {
    free_mem( param->value );
    free_mem( param );
  }
}

bool
initialize_wel_data( struct stumpless_entry *entry ) {
  struct wel_data *data;

  data = alloc_mem( sizeof( *data ) );
  if( !data ){
    return false;
  }

  data->insertion_strings = NULL;
  data->insertion_params = NULL;
  data->insertion_count = 0;
  config_init_mutex( &data->mutex );

  entry->wel_data = data;
  return true;
}

void
lock_wel_data( const struct wel_data *data ) {
  config_lock_mutex( &data->mutex );
}

struct stumpless_param **
resize_insertion_params( struct stumpless_entry *entry, WORD max_index ) {
  size_t new_size;
  struct wel_data *data;
  struct stumpless_param **new_params;
  LPCSTR *new_strings;
  WORD i;

  new_size = sizeof( *new_params ) * ( max_index + 1 );
  data = entry->wel_data;
  new_params = realloc_mem( data->insertion_params, new_size );
  if( !new_params ) {
    return NULL;

  } else {
    for( i = data->insertion_count; i <= max_index; i++ ) {
      new_params[i] = NULL;
    }

    data->insertion_params = new_params;

  }

  new_size = sizeof( LPCSTR ) * ( max_index + 1 );
  new_strings = realloc_mem( ( void * ) data->insertion_strings, new_size );
  if( !new_strings ) {
    return NULL;

  } else {
    for( i = data->insertion_count; i <= max_index; i++ ) {
      new_strings[i] = NULL;
    }

    data->insertion_strings = new_strings;

  }

  data->insertion_count = max_index + 1;
  return new_params;
}

void
set_entry_wel_type( struct stumpless_entry *entry, int severity ) {
  struct wel_data *data;

  data = entry->wel_data;

  switch ( severity ) {
    case STUMPLESS_SEVERITY_ERR:
      data->type = EVENTLOG_ERROR_TYPE;
      break;

    case STUMPLESS_SEVERITY_INFO:
      data->type = EVENTLOG_INFORMATION_TYPE;
      break;

    case STUMPLESS_SEVERITY_WARNING:
      data->type = EVENTLOG_WARNING_TYPE;
      break;

    default:
      data->type = EVENTLOG_SUCCESS;
  }
}

void
unlock_wel_data( const struct wel_data *data ) {
  config_unlock_mutex( &data->mutex );
}

struct stumpless_target *
wel_open_default_target( void ) {
  return stumpless_open_local_wel_target( STUMPLESS_DEFAULT_TARGET_NAME,
                                          STUMPLESS_OPTION_NONE );
}
