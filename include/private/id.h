
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

#ifndef __STUMPLESS_PRIVATE_ID_H
#  define __STUMPLESS_PRIVATE_ID_H

#  include <stumpless/id.h>

struct id_map_node {
  struct id_map_node *next;
  stumpless_id_t id;
  void *value;
};

struct id_map {
  struct id_map_node *root;
};

/* returns 0 on error, id otherwise */
stumpless_id_t add_to_id_map( struct id_map *map, void *value );
void *get_by_id( struct id_map *map, stumpless_id_t id );
struct id_map *new_id_map( void );

#endif /* __STUMPLESS_PRIVATE_ID_H */
