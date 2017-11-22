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

#ifndef __STUMPLESS_H
#define __STUMPLESS_H

#define STUMPLESS_PIPE_NAME "/tmp/stumplesstestpipe"
#define STUMPLESS_PIPE_NAME_LENGTH 22
#define STUMPLESS_MAX_TARGET_COUNT 10

#ifdef __cplusplus
extern "C" {
#endif

typedef int stumpless_id_t;

struct stumpless_target {
  stumpless_id_t id;
  char *name;
  int options;
  int facility;
};

struct stumpless_target *stumpless_open_target(const char *name, int options, int facility);
void stumpless_close_target(struct stumpless_target *target);
int stumpless(const char *message);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_H */
