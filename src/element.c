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

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/element.h>
#include <stumpless/param.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/journald.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/deprecate.h"
#include "private/element.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/strhelper.h"
#include "private/validate.h"

struct stumpless_element *
stumpless_add_new_param( struct stumpless_element *element,
                         const char *param_name,
                         const char *param_value ) {
  struct stumpless_param *new_param;
  struct stumpless_element *result;

  new_param = stumpless_new_param( param_name, param_value );
  if( !new_param ) {
    return NULL;
  }

  result = stumpless_add_param( element, new_param );

  if( !result ) {
    stumpless_destroy_param( new_param );
  }

  return result;
}

struct stumpless_element *
stumpless_add_param( struct stumpless_element *element,
                     struct stumpless_param *param ) {
  struct stumpless_param **new_params;
  size_t old_params_size;
  size_t new_params_size;

  VALIDATE_ARG_NOT_NULL( element );
  VALIDATE_ARG_NOT_NULL( param );

  lock_element( element );

  old_params_size = sizeof( param ) * element->param_count;
  new_params_size = old_params_size + sizeof( param );

  new_params = realloc_mem( element->params, new_params_size );
  if( !new_params ) {
    unlock_element( element );
    return NULL;
  }

  new_params[element->param_count] = param;
  element->param_count++;
  element->params = new_params;
  unlock_element( element );

  clear_error(  );
  return element;
}

struct stumpless_element *
stumpless_copy_element( const struct stumpless_element *element ) {
  struct stumpless_element *copy;
  size_t i;
  struct stumpless_param *param_copy;

  lock_element( element );
  copy = stumpless_new_element( element->name );
  if( !copy ) {
    goto fail;
  }

  copy->params = alloc_mem( element->param_count * sizeof( param_copy ) );
  if( !copy->params ) {
    goto fail_param_copy;
  }

  for( i = 0; i < element->param_count; i++ ) {
    param_copy = stumpless_copy_param( element->params[i] );
    if( !param_copy ) {
      goto fail_param_copy;
    }

    copy->params[i] = param_copy;
    copy->param_count++;
  }

  unlock_element( element );
  return copy;

fail_param_copy:
  stumpless_destroy_element_and_contents( copy );
fail:
  unlock_element( element );
  return NULL;
}

void
stumpless_destroy_element( const struct stumpless_element *element ) {
  warn_of_deprecation( "stumpless_destroy_element has been deprecated in favor "
                       "of the more descriptive and deliberate "
                       "stumpless_destroy_element_and_contents and "
                       "stumpless_destroy_element_only functions in order to "
                       "avoid unintentional memory leaks and use-after-free "
                       "mistakes" );

  stumpless_destroy_element_and_contents( element );
}

void
stumpless_destroy_element_and_contents( const struct stumpless_element *e ) {
  size_t i;

  if( !e ) {
    return;
  }

  for( i = 0; i < e->param_count; i++ ) {
    stumpless_destroy_param( e->params[i] );
  }

  unchecked_destroy_element( e );
}

void
stumpless_destroy_element_only( const struct stumpless_element *element ) {
  if( !element ) {
    return;
  }

  unchecked_destroy_element( element );
}

bool
stumpless_element_has_param( const struct stumpless_element *element,
                             const char *name ) {
  size_t i;
  const struct stumpless_param *param;
  int cmp_result;

  if( !element ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "element" ) );
    return false;
  }

  if( !name ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "name" ) );
    return false;
  }

  if ( !validate_param_name( name ) ) {
    return false;
  }

  clear_error(  );
  lock_element( element );
  FOR_EACH_PARAM_WITH_NAME( element, name )
    unlock_element( element );
    return true;
  }

  unlock_element( element );
  return false;
}

const char *
stumpless_get_element_name( const struct stumpless_element *element ) {
  char *name_copy;

  VALIDATE_ARG_NOT_NULL( element );

  lock_element( element );
  name_copy = alloc_mem( element->name_length + 1 );
  if( !name_copy ) {
    goto cleanup_and_return;
  }
  memcpy( name_copy, element->name, element->name_length + 1 );
  clear_error(  );

cleanup_and_return:
  unlock_element( element );
  return name_copy;
}

struct stumpless_param *
stumpless_get_param_by_index( const struct stumpless_element *element,
                              size_t index ) {
  struct stumpless_param *result = NULL;

  VALIDATE_ARG_NOT_NULL( element );

  if( index >= element->param_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "param" ),
                               index );
    return NULL;
  }

  clear_error(  );

  lock_element( element );
  result = locked_get_param_by_index( element, index );
  unlock_element( element );

  return result;
}

