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
#include <string.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include "private/error.h"
#include "private/id.h"
#include "private/memory.h"
#include "private/target/buffer.h"

//static struct buffer_target **targets=NULL;
static struct id_map *targets=NULL;

/* public functions */

void
stumpless_close_buffer_target(struct stumpless_target *target){
  clear_error();
  
  if(target && targets){
    destroy_buffer_target(get_by_id(targets, target->id));
  }
  
  // todo need to clean up the id list
}

struct stumpless_target *
stumpless_open_buffer_target(const char *name, char *buffer, size_t size, int options, int facility){
  struct stumpless_target *pub_target;
  struct buffer_target *priv_target;
  size_t name_len;

  clear_error();
  
  if(!targets){
    targets = new_id_map();
    if(!targets){
      goto fail;
    }
  }

  pub_target = alloc_mem(sizeof(struct stumpless_target));
  if( !pub_target ){
    goto fail;
  }
  
  priv_target = new_buffer_target(buffer, size);
  if( !priv_target ){
    goto fail_priv_target;
  }

  name_len = strlen(name);
  pub_target->name = alloc_mem(name_len+1);
  if( !pub_target->name ){
    goto fail_pub_name;
  }

  memcpy(pub_target->name, name, name_len);
  pub_target->name[name_len] = '\0';
  pub_target->type = STUMPLESS_BUFFER_TARGET;
  pub_target->options = options;
  pub_target->facility = facility;
  pub_target->severity = 6; // todo change this from a hardcoded value
  pub_target->id = add_to_id_map(targets, priv_target);

  stumpless_set_current_target(pub_target);
  return pub_target;

fail_pub_name:
  free_mem(priv_target);
fail_priv_target:
  free_mem(pub_target);
fail:
  return NULL;
}


/* private definitions */

void destroy_buffer_target(struct buffer_target *target){
  if( target ){
    free_mem(target);
  }
  
}

struct buffer_target *new_buffer_target(char *buffer, size_t size){
  struct buffer_target *target;

  if(!buffer){
    return NULL;
  }
  
  target = alloc_mem(sizeof(struct buffer_target));
  if( !target ){
    return NULL;
  }
  
  target->buffer = buffer;
  target->size = size;
  target->position = 0;
 
  return target;
}

int sendto_buffer_target(const struct stumpless_target *target, const char *msg){
  struct buffer_target *priv_trgt;
  size_t msg_len;
  size_t buffer_remaining;

  if(!target || !targets || !msg){
    return 0;
  }
  
  priv_trgt = get_by_id(targets, target->id);
  msg_len = strlen(msg);

  if(msg_len >= priv_trgt->size){
    // todo generate error buffer too small
    return -1;
  }

  buffer_remaining = priv_trgt->size - priv_trgt->position;
  
  if(buffer_remaining > msg_len){
    memcpy(priv_trgt->buffer+priv_trgt->position, msg, msg_len);
    priv_trgt->position = msg_len+1;
  } else {
    memcpy(priv_trgt->buffer+priv_trgt->position, msg, buffer_remaining);
    memcpy(priv_trgt->buffer, msg+buffer_remaining, msg_len-buffer_remaining);
    priv_trgt->position = msg_len - buffer_remaining + 1;
  }

  priv_trgt->buffer[priv_trgt->position-1] = '\0';

  return msg_len+1;
}
