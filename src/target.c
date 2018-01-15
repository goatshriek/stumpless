/*
 * Copyright 2017, Joel Anderson.
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
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/socket.h>
#include "private/error.h"
#include "private/formatter.h"
#include "private/target/buffer.h"
#include "private/target/socket.h"

static struct stumpless_target *current_target=NULL;

int stumpless(const char *message){
  struct stumpless_entry *entry;
  struct stumpless_target *current_target;
  int result;

  clear_error();

  current_target = stumpless_get_current_target();
  if(!current_target){
    current_target = stumpless_open_socket_target(STUMPLESS_SOCKET_NAME, 0, 0);
  }

  entry = stumpless_new_entry("APP-NAME", "MSGID", message);
  if(!entry){
    return -1;
  }

  result = stumpless_add_entry(current_target, entry);
  stumpless_destroy_entry(entry);
  return result;
}

int stumpless_add_entry(struct stumpless_target *target, struct stumpless_entry *entry){
  char *message;

  clear_error();
 
  if( !target ){
    return -1;
  }

  message = format_entry(target, entry);

  switch(target->type){
    case STUMPLESS_SOCKET_TARGET:
      if( sendto_socket_target(target, message) <= 0){
        perror("could not send message");
        return -1;
      }
      break;
    case STUMPLESS_BUFFER_TARGET:
      if( sendto_buffer_target(target, message) <= 0 ){
        printf("could not send message to target");
        return -1;
      }
      break;
    default:
      printf("target type unrecognized\n");
      return -1;
  }

  return 0;
}

struct stumpless_target *stumpless_get_current_target(){
  clear_error();

  return current_target;
}

void stumpless_set_current_target(struct stumpless_target *target){
  current_target = target;
}