struct stumpless_param *
stumpless_get_param_by_name( const struct stumpless_element *element,
                             const char *name ) {
  size_t i;
  struct stumpless_param *param;
  int cmp_result;

  VALIDATE_ARG_NOT_NULL( element );
  VALIDATE_ARG_NOT_NULL( name );

  if ( !validate_param_name( name ) ) {
    return NULL;
  }

  lock_element( element );
  FOR_EACH_PARAM_WITH_NAME( element, name )
    clear_error(  );
    goto cleanup_and_return;
  }

  param = NULL;
  raise_param_not_found(  );

cleanup_and_return:
  unlock_element( element );
  return param;
}

size_t
stumpless_get_param_count( const struct stumpless_element *element ) {
  size_t result;

  if( !element ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "element" ) );
    return 0;
  }

  lock_element( element );
  result = element->param_count;
  unlock_element( element );

  clear_error(  );
  return result;
}

size_t
stumpless_get_param_index( const struct stumpless_element *element,
                           const char *name ) {
  size_t i;
  const struct stumpless_param *param;
  int cmp_result;

  if( !element ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "element" ) );
    return 0;
  }

  if( !name ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "name" ) );
    return 0;
  }

  if  ( !validate_param_name(name) ) {
    return 0;
  }

  lock_element( element );
  FOR_EACH_PARAM_WITH_NAME( element, name )
    clear_error(  );
    goto cleanup_and_return;
  }

  i = 0;
  raise_param_not_found(  );

cleanup_and_return:
  unlock_element( element );
  return i;
}

const char *
stumpless_get_param_name_by_index( const struct stumpless_element *element,
                                   size_t index ) {
  const struct stumpless_param *param;

  param = stumpless_get_param_by_index( element, index );
  if( !param ) {
    return NULL;
  }

  return stumpless_get_param_name( param );
}

size_t
stumpless_get_param_name_count( const struct stumpless_element *element,
                                const char *name ) {
  size_t i;
  size_t count = 0;
  const struct stumpless_param *param;
  int cmp_result;

  if( !element ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "element" ) );
    return 0;
  }

  if( !name ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "name" ) );
    return 0;
  }

  if (!validate_param_name(name)) {
    return 0;
  }

  lock_element( element );
  FOR_EACH_PARAM_WITH_NAME( element, name )
    count++;
  }
  unlock_element( element );

  clear_error(  );
  return count;
}

const char *
stumpless_get_param_value_by_index( const struct stumpless_element *element,
                                    size_t index ) {
  const struct stumpless_param *param;

  param = stumpless_get_param_by_index( element, index );
  if( !param ) {
    return NULL;
  }

  return stumpless_get_param_value( param );
}

const char *
stumpless_get_param_value_by_name( const struct stumpless_element *element,
                                   const char *name ) {
  const struct stumpless_param *param;

  if (name && !validate_param_name(name)) {
    return NULL;
  }

  param = stumpless_get_param_by_name( element, name );
  if( !param ) {
    return NULL;
  }

  return stumpless_get_param_value( param );
}

struct stumpless_element *
stumpless_new_element( const char *name ) {
  struct stumpless_element *element;

  VALIDATE_ARG_NOT_NULL( name );

  if ( !validate_element_name( name ) ||
       !validate_element_name_length( name )) {
    goto fail;
  }

  element = alloc_mem( sizeof( *element ) );
  if( !element ) {
    goto fail;
  }

  element->name_length = strlen( name );
  memcpy( element->name, name, element->name_length + 1 );

  element->params = NULL;
  element->param_count = 0;

  config_assign_cached_mutex( element->mutex );
  if( !config_check_mutex_valid( element->mutex ) ) {
    goto fail_mutex;
  }

  config_init_journald_element( element );

  clear_error(  );
  return element;

fail_mutex:
  free_mem( element );

fail:
  return NULL;
}

struct stumpless_element *
stumpless_set_element_name( struct stumpless_element *element,
                            const char *name ) {
  VALIDATE_ARG_NOT_NULL( element );
  VALIDATE_ARG_NOT_NULL( name );

  if ( !validate_element_name( name ) ||
       !validate_element_name_length( name )) {
    goto fail;
  }

  element->name_length = strlen( name );

  lock_element( element );
  memcpy( element->name, name, element->name_length + 1 );
  unlock_element( element );

  clear_error(  );
  return element;

fail:
  return NULL;
}

