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
#include <string.h>
#include <stumpless/element.h>
#include <stumpless/param.h>
#include "private/element.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/strhelper.h"

struct stumpless_element *
stumpless_add_new_param( struct stumpless_element *element,
                         const char *param_name,
                         const char *param_value ) {
  struct stumpless_param *new_param;

  new_param = stumpless_new_param( param_name, param_value );
  if( !new_param ) {
    return NULL;
  }

  return stumpless_add_param( element, new_param );
}

struct stumpless_element *
stumpless_add_param( struct stumpless_element *element,
                     struct stumpless_param *param ) {
  struct stumpless_param **new_params;
  size_t old_params_size;
  size_t new_params_size;

  clear_error(  );

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    return NULL;
  }

  old_params_size = sizeof( param ) * element->param_count;
  new_params_size = old_params_size + sizeof( param );

  new_params = realloc_mem( element->params, new_params_size );
  if( !new_params ) {
    return NULL;
  }

  new_params[element->param_count] = param;
  element->param_count++;
  element->params = new_params;

  return element;
}

struct stumpless_element *
stumpless_copy_element( const struct stumpless_element *element ) {
  struct stumpless_element *copy;
  size_t i;
  struct stumpless_param *param_copy;
  const struct stumpless_element *add_result;

  copy = stumpless_new_element( stumpless_get_element_name( element ) );
  if( !copy ) {
    goto fail;
  }

  for( i = 0; i < element->param_count; i++ ) {
    param_copy = stumpless_copy_param( element->params[i] );
    if( !param_copy ) {
      goto fail_param_copy;
    }

    add_result = stumpless_add_param( copy, param_copy );
    if( !add_result ) {
      goto fail_param_copy;
    }
  }

  return copy;

fail_param_copy:
  stumpless_destroy_element_and_contents( copy );
fail:
  return NULL;
}

void
stumpless_destroy_element( const struct stumpless_element *element ) {
  stumpless_destroy_element_and_contents( element );
}

void
stumpless_destroy_element_and_contents( const struct stumpless_element *element ) {
  size_t i;

  if( !element ) {
    return;
  }

  for( i = 0; i < element->param_count; i++ ) {
    stumpless_destroy_param( element->params[i] );
  }

  unchecked_destroy_element( element );
}

void
stumpless_destroy_element_only( const struct stumpless_element *element ) {
  if( !element ) {
    return;
  }

  unchecked_destroy_element( element );
}

const char *
stumpless_get_element_name( const struct stumpless_element *element ) {
  clear_error(  );

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  return element->name;
}

struct stumpless_param *
stumpless_get_param_by_index( struct stumpless_element *element,
                              size_t index ) {
  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  if( index >= element->param_count ) {
    raise_index_out_of_bounds( "invalid param index", index );
    return NULL;
  }

  clear_error(  );
  return element->params[index];
}

struct stumpless_param *
stumpless_get_param_by_name( struct stumpless_element *element,
                             const char *name ) {
  size_t i;
  struct stumpless_param *param;

  clear_error(  );

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    return NULL;
  }

  for( i = 0; i < element->param_count; i++ ) {
    param = element->params[i];
    if( strcmp( param->name, name ) == 0 ) {
      return param;
    }
  }

  raise_param_not_found(  );
  return NULL;
}

size_t
stumpless_get_param_count( const struct stumpless_element *element ) {
  clear_error(  );

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return 0;
  }

  return element->param_count;
}

size_t
stumpless_get_param_index( struct stumpless_element *element,
                           const char *name ) {
  size_t i;
  struct stumpless_param *param;

  clear_error(  );

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return 0;
  }

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    return 0;
  }

  for( i = 0; i < element->param_count; i++ ) {
    param = element->params[i];
    if( strcmp( param->name, name ) == 0 ) {
      return i;
    }
  }

  raise_param_not_found(  );
  return 0;
}

const char *
stumpless_get_param_name_by_index( struct stumpless_element *element,
                                   size_t index ) {
  struct stumpless_param *param;

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
  struct stumpless_param *param;

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return 0;
  }

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    return 0;
  }

  for( i = 0; i < element->param_count; i++ ) {
    param = element->params[i];
    if( strcmp( param->name, name ) == 0 ) {
      count++;
    }
  }

  clear_error(  );
  return count;
}

const char *
stumpless_get_param_value_by_index( struct stumpless_element *element,
                                    size_t index ) {
  struct stumpless_param *param;

  param = stumpless_get_param_by_index( element, index );
  if( !param ) {
    return NULL;
  }

  return stumpless_get_param_value( param );
}

const char *
stumpless_get_param_value_by_name( struct stumpless_element *element,
                                   const char *name ) {
  struct stumpless_param *param;

  param = stumpless_get_param_by_name( element, name );
  if( !param ) {
    return NULL;
  }

  return stumpless_get_param_value( param );
}

struct stumpless_element *
stumpless_new_element( const char *name ) {
  struct stumpless_element *element;

  clear_error(  );

  if( !name ) {
    raise_argument_empty( "name is NULL" );
    goto fail;
  }

  element = alloc_mem( sizeof( *element ) );
  if( !element ) {
    goto fail;
  }

  element->name = copy_cstring_with_length( name, &( element->name_length ) );
  if( !element->name ) {
    goto fail_name;
  }

  element->params = NULL;
  element->param_count = 0;

  return element;

fail_name:
  free_mem( element );

fail:
  return NULL;
}

struct stumpless_element *
stumpless_set_element_name( struct stumpless_element *element,
                            const char *name ) {
  char *temp_name;
  size_t temp_size;

  clear_error(  );

  if( !element ) {
    raise_argument_empty( "element is NULL" );
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

  free_mem( element->name );
  element->name = temp_name;
  element->name_length = temp_size;

  return element;

fail:
  return NULL;
}

struct stumpless_element *
stumpless_set_param( struct stumpless_element *element,
                     size_t index,
                     struct stumpless_param *param ) {
  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  if( !param ) {
    raise_argument_empty( "param is NULL" );
    return NULL;
  }

  if( index >= element->param_count ) {
    raise_index_out_of_bounds( "invalid param index", index );
    return NULL;
  }

  element->params[index] = param;

  clear_error(  );
  return element;
}

struct stumpless_element *
stumpless_set_param_value_by_index( struct stumpless_element *element,
                                    size_t index,
                                    const char *value ) {
  struct stumpless_param *param;
  const struct stumpless_param *result;

  param = stumpless_get_param_by_index( element, index );
  if( !param ) {
    return NULL;
  }

  result = stumpless_set_param_value( param, value );
  if( !result ) {
    return NULL;
  }

  return element;
}

struct stumpless_element *
stumpless_set_param_value_by_name( struct stumpless_element *element,
                                   const char *name,
                                   const char *value ) {
  struct stumpless_param *param;
  const struct stumpless_param *result;

  param = stumpless_get_param_by_name( element, name );
  if( !param ) {
    return NULL;
  }

  result = stumpless_set_param_value( param, value );
  if( !result ) {
    return NULL;
  }

  return element;
}

/* private functions */

void
unchecked_destroy_element( const struct stumpless_element *element ) {
  free_mem( element->params );
  free_mem( element->name );
  free_mem( element );
}
