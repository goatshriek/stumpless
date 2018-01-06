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
#include <stumpless/entry.h>
#include "private/error.h"
#include "private/memory.h"

struct stumpless_entry *stumpless_new_entry(const char *app_name, const char *message){
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

  entry->message_length = strlen(message);
  entry->message = alloc_mem(entry->message_length);
  if(!entry->message){
    free_mem(entry->app_name);
    free_mem(entry);
    return NULL;
  }
  memcpy(entry->message, message, entry->message_length);

  return entry;
}
