/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_TARGET_SQLITE3_H
#define __STUMPLESS_PRIVATE_TARGET_SQLITE3_H

#include <sqlite3.h>
#include <stddef.h>
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include "private/config/wrapper/thread_safety.h"

//sqlite3_stmt **
//prep_statments( target, entry, data, &size );

/**
 * Internal representation of a sqlite3 target.
 */
struct sqlite3_target {
/** A connection to the database this target writes to. */
  sqlite3 *db;
/** The SQL statement used to insert entries into the database. */
  const char *insert_sql;
/** The function used to create prepared statements for database insertion. */
  void * ( *prepare_func )( const struct stumpless_entry *entry, void *data, size_t * );
/** The data pointer used for custom prepare functions. */
  void *prepare_data;
/** The prepared statement for the default prepare function. */
  sqlite3_stmt *insert_stmts[1];
#ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * Protects db. This mutex must be locked by a thread before it uses the
 * database connection.
 */
  config_mutex_t db_mutex;
#endif
};

/**
 * TODO update
 */
void
destroy_sqlite3_target( struct sqlite3_target *target );

/**
 * TODO update
 */
struct sqlite3_target *
new_sqlite3_target( const char *db_filename );

/**
 * TODO update
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The stream_mutex is used to coordinate updates
 * to the logged file.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate file writes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 */
int

send_entry_to_sqlite3_target( const struct stumpless_target *target,
                              const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_TARGET_SQLITE3_H */
