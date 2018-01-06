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

#ifndef __STUMPLESS_ENTRY_H
#define __STUMPLESS_ENTRY_H

#include <stddef.h>
#include <stumpless.h>

#ifdef __cplusplus
extern "C" {
#endif

struct stumpless_entry {
  stumpless_id_t id;
  char *app_name;
  size_t app_name_length;
  char *message;
  size_t message_length;
};

struct stumpless_entry *stumpless_new_entry(const char *app_name, const char *message);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_ENTRY_H */
