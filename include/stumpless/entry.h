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
#include <stumpless/id.h>

#ifdef __cplusplus
extern "C" {
#endif

struct stumpless_param {
  char *name;
  size_t name_length;
  char *value;
  size_t value_length;
};

struct stumpless_element {
  char *name;
  size_t name_length;
  struct stumpless_param **params;
  size_t param_count;
};

struct stumpless_entry {
  stumpless_id_t id;
  char *app_name;
  size_t app_name_length;
  char *message;
  size_t message_length;
  char *msgid;
  size_t msgid_length;
  struct stumpless_element **elements;
  size_t element_count;
};

struct stumpless_entry *stumpless_add_element(struct stumpless_entry *entry, struct stumpless_element *element);
struct stumpless_element *stumpless_add_param(struct stumpless_element *element, struct stumpless_param *param);
struct stumpless_element *stumpless_new_element(const char *name);
struct stumpless_entry *stumpless_new_entry(const char *app_name, const char *msgid, const char *message);
struct stumpless_param *stumpless_new_param(const char *name, const char *value);
void stumpless_destroy_element(struct stumpless_element *element);
void stumpless_destroy_entry(struct stumpless_entry *entry);
void stumpless_destroy_param(struct stumpless_param *param);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_ENTRY_H */
