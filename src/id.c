
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
#include <stumpless/id.h>
#include "private/id.h"
#include "private/memory.h"

static stumpless_id_t next_id = 1;

stumpless_id_t
add_to_id_map( struct id_map *map, void *value ) {
  struct id_map_node *new, *curr;

  if( !map || !value ) {
    return 0;
  }

  new = alloc_mem( sizeof( *new ) );
  if( !new ) {
    return 0;
  }
  new->id = next_id++;
  new->next = NULL;
  new->value = value;

  curr = map->root;
  if( !curr ) {
    map->root = new;
  }
  else {
    while ( curr->next ) {
      curr = curr->next;
    }
    curr->next = new;
  }

  return new->id;
}

void
destroy_id_map( struct id_map *map ) {
  struct id_map_node *next, *remove = NULL;

  if( !map ) {
    return;
  }

  next = map->root;
  while ( next != NULL ) {
    remove = next;
    next = next->next;
    free_mem( remove );
  }

  free_mem( map );
}

void *
get_by_id( struct id_map *map, stumpless_id_t id ) {
  struct id_map_node *curr;

  if( !map ) {
    return NULL;
  }

  for( curr = map->root; curr != NULL; curr = curr->next ) {
    if( curr->id == id ) {
      return curr->value;
    }
  }

  return NULL;
}

struct id_map *
new_id_map(  ) {
  struct id_map *map;

  map = alloc_mem( sizeof( *map ) );
  if( !map ) {
    return NULL;
  }

  map->root = NULL;

  return map;
}
