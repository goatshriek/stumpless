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

#include <stddef.h>
#include <string.h>
#include <stumpless/param.h>
#include "private/config.h"
#include "private/config/wrapper/journald.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/param.h"
#include "private/strhelper.h"
#include "private/validate.h"

struct stumpless_param *
stumpless_copy_param( const struct stumpless_param *param ) {
  struct stumpless_param *result;

  VALIDATE_ARG_NOT_NULL( param );

  lock_param( param );
  result = stumpless_new_param( param->name, param->value );
  unlock_param( param );

  return result;
}

void
stumpless_destroy_param( const struct stumpless_param *param ) {
  if( !param ) {
    return;
  }

  config_destroy_cached_mutex( param->mutex );
  free_mem( param->value );
  free_mem( param );
}

const char *
stumpless_get_param_name( const struct stumpless_param *param ) {
  char *name_copy;

  VALIDATE_ARG_NOT_NULL( param );

  lock_param( param );
  name_copy = alloc_mem( param->name_length + 1 );
  if( !name_copy ) {
    goto cleanup_and_return;
  }
  memcpy( name_copy, param->name, param->name_length );
  name_copy[param->name_length] = '\0';
  clear_error(  );

cleanup_and_return:
  unlock_param( param );
  return name_copy;
}

const char *
stumpless_get_param_value( const struct stumpless_param *param ) {
  char *value_copy;

  VALIDATE_ARG_NOT_NULL( param );

  lock_param( param );
  value_copy = alloc_mem( param->value_length + 1 );
  if( !value_copy ) {
    goto cleanup_and_return;
  }
  memcpy( value_copy, param->value, param->value_length );
  value_copy[param->value_length] = '\0';
  clear_error(  );

cleanup_and_return:
  unlock_param( param );
  return value_copy;
}

struct stumpless_param *
stumpless_load_param( struct stumpless_param *param,
                      const char *name,
                      const char *value ) {
  size_t name_length;

  VALIDATE_ARG_NOT_NULL( param );
  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( value );

  if( unlikely( !validate_param_name( name, &name_length ) ) ) {
    return NULL;
  }

  clear_error(  );
  return unchecked_load_param( param, name, name_length, value );
}

struct stumpless_param *
stumpless_new_param( const char *name, const char *value ) {
  size_t name_length;
  struct stumpless_param *param;
  struct stumpless_param *result;

  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( value );

  if( unlikely( !validate_param_name( name, &name_length ) ) ) {
    return NULL;
  }

  if( unlikely( !validate_param_value( value, strlen(value) ) ) ) {
    return NULL;
  }

  clear_error(  );

  param = alloc_mem( sizeof( *param ) );
  if( !param ) {
    return NULL;
  }

  result = unchecked_load_param( param, name, name_length, value );
  if( !result ) {
    free_mem( param );
  }

  return result;
}

struct stumpless_param *
stumpless_new_param_from_string( const char *string ) {
  struct stumpless_param *param;
  size_t i;
  const char *value;
  size_t value_len;

  VALIDATE_ARG_NOT_NULL( string );

  param = alloc_mem( sizeof( *param ) );
  if( !param ){
    return NULL;
  }

  // this setup should be consolidated once the load param function
  // is able to accept string references instead of only NULL-terminated strings
  config_assign_cached_mutex( param->mutex );
  if( !config_check_mutex_valid( param->mutex ) ) {
    goto fail;
  }
  config_init_journald_param( param );

  // validate and load the param name
  for( i = 0; string[i] != '='; i++ ){
    if( i >= STUMPLESS_MAX_PARAM_NAME_LENGTH ){
      raise_argument_too_big( L10N_STRING_TOO_LONG_ERROR_MESSAGE,
                              0,
                              NULL );
      goto fail;
    }

    if( string[i] < 33 ||
        string[i] > 126 ||
        string[i] == ']' ||
        string[i] == '"' ){
      raise_invalid_param();
      goto fail;
    }

    param->name[i] = string[i];
  }
  param->name_length = i;
  
  // validate the character after the '=' is '"'
  if( string[i + 1] != '"' ){
    raise_invalid_param();
    goto fail;
  }

  value = string + i + 2;
  value_len = strlen( value );

  // validate the final character is '"'
  if( value_len == 0 || value[value_len-1] != '"' ){
    raise_invalid_param();
    goto fail;
  }

  // we're going to replace the ending '"' with a null character
  param->value = alloc_mem( value_len );
  if( !param->value ){
    goto fail;
  }

  memcpy( param->value, value, value_len - 1 );
  param->value[value_len-1] = '\0';
  param->value_length = value_len - 1;

  clear_error();
  return param;

fail:
  free_mem( param );
  return NULL;
}

