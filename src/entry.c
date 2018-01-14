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
#include <string.h>
#include <sys/types.h>
#include <stumpless/entry.h>
#include "private/entry.h"
#include "private/error.h"
#include "private/memory.h"

struct stumpless_entry *stumpless_new_entry(const char *app_name, const char *msgid, const char *message){
  struct stumpless_entry *entry;

  clear_error();

  entry = alloc_mem(sizeof(struct stumpless_entry));
  if(!entry){
    return NULL;
  }

  entry->app_name_length = strlen(app_name);
  entry->app_name = alloc_mem(entry->app_name_length);
  if(!entry->app_name){
    free_mem(entry);
    return NULL;
  }
  memcpy(entry->app_name, app_name, entry->app_name_length);

  entry->msgid_length = strlen(msgid);
  entry->msgid = alloc_mem(entry->msgid_length);
  if(!entry->msgid){
    free_mem(entry->app_name);
    free_mem(entry);
    return NULL;
  }
  memcpy(entry->msgid, msgid, entry->msgid_length);

  entry->message_length = strlen(message);
  entry->message = alloc_mem(entry->message_length);
  if(!entry->message){
    free_mem(entry->msgid);
    free_mem(entry->app_name);
    free_mem(entry);
    return NULL;
  }
  memcpy(entry->message, message, entry->message_length);

  return entry;
}

void stumpless_destroy_entry(struct stumpless_entry *entry){
  if(!entry){
    return;
  }

  free_mem(entry->msgid);
  free_mem(entry->app_name);
  free_mem(entry->message);
  free_mem(entry);
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
