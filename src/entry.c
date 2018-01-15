/*
 * Copyright 2018, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stumpless/entry.h>
#include <unistd.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/formatter.h"
#include "private/memory.h"

struct stumpless_entry *
stumpless_add_element(struct stumpless_entry *entry, struct stumpless_element *element){
  struct stumpless_element **new_elements;

  clear_error();

  if(!entry || !element){
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
ssize_t get_app_name(struct stumpless_entry *entry, char *destination, size_t size){
  if(!entry || !destination || !entry->app_name){
    return 0;
  }

  if( entry->app_name_length > size){
    return -((ssize_t)(entry->app_name_length));
  } else {
    memcpy(destination, entry->app_name, entry->app_name_length);
    return entry->app_name_length;
  }
}

ssize_t get_hostname(char *destination, size_t size){
  char buffer[RFC_5424_MAX_HOSTNAME_LENGTH+1];
  size_t hostname_length;

  gethostname(buffer, RFC_5424_MAX_HOSTNAME_LENGTH);
  buffer[RFC_5424_MAX_HOSTNAME_LENGTH] = '\0';
  hostname_length = strlen(buffer);

  if(hostname_length > size){
    return -((ssize_t)hostname_length);
  } else {
    memcpy(destination, buffer, hostname_length);
    return hostname_length;
  }
}

ssize_t get_msgid(struct stumpless_entry *entry, char *destination, size_t size){
  if(!entry || !destination || !entry->msgid){
    return 0;
  }

  if( entry->msgid_length > size){
    return -((ssize_t)(entry->msgid_length));
  } else {
    memcpy(destination, entry->msgid, entry->msgid_length);
    return entry->msgid_length;
  }
}

ssize_t get_message(struct stumpless_entry *entry, char *destination, size_t size){
  if(!entry || !destination || !entry->message){
    return 0;
  }

  if( entry->message_length > size){
    return -((ssize_t)(entry->message_length));
  } else {
    memcpy(destination, entry->message, entry->message_length);
    return entry->message_length;
  }
}

ssize_t get_procid(char *destination, size_t size){
  char buffer[RFC_5424_MAX_PROCID_LENGTH];
  size_t written;

  written = snprintf(buffer, RFC_5424_MAX_PROCID_LENGTH, "%d", getpid());

  if(written > size){
    return -((ssize_t)written);
  } else {
    memcpy(destination, buffer, written);
    return written;
  }
}

ssize_t get_structured_data(struct stumpless_entry *entry, char *destination, size_t size){
  const char *sd = "[exampleSDID@32473 iut=\"3\xcf\x8f\" eventSource=\"Application\\]\" eventID=\"1011\"][example2@32473 class=\"high\"]";
  size_t sd_length;
  
  sd_length = strlen(sd);

  if(sd_length > size){
    return -((size_t)sd_length);
  } else {
    memcpy(destination, sd, sd_length);
    return sd_length;
  }
}