struct stumpless_param *
stumpless_set_param_name( struct stumpless_param *param, const char *name ) {
  size_t new_size;

  VALIDATE_ARG_NOT_NULL( param );
  VALIDATE_ARG_NOT_NULL( name );

  if( unlikely( !validate_param_name( name, &new_size ) ) ) {
    goto fail;
  }

  lock_param( param );
  param->name_length = new_size;
  memcpy( param->name, name, new_size );
  param->name[new_size] = '\0';
  unlock_param( param );

  clear_error(  );
  return param;

fail:
  return NULL;
}

struct stumpless_param *
stumpless_set_param_value( struct stumpless_param *param, const char *value ) {
  char *new_value;
  size_t new_size;
  const char *old_value;

  VALIDATE_ARG_NOT_NULL( param );
  VALIDATE_ARG_NOT_NULL( value );

  if( unlikely( !validate_param_value( value, strlen(value) ) ) ) {
    goto fail;
  }

  new_value = copy_cstring_with_length( value, &new_size );
  if( !new_value ) {
    goto fail;
  }

  lock_param( param );
  old_value = param->value;
  param->value = new_value;
  param->value_length = new_size;
  unlock_param( param );

  free_mem( old_value );
  clear_error(  );
  return param;

fail:
  return NULL;
}

const char *
stumpless_param_to_string( const struct stumpless_param *param ) {
    char *format;
    const char *name;
    const char *value;
    size_t value_len;
    size_t name_len;

    VALIDATE_ARG_NOT_NULL( param );

    lock_param( param );

    name  = param->name;
    value = param->value;
    name_len = param->name_length;
    value_len = param->value_length;

    /* name="value"*/
    format = alloc_mem( value_len + name_len + 4 );
    if( !format ) {
      goto fail;
    }

  
    memcpy(format, name, name_len);
    memcpy(format + name_len + 2, value, value_len);

    unlock_param( param );

    format[name_len ] = '=';
    format[name_len + 1] = '\"';
    format[name_len + value_len + 2] = '\"';
    format[name_len + value_len + 3] = '\0';


    clear_error( );
    return format;

fail:
    unlock_param( param );
    return NULL;
}

size_t
stumpless_param_into_string( const struct stumpless_param *param, char *str, size_t max_size ) {
  const char *name;
  const char *value;
  size_t value_len;
  size_t name_len;
  size_t min_buff_size;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( param );
  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( str );

  lock_param( param );

  name  = param->name;
  value = param->value;
  name_len = param->name_length;
  value_len = param->value_length;

  min_buff_size = name_len + value_len + 4;
  if ( min_buff_size > max_size ) {
    raise_argument_too_small( L10N_BUFFER_TOO_SMALL_ERROR_MESSAGE,
                              max_size,
                              L10N_BUFFER_SIZE_ERROR_CODE_TYPE );
    goto fail;
  }

  memcpy(str, name, name_len);
  memcpy(str + name_len + 2, value, value_len);

  unlock_param( param );

  str[name_len ] = '=';
  str[name_len + 1] = '\"';
  str[name_len + value_len + 2] = '\"';
  str[name_len + value_len + 3] = '\0';

  return min_buff_size;

fail:
  unlock_param( param );
  return min_buff_size;
}

void
stumpless_unload_param( const struct stumpless_param *param ) {
  if( !param ) {
    return;
  }

  config_destroy_cached_mutex( param->mutex );
  free_mem( param->value );
}

/* private functions */

void
lock_param( const struct stumpless_param *param ) {
  config_lock_mutex( param->mutex );
}

struct stumpless_param *
unchecked_load_param( struct stumpless_param *param,
                      const char *name,
                      size_t name_length,
                      const char *value ) {
  param->value = copy_cstring_with_length( value, &( param->value_length ) );
  if( !param->value ) {
    goto fail_value;
  }

  config_assign_cached_mutex( param->mutex );
  if( !config_check_mutex_valid( param->mutex ) ) {
    goto fail_mutex;
  }

  param->name_length = name_length;
  memcpy( param->name, name, name_length );
  param->name[name_length] = '\0';

  config_init_journald_param( param );

  return param;

fail_mutex:
  free_mem( param->value );

fail_value:
  return NULL;
}

void
unlock_param( const struct stumpless_param *param ) {
  config_unlock_mutex( param->mutex );
}
