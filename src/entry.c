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

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/param.h>
#include <stumpless/error.h>
#include "private/cache.h"
#include "private/config/wrapper.h"
#include "private/config/locale/wrapper.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/formatter.h"
#include "private/severity.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/memory.h"
#include "private/validate.h"

static struct cache *entry_cache = NULL;

struct stumpless_entry *
stumpless_add_element( struct stumpless_entry *entry,
                       struct stumpless_element *element ) {
  struct stumpless_element **new_elements;
  size_t old_elements_size;
  size_t new_elements_size;

  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( element );

  if( unchecked_entry_has_element( entry, element->name ) ) {
    raise_duplicate_element(  );
    return NULL;
  }

  old_elements_size = sizeof( element ) * entry->element_count;
  new_elements_size = old_elements_size + sizeof( element );

  new_elements = realloc_mem( entry->elements, new_elements_size );
  if( !new_elements ) {
    return NULL;
  }

  new_elements[entry->element_count] = element;
  entry->elements = new_elements;
  entry->element_count++;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_add_new_element( struct stumpless_entry *entry,
                           const char *name ) {
  struct stumpless_element *new_element;
  struct stumpless_entry *result;

  new_element = stumpless_new_element( name );
  if( !new_element ) {
    return NULL;
  }

  result = stumpless_add_element( entry, new_element );

  if( !result ) {
    stumpless_destroy_element( new_element );
  }

  return result;
}

struct stumpless_entry *
stumpless_add_new_param_to_entry( struct stumpless_entry *entry,
                                  const char *element_name,
                                  const char *param_name,
                                  const char *param_value ) {
  struct stumpless_element *element;
  bool element_created = false;
  const void *result;

  element = stumpless_get_element_by_name( entry, element_name );
  if( !element ) {
    element = stumpless_new_element( element_name );
    if( !element ) {
      goto fail;
    }

    element_created = true;
  }

  result = stumpless_add_new_param( element, param_name, param_value );
  if( !result ) {
    goto fail_add;
  }

  if( element_created ) {
    result = stumpless_add_element( entry, element );
    if( !result ) {
      goto fail_add;
    }
  }

  return entry;

fail_add:
  if( element_created ) {
    stumpless_destroy_element_and_contents( element );
  }
fail:
  return NULL;
}

struct stumpless_entry *
stumpless_copy_entry( const struct stumpless_entry *entry ) {
  struct stumpless_entry *copy;
  size_t i;
  struct stumpless_element *element_copy;
  const struct stumpless_entry *result;

  VALIDATE_ARG_NOT_NULL( entry );

  copy = stumpless_new_entry( get_facility( entry->prival ),
                              get_severity( entry->prival ),
                              entry->app_name,
                              entry->msgid,
                              entry->message );
  if( !copy ) {
    goto fail;
  }

  copy->elements = alloc_mem( entry->element_count * sizeof( element_copy ) );
  if( !copy->elements ) {
    goto fail_elements;
  }

  for( i = 0; i < entry->element_count; i++ ){
    element_copy = stumpless_copy_element( entry->elements[i] );
    if( !element_copy ) {
      goto fail_elements;
    }

    copy->elements[i] = element_copy;
    copy->element_count++;
  }

  result = config_copy_wel_data( copy, entry );
  if( !result ) {
    goto fail_elements;
  }

  clear_error(  );
  return copy;

fail_elements:
  stumpless_destroy_entry_and_contents( copy );
fail:
  return NULL;
}

void
stumpless_destroy_entry( const struct stumpless_entry *entry ) {
  stumpless_destroy_entry_and_contents( entry );
}

void
stumpless_destroy_entry_and_contents( const struct stumpless_entry *entry ) {
  size_t i;

  if( !entry ) {
    return;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    stumpless_destroy_element( entry->elements[i] );
  }

  unchecked_destroy_entry( entry );
}

void
stumpless_destroy_entry_only( const struct stumpless_entry *entry ) {
  if( !entry ) {
    return;
  }

  unchecked_destroy_entry( entry );
}

bool
stumpless_entry_has_element( const struct stumpless_entry *entry,
                             const char *name ) {
  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return false;
  }

  if( !name ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "name" ) );
    return false;
  }

  clear_error(  );
  return unchecked_entry_has_element( entry, name );
}

