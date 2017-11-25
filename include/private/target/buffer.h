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

#ifndef __STUMPLESS_PRIVATE_TARGET_BUFFER_H
#define __STUMPLESS_PRIVATE_TARGET_BUFFER_H

#include <stddef.h> 
#include <stumpless/target.h>
 
struct buffer_target {
  char *buffer;
  size_t size;
  size_t position;
};

void destroy_buffer_target(struct buffer_target *target);
struct buffer_target *new_buffer_target(char *buffer, size_t size);
int sendto_buffer_target(const struct stumpless_target *target, const char *msg);

#endif /* __STUMPLESS_PRIVATE_TARGET_BUFFER_H */
