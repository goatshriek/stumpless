// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2021 Joel E. Anderson
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
  free_mem( param->name );
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
  memcpy( name_copy, param->name, param->name_length + 1 );
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
  memcpy( value_copy, param->value, param->value_length + 1 );
  clear_error(  );

cleanup_and_return:
  unlock_param( param );
  return value_copy;
}

struct stumpless_param *
stumpless_new_param( const char *name, const char *value ) {
  size_t name_length;
  struct stumpless_param *param;

  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( value );

  if ( !validate_param_name_length( name, &name_length ) ||
       !validate_param_name( name )) {
    goto fail;
  }

  param = alloc_mem( sizeof( *param ) );
  if( !param ) {
    goto fail;
  }

  param->name = alloc_mem( name_length + 1 );
  if( !param->name ) {
    goto fail_name;
  }
  param->name_length = name_length;
  memcpy( param->name, name, name_length + 1 );

  param->value = copy_cstring_with_length( value, &( param->value_length ) );
  if( !param->value ) {
    goto fail_value;
  }

  config_assign_cached_mutex( param->mutex );
  if( !config_check_mutex_valid( param->mutex ) ) {
    goto fail_mutex;
  }

  config_init_journald_param( param );

  clear_error(  );
  return param;

fail_mutex:
  free_mem( param->value );

fail_value:
  free_mem( param->name );

fail_name:
  free_mem( param );

fail:
  return NULL;
}

struct stumpless_param *
stumpless_set_param_name( struct stumpless_param *param, const char *name ) {
  char *new_name;
  size_t new_size;
  const char *old_name;

  VALIDATE_ARG_NOT_NULL( param );
  VALIDATE_ARG_NOT_NULL( name );

  if ( !validate_param_name_length( name, &new_size ) ||
       !validate_param_name( name )) {
    goto fail;
  }

  new_name = alloc_mem( new_size + 1 );
  if( !new_name ) {
    goto fail;
  }
  memcpy( new_name, name, new_size + 1 );

  lock_param( param );
  old_name = param->name;
  param->name = new_name;
  param->name_length = new_size;
  unlock_param( param );

  free_mem( old_name );
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

    /* <name>:<value> */
    format = alloc_mem( value_len + name_len + 6 );
    if( !format ) {
      goto fail;
    }

    memcpy(format + 1, name, name_len);
    memcpy(format + name_len + 4, value, value_len);

    unlock_param( param );

    format[0] = '<';
    format[name_len + 1] = '>';
    format[name_len + 2] = ':';
    format[name_len + 3] = '<';
    format[name_len + value_len + 4] = '>';
    format[name_len + value_len + 5] = '\0';


    clear_error( );
    return format;

fail:
    unlock_param( param );
    return NULL;
}

/* private functions */

void
lock_param( const struct stumpless_param *param ) {
  config_lock_mutex( param->mutex );
}

void
unlock_param( const struct stumpless_param *param ) {
  config_unlock_mutex( param->mutex );
}