struct stumpless_element *
stumpless_get_element_by_index( const struct stumpless_entry *entry,
                                size_t index ) {
  VALIDATE_ARG_NOT_NULL( entry );

  if( index >= entry->element_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "element" ),
                               index );
    return NULL;
  }

  clear_error(  );
  return entry->elements[index];
}

struct stumpless_element *
stumpless_get_element_by_name( const struct stumpless_entry *entry,
                               const char *name ) {
  size_t index;

  index = stumpless_get_element_index( entry, name );

  if( stumpless_has_error(  ) ) {
    return NULL;
  }

  return entry->elements[index];
}

size_t
stumpless_get_element_index( const struct stumpless_entry *entry,
                             const char *name ) {
  size_t i;

  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return 0;
  }

  if( !name ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "name" ) );
    return 0;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    if( strcmp( entry->elements[i]->name, name ) == 0 ) {
      clear_error(  );
      return i;
    }
  }

  raise_element_not_found(  );
  return 0;
}

const char *
stumpless_get_entry_app_name( const struct stumpless_entry *entry ) {
  VALIDATE_ARG_NOT_NULL( entry );

  clear_error(  );
  return entry->app_name;
}

int
stumpless_get_entry_facility( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return -1;
  }

  clear_error(  );
  return get_facility( entry->prival );
}

const char *
stumpless_get_entry_message( const struct stumpless_entry *entry ) {
  VALIDATE_ARG_NOT_NULL( entry );

  clear_error(  );
  return entry->message;
}

const char *
stumpless_get_entry_msgid( const struct stumpless_entry *entry ) {
  VALIDATE_ARG_NOT_NULL( entry );

  clear_error(  );
  return entry->msgid;
}

struct stumpless_param *
stumpless_get_entry_param_by_index( const struct stumpless_entry *entry,
                                    size_t element_index,
                                    size_t param_index ) {
  const struct stumpless_element *element;

  element = stumpless_get_element_by_index( entry, element_index );
  if( !element ) {
    return NULL;
  }

  return stumpless_get_param_by_index( element, param_index );
}

struct stumpless_param *
stumpless_get_entry_param_by_name( const struct stumpless_entry *entry,
                                   const char *element_name,
                                   const char *param_name ) {
  const struct stumpless_element *element;

  element = stumpless_get_element_by_name( entry, element_name );
  if( !element ) {
    return NULL;
  }

  return stumpless_get_param_by_name( element, param_name );
}

const char *
stumpless_get_entry_param_value_by_index( const struct stumpless_entry *entry,
                                          size_t element_index,
                                          size_t param_index ) {
  const struct stumpless_element *element;

  element = stumpless_get_element_by_index( entry, element_index );
  if( !element ) {
    return NULL;
  }

  return stumpless_get_param_value_by_index( element, param_index );
}

const char *
stumpless_get_entry_param_value_by_name( const struct stumpless_entry *entry,
                                         const char *element_name,
                                         const char *param_name ) {
  const struct stumpless_element *element;

  element = stumpless_get_element_by_name( entry, element_name );
  if( !element ) {
    return NULL;
  }

  return stumpless_get_param_value_by_name( element, param_name );
}

int
stumpless_get_entry_prival( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return -1;
  }

  clear_error(  );
  return entry->prival;
}

int
stumpless_get_entry_severity( const struct stumpless_entry *entry ) {
  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return -1;
  }

  clear_error(  );
  return get_severity( entry->prival );
}

struct stumpless_entry *
stumpless_new_entry( int facility,
                     int severity,
                     const char *app_name,
                     const char *msgid,
                     const char *message,
                     ... ) {
  va_list subs;
  struct stumpless_entry *entry;

  va_start( subs, message );
  entry = vstumpless_new_entry( facility,
                                severity,
                                app_name,
                                msgid,
                                message,
                                subs );
  va_end( subs );

  return entry;
}

