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

#ifndef __STUMPLESS_TARGET_H
#define __STUMPLESS_TARGET_H

#include <stumpless/entry.h>
#include <stumpless/id.h>

#define STUMPLESS_MAX_TARGET_COUNT 10

#ifdef __cplusplus
extern "C" {
#endif

enum stumpless_target_type {
  STUMPLESS_BUFFER_TARGET,
  STUMPLESS_SOCKET_TARGET
};

struct stumpless_target {
  stumpless_id_t id;
  enum stumpless_target_type type;
  char *name;
  int options;
  int facility;
  int severity;
};

int stumpless(const char *message);
int stumpless_add_entry(struct stumpless_target *target, struct stumpless_entry *entry);
struct stumpless_target *stumpless_get_current_target();
void stumpless_set_current_target(struct stumpless_target *target);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_TARGET_H */
