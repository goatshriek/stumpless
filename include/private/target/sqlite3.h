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
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/sqlite3.h>
#include "private/config/wrapper/thread_safety.h"

/**
 * Internal representation of a sqlite3 target.
 */
struct sqlite3_target {
/** A connection to the database this target writes to. */
  sqlite3 *db;
/** The SQL statement used to insert entries into the database. */
  const char *insert_sql;
/** The function used to create prepared statements for database insertion. */
  stumpless_sqlite3_prepare_func_t prepare_func;
/** The data pointer used for custom prepare functions. */
  void *prepare_data;
/** The prepared statement for the default prepare function. */
  sqlite3_stmt *insert_stmts[1];
#ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * Protects this target structure. This mutex must be locked by a thread before
 * it uses the database connection or fields in this structure.
 */
  config_mutex_t db_mutex;
#endif
};

/**
 * Destroys an internal SQLite3 target structure. The database handle is not
 * modified: if it is needed after this, it must be saved elsewhere.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this target.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @param target The SQLite3 target to close.
 */
void
destroy_sqlite3_target( const struct sqlite3_target *target );

/**
 * Creates a new SQLite3 internal target structure with the given database
 * handle.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @param db The database handle to use for the new target.
 *
 * @return The new target. If an error occurs then NULL is returned and an error
 * code is set appropriately.
 */
struct sqlite3_target *
new_sqlite3_target( sqlite3 *db );

/**
 * Sends an entry to a database target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The db_mutex is used to coordinate requests
 * to the database.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate database access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.2.0
 *
 * @param target The SQLite3 target to send the entry to.
 *
 * @param entry The entry to send to the database.
 *
 * @return A value greater than or equal to zero if no errors were encountered.
 * If an error was encountered then a negative value is returned an an error
 * code is set appropriately.
 */
int
send_entry_to_sqlite3_target( const struct stumpless_target *target,
                              const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_TARGET_SQLITE3_H */
