
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

#ifndef __STUMPLESS_ENTRY_H
#  define __STUMPLESS_ENTRY_H

#  include <stddef.h>
#  include <stumpless/id.h>

#  ifdef __cplusplus
extern "C" {
#  endif

  struct stumpless_param {
    char *name;
    size_t name_length;
    char *value;
    size_t value_length;
  };

  struct stumpless_element {
    char *name;
    size_t name_length;
    struct stumpless_param **params;
    size_t param_count;
  };

  struct stumpless_entry {
    stumpless_id_t id;
    int prival;
    char *app_name;
    size_t app_name_length;
    char *message;
    size_t message_length;
    char *msgid;
    size_t msgid_length;
    struct stumpless_element **elements;
    size_t element_count;
  };

  /* 
   * While the functions provided right now offer basic creation and deletion
   * capabilities, there will need to be many more added to make working with
   * the messages, elements, and params easier. For example, hash-style accessors
   * and assignments, as well as a clear memory management strategy.
   */

  struct stumpless_entry *stumpless_add_element( struct stumpless_entry *entry, struct stumpless_element
                                                 *element );
  struct stumpless_element *stumpless_add_param( struct stumpless_element
                                                 *element, struct stumpless_param
                                                 *param );
  struct stumpless_element *stumpless_new_element( const char *name );
  struct stumpless_entry *stumpless_new_entry( int facility, int severity,
                                               const char *app_name,
                                               const char *msgid,
                                               const char *message );
  struct stumpless_param *stumpless_new_param( const char *name,
                                               const char *value );
  void stumpless_destroy_element( struct stumpless_element *element );
  void stumpless_destroy_entry( struct stumpless_entry *entry );
  void stumpless_destroy_param( struct stumpless_param *param );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_ENTRY_H */
