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

#include <stdarg.h>
#include <stddef.h>
#include <stumpless/config/wel_supported.h>
#include <stumpless/entry.h>
#include <stumpless/option.h>
#include <stumpless/param.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/wel.h>
#include <windows.h>
#include "private/config/wel_supported.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/strhelper.h"

static
struct stumpless_entry *
set_wel_insertion_string( struct stumpless_entry *entry,
                          WORD index,
                          LPCSTR str ) {
  size_t *str_length;
  struct stumpless_param *param;

  param = alloc_mem( sizeof( *param ) );
  if( !param ) {
    goto fail;
  }

  str_length = &( param->value_length );
  param->value = copy_cstring_with_length( str, str_length );
  if( !param->value ) {
    goto fail_str;
  }

  if( index >= entry->wel_insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      goto fail_resize;
    }
  }

  destroy_insertion_string_param( entry->wel_insertion_params[index] );

  param->name = NULL;
  param->name_length = 0;
  entry->wel_insertion_params[index] = param;

  return entry;


fail_resize:
  free_mem( param->value );
fail_str:
  free_mem( param );
fail:
  return NULL;
}

LPCSTR
stumpless_get_wel_insertion_string( const struct stumpless_entry *entry,
                                    WORD index ) {
  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    goto fail;
  }

  if( index >= entry->wel_insertion_count ) {
    raise_index_out_of_bounds( "invalid insertion string index", index );
    goto fail;
  }

  return entry->wel_insertion_params[index]->value;

fail:
  return NULL;
}

struct stumpless_entry *
stumpless_set_wel_category( struct stumpless_entry *entry, WORD category ) {
  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  entry->wel_category = category;

  return entry;
}

struct stumpless_entry *
stumpless_set_wel_event_id( struct stumpless_entry *entry, DWORD event_id ) {
  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  entry->wel_event_id = event_id;

  return entry;
}

struct stumpless_entry *
stumpless_set_wel_insertion_param( struct stumpless_entry *entry,
                                   WORD index,
                                   struct stumpless_param *param ) {
  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    return NULL;
  }

  if( index >= entry->wel_insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      return NULL;
    }
  }

  entry->wel_insertion_params[index] = param;

  return entry;
}

struct stumpless_entry *
stumpless_set_wel_insertion_string( struct stumpless_entry *entry,
                                    WORD index,
                                    LPCSTR str ) {
  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    goto fail;
  }

  if( !str ) {
    raise_argument_empty( "insertion string is NULL" );
    goto fail;
  }

  return set_wel_insertion_string( entry, index, str );

fail:
  return NULL;
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
  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    return NULL;
  }

  entry->wel_type = type;

  return entry;
}

struct stumpless_entry *
vstumpless_set_wel_insertion_strings( struct stumpless_entry *entry,
                                      WORD count,
                                      va_list insertions ) {
  struct stumpless_entry *result;
  WORD i = 0;
  const char *arg;

  clear_error(  );

  if( !entry ) {
    raise_argument_empty( "entry is NULL" );
    goto fail;
  }

  for( i = 0; i < count; i++ ) {
    arg = va_arg( insertions, char * );

    if( !arg ) {
      raise_argument_empty( "insertion string is NULL" );
      goto fail;
    }

    result = stumpless_set_wel_insertion_string( entry, i, arg );
    if( !result ) {
      goto fail;
    }
  }

  return entry;

fail:
  return NULL;
}

/* private definitions */

struct stumpless_entry *
copy_wel_fields( struct stumpless_entry *destination,
                 const struct stumpless_entry *source ) {
  destination->wel_type = source->wel_type;
  destination->wel_category = source->wel_category;
  destination->wel_event_id = source->wel_event_id;

  return destination;
}

void
destroy_insertion_params( struct stumpless_entry *entry ) {
  WORD i;

  for( i = 0; i < entry->wel_insertion_count; i++ ) {
    destroy_insertion_string_param( entry->wel_insertion_params[i] );
  }

  free_mem( entry->wel_insertion_params );
}

void
destroy_insertion_string_param( struct stumpless_param *param ) {
  if( param && !param->name ) {
    free_mem( param->value );
    free_mem( param );
  }
}

void
initialize_insertion_params( struct stumpless_entry *entry ) {
  entry->wel_insertion_strings = NULL;
  entry->wel_insertion_params = NULL;
  entry->wel_insertion_count = 0;
}

struct stumpless_param **
resize_insertion_params( struct stumpless_entry *entry, WORD max_index ) {
  size_t new_size;
  struct stumpless_param **new_params;
  LPCSTR *new_strings;
  WORD i;

  new_size = sizeof( *new_params ) * ( max_index + 1 );
  new_params = realloc_mem( entry->wel_insertion_params, new_size );
  if( !new_params ) {
    return NULL;

  } else {
    for( i = entry->wel_insertion_count; i <= max_index; i++ ) {
      new_params[i] = NULL;
    }

    entry->wel_insertion_params = new_params;

  }

  new_size = sizeof( LPCSTR ) * ( max_index + 1 );
  new_strings = realloc_mem( ( void * ) entry->wel_insertion_strings, new_size );
  if( !new_strings ) {
    return NULL;

  } else {
    for( i = entry->wel_insertion_count; i <= max_index; i++ ) {
      new_strings[i] = NULL;
    }

    entry->wel_insertion_strings = new_strings;

  }

  entry->wel_insertion_count = max_index + 1;
  return new_params;
}

void
set_entry_wel_type( struct stumpless_entry *entry, int severity ) {
  switch ( severity ) {
    case STUMPLESS_SEVERITY_ERR:
      entry->wel_type = EVENTLOG_ERROR_TYPE;
      break;

    case STUMPLESS_SEVERITY_INFO:
      entry->wel_type = EVENTLOG_INFORMATION_TYPE;
      break;

    case STUMPLESS_SEVERITY_WARNING:
      entry->wel_type = EVENTLOG_WARNING_TYPE;
      break;

    default:
      entry->wel_type = EVENTLOG_SUCCESS;
  }
}

struct stumpless_target *
wel_open_default_target( void ) {
  return stumpless_open_local_wel_target( STUMPLESS_DEFAULT_TARGET_NAME,
                                          STUMPLESS_OPTION_NONE );
}
