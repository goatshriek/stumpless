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
#include <stumpless/target.h>
#include <stumpless/target/file.h>
#include "private/target/file.h"

void
stumpless_close_file_target( struct stumpless_target *target ) {
  return;
}

struct stumpless_target *
stumpless_open_file_target( const char *name,
                            int options,
                            int default_facility ) {
  return NULL;
}

/* private definitions */

void
destroy_file_target( struct file_target *target ) {
  return;
}

struct file_target *
new_file_target( const char *filename ) {
  return NULL;
}

int
sendto_file_target( struct file_target *target,
                    const char *msg,
                    size_t msg_length ) {
  return -1;
}
