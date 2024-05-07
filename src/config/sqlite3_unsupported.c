// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023 Joel E. Anderson
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

#include <stdbool.h>
#include <stddef.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/sqlite3.h>
#include "private/config/wrapper/locale.h"
#include "private/error.h"

bool
stumpless_close_sqlite3_target_and_db( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return false;
}

void
stumpless_close_sqlite3_target_only( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return;
}

struct stumpless_target *
stumpless_create_default_sqlite3_table( struct stumpless_target *target ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

void *
stumpless_get_sqlite3_db( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

const char *
stumpless_get_sqlite3_insert_sql( const struct stumpless_target *target ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

stumpless_sqlite3_prepare_func_t
stumpless_get_sqlite3_prepare( const struct stumpless_target *target,
                               void **data ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_sqlite3_target( const char *name ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_sqlite3_target_from_db( void *db ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_open_sqlite3_target_with_options( const char *name,
                                            int flags,
                                            const char *vfs ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_set_sqlite3_insert_sql( struct stumpless_target *target,
                                  const char *sql ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

struct stumpless_target *
stumpless_set_sqlite3_prepare( struct stumpless_target *target,
                               stumpless_sqlite3_prepare_func_t preparer,
                               void *data ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}

void *
stumpless_sqlite3_prepare( const struct stumpless_entry *entry,
                           void *data,
                           size_t *count ) {
  raise_target_unsupported( L10N_SQLITE3_TARGETS_UNSUPPORTED );
  return NULL;
}
