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

/* this must be included first to avoid errors */
#include "private/windows_wrapper.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/config/wel_supported.h>
#include <stumpless/entry.h>
#include <stumpless/param.h>
#include <stumpless/severity.h>
#include <stumpless/target.h>
#include <stumpless/target/wel.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wel_supported.h"
#include "private/config/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/validate.h"

/**
 * Creates a copy of a NULL terminated multibyte string in wide string format.
 *
 * @param str A multibyte string to copy, in UTF-8 format.
 *
 * @return A copy of the given string in wide string format, or NULL if an
 * error is encountered.
 */
static
LPCWSTR
copy_cstring_to_lpcwstr( LPCSTR str ) {
  int needed_wchar_length;
  LPWSTR str_copy;
  int conversion_result;

  needed_wchar_length = MultiByteToWideChar( CP_UTF8,
                                             MB_ERR_INVALID_CHARS |
                                               MB_PRECOMPOSED,
                                             str,
                                             -1,
                                             NULL,
                                             0 );

  if( needed_wchar_length == 0 ) {
    raise_mb_conversion_failure( GetLastError(  ) );
    return NULL;
  }

  str_copy = alloc_mem( needed_wchar_length * sizeof( WCHAR ) );
  if( !str_copy ) {
    return NULL;
  }

  conversion_result = MultiByteToWideChar( CP_UTF8,
                                           MB_ERR_INVALID_CHARS |
                                             MB_PRECOMPOSED,
                                           str,
                                           -1,
                                           str_copy,
                                           needed_wchar_length );

  if( conversion_result == 0 ) {
    free_mem( str_copy );
    raise_mb_conversion_failure( GetLastError(  ) );
    return NULL;
  }

  return str_copy;
}

/**
 * Creates a copy of a NULL terminated wide character string.
 *
 * @param str A wide character string to copy.
 *
 * @return A copy of the given wide character string, or NULL if an error is
 * encountered.
 */
static
LPWSTR
copy_lpcwstr( LPCWSTR str ) {
  size_t str_len;
  size_t str_size;
  LPWSTR str_copy;

  str_len = wcslen( str );
  str_size = ( str_len + 1 ) * sizeof( WCHAR );
  str_copy = alloc_mem( str_size );
  if( !str_copy ) {
    return NULL;
  }

  memcpy( str_copy, str, str_size );
  return str_copy;
}

/**
 * Sets the insertion string at the given index to the provided wide string,
 * freeing the previous one if it existed.
 *
 * @param entry The entry to set the insertion string of. Must not be NULL.
 *
 * @param index The index of the insertion string.
 *
 * @param str The wide string to use as the insertion string. Must not be NULL.
 *
 * @return The modified entry, or NULL if an error is encountered.
 */
static
struct stumpless_entry *
swap_wel_insertion_string( struct stumpless_entry *entry,
                           WORD index,
                           LPCWSTR str ) {
  struct wel_data *data;
  struct stumpless_entry *result;

  data = entry->wel_data;

  lock_wel_data( data );
  result = unsafe_swap_wel_insertion_string( entry, index, str );
  unlock_wel_data( data );

  return result;
}

/**
* Sets the insertion string at the given index to the provided UTF-8 string.
*
* A copy of the string is created in wide character format.
*
* If the index is higher than the current max, then the insertion string arrays
* are expanded to accomodate it.
*
* @param entry The entry to set the insertion string of. Must not be NULL.
*
* @param index The index of the insertion string.
*
* @param str The UTF-8 string to use as the insertion string. Must not be NULL.
*
* @return The modified entry, or NULL if an error is encountered.
*/
static
struct stumpless_entry *
set_wel_insertion_string( struct stumpless_entry *entry,
                          WORD index,
                          LPCSTR str ) {
  LPCWSTR str_copy;

  str_copy = copy_cstring_to_lpcwstr( str );
  if( !str_copy ) {
    return NULL;
  }

  return swap_wel_insertion_string( entry, index, str_copy );
}

/**
* Sets the insertion string at the given index to the provided wide string.
*
* A copy of the string is created in wide character format.
*
* If the index is higher than the current max, then the insertion string arrays
* are expanded to accomodate it.
*
* @param entry The entry to set the insertion string of. Must not be NULL.
*
* @param index The index of the insertion string.
*
* @param str The wide string to use as the insertion string. Must not be NULL.
*
* @return The modified entry, or NULL if an error is encountered.
*/
static
struct stumpless_entry *
  set_wel_insertion_string_w( struct stumpless_entry *entry,
                              WORD index,
                              LPCWSTR str ) {
  LPCWSTR str_copy;

  str_copy = copy_lpcwstr( str );
  if( !str_copy ) {
    return NULL;
  }

  return swap_wel_insertion_string( entry, index, str_copy );
}

WORD
stumpless_get_wel_category( const struct stumpless_entry *entry ) {
  const struct wel_data *data;
  WORD category;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );

  clear_error(  );
  data = entry->wel_data;
  lock_wel_data( data );
  category = data->category;
  unlock_wel_data( data );

  return category;
}

