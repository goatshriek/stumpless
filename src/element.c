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

void
stumpless_destroy_element( struct stumpless_element *element ) {
  stumpless_destroy_element_and_contents( element );
}

void
stumpless_destroy_element_and_contents( struct stumpless_element *element ) {
  size_t i;

  clear_error(  );

  if( !element ) {
    return;
  }

  for( i = 0; i < element->param_count; i++ ) {
    stumpless_destroy_param( element->params[i] );
  }

  unchecked_destroy_element( element );
}

void
stumpless_destroy_element_only( struct stumpless_element *element ) {
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
  clear_error(  );

  if( !element ) {
    raise_argument_empty( "element is NULL" );
    return NULL;
  }

  if( index >= element->param_count ) {
    raise_index_out_of_bounds( "invalid param index", index );
    return NULL;
  }

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

  return unchecked_get_param_by_name( element, name );
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
  return -1;
}

const char *
stumpless_get_param_value_by_index( struct stumpless_element *element,
                                    size_t index ) {
  return NULL;
}

const char *
stumpless_get_param_value_by_name( struct stumpless_element *element,
                                   const char *name ) {
  return NULL;
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
stumpless_set_param_by_index( struct stumpless_element *element,
                              size_t index,
                              struct stumpless_param *param ) {
  return NULL;
}

struct stumpless_element *
stumpless_set_param_value_by_index( struct stumpless_element *element,
                                    size_t param_index,
                                    const char *param_value ) {
  return NULL;
}

struct stumpless_element *
stumpless_set_param_value_by_name( struct stumpless_element *element,
                                   const char *param_name,
                                   const char *param_value ) {
  return NULL;
}

/* private functions */

void
unchecked_destroy_element( struct stumpless_element *element ) {
  free_mem( element->params );
  free_mem( element->name );
  free_mem( element );
}

struct stumpless_param *
unchecked_get_param_by_name( struct stumpless_element *element,
                             const char *name ) {
  size_t i;
  struct stumpless_param *param;

  for( i = 0; i < element->param_count; i++ ) {
    param = element->params[i];
    if( strcmp( param->name, name ) == 0 ) {
      return param;
    }
  }

  return NULL;
}
