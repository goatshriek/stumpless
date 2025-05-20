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

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stumpless/element.h>
#include <stumpless/entry.h>
#include <stumpless/facility.h>
#include <stumpless/param.h>
#include <stumpless/severity.h>
#include "private/cache.h"
#include "private/config.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/format_string.h"
#include "private/config/wrapper/gethostname.h"
#include "private/config/wrapper/getpid.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/config/wrapper/wel.h"
#include "private/config/wrapper/wstring.h"
#include "private/element.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/prival.h"
#include "private/severity.h"
#include "private/strbuilder.h"
#include "private/strhelper.h"
#include "private/memory.h"
#include "private/validate.h"

static struct cache *entry_cache = NULL;

struct stumpless_entry *
stumpless_add_element( struct stumpless_entry *entry,
                       struct stumpless_element *element ) {
  struct stumpless_entry *result;

  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( element );

  clear_error(  );

  lock_entry( entry );
  result = locked_add_element( entry, element );
  unlock_entry( entry );

  return result;
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
    stumpless_destroy_element_only( new_element );
  }

  return result;
}

struct stumpless_entry *
stumpless_add_new_param_to_entry( struct stumpless_entry *entry,
                                  const char *element_name,
                                  const char *param_name,
                                  const char *param_value ) {
  size_t element_name_len;
  struct stumpless_element *element;
  bool element_created = false;
  const void *result;

   VALIDATE_ARG_NOT_NULL( entry );
   VALIDATE_ARG_NOT_NULL( element_name );

  if( unlikely( !validate_element_name( element_name, &element_name_len ) ) ) {
    goto fail;
  }

  lock_entry( entry );

  element = locked_get_element_by_name( entry, element_name );
  if( !element ) {
    element = stumpless_new_element( element_name );
    if( !element ) {
      goto fail_locked;
    }

    element_created = true;
  }

  result = stumpless_add_new_param( element, param_name, param_value );
  if( !result ) {
    goto fail_locked;
  }

  if( element_created ) {
    result = locked_add_element( entry, element );
    if( !result ) {
      goto fail_locked;
    }
  }

  unlock_entry( entry );
  return entry;

fail_locked:
  unlock_entry( entry );
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

  lock_entry( entry );
  copy = stumpless_new_entry( get_facility( entry->prival ),
                              get_severity( entry->prival ),
                              entry->app_name,
                              entry->msgid,
                              entry->message );
  if( !copy ) {
    goto cleanup_and_fail;
  }

  copy->elements = alloc_array( entry->element_count, sizeof( element_copy ) );
  if( !copy->elements ) {
    unchecked_destroy_entry( copy );
    goto cleanup_and_fail;
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

  unlock_entry( entry );
  clear_error(  );
  return copy;

fail_elements:
  stumpless_destroy_entry_and_contents( copy );
cleanup_and_fail:
  unlock_entry( entry );
  return NULL;
}

void
stumpless_destroy_entry_and_contents( const struct stumpless_entry *entry ) {
  size_t i;

  if( !entry ) {
    return;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    stumpless_destroy_element_and_contents( entry->elements[i] );
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
  size_t name_len;
  bool result;

  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return false;
  }

  if( !name ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "name" ) );
    return false;
  }

  if( unlikely( !validate_element_name( name, &name_len ) ) ) {
    return false;
  }

  lock_entry( entry );
  result = unchecked_entry_has_element( entry, name );
  unlock_entry( entry );

  clear_error(  );
  return result;
}

struct stumpless_element *
stumpless_get_element_by_index( const struct stumpless_entry *entry,
                                size_t index ) {
  struct stumpless_element *result;

  VALIDATE_ARG_NOT_NULL( entry );

  if( index >= entry->element_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "element" ),
                               index );
    return NULL;
  }

  clear_error(  );

  lock_entry( entry );
  result = locked_get_element_by_index( entry, index );
  unlock_entry( entry );

  return result;
}

