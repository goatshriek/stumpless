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

#ifndef __STUMPLESS_PRIVATE_ID_H
#define __STUMPLESS_PRIVATE_ID_H
 
#include <stumpless/id.h>

struct id_map_node {
  struct id_map_node *next;
  stumpless_id_t id;
  void *value;
};

struct id_map {
  struct id_map_node *root;
};

/* returns 0 on error, id otherwise */
stumpless_id_t add_to_id_map(struct id_map *map, void *value);
void destroy_id_map(struct id_map *map);
void *get_id(struct id_map *map, stumpless_id_t id);
struct id_map *new_id_map();

#endif /* __STUMPLESS_PRIVATE_ID_H */
