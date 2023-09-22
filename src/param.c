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

#include <stddef.h>
#include <string.h>
#include <stumpless/param.h>
#include "private/config.h"
#include "private/config/wrapper/journald.h"
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
  
  VALIDATE_ARG_NOT_NULL( string );

  int i;
  size_t name_len = 0;
  size_t name_start = 0;
  size_t value_len = 0;
  size_t value_start = 0;
  char *name;
  char *value;
  struct stumpless_param *result;

  /* Check that the characters in 'name' are allowed. */
  for (i = 0; string[i] != '='; i++) {
    if (!((string[i] >= 'a' && string[i] <= 'z') ||
	  (string[i] >= 'A' && string[i] <= 'Z') ||
	  (string[i] >= '0' && string[i] <= '9') ||
	  (string[i] == '-') ||
	  (string[i] == '.') ||
	  (string[i] == '_'))){
      raise_invalid_param(  );
      return NULL;
    }
  }
  
  /* Check if the character after the '=' is '"', else raise an error. */
  if (string[i + 1] != '"'){
    raise_invalid_param(  );
    return NULL;
  }

  name_len = i;
  /* We add 1 to the length for the '\0' character. */
  name = alloc_mem( name_len + 1 );
  /* We make this addition to skip '=' and '"' characters. */
  i += 2;
  value_start = i;

  /* Iterate to the end of the 'value' string. */
  //for (; string[i] != '\0'; i++){}
  while (string[i] != '\0'){
    i++;
  }
  /* If the final character isn't '"' we raise an error. */
  if (string[i - 1] != '"') {
    raise_invalid_param(  );
    /* We need to free name here to avoid memory leaks */
    free_mem( name );
    return NULL;
  } else {
    /* We make this substraction for the 2 '"' characters and for the '=' character. */
    value_len = i - name_len - 3;
  }
  
  /* We add 1 to the length for the '\0' character. */
  value = alloc_mem( value_len + 1 );
  
  memcpy(name, string + name_start, name_len);
  name[name_len] = '\0';
  memcpy(value, string + value_start, value_len);
  value[value_len] = '\0';
  result = stumpless_new_param(name, value);
  free_mem( name );
  free_mem( value );
  
  return result;
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