struct stumpless_element *
stumpless_get_element_by_name( const struct stumpless_entry *entry,
                               const char *name ) {
  size_t name_len;
  struct stumpless_element *result;

  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( name );

  if( unlikely( !validate_element_name( name, &name_len ) ) ) {
    return NULL;
  }

  clear_error(  );

  lock_entry( entry );
  result = locked_get_element_by_name( entry, name );
  unlock_entry( entry );

  return result;
}

size_t
stumpless_get_element_count( const struct stumpless_entry *entry ) {
  size_t count;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );

  lock_entry( entry );
  count = entry->element_count;
  unlock_entry( entry );

  return count;
}

size_t
stumpless_get_element_index( const struct stumpless_entry *entry,
                             const char *name ) {
  size_t name_len;
  size_t i;
  const struct stumpless_element *element;
  int cmp_result;

  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( entry );
  VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( name );

  if ( unlikely( !validate_element_name( name, &name_len ) ) ) {
    return 0;
  }

  lock_entry( entry );
  for( i = 0; i < entry->element_count; i++ ) {
    element = entry->elements[i];

    lock_element( element );
    cmp_result = memcmp( element->name, name, name_len );
    unlock_element( element );

    if( cmp_result == 0 ) {
      clear_error(  );
      goto cleanup_and_return;
    }
  }

  i = 0;
  raise_element_not_found(  );

cleanup_and_return:
  unlock_entry( entry );
  return i;
}

const char *
stumpless_get_entry_app_name( const struct stumpless_entry *entry ) {
  char *app_name_copy;

  VALIDATE_ARG_NOT_NULL( entry );

  lock_entry( entry );
  app_name_copy = alloc_mem( entry->app_name_length + 1 );
  if( !app_name_copy ) {
    goto cleanup_and_return;
  }
  memcpy( app_name_copy, entry->app_name, entry->app_name_length + 1 );
  clear_error(  );

cleanup_and_return:
  unlock_entry( entry );
  return app_name_copy;
}

enum stumpless_facility
stumpless_get_entry_facility( const struct stumpless_entry *entry ) {
  int prival;

  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return -1;
  }

  lock_entry( entry );
  prival = entry->prival;
  unlock_entry( entry );

  clear_error(  );
  return get_facility( prival );
}

const char *
stumpless_get_entry_hostname( const struct stumpless_entry *entry ) {
  struct strbuilder *hostname_builder;
  const char *hostname;

  VALIDATE_ARG_NOT_NULL( entry );

  hostname_builder = strbuilder_new();

  lock_entry( entry );
  if( entry->hostname_length > 0 ) {
    strbuilder_append_buffer( hostname_builder,
                              entry->hostname,
                              entry->hostname_length );
  } else {
    strbuilder_append_hostname( hostname_builder );
  }
  unlock_entry( entry );

  hostname = strbuilder_to_string( hostname_builder );
  strbuilder_destroy( hostname_builder );

  return hostname;
}

const char *
stumpless_get_entry_message( const struct stumpless_entry *entry ) {
  char *message_copy;

  VALIDATE_ARG_NOT_NULL( entry );

  lock_entry( entry );
  if( !entry->message ) {
    message_copy = NULL;
  } else {
    message_copy = alloc_mem( entry->message_length + 1 );
    if( !message_copy ) {
      goto cleanup_and_return;
    }
    memcpy( message_copy, entry->message, entry->message_length + 1 );
  }
  clear_error(  );

cleanup_and_return:
  unlock_entry( entry );
  return message_copy;
}

const char *
stumpless_get_entry_msgid( const struct stumpless_entry *entry ) {
  char *msgid_copy;

  VALIDATE_ARG_NOT_NULL( entry );

  lock_entry( entry );
  msgid_copy = alloc_mem( entry->msgid_length + 1 );
  if( !msgid_copy ) {
    goto cleanup_and_return;
  }
  memcpy( msgid_copy, entry->msgid, entry->msgid_length + 1 );
  clear_error(  );

cleanup_and_return:
  unlock_entry( entry );
  return msgid_copy;
}

