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

#include <stddef.h>
#include <stumpless/param.h>
#include <string.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/strhelper.h"
#include "private/validate.h"

struct stumpless_param *
stumpless_copy_param( const struct stumpless_param *param ) {
  VALIDATE_ARG_NOT_NULL( param );

  return stumpless_new_param( param->name, param->value );
}

void
stumpless_destroy_param( const struct stumpless_param *param ) {
  if( !param ) {
    return;
  }

  free_mem( param->name );
  free_mem( param->value );
  free_mem( param );
}

const char *
stumpless_get_param_name( const struct stumpless_param *param ) {
  VALIDATE_ARG_NOT_NULL( param );

  clear_error(  );
  return param->name;
}

const char *
stumpless_get_param_value( const struct stumpless_param *param ) {
  VALIDATE_ARG_NOT_NULL( param );

  clear_error(  );
  return param->value;
}

struct stumpless_param *
stumpless_new_param( const char *name, const char *value ) {
  struct stumpless_param *param;

  VALIDATE_ARG_NOT_NULL( name );
  VALIDATE_ARG_NOT_NULL( value );

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

  VALIDATE_ARG_NOT_NULL( param );
  VALIDATE_ARG_NOT_NULL( name );

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

  VALIDATE_ARG_NOT_NULL( param );
  VALIDATE_ARG_NOT_NULL( value );

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

const char *
stumpless_param_to_string(const struct stumpless_param * param) {

    char *format;
    const char *name;
    const char *value;
    size_t value_len;
    size_t name_len;

    VALIDATE_ARG_NOT_NULL(param);

    name  = stumpless_get_param_name(param);
    value = stumpless_get_param_value(param);

    name_len = param->name_length;
    value_len = param->value_length;

    /* <name>:<value> */
    format = alloc_mem(value_len + name_len + 6);
    if (format == NULL)
        goto fail;
   
    

    format[0] = '<';
    memcpy(format + 1, name, name_len);
    format[name_len + 1] = '>';
    format[name_len + 2] = ':';
    format[name_len + 3] = '<';
    memcpy(format + name_len + 4, value, value_len);
    format[name_len + value_len + 4] = '>';
    format[name_len + value_len + 5] = '\0';


    clear_error( );
    return format;
    
fail:
    return NULL;
}