DWORD
stumpless_get_wel_event_id( const struct stumpless_entry *entry ) {
  const struct wel_data *data;
  DWORD event_id;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );

  clear_error(  );
  data = entry->wel_data;
  lock_wel_data( data );
  event_id = data->event_id;
  unlock_wel_data( data );

  return event_id;
}

struct stumpless_param *
stumpless_get_wel_insertion_param( const struct stumpless_entry *entry,
                                   WORD index ) {
  const struct wel_data *data;
  struct stumpless_param *param = NULL;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    raise_index_out_of_bounds(
       L10N_INVALID_INDEX_ERROR_MESSAGE( "insertion string" ),
       index
    );
    goto cleanup_and_return;
  }

  clear_error(  );
  param = data->insertion_params[index];

cleanup_and_return:
  unlock_wel_data( data );
  return param;
}

LPCSTR
stumpless_get_wel_insertion_string( const struct stumpless_entry *entry,
                                    WORD index ) {
  struct wel_data *data;
  const struct stumpless_param *param;
  char *str_copy = NULL;
  int needed_mb_length;
  int conversion_result;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    raise_index_out_of_bounds(
       L10N_INVALID_INDEX_ERROR_MESSAGE( "insertion string" ),
       index
    );
    goto cleanup_and_return;
  }

  clear_error(  );
  param = data->insertion_params[index];
  if( param ) {
    str_copy = alloc_mem( param->value_length + 1 );
    if( !str_copy ) {
      goto cleanup_and_return;
    }
    memcpy( str_copy, param->value, param->value_length );
    str_copy[param->value_length] = '\0';

  } else if( data->insertion_strings[index] ) {
    needed_mb_length = WideCharToMultiByte( CP_UTF8,
                                            WC_ERR_INVALID_CHARS |
                                              WC_NO_BEST_FIT_CHARS,
                                            data->insertion_strings[index],
                                            -1,
                                            NULL,
                                            0,
                                            NULL,
                                            NULL );
    if( needed_mb_length == 0 ) {
      raise_wide_conversion_failure( GetLastError(  ) );
      goto cleanup_and_return;
    }

    str_copy = alloc_mem( needed_mb_length  );
    if( !str_copy ) {
      goto cleanup_and_return;
    }

    conversion_result = WideCharToMultiByte( CP_UTF8,
                                             WC_ERR_INVALID_CHARS |
                                               WC_NO_BEST_FIT_CHARS,
                                             data->insertion_strings[index],
                                             -1,
                                             str_copy,
                                             needed_mb_length,
                                             NULL,
                                             NULL );
    if( conversion_result == 0 ) {
      free_mem( str_copy );
      str_copy = NULL;
      raise_wide_conversion_failure( GetLastError(  ) );
      goto cleanup_and_return;
    }
  }

cleanup_and_return:
  unlock_wel_data( data );
  return str_copy;
}

LPCWSTR
stumpless_get_wel_insertion_string_w( const struct stumpless_entry *entry,
                                      WORD index ) {
  struct wel_data *data;
  const struct stumpless_param *param;
  LPCWSTR str_copy = NULL;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    raise_index_out_of_bounds(
       L10N_INVALID_INDEX_ERROR_MESSAGE( "insertion string" ),
       index
    );
    goto cleanup_and_return;
  }

  clear_error(  );
  param = data->insertion_params[index];
  if( param ) {
    str_copy = copy_param_value_to_lpwstr( param );

  } else if( data->insertion_strings[index] ) {
    str_copy = copy_lpcwstr( data->insertion_strings[index] );
  }

cleanup_and_return:
  unlock_wel_data( data );
  return str_copy;
}