struct stumpless_param *
stumpless_get_entry_param_by_index( const struct stumpless_entry *entry,
                                    size_t element_index,
                                    size_t param_index ) {
  const struct stumpless_element *element;

  VALIDATE_ARG_NOT_NULL( entry );

  lock_entry( entry );
  element = locked_get_element_by_index( entry, element_index );
  unlock_entry( entry );

  if( !element ) {
    return NULL;
  }

  return stumpless_get_param_by_index( element, param_index );
}

struct stumpless_param *
stumpless_get_entry_param_by_name( const struct stumpless_entry *entry,
                                   const char *element_name,
                                   const char *param_name ) {
  size_t param_name_len;
  const struct stumpless_element *element;

  VALIDATE_ARG_NOT_NULL( param_name );

  if( unlikely( !validate_param_name( param_name, &param_name_len ) ) ) {
    return NULL;
  }

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

  VALIDATE_ARG_NOT_NULL( entry );

  lock_entry( entry );
  element = locked_get_element_by_index( entry, element_index );
  unlock_entry( entry );

  if( !element ) {
    return NULL;
  }

  return stumpless_get_param_value_by_index( element, param_index );
}

const char *
stumpless_get_entry_param_value_by_name( const struct stumpless_entry *entry,
                                         const char *element_name,
                                         const char *param_name ) {
  size_t param_name_len;
  const struct stumpless_element *element;

  VALIDATE_ARG_NOT_NULL( param_name );

  if( unlikely( !validate_param_name( param_name, &param_name_len ) ) ) {
    return NULL;
  }

  element = stumpless_get_element_by_name( entry, element_name );
  if( !element ) {
    return NULL;
  }

  return stumpless_get_param_value_by_name( element, param_name );
}

int
stumpless_get_entry_prival( const struct stumpless_entry *entry ) {
  int prival;

  VALIDATE_ARG_NOT_NULL_INT_RETURN( entry );

  lock_entry( entry );
  prival = entry->prival;
  unlock_entry( entry );

  clear_error(  );
  return prival;
}

const char *
stumpless_get_entry_procid( const struct stumpless_entry *entry ) {
  struct strbuilder *procid_builder;
  const char *procid;

  VALIDATE_ARG_NOT_NULL( entry );

  procid_builder = strbuilder_new(  );

  lock_entry( entry );
  if( entry->procid_length > 0 ) {
    strbuilder_append_buffer( procid_builder,
                              entry->procid,
                              entry->procid_length );
  } else {
    strbuilder_append_procid( procid_builder );
  }
  unlock_entry( entry );

  procid = strbuilder_to_string( procid_builder );
  strbuilder_destroy( procid_builder );

  return procid;
}

enum stumpless_severity
stumpless_get_entry_severity( const struct stumpless_entry *entry ) {
  int prival;

  if( !entry ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "entry" ) );
    return -1;
  }

  lock_entry( entry );
  prival = entry->prival;
  unlock_entry( entry );

  clear_error(  );
  return get_severity( prival );
}

struct stumpless_entry *
stumpless_load_entry( struct stumpless_entry *entry,
                      enum stumpless_facility facility,
                      enum stumpless_severity severity,
                      const char *app_name,
                      const char *msgid,
                      const char *message,
                      ... ) {
  va_list subs;
  struct stumpless_entry *result;

  va_start( subs, message );
  result = vstumpless_load_entry( entry,
                                  facility,
                                  severity,
                                  app_name,
                                  msgid,
                                  message,
                                  subs );
  va_end( subs );

  return result;
}

struct stumpless_entry *
stumpless_load_entry_str( struct stumpless_entry *entry,
                          enum stumpless_facility facility,
                          enum stumpless_severity severity,
                          const char *app_name,
                          const char *msgid,
                          const char *message ) {
  char *msg;
  size_t msg_length;
  struct stumpless_entry *result;

  if( message ) {
    msg = copy_cstring_with_length( message, &msg_length );
    if( !msg ) {
      return NULL;
    }

  } else {
    msg = NULL;
    msg_length = 0;
  }

  clear_error(  );
  result = unchecked_load_entry( entry,
                                 facility,
                                 severity,
                                 app_name,
                                 msgid,
                                 msg,
                                 msg_length );

  if( !result ) {
    free_mem( msg );
  }

  return result;
}

