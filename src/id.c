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
#include <stumpless/id.h>
#include "private/id.h"
#include "private/memory.h"

static stumpless_id_t next_id=1;

stumpless_id_t add_to_id_map(struct id_map *map, void *value){
  struct id_map_node *new, *curr;

  if(!map || !value){
    return 0;
  }

  new = alloc_mem(sizeof(struct id_map_node));
  if(!new){
    return 0;
  }
  new->id = next_id++;
  new->next = NULL;
  new->value = value;

  curr = map->root;
  if(!curr){
    map->root = new;
  } else {
    while(curr->next){
      curr = curr->next;
    }
    curr->next = new;
  }

  return new->id;
}

void destroy_id_map(struct id_map *map){
  struct id_map_node *next, *remove=NULL;

  if(!map){
    return;
  }

  next = map->root;
  while(next != NULL){
    remove = next;
    next = next->next;
    free_mem(remove);
  }

  free_mem(map);
}

void *get_by_id(struct id_map *map, stumpless_id_t id){
  struct id_map_node *curr;

  if(!map){
    return NULL;
  }

  for(curr=map->root; curr != NULL; curr=curr->next){
    if(curr->id == id){
      return curr->value;
    }
  }

  return NULL;
}

struct id_map *new_id_map(){
  struct id_map *map;

  map = alloc_mem(sizeof(struct id_map));
  if(!map){
    return NULL;
  }

  map->root = NULL;

  return map;
}
