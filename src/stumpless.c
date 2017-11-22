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
#include <string.h>
#include <stumpless.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"

static struct target **targets=NULL;
static stumpless_id_t current_target=0;

int stumpless(const char *message){
  clear_error();
  
  if( current_target == 0 ){
    stumpless_open_target(STUMPLESS_PIPE_NAME, 0, 0);
    if( current_target == 0 ){
      return -1;
    }
  }
  
  if( sendto_target(targets[current_target-1], message) <= 0){
    perror("could not send message");
    return -1;
  }

  return 0;
}

struct stumpless_target *
stumpless_open_target(const char *name, int options, int facility){
  clear_error();
  struct stumpless_target *pub_target;
  struct target *priv_target;
  size_t name_len;

  if( current_target == STUMPLESS_MAX_TARGET_COUNT-1 ){
    return NULL;
  }

  if(!targets){
    targets = alloc_mem(sizeof(struct stumpless_target *) * STUMPLESS_MAX_TARGET_COUNT);
    if(!targets)
      return NULL;
  }

  pub_target = alloc_mem(sizeof(struct stumpless_target));
  if( !pub_target ){
    return NULL;
  }
  
  name_len = strlen(name) ;
  priv_target = new_target(name, name_len);
  if( !priv_target ){
    free_mem(pub_target);
    return NULL;
  }

  pub_target->name = alloc_mem(name_len);
  if( !pub_target->name ){
    free_mem(pub_target);
    free_mem(priv_target);
    return NULL;
  }

  memcpy(pub_target->name, name, name_len);

  pub_target->id = current_target++;
  pub_target->options = options;
  pub_target->facility = facility;

  targets[pub_target->id] = priv_target;
  
  return pub_target;
}

void
stumpless_close_target(struct stumpless_target *target){
  clear_error();
  
  if(target && targets){
    destroy_target(targets[target->id]);
  }
  
  // todo need to clean up the id list
}

struct stumpless_version *
get_stumpless_version(){
  struct stumpless_version *version;

  clear_error();

  version = alloc_mem(sizeof(struct stumpless_version));
  if(!version){
    return NULL;
  }

  version->major = STUMPLESS_MAJOR_VERSION;
  version->minor = STUMPLESS_MINOR_VERSION;
  version->patch = STUMPLESS_PATCH_VERSION;

  return version;
}