struct stumpless_entry *
stumpless_set_element( struct stumpless_entry *entry,
                       size_t index,
                       struct stumpless_element *element ) {
  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( element );

  if( index >= entry->element_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "element" ),
                               index );
    return NULL;
  }

  if( unchecked_entry_has_element( entry, element->name ) ) {
    raise_duplicate_element(  );
    return NULL;
  }

  entry->elements[index] = element;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_app_name( struct stumpless_entry *entry,
                              const char *app_name ) {
  const char * effective_name;
  size_t temp_name_length;
  char *temp_name;

  VALIDATE_ARG_NOT_NULL( entry );

  effective_name = app_name ? app_name : "-";

  if ( !validate_app_name_length( effective_name ) ) {
      return NULL;
  }

  temp_name = copy_cstring_with_length( effective_name, &temp_name_length );
  if( !temp_name ) {
    return NULL;
  }

  free_mem( entry->app_name );
  entry->app_name = temp_name;
  entry->app_name_length = temp_name_length;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_facility( struct stumpless_entry *entry, int facility ) {
  VALIDATE_ARG_NOT_NULL( entry );

  if( facility_is_invalid( facility ) ) {
    raise_invalid_facility( facility );
    return NULL;
  }

  entry->prival = get_prival( facility, get_severity( entry->prival ) );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_msgid( struct stumpless_entry *entry,
                           const char *msgid ) {
  const char *effective_msgid;
  size_t temp_length;
  char *temp_msgid;

  VALIDATE_ARG_NOT_NULL( entry );

  effective_msgid = msgid ? msgid : "-";
  if( !validate_msgid_length( effective_msgid ) || !validate_msgid_format( effective_msgid ) ) {
      return NULL;
  }

  temp_msgid = copy_cstring_with_length( effective_msgid, &temp_length );
  if( !temp_msgid ) {
    return NULL;
  }

  free_mem( entry->msgid );
  entry->msgid = temp_msgid;
  entry->msgid_length = temp_length;

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_message( struct stumpless_entry *entry,
                             const char *message,
                             ... ) {
  va_list subs;
  struct stumpless_entry *result;

  va_start( subs, message );
  result = vstumpless_set_entry_message( entry, message, subs );
  va_end( subs );

  return result;
}

struct stumpless_entry *
stumpless_set_entry_param_by_index( struct stumpless_entry *entry,
                                    size_t element_index,
                                    size_t param_index,
                                    struct stumpless_param *param ) {
  struct stumpless_element *element;
  const struct stumpless_element *set_result;

  VALIDATE_ARG_NOT_NULL( entry );

  if( element_index >= entry->element_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "element" ),
                               element_index );
    return NULL;
  }

  element = entry->elements[element_index];
  set_result = stumpless_set_param( element, param_index, param );
  if( !set_result ) {
    return NULL;
  }

  return entry;
}

struct stumpless_entry *
stumpless_set_entry_param_value_by_index( struct stumpless_entry *entry,
                                          size_t element_index,
                                          size_t param_index,
                                          const char *value ) {
  struct stumpless_element *element;
  const struct stumpless_element *set_result;

  VALIDATE_ARG_NOT_NULL( entry );

  if( element_index >= entry->element_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "element" ),
                               element_index );
    return NULL;
  }

  element = entry->elements[element_index];
  set_result = stumpless_set_param_value_by_index( element,
                                                   param_index,
                                                   value );
  if( !set_result ) {
    return NULL;
  }

  return entry;
}

struct stumpless_entry *
stumpless_set_entry_param_value_by_name( struct stumpless_entry *entry,
                                         const char *element_name,
                                         const char *param_name,
                                         const char *value ) {
  struct stumpless_element *element;
  bool element_created = false;
  const void *result;

  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( element_name );

  element = stumpless_get_element_by_name( entry, element_name );
  if( !element ) {
    element = stumpless_new_element( element_name );
    if( !element ) {
      goto fail;
    }

    element_created = true;
  }

  result = stumpless_set_param_value_by_name( element, param_name, value );
  if( !result ) {
    goto fail_set;
  }

  if( element_created ) {
    result = stumpless_add_element( entry, element );
    if( !result ) {
      goto fail_set;
    }
  }

  return entry;

fail_set:
  if( element_created ) {
    stumpless_destroy_element_and_contents( element );
  }
fail:
  return NULL;
}

