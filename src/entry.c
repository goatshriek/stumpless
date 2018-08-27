// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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
#include <stumpless/entry.h>
#include "private/cache.h"
#include "private/config/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/formatter.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/memory.h"

static struct cache *entry_cache = NULL;

struct stumpless_entry *
stumpless_add_element( struct stumpless_entry *entry,
                       struct stumpless_element *element ) {

  struct stumpless_element **new_elements;
  size_t old_elements_size, new_elements_size;

  clear_error(  );

  if( !entry || !element ) {
    raise_argument_empty(  );
    return NULL;
  }
  // todo need to check for duplicates first

  old_elements_size = sizeof( element ) * entry->element_count;
  new_elements_size = old_elements_size + sizeof( element );

  new_elements = alloc_mem( new_elements_size );
  if( !new_elements ) {
    return NULL;
  }

  if( entry->elements != NULL ) {
    memcpy( new_elements, entry->elements, old_elements_size );
    free_mem( entry->elements );
  }

  new_elements[entry->element_count] = element;
  entry->element_count++;
  entry->elements = new_elements;

  return entry;
}


struct stumpless_element *
stumpless_add_param( struct stumpless_element *element,
                     struct stumpless_param *param ) {

  struct stumpless_param **new_params;
  size_t old_params_size, new_params_size;

  clear_error(  );

  if( !element || !param ) {
    raise_argument_empty(  );
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
stumpless_new_element( const char *name ) {
  struct stumpless_element *element;

  clear_error(  );

  if( !name ) {
    raise_argument_empty(  );
    goto fail;
  }

  element = alloc_mem( sizeof( *element ) );
  if( !element ) {
    goto fail;
  }

  element->name = cstring_to_sized_string( name, &( element->name_length ) );
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

struct stumpless_entry *
stumpless_new_entry( int facility, int severity, const char *app_name,
                     const char *msgid, const char *message ) {
  struct stumpless_entry *entry;
  size_t *app_name_length, *msgid_length, *message_length;

  clear_error(  );

  if( !entry_cache ) {
    entry_cache = cache_new( sizeof( *entry ), NULL );

    if( !entry_cache ) {
      goto fail;
    }
  }

  entry = cache_alloc( entry_cache );
  if( !entry ) {
    goto fail;
  }

  entry->prival = get_prival( facility, severity );

  app_name_length = &( entry->app_name_length );
  entry->app_name = cstring_to_sized_string( app_name, app_name_length );
  if( !entry->app_name ) {
    goto fail_app_name;
  }

  msgid_length = &( entry->msgid_length );
  entry->msgid = cstring_to_sized_string( msgid, msgid_length );
  if( !entry->msgid ) {
    goto fail_msgid;
  }

  message_length = &( entry->message_length );
  entry->message = cstring_to_sized_string( message, message_length );
  if( !entry->message ) {
    goto fail_message;
  }

  entry->elements = NULL;
  entry->element_count = 0;

  return entry;

fail_message:
  free_mem( entry->msgid );
fail_msgid:
  free_mem( entry->app_name );
fail_app_name:
  cache_free( entry_cache, entry );
fail:
  return NULL;
}

struct stumpless_param *
stumpless_new_param( const char *name, const char *value ) {
  struct stumpless_param *param;

  clear_error(  );

  if( !name || !value ) {
    raise_argument_empty(  );
    goto fail;
  }

  param = alloc_mem( sizeof( *param ) );
  if( !param ) {
    goto fail;
  }

  param->name = cstring_to_sized_string( name, &( param->name_length ) );
  if( !param->name ) {
    goto fail_name;
  }

  param->value = cstring_to_sized_string( value, &( param->value_length ) );
  if( !param->value ) {
    goto fail_value;
  }

  return param;

fail_value:
  free_mem( param->name );

fail_name:
  free_mem( param );

fail:
  return NULL;
}

void
stumpless_destroy_element( struct stumpless_element *element ) {
  size_t i;

  clear_error(  );

  if( !element ) {
    return;
  }

  for( i = 0; i < element->param_count; i++ ) {
    stumpless_destroy_param( element->params[i] );
  }
}

void
stumpless_destroy_entry( struct stumpless_entry *entry ) {
  size_t i;

  clear_error(  );

  if( !entry ) {
    return;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    stumpless_destroy_element( entry->elements[i] );
  }

  free_mem( entry->elements );
  free_mem( entry->msgid );
  free_mem( entry->app_name );
  free_mem( entry->message );

  cache_free( entry_cache, entry );
}

void
stumpless_destroy_param( struct stumpless_param *param ) {
  clear_error(  );

  if( !param ) {
    return;
  }

  free_mem( param->name );
  free_mem( param->value );
  free_mem( param );
}

struct stumpless_entry *
stumpless_set_entry_app_name( struct stumpless_entry *entry,
                              const char *app_name ) {
  size_t *app_name_length;

  clear_error(  );

  if( !entry ) {
    raise_argument_empty(  );
    return NULL;
  }

  app_name_length = &( entry->app_name_length );
  entry->app_name = cstring_to_sized_string( app_name, app_name_length );
  if( !entry->app_name ) {
    return NULL;
  } else {
    return entry;
  }
}

struct stumpless_entry *
stumpless_set_entry_message( struct stumpless_entry *entry,
                             const char *message ) {
  char *converted_message;
  size_t message_length;

  clear_error(  );

  if( !entry ) {
    raise_argument_empty(  );
    return NULL;
  }

  converted_message = cstring_to_sized_string( message, &( message_length ) );
  if( !converted_message ) {
    return NULL;
  } else {
    free_mem( entry->message );
    entry->message = converted_message;
    entry->message_length = message_length;
    return entry;
  }
}

/* private functions */

int
get_prival( int facility, int severity ) {
  return facility | severity;
}

struct strbuilder *
strbuilder_append_app_name( struct strbuilder *builder,
                            const struct stumpless_entry *entry ) {
  return strbuilder_append_buffer( builder,
                                   entry->app_name, entry->app_name_length );
}

struct strbuilder *
strbuilder_append_hostname( struct strbuilder *builder ) {
  char buffer[RFC_5424_MAX_HOSTNAME_LENGTH + 1];

  config_gethostname( buffer, RFC_5424_MAX_HOSTNAME_LENGTH + 1 );

  return strbuilder_append_string( builder, buffer );
}

struct strbuilder *
strbuilder_append_msgid( struct strbuilder *builder,
                         const struct stumpless_entry *entry ) {
  return strbuilder_append_buffer( builder, entry->msgid, entry->msgid_length );
}

struct strbuilder *
strbuilder_append_message( struct strbuilder *builder,
                           const struct stumpless_entry *entry ) {
  return strbuilder_append_buffer( builder,
                                   entry->message, entry->message_length );
}

struct strbuilder *
strbuilder_append_procid( struct strbuilder *builder ) {
  return strbuilder_append_int( builder, config_getpid(  ) );
}

struct strbuilder *
strbuilder_append_structured_data( struct strbuilder *builder,
                                   const struct stumpless_entry *entry ) {
  size_t i, j;
  struct stumpless_element *element;
  struct stumpless_param *param;

  if( entry->element_count == 0 ) {
    return strbuilder_append_char( builder, '-' );
  }

  for( i = 0; i < entry->element_count; i++ ) {
    element = entry->elements[i];

    builder = strbuilder_append_char( builder, '[' );
    builder = strbuilder_append_buffer( builder,
                                        element->name, element->name_length );

    for( j = 0; j < entry->elements[i]->param_count; j++ ) {
      param = element->params[j];

      builder = strbuilder_append_char( builder, ' ' );

      builder = strbuilder_append_buffer( builder,
                                          param->name, param->name_length );

      builder = strbuilder_append_char( builder, '=' );
      builder = strbuilder_append_char( builder, '"' );

      builder = strbuilder_append_buffer( builder,
                                          param->value, param->value_length );

      builder = strbuilder_append_char( builder, '"' );
    }

    builder = strbuilder_append_char( builder, ']' );
  }

  return builder;
}
