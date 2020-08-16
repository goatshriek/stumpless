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
#include <stddef.h>
#include <string.h>
#include <stumpless/param.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/param.h"
#include "private/strhelper.h"

struct stumpless_param *
stumpless_copy_param( const struct stumpless_param *param ) {
  struct stumpless_param *result;

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    return NULL;

  }

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

  pthread_mutex_destroy( ( pthread_mutex_t * ) &param->param_mutex );
  free_mem( param->name );
  free_mem( param->value );
  free_mem( param );
}

const char *
stumpless_get_param_name( const struct stumpless_param *param ) {
  char *name_copy;

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    return NULL;
  }

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

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    return NULL;
  }

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
  struct stumpless_param *param;

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  if( !value ) {
    raise_argument_empty( "value is NULL" );
    goto fail;
  }

  param = alloc_mem( sizeof( *param ) );
  if( !param ) {
    goto fail;
  }

  param->name = copy_cstring_with_length( name, &( param->name_length ) );
  if( !param->name ) {
    goto fail_name;
  }

  param->value = copy_cstring_with_length( value, &( param->value_length ) );
  if( !param->value ) {
    goto fail_value;
  }

  pthread_mutex_init( &param->param_mutex, NULL );

  clear_error(  );
  return param;

fail_value:
  free_mem( param->name );

fail_name:
  free_mem( param );

fail:
  return NULL;
}

struct stumpless_param *
stumpless_set_param_name( struct stumpless_param *param, const char *name ) {
  char *temp_name;
  size_t temp_size;

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    goto fail;
  }

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  temp_name = copy_cstring_with_length( name, &temp_size );
  if( !temp_name ) {
    goto fail;
  }

  free_mem( param->name );
  param->name = temp_name;
  param->name_length = temp_size;

  clear_error(  );
  return param;

fail:
  return NULL;
}

struct stumpless_param *
stumpless_set_param_value( struct stumpless_param *param, const char *value ) {
  char *temp_value;
  size_t temp_size;

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    goto fail;
  }

  if( !value ) {
    raise_argument_empty( "value is NULL" );
    goto fail;
  }

  temp_value = copy_cstring_with_length( value, &temp_size );
  if( !temp_value ) {
    goto fail;
  }

  free_mem( param->value );
  param->value = temp_value;
  param->value_length = temp_size;

  clear_error(  );
  return param;

fail:
  return NULL;
}

/* private functions */

int
lock_param( const struct stumpless_param *param ) {
  return pthread_mutex_lock( ( pthread_mutex_t * ) &param->param_mutex );
}

int
unlock_param( const struct stumpless_param *param ) {
  return pthread_mutex_unlock( ( pthread_mutex_t * ) &param->param_mutex );
}
