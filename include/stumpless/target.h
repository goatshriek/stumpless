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

#ifndef __STUMPLESS_TARGET_H
#define __STUMPLESS_TARGET_H

#ifdef __cplusplus
extern "C" {
#endif

enum stumpless_target_type {
  STUMPLESS_BUFFER_TARGET,
  STUMPLESS_SOCKET_TARGET
};

typedef int stumpless_id_t;

struct stumpless_target {
  stumpless_id_t id;
  enum stumpless_target_type type;
  char *name;
  int options;
  int facility;
};

int stumpless_add_entry(struct stumpless_target *target, const char *message);
struct stumpless_target *stumpless_get_current_target();
void stumpless_set_current_target(struct stumpless_target *target);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_TARGET_H */