struct stumpless_element *
stumpless_set_param( struct stumpless_element *element,
                     size_t index,
                     struct stumpless_param *param ) {
  VALIDATE_ARG_NOT_NULL( element );
  VALIDATE_ARG_NOT_NULL( param );

  lock_element( element );

  if( index >= element->param_count ) {
    unlock_element( element );
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "param" ),
                               index );
    return NULL;
  }

  element->params[index] = param;
  unlock_element( element );

  clear_error(  );
  return element;
}

struct stumpless_element *
stumpless_set_param_value_by_index( struct stumpless_element *element,
                                    size_t index,
                                    const char *value ) {
  struct stumpless_param *param;
  const struct stumpless_param *result;

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  lock_element( element );
  param = locked_get_param_by_index( element, index );
  if( !param ) {
    goto fail;
  }

  result = stumpless_set_param_value( param, value );
  if( !result ) {
    goto fail;
  }

  unlock_element( element );
  return element;

fail:
  unlock_element( element );
  return NULL;
}

struct stumpless_element *
stumpless_set_param_value_by_name( struct stumpless_element *element,
                                   const char *name,
                                   const char *value ) {
  struct stumpless_param *param;
  const void *result;

  VALIDATE_ARG_NOT_NULL( element );
  VALIDATE_ARG_NOT_NULL( name );

  param = stumpless_get_param_by_name( element, name );
  if( param ) {
    result = stumpless_set_param_value( param, value );
  } else {
    result = stumpless_add_new_param( element, name, value );
  }

  if( !result ) {
    return NULL;
  }

  return element;
}

const char *
stumpless_element_to_string( const struct stumpless_element *element ) {
    char *format;
    const char *name;
    size_t name_len;
    size_t format_len;
    size_t param_count;
    struct stumpless_param **params;

    VALIDATE_ARG_NOT_NULL( element );

    lock_element( element );

    name = element->name;
    name_len = element->name_length;
    params = element->params;
    param_count = element->param_count;

    // acc total format size
    format_len = name_len;

    const char **params_format = alloc_mem(sizeof(char*) * param_count);
    for( size_t i = 0; i < param_count; i++ ) {
      params_format[i] = stumpless_param_to_string(params[i]);
      // does not count '\0' on purpose
      format_len += strlen(params_format[i]);
    }

    if( param_count != 0 ) {
      // extra param list chars and commas
      format_len += 6 + param_count - 1;
    } else {
      // no params, just name
      format_len += 3;
    }

    format = alloc_mem( format_len );
    if( !format ) {
      goto fail;
    }

    memcpy( format + 1, name, name_len );

    // build params list "param_1_to_string,param_2_to_string, ..."
    size_t pos_offset = name_len + 4;
    for( size_t i = 0; i < param_count; i++) {
      // replace '\0' with ',' at the end of each string
      memcpy( format + pos_offset, params_format[i], strlen(params_format[i]));
      pos_offset += strlen(params_format[i]);
      if( i < param_count - 1 ) {
        format[pos_offset++] = ',';
      }
      free_mem(params_format[i]);
    }
    free_mem(params_format);

    unlock_element( element );

    format[0] = '<';
    format[name_len + 1] = '>';

    if (param_count != 0 ) {
      // <name>:[param_1_to_string,param_2_to_string,etc.] (with params)
      format[name_len + 2] = ':';
      format[name_len + 3] = '[';
      format[pos_offset] = ']';
    } else {
      // <name> (no params)
      // pos_offset is name_len + 4 here
      pos_offset -= 3;
    }

    format[pos_offset + 1] = '\0';

    clear_error( );
    return format;
fail:
    unlock_element( element );
    return NULL;
}

/* private functions */

void
lock_element( const struct stumpless_element *element ) {
  config_lock_mutex( element->mutex );
}

struct stumpless_param *
locked_get_param_by_index( const struct stumpless_element *element,
                           size_t index ) {
  if( index >= element->param_count ) {
    raise_index_out_of_bounds( "invalid param index", index );
    return NULL;
  }

  return element->params[index];
}

void
unchecked_destroy_element( const struct stumpless_element *element ) {
  config_destroy_cached_mutex( element->mutex );
  free_mem( element->params );
  free_mem( element );
}

void
unlock_element( const struct stumpless_element *element ) {
  config_unlock_mutex( element->mutex );
}
