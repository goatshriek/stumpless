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
#include <unistd.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/formatter.h"
#include "private/strbuilder.h"
#include "private/memory.h"

struct stumpless_entry *
stumpless_add_element(struct stumpless_entry *entry, struct stumpless_element *element){
  struct stumpless_element **new_elements;

  clear_error();

  if(!entry || !element){
    raise_argument_empty();
    return NULL;
  }

  // todo need to check for duplicates first

  new_elements = alloc_mem(sizeof(struct stumpless_element *) * (entry->element_count+1));
  if(!new_elements){
    return NULL;
  }

  if(entry->elements != NULL){
    memcpy(new_elements, entry->elements, sizeof(struct stumpless_element *) * entry->element_count);
    free_mem(entry->elements);
  }

  new_elements[entry->element_count] = element;
  entry->element_count++;
  entry->elements = new_elements;

  return entry;
}


struct stumpless_element *stumpless_add_param(struct stumpless_element *element, struct stumpless_param *param){
  struct stumpless_param **new_params;

  clear_error();

  if(!element || !param){
    raise_argument_empty();
    return NULL;
  }

  new_params = alloc_mem(sizeof(struct stumpless_param *) * (element->param_count+1));
  if(!new_params){
    return NULL;
  }

  if(element->params != NULL){
    memcpy(new_params, element->params, sizeof(struct stumpless_param *) * element->param_count);
    free_mem(element->params);
  }

  new_params[element->param_count] = param;
  element->param_count++;
  element->params = new_params;

  return element;
}

struct stumpless_element *stumpless_new_element(const char *name){
  struct stumpless_element *element;

  clear_error();

  if(!name){
    goto fail;
  }

  element = alloc_mem(sizeof(struct stumpless_element));
  if(!element){
    goto fail;
  }

  element->name_length = strlen(name);
  element->name = alloc_mem(element->name_length);
  if(!element->name){
    goto fail_name;
  }

  memcpy(element->name, name, element->name_length);
  element->params = NULL;
  element->param_count = 0;

  return element;

fail_name:
  free_mem(element);

fail:
  return NULL;
}

struct stumpless_entry *stumpless_new_entry(const char *app_name, const char *msgid, const char *message){
  struct stumpless_entry *entry;

  clear_error();

  entry = alloc_mem(sizeof(struct stumpless_entry));
  if(!entry){
    goto fail;
  }

  entry->app_name_length = strlen(app_name);
  entry->app_name = alloc_mem(entry->app_name_length);
  if(!entry->app_name){
    goto fail_app_name;
  }
  memcpy(entry->app_name, app_name, entry->app_name_length);

  entry->msgid_length = strlen(msgid);
  entry->msgid = alloc_mem(entry->msgid_length);
  if(!entry->msgid){
    goto fail_msgid;
  }
  memcpy(entry->msgid, msgid, entry->msgid_length);

  entry->message_length = strlen(message);
  entry->message = alloc_mem(entry->message_length);
  if(!entry->message){
    goto fail_message;
  }
  memcpy(entry->message, message, entry->message_length);

  entry->elements = NULL;
  entry->element_count = 0;

  return entry;

fail_message:
  free_mem(entry->msgid);
fail_msgid:
  free_mem(entry->app_name);
fail_app_name:
  free_mem(entry);
fail:
  return NULL;
}

struct stumpless_param *stumpless_new_param(const char *name, const char *value){
  struct stumpless_param *param;

  clear_error();

  if(!name || !value){
    raise_argument_empty();
    goto fail;
  }

  param = alloc_mem(sizeof(struct stumpless_param));
  if(!param){
    goto fail;
  }

  param->name_length = strlen(name);
  param->name = alloc_mem(param->name_length);
  if(!param->name){
    goto fail_name;
  }
  memcpy(param->name, name, param->name_length);

  param->value_length = strlen(value);
  param->value = alloc_mem(param->value_length);
  if(!param->value){
    goto fail_value;
  }
  memcpy(param->value, value, param->value_length);

  return param;

fail_value:
  free_mem(param->name);

fail_name:
  free_mem(param);

fail:
  return NULL;
}

void stumpless_destroy_element(struct stumpless_element *element){
  size_t i;

  if(!element){
    return;
  }

  for(i=0; i<element->param_count; i++){
    stumpless_destroy_param(element->params[i]);
  }
}

void stumpless_destroy_entry(struct stumpless_entry *entry){
  size_t i;

  if(!entry){
    return;
  }

  for(i=0; i<entry->element_count; i++){
    stumpless_destroy_element(entry->elements[i]);
  }

  free_mem(entry->elements);
  free_mem(entry->msgid);
  free_mem(entry->app_name);
  free_mem(entry->message);
  free_mem(entry);
}

void stumpless_destroy_param(struct stumpless_param *param){
  if(!param){
    return;
  }

  free_mem(param->name);
  free_mem(param->value);
  free_mem(param);
}

/* private functions */
struct strbuilder *
strbuilder_append_app_name(struct strbuilder *builder,
                           const struct stumpless_entry *entry){
  if(!entry){
    return NULL;
  }

  return strbuilder_append_buffer(builder,
                                  entry->app_name,
                                  entry->app_name_length);
}

struct strbuilder *strbuilder_append_hostname(struct strbuilder *builder){
  char buffer[RFC_5424_MAX_HOSTNAME_LENGTH+1];

  gethostname(buffer, RFC_5424_MAX_HOSTNAME_LENGTH);
  buffer[RFC_5424_MAX_HOSTNAME_LENGTH] = '\0';

  return strbuilder_append_string(builder, buffer);
}

struct strbuilder *strbuilder_append_msgid(struct strbuilder *builder,
                                           const struct stumpless_entry *entry){
  if(!entry){
    return NULL;
  }

  return strbuilder_append_buffer(builder, entry->msgid, entry->msgid_length);
}

struct strbuilder *
strbuilder_append_message(struct strbuilder *builder,
                          const struct stumpless_entry *entry){
  if(!entry){
    return NULL;
  }

  return strbuilder_append_buffer(builder,
                                  entry->message,
                                  entry->message_length);
}

struct strbuilder *strbuilder_append_procid(struct strbuilder *builder){
  return strbuilder_append_int(builder, getpid());
}

struct strbuilder *
strbuilder_append_structured_data(struct strbuilder *builder,
                                  const struct stumpless_entry *entry){
  size_t i, j;
  
  if(!entry){
    return NULL;
  }

  if(entry->element_count == 0){
    return strbuilder_append_char(builder, '-');
  }

  if(!entry->elements){
    return builder;
  }

  for(i=0; i < entry->element_count; i++){
    builder = strbuilder_append_char(builder, '[');
    builder = strbuilder_append_buffer(builder,
                                       entry->elements[i]->name,
                                       entry->elements[i]->name_length);

    for(j=0; j < entry->elements[i]->param_count; j++){
      builder = strbuilder_append_char(builder, ' ');

      builder = strbuilder_append_buffer(builder,
                                         entry->elements[i]->params[j]->name,
                                         entry->elements[i]->params[j]->name_length);

      builder = strbuilder_append_char(builder, '=');
      builder = strbuilder_append_char(builder, '"');

      builder = strbuilder_append_buffer(builder,
                                         entry->elements[i]->params[j]->value,
                                         entry->elements[i]->params[j]->value_length);

      builder = strbuilder_append_char(builder, '"');
    }

    builder = strbuilder_append_char(builder, ']');
  }

  return builder; 
}