WORD
stumpless_get_wel_type( const struct stumpless_entry *entry ) {
  const struct wel_data *data;
  WORD type;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );

  clear_error(  );
  data = entry->wel_data;
  lock_wel_data( data );
  type = data->type;
  unlock_wel_data( data );

  return type;
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
                                   const struct stumpless_param *param ) {
  struct wel_data *data;
  LPCWSTR old_str;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );
  if( index >= data->insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      unlock_wel_data( data );
      return NULL;
    }
  }

  clear_error();

  data->insertion_params[index] = param;
  old_str = data->insertion_strings[index];
  data->insertion_strings[index] = NULL;
  unlock_wel_data( data );

  free_mem( old_str );
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
stumpless_set_wel_insertion_string_w( struct stumpless_entry *entry,
                                      WORD index,
                                      LPCWSTR str ) {
  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( str );

  clear_error(  );
  return set_wel_insertion_string_w( entry, index, str );
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
  stumpless_set_wel_insertion_strings_w( struct stumpless_entry *entry,
                                         WORD count,
                                         ... ) {
  return NULL;
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
  struct wel_data *data;
  struct stumpless_entry *result;
  WORD i = 0;
  const char *arg;

  VALIDATE_ARG_NOT_NULL( entry );

  data = entry->wel_data;
  lock_wel_data( data );

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

  unlock_wel_data( data );
  clear_error(  );
  return entry;

fail:
  unlock_wel_data( data );
  return NULL;
}

struct stumpless_entry *
vstumpless_set_wel_insertion_strings_w( struct stumpless_entry *entry,
                                        WORD count,
                                        va_list insertions ) {
  return NULL;
}

/* private definitions */

LPCWSTR
copy_param_value_to_lpwstr( const struct stumpless_param *param ) {
  LPWSTR str_copy;
  int needed_wchar_length;
  size_t needed_wchar_count;
  int value_length_int;
  int conversion_result;

  value_length_int = cap_size_t_to_int( param->value_length );

  needed_wchar_length = MultiByteToWideChar( CP_UTF8,
                                             MB_ERR_INVALID_CHARS |
                                               MB_PRECOMPOSED,
                                             param->value,
                                             value_length_int,
                                             NULL,
                                             0 );

  if( needed_wchar_length == 0 ) {
    raise_mb_conversion_failure( GetLastError(  ) );
    return NULL;
  }

  needed_wchar_count = ( ( size_t ) needed_wchar_length ) + 1;
  str_copy = alloc_mem( needed_wchar_count * sizeof( WCHAR ) );
  if( !str_copy ) {
    return NULL;
  }

  conversion_result = MultiByteToWideChar( CP_UTF8,
                                           MB_ERR_INVALID_CHARS |
                                             MB_PRECOMPOSED,
                                           param->value,
                                           value_length_int,
                                           str_copy,
                                           needed_wchar_length );

  if( conversion_result == 0 ) {
    free_mem( str_copy );
    raise_mb_conversion_failure( GetLastError(  ) );
    return NULL;
  }

  str_copy[needed_wchar_length] = L'\0';

  return str_copy;
}

struct stumpless_entry *
copy_wel_data( struct stumpless_entry *destination,
               const struct stumpless_entry *source ) {
  struct wel_data *dest_data;
  struct wel_data* source_data;
  WORD i;

  if( !config_initialize_wel_data( destination ) ) {
    return NULL;
  }

  source_data = source->wel_data;
  dest_data = destination->wel_data;
  lock_wel_data( source_data );

  dest_data->type = source_data->type;
  dest_data->category = source_data->category;
  dest_data->event_id = source_data->event_id;


  if( source_data->insertion_count > 0 ) {
    dest_data->insertion_params = alloc_mem( sizeof( struct stumpless_param * ) * source_data->insertion_count );
    if( !dest_data->insertion_params) {
      goto fail;
    }

    dest_data->insertion_strings = alloc_mem( sizeof( LPCSTR ) * source_data->insertion_count );
    if( !dest_data->insertion_strings) {
      goto fail_strings;
    }

    for( i = 0; i < source_data->insertion_count; i++ ) {
      dest_data->insertion_params[i] = source_data->insertion_params[i];
      if( source_data->insertion_strings[i] ){
        dest_data->insertion_strings[i] = copy_lpcwstr( source_data->insertion_strings[i] );
        if( !dest_data->insertion_strings[i] ) {
          goto fail_set_strings;
        }
      } else {
        dest_data->insertion_strings[i] = NULL;
      }
    }

    dest_data->insertion_count = source_data->insertion_count;
  }

  unlock_wel_data( source_data );
  clear_error(  );
  return destination;

fail_set_strings:
  while( i > 0 ) {
    i -= 1;
    free_mem( dest_data->insertion_strings[i] );
  }
  free_mem( dest_data->insertion_strings );
fail_strings:
  free_mem( dest_data->insertion_params );
fail:
  unlock_wel_data( source_data );
  return NULL;
}

void
destroy_wel_data(const struct stumpless_entry* entry) {
  struct wel_data *data;
  WORD i;

  data = ( struct wel_data * ) entry->wel_data;
  config_destroy_mutex( &data->mutex );

  for( i = 0; i < data->insertion_count; i++ ) {
    free_mem( data->insertion_strings[i] );
  }

  free_mem( data->insertion_strings );
  free_mem( data->insertion_params );
  free_mem( data );
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
  size_t new_max_index;
  size_t new_size;
  struct wel_data *data;
  struct stumpless_param **new_params;
  LPCWSTR *new_strings;
  WORD i;

  new_max_index = ( ( size_t ) max_index ) + 1;
  new_size = sizeof( *new_params ) * new_max_index;
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

  new_size = sizeof( LPCSTR ) * new_max_index;
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

struct stumpless_entry *
unsafe_swap_wel_insertion_string( struct stumpless_entry *entry,
                                  WORD index,
                                  LPCWSTR str ) {
  struct wel_data *data;

  data = entry->wel_data;
  if( index >= data->insertion_count ) {
    if( !resize_insertion_params( entry, index ) ) {
      return NULL;
    }
  } else {
    free_mem( data->insertion_strings[index] );
  }

  data->insertion_strings[index] = str;

  return entry;
}

struct stumpless_target *
wel_open_default_target( void ) {
  return stumpless_open_local_wel_target( STUMPLESS_DEFAULT_TARGET_NAME );
}