struct stumpless_entry *
stumpless_set_entry_priority( struct stumpless_entry *entry,
                              int facility,
                              int severity ) {
  VALIDATE_ARG_NOT_NULL( entry );

  if( facility_is_invalid( facility ) ) {
    raise_invalid_facility( facility );
    return NULL;
  }

  if( severity_is_invalid( severity ) ) {
    raise_invalid_severity( severity );
    return NULL;
  }

  entry->prival = get_prival( facility, severity );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_prival( struct stumpless_entry *entry,
                            int prival ) {
  return stumpless_set_entry_priority( entry,
                                       get_facility( prival ),
                                       get_severity( prival ) );
}

struct stumpless_entry *
stumpless_set_entry_severity( struct stumpless_entry *entry, int severity ) {
  VALIDATE_ARG_NOT_NULL( entry );

  if( severity_is_invalid( severity ) ) {
    raise_invalid_severity( severity );
    return NULL;
  }

  entry->prival = get_prival( get_facility( entry->prival ), severity );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
vstumpless_new_entry( int facility,
                      int severity,
                      const char *app_name,
                      const char *msgid,
                      const char *message,
                      va_list subs ) {
  struct stumpless_entry *entry;
  const char *effective_app_name;
  size_t *app_name_length;
  const char *effective_msgid;
  size_t *msgid_length;
  size_t *message_length;

  if( !entry_cache ) {
    entry_cache = cache_new( sizeof( *entry ), NULL, NULL );

    if( !entry_cache ) {
      goto fail;
    }
  }

  entry = cache_alloc( entry_cache );
  if( !entry ) {
    goto fail;
  }

  effective_app_name = app_name ? app_name : "-";
  if ( !validate_app_name_length ( effective_app_name ) ) {
      goto fail_app_name;
  }

  app_name_length = &( entry->app_name_length );
  entry->app_name = copy_cstring_with_length( effective_app_name,
                                              app_name_length );
  if( !entry->app_name ) {
    goto fail_app_name;
  }

  

  effective_msgid = msgid ? msgid : "-";
  if( !validate_msgid_length( effective_msgid ) || !validate_msgid_format( effective_msgid ) ) {
      goto fail_msgid;
  }

  msgid_length = &( entry->msgid_length );
  entry->msgid = copy_cstring_with_length( effective_msgid, msgid_length );
  if( !entry->msgid ) {
    goto fail_msgid;
  }

  if( !message ) {
    entry->message = NULL;
    entry->message_length = 0;
  } else {
    message_length = &( entry->message_length );
    entry->message = config_format_string( message, subs, message_length );
    if( !entry->message ) {
      goto fail_message;
    }
  }

  if( !config_initialize_wel_data( entry ) ) {
    goto fail_wel_data;
  }
  config_set_entry_wel_type( entry, severity );

  entry->prival = get_prival( facility, severity );
  entry->elements = NULL;
  entry->element_count = 0;

  clear_error(  );
  return entry;

fail_wel_data:
  free_mem( entry->message );
fail_message:
  free_mem( entry->msgid );
fail_msgid:
  free_mem( entry->app_name );
fail_app_name:
  cache_free( entry_cache, entry );
fail:
  return NULL;
}

struct stumpless_entry *
vstumpless_set_entry_message( struct stumpless_entry *entry,
                              const char *message,
                              va_list subs ) {
  char *formatted_message;
  size_t message_length;

  VALIDATE_ARG_NOT_NULL( entry );

  if( !message ) {
    free_mem( entry->message );
    entry->message = NULL;
    entry->message_length = 0;

  } else {
    formatted_message = config_format_string( message, subs, &message_length );
    if( !formatted_message ) {
      return NULL;

    } else {
      free_mem( entry->message );
      entry->message = formatted_message;
      entry->message_length = message_length;

    }
  }

  clear_error(  );
  return entry;
}

/* private functions */

void
entry_free_all( void ) {
  cache_destroy( entry_cache );
  entry_cache = NULL;
}

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
  size_t i;
  size_t j;
  const struct stumpless_element *element;
  const struct stumpless_param *param;

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

void
unchecked_destroy_entry( const struct stumpless_entry *entry ) {
  config_destroy_wel_data( entry );

  free_mem( entry->elements );
  free_mem( entry->msgid );
  free_mem( entry->app_name );
  free_mem( entry->message );

  cache_free( entry_cache, entry );
}

bool
unchecked_entry_has_element( const struct stumpless_entry *entry,
                             const char *name ) {
  size_t i;

  for( i = 0; i < entry->element_count; i++ ) {
    if( strcmp( entry->elements[i]->name, name ) == 0 ) {
      return true;
    }
  }

  return false;
}
