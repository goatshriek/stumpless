// SPDX-License-Identifier: Apache-2.0

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

stumpless_id_t
add_to_id_map( struct id_map *map, void *value ) {
  stumpless_id_t index;
  void **new_values;
  size_t i, current_size, new_size;

  current_size = map->size;

  for( i = 0; i < current_size; i++ ) {
    if( map->values[i] == NULL ) {
      map->values[i] = value;
      return i;
    }
  }

  new_size = current_size * 2;
  new_values = realloc_mem( map->values, new_size * sizeof( *( map->values ) ) );
  if( !new_values ) {
    return -1;
  } else {
    map->values = new_values;
    map->values[current_size] = value;
    map->size = new_size;

    for( i=current_size+1; i < new_size; i++ ) {
      map->values[i] = NULL;
    }

    return current_size;
  }
}

void *
get_by_id( struct id_map *map, stumpless_id_t id ) {
  if( !map || id < 0 || id >= map->size ) {
    return NULL;
  } else {
    return map->values[id];
  }
}

struct id_map *
new_id_map(  ) {
  struct id_map *map;
  size_t i;

  map = alloc_mem( sizeof( *map ) );
  if( !map ) {
    return NULL;
  }

  map->size = 64;
  map->values = alloc_mem( map->size * sizeof( *( map->values ) ) );
  if( !map->values ) {
    free_mem( map );
    return NULL;
  } else {
    for( i=0; i < map->size; i++ ) {
      map->values[i] = NULL;
    }
  }

  return map;
}

void
remove_by_id( struct id_map *map, stumpless_id_t id ) {
  if( map && id >= 0 && id < map->size ) {
    map->values[id] = NULL;
  }
}