struct stumpless_entry *
stumpless_new_entry( enum stumpless_facility facility,
                     enum stumpless_severity severity,
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
stumpless_new_entry_str( enum stumpless_facility facility,
                         enum stumpless_severity severity,
                         const char *app_name,
                         const char *msgid,
                         const char *message ) {
  char *msg;
  size_t msg_length;
  struct stumpless_entry *entry;

  if( message ) {
    msg = copy_cstring_with_length( message, &msg_length );
    if( !msg ) {
      return NULL;
    }

  } else {
    msg = NULL;
    msg_length = 0;
  }

  entry = new_entry( facility, severity, app_name, msgid, msg, msg_length );

  if( !entry ) {
    free_mem( msg );
  }

  return entry;
}

struct stumpless_entry *
stumpless_set_element( struct stumpless_entry *entry,
                       size_t index,
                       struct stumpless_element *element ) {
  struct stumpless_entry *result = NULL;

  VALIDATE_ARG_NOT_NULL( entry );
  VALIDATE_ARG_NOT_NULL( element );

  lock_entry( entry );

  if( index >= entry->element_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "element" ),
                               index );
    goto cleanup_and_return;
  }

  if( unchecked_entry_has_element( entry, element->name ) ) {
    raise_duplicate_element(  );
    goto cleanup_and_return;
  }

  entry->elements[index] = element;

  result = entry;
  clear_error(  );

cleanup_and_return:
  unlock_entry( entry );
  return result;
}

struct stumpless_entry *
stumpless_set_entry_app_name( struct stumpless_entry *entry,
                              const char *app_name ) {
  size_t name_length;

  VALIDATE_ARG_NOT_NULL( entry );

  if( unlikely( app_name && !validate_app_name( app_name, &name_length ) ) ) {
    return NULL;
  }

  lock_entry( entry );
  if( app_name ) {
    entry->app_name_length = name_length;
    memcpy( entry->app_name, app_name, name_length );
    entry->app_name[name_length] = '\0';
  } else {
    entry->app_name_length = 1;
    entry->app_name[0] = '-';
    entry->app_name[1] = '\0';
  }
  unlock_entry( entry );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_facility( struct stumpless_entry *entry,
                              enum stumpless_facility facility ) {
  VALIDATE_ARG_NOT_NULL( entry );

  if( facility_is_invalid( facility ) ) {
    raise_invalid_facility( facility );
    return NULL;
  }

  lock_entry( entry );
  entry->prival = get_prival( facility, get_severity( entry->prival ) );
  unlock_entry( entry );

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_hostname( struct stumpless_entry *entry,
                              const char *hostname ) {
  size_t new_length;

  VALIDATE_ARG_NOT_NULL( entry );

  if( unlikely( hostname && !validate_hostname( hostname, &new_length ) ) ) {
    return NULL;
  }

  lock_entry( entry );
  if( !hostname ) {
    // setting the hostname to NULL effectively restores default behavior
    entry->hostname_length = 0;
  } else {
    entry->hostname_length = new_length;
    memcpy( entry->hostname, hostname, new_length );
    entry->hostname[new_length] = '\0';
  }
  unlock_entry(entry);

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_msgid( struct stumpless_entry *entry,
                           const char *msgid ) {
  size_t new_msgid_length;

  VALIDATE_ARG_NOT_NULL( entry );

  if( unlikely( msgid && !validate_msgid( msgid, &new_msgid_length ) ) ) {
    return NULL;
  }

  lock_entry( entry );
  if( msgid ) {
    entry->msgid_length = new_msgid_length;
    memcpy( entry->msgid, msgid, new_msgid_length );
    entry->msgid[new_msgid_length] = '\0';
  } else {
    entry->msgid[0] = '-';
    entry->msgid[1] = '\0';
    entry->msgid_length = 1;
  }
  unlock_entry( entry );

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
stumpless_set_entry_message_str( struct stumpless_entry *entry,
                                 const char *message ) {
  char *new_message;
  size_t new_message_length;
  const char *old_message;

  VALIDATE_ARG_NOT_NULL( entry );

  if( message ) {
    new_message = copy_cstring_with_length( message, &new_message_length );
    if( !new_message ) {
      return NULL;
    }
  } else {
    new_message = NULL;
    new_message_length = 0;
  }

  lock_entry( entry );
  old_message = entry->message;
  entry->message = new_message;
  entry->message_length = new_message_length;
  unlock_entry( entry );

  free_mem( old_message );
  clear_error(  );

  return entry;
}

struct stumpless_entry *
stumpless_set_entry_message_str_w( struct stumpless_entry *entry,
                                   const wchar_t *message ){
  char *new_message;
  int new_message_size;
  const char *old_message;

  VALIDATE_ARG_NOT_NULL( entry );

  if( message ){
    new_message = config_copy_wstring_to_cstring( message, &new_message_size );
    if( !new_message ){
      return NULL;
    }
    new_message_size--; // leave off the NULL character

  } else {
    new_message = NULL;
    new_message_size = 0;
  }

  lock_entry( entry );
  old_message = entry->message;
  entry->message = new_message;
  entry->message_length = new_message_size;
  unlock_entry( entry );

  free_mem( old_message );
  clear_error();

  return entry;
}

struct stumpless_entry *
stumpless_set_entry_param_by_index( struct stumpless_entry *entry,
                                    size_t element_index,
                                    size_t param_index,
                                    struct stumpless_param *param ) {
  struct stumpless_element *element;
  const struct stumpless_element *set_result;

  VALIDATE_ARG_NOT_NULL( entry );

  lock_entry( entry );
  element = locked_get_element_by_index( entry, element_index );
  unlock_entry( entry );

  if( !element ) {
    return NULL;
  }

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

  lock_entry( entry );
  element = locked_get_element_by_index( entry, element_index );
  unlock_entry( entry );

  if( !element ) {
    return NULL;
  }

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

  lock_entry( entry );
  element = locked_get_element_by_name( entry, element_name );

  if( !element ) {
    element = stumpless_new_element( element_name );
    if( !element ) {
      goto cleanup_and_fail;
    }

    element_created = true;
  }

  result = stumpless_set_param_value_by_name( element, param_name, value );
  if( !result ) {
    goto fail_set;
  }

  if( element_created ) {
    result = locked_add_element( entry, element );
    if( !result ) {
      goto fail_set;
    }
  }

  unlock_entry( entry );
  clear_error(  );
  return entry;

fail_set:
  if( element_created ) {
    stumpless_destroy_element_and_contents( element );
  }
cleanup_and_fail:
  unlock_entry( entry );
  return NULL;
}

struct stumpless_entry *
stumpless_set_entry_priority( struct stumpless_entry *entry,
                              enum stumpless_facility facility,
                              enum stumpless_severity severity ) {
  VALIDATE_ARG_NOT_NULL( entry );

  if( facility_is_invalid( facility ) ) {
    raise_invalid_facility( facility );
    return NULL;
  }

  if( severity_is_invalid( severity ) ) {
    raise_invalid_severity( severity );
    return NULL;
  }

  lock_entry( entry );
  entry->prival = get_prival( facility, severity );
  unlock_entry( entry );

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
stumpless_set_entry_procid( struct stumpless_entry *entry,
                            const char *procid ) {
  size_t procid_length;

  VALIDATE_ARG_NOT_NULL( entry );

  if( !procid ) {
    procid_length = 0;
  } else {
    if( unlikely( !validate_procid( procid, &procid_length ) ) ) {
      return NULL;
    }
  }

  lock_entry( entry );
  entry->procid_length = procid_length;
  if( procid ) {
    memcpy( entry->procid, procid, procid_length );
    entry->procid[procid_length] = '\0';
  }
  unlock_entry(entry);

  clear_error(  );
  return entry;
}

struct stumpless_entry *
stumpless_set_entry_severity( struct stumpless_entry *entry,
                              enum stumpless_severity severity ) {
  VALIDATE_ARG_NOT_NULL( entry );

  if( severity_is_invalid( severity ) ) {
    raise_invalid_severity( severity );
    return NULL;
  }

  lock_entry( entry );
  entry->prival = get_prival( get_facility( entry->prival ), severity );
  unlock_entry( entry );

  clear_error(  );
  return entry;
}

void
stumpless_unload_entry_and_contents( const struct stumpless_entry *entry ) {
  size_t i;

  if( !entry ) {
    return;
  }

  for( i = 0; i < entry->element_count; i++ ) {
    stumpless_unload_element_and_contents( entry->elements[i] );
  }

  unchecked_unload_entry( entry );
}

void
stumpless_unload_entry_only( const struct stumpless_entry *entry ) {
  if( !entry ) {
    return;
  }

  unchecked_unload_entry( entry );
}

struct stumpless_entry *
vstumpless_load_entry( struct stumpless_entry *entry,
                       enum stumpless_facility facility,
                       enum stumpless_severity severity,
                       const char *app_name,
                       const char *msgid,
                       const char *message,
                       va_list subs ) {
  char *msg;
  size_t msg_length;
  struct stumpless_entry *result;

  if( message ) {
    msg = config_format_string( message, subs, &msg_length );
    if( !msg ) {
      return NULL;
    }

  } else {
    msg = NULL;
    msg_length = 0;
  }

  clear_error(  );
  result = unchecked_load_entry( entry,
                                 facility,
                                 severity,
                                 app_name,
                                 msgid,
                                 msg,
                                 msg_length );

  if( !result ) {
    free_mem( msg );
  }

  return result;
}

struct stumpless_entry *
vstumpless_new_entry( enum stumpless_facility facility,
                      enum stumpless_severity severity,
                      const char *app_name,
                      const char *msgid,
                      const char *message,
                      va_list subs ) {
  char *msg;
  size_t msg_length;
  struct stumpless_entry *entry;

  if( message ) {
    msg = config_format_string( message, subs, &msg_length );
    if( !msg ) {
      return NULL;
    }

  } else {
    msg = NULL;
    msg_length = 0;
  }

  entry = new_entry( facility, severity, app_name, msgid, msg, msg_length );

  if( !entry ) {
    free_mem( msg );
  }

  return entry;
}

struct stumpless_entry *
vstumpless_set_entry_message( struct stumpless_entry *entry,
                              const char *message,
                              va_list subs ) {
  const char *old_message;
  char *new_message;
  size_t message_length;

  VALIDATE_ARG_NOT_NULL( entry );

  if( !message ) {
    new_message = NULL;
    message_length = 0;

  } else {
    new_message = config_format_string( message, subs, &message_length );
    if( !new_message ) {
      return NULL;
    }
  }

  lock_entry( entry );
  old_message = entry->message;
  entry->message = new_message;
  entry->message_length = message_length;
  unlock_entry( entry );

  free_mem( old_message );
  clear_error(  );
  return entry;
}

/* private functions */

void
entry_free_all( void ) {
  cache_destroy( entry_cache );
  entry_cache = NULL;
}

void
lock_entry( const struct stumpless_entry *entry ) {
  config_lock_mutex( entry->mutex );
}

struct stumpless_entry *
locked_add_element( struct stumpless_entry *entry,
                    struct stumpless_element *element ) {
  struct stumpless_element **new_elements;
  size_t old_elements_size;
  size_t new_elements_size;

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

  return entry;
}

struct stumpless_element *
locked_get_element_by_index( const struct stumpless_entry *entry,
                             size_t index ) {
  if( index >= entry->element_count ) {
    raise_index_out_of_bounds( L10N_INVALID_INDEX_ERROR_MESSAGE( "element" ),
                               index );
    return NULL;
  }

  return entry->elements[index];
}

struct stumpless_element *
locked_get_element_by_name( const struct stumpless_entry *entry,
                            const char *name ) {
  size_t i;
  struct stumpless_element *element;
  int cmp_result;

  for( i = 0; i < entry->element_count; i++ ) {
    element = entry->elements[i];

    lock_element( element );
    cmp_result = strcmp( element->name, name );
    unlock_element( element );

    if( cmp_result == 0 ) {
      return element;
    }
  }

  raise_element_not_found(  );
  return NULL;
}

struct stumpless_entry *
new_entry( enum stumpless_facility facility,
           enum stumpless_severity severity,
           const char *app_name,
           const char *msgid,
           char *message,
           size_t message_length ) {
  struct stumpless_entry *entry;
  struct stumpless_entry *result;

  if( unlikely( !entry_cache ) ) {
    entry_cache = cache_new( sizeof( *entry ), NULL, NULL );
    if( !entry_cache ) {
      return NULL;
    }
  }

  entry = cache_alloc( entry_cache );
  if( unlikely( !entry ) ) {
    return NULL;
  }

  clear_error(  );

  result = unchecked_load_entry( entry,
                                 facility,
                                 severity,
                                 app_name,
                                 msgid,
                                 message,
                                 message_length );

  if( !result ) {
    cache_free( entry_cache, entry );
  }

  return result;
}

struct strbuilder *
strbuilder_append_app_name( struct strbuilder *builder,
                            const struct stumpless_entry *entry ) {
  return strbuilder_append_buffer( builder,
                                   entry->app_name, entry->app_name_length );
}

struct strbuilder *
strbuilder_append_hostname( struct strbuilder *builder ) {
  char buffer[STUMPLESS_MAX_HOSTNAME_LENGTH + 1];
  int result;

  result = config_gethostname( buffer, STUMPLESS_MAX_HOSTNAME_LENGTH + 1 );

  if( result == -1 ) {
    return strbuilder_append_char( builder, '-' );
  } else {
    return strbuilder_append_string( builder, buffer );
  }
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
  return strbuilder_append_positive_int( builder, config_getpid(  ) );
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
  unchecked_unload_entry( entry );
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

struct stumpless_entry *
unchecked_load_entry( struct stumpless_entry *entry,
                      enum stumpless_facility facility,
                      enum stumpless_severity severity,
                      const char *app_name,
                      const char *msgid,
                      char *message,
                      size_t message_length ) {
  if( app_name ) {
    if( unlikely( !validate_app_name( app_name, &entry->app_name_length ) ) ) {
      return NULL;
    }
    memcpy( entry->app_name, app_name, entry->app_name_length );
    entry->app_name[entry->app_name_length] = '\0';
  } else {
    entry->app_name[0] = '-';
    entry->app_name[1] = '\0';
    entry->app_name_length = 1;
  }

  if( msgid ) {
    if( unlikely( !validate_msgid( msgid, &entry->msgid_length ) ) ) {
      return NULL;
    }
    memcpy( entry->msgid, msgid, entry->msgid_length );
    entry->msgid[entry->msgid_length] = '\0';
  } else {
    entry->msgid[0] = '-';
    entry->msgid[1] = '\0';
    entry->msgid_length = 1;
  }

  config_assign_cached_mutex( entry->mutex );
  if( !config_check_mutex_valid( entry->mutex ) ) {
    return NULL;
  }

  if( !config_initialize_wel_data( entry ) ) {
    return NULL;
  }
  config_set_entry_wel_type( entry, severity );

  entry->procid_length = 0;
  entry->hostname_length = 0;
  entry->message = message;
  entry->message_length = message_length;
  entry->prival = get_prival( facility, severity );
  entry->elements = NULL;
  entry->element_count = 0;

  return entry;
}

void
unchecked_unload_entry( const struct stumpless_entry *entry ) {
  config_destroy_cached_mutex( entry->mutex );

  config_destroy_wel_data( entry );

  free_mem( entry->elements );
  free_mem( entry->message );
}

void
unlock_entry( const struct stumpless_entry *entry ) {
  config_unlock_mutex( entry->mutex );
}

/*
 * static function for stumpless_entry_to_string
 *  @param dest string to append formatted string
 *  @param size_t offset dest's offset
 *  @param key,value it is formatted to key="value",
 *  @return updated offset
 */
static size_t append_key_value_pair(char *dest, size_t offset, const char *key, size_t key_length, const char *value, size_t value_length) {
  // key="
  memcpy(dest + offset, key, key_length);
  offset += key_length;
  dest[offset++] = '=';
  dest[offset++] = '"';

  // value
    memcpy(dest + offset, value, value_length);
    offset += value_length;


  // "
  dest[offset++] = '"';
  dest[offset++] = ',';

  return offset;
}

char *stumpless_entry_to_string(const struct stumpless_entry *entry) {
    VALIDATE_ARG_NOT_NULL(entry);

    lock_entry(entry);

    const char *app_name = entry->app_name;
    size_t app_name_length = entry->app_name_length;
    struct stumpless_element **elements = entry->elements;
    size_t elements_count = entry->element_count;
    const char *hostname = entry->hostname;
    size_t hostname_length = entry->hostname_length;
    char *message = entry->message;
    size_t message_length = entry->message_length;
    const char *message_id = entry->msgid;
    size_t message_id_length = entry->msgid_length;
    const char *process_id = entry->procid;
    size_t process_id_length = entry->procid_length;
    size_t entry_priority_value = entry->prival;

    size_t format_total_length = 0;

    format_total_length += 7 + 20; // "prival=" + entry_priority_value
    format_total_length += 9 + app_name_length; // "app_name="
    format_total_length += 10 + hostname_length; // "hostname="
    format_total_length += 12 + message_id_length; // "message_id="
    format_total_length += 12 + process_id_length; // "process_id="
    format_total_length += 9 + message_length; // "message="

    for (size_t i = 0; i < elements_count; i++) {
        const char *element_str = stumpless_element_to_string(elements[i]);
        if (element_str) {
            format_total_length += strlen(element_str) + 1; // +1 for comma
            free_mem(element_str);
        }
    }

    char *return_format = alloc_mem(format_total_length+1);
    if (!return_format) {
        return NULL;
    }

    size_t offset = 0;
    char temp[21];

  // prival
  sprintf(temp, "%zu", entry_priority_value);
  offset = append_key_value_pair(return_format, offset, "prival", strlen("prival"), temp, strlen(temp));

  // app_name
  offset = append_key_value_pair(return_format, offset, "app_name", strlen("app_name"), app_name, app_name_length);

  // hostname
  offset = append_key_value_pair(return_format, offset, "hostname", strlen("hostname"), hostname, hostname_length);

  // message_id
  offset = append_key_value_pair(return_format, offset, "message_id", strlen("message_id"), message_id, message_id_length);

  // process_id
  offset = append_key_value_pair(return_format, offset, "process_id", strlen("process_id"), process_id, process_id_length);

  // message
  offset = append_key_value_pair(return_format, offset, "message", strlen("message"), message, message_length);


  bool is_first_element = true;
  for (size_t i = 0; i < elements_count; i++) {
    const char *element_str = stumpless_element_to_string(elements[i]);

      size_t len = strlen(element_str);
        if (!is_first_element) {
          return_format[offset++] = ',';
        }
        memcpy(return_format + offset, element_str, len);
        offset += len;
        is_first_element = false;
      free_mem(element_str);
  }
  unlock_entry(entry);

  //erase , if no element
  if(is_first_element) {
    offset--;
  }

    return_format[offset] = '\0';
    return return_format;
}
