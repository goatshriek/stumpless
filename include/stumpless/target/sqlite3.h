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

/** @file
 * SQLite3 targets allow logs to be sent to a SQLite3 database. The database,
 * tables, and fields can be left up to the defaults, or customized as needed.
 *
 * **Thread Safety: MT-Safe**
 * Logging to sqlite3 targets is thread safe. A mutex is used to coordinate
 * transactions.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to sqlite3 targets is not signal safe, as a non-reentrant lock is
 * used to coordinate transactions.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to sqlite3 targets is not safe to call from threads that may be
 * asynchronously cancelled, as the cleanup of the lock may not be completed.
 *
 * @since release v2.2.0
 */

#ifndef __STUMPLESS_TARGET_SQLITE3_H
#define __STUMPLESS_TARGET_SQLITE3_H

#include <stdbool.h>
#include <stddef.h>
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>

/**
 * The default SQL statement used to insert entries into a SQLite3 database.
 *
 * @since release v2.2.0
 */
#define STUMPLESS_DEFAULT_SQLITE3_INSERT_SQL \
"INSERT INTO " STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING " "                 \
"( prival, version, timestamp, hostname, app_name, procid, msgid,"             \
"  structured_data, message ) "                                                \
"VALUES ( $prival, 1, $timestamp, $hostname, $app_name, $procid, $msgid, "     \
         "$structured_data, $message )"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A function for generating SQLite3 prepared statements for a given entry. See
 * \ref stumpless_set_sqlite3_prepare for the semantics of writing and using a
 * prepare function with SQLite3 targets.
 *
 * @since release v2.2.0
 */
typedef
void *
( *stumpless_sqlite3_prepare_func_t )( const struct stumpless_entry *entry,
                                       void *data,
                                       size_t *count );

/**
 * Closes a SQLite3 target and its database handle.
 *
 * This function can fail if the database handle cannot be closed. In this case,
 * the target is not closed, and no resources are released.
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
 *
 * @return true if the target was closed, and false if not. An error code is
 * set appropriately if the target could not be closed.
 */
STUMPLESS_PUBLIC_FUNCTION
bool
stumpless_close_sqlite3_target_and_db( const struct stumpless_target *target );

/**
 * Closes a SQLite3 target, but does not touch the database handle.
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
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_sqlite3_target_only( const struct stumpless_target *target );

/**
 * Creates a table in the target's database for use with the default SQLite3
 * insertion behavior. The schema of this table is described below. Note that
 * the value of \c STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING is configurable
 * and set at build time for the library.
 *
 * \code{.sql}
 * CREATE TABLE STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING (
 *   log_id INTEGER PRIMARY KEY,
 *   prival INTEGER NOT NULL,
 *   version INTEGER NOT NULL,
 *   timestamp TEXT,
 *   hostname TEXT,
 *   app_name TEXT,
 *   procid TEXT,
 *   msgid TEXT,
 *   structured_data TEXT,
 *   message TEXT
 * );
 * \endcode
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as a mutex is used to coordinate the table
 * creation with other target modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Thisi function is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the target with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock used for the target may not be
 * completed.
 *
 * @since release v2.2.0
 *
 * @param target The target to create the default table in.
 *
 * @return The modified target if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_create_default_sqlite3_table( struct stumpless_target *target );

/**
 * Gets the SQLite3 database handle used by the target.
 *
 * The database handle is used by stumpless sqlite3 routines, and serialized
 * using an internal mutex. When you use this handle outside of the library, you
 * must ensure that your operations are also thread safe without this mutex, for
 * example by using the SQLITE_OPEN_NOMUTEX or SQLITE_OPEN_FULLMUTEX options.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as a mutex is used to coordinate the retrieval
 * of the handle with other target modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Thisi function is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the target with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock used for the target may not be
 * completed.
 *
 * @since release v2.2.0
 *
 * @return The sqlite3 database handle for this target, a sqlite3 *. The return
 * type is void * so that all users of stumpless do not have to have sqlite3
 * types defined in order to include the headers.
 */
STUMPLESS_PUBLIC_FUNCTION
void *
stumpless_get_sqlite3_db( const struct stumpless_target *target );

/**
 * Gets the SQL statement used to insert entries into the database. See
 * \ref stumpless_set_sqlite3_insert_sql to change this statement.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as a mutex is used to coordinate the retrieval
 * of the SQL statement with other target modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Thisi function is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the target with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock used for the target may not be
 * completed.
 *
 * @since release v2.2.0
 *
 * @param target The target to get the insert SQL from.
 *
 * @return The current SQL used to insert entries into the database, as a UTF-8
 * encoded string. If an error occurs then NULL is returned and an error is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_sqlite3_insert_sql( const struct stumpless_target *target );

/**
 * Gets the preparation function and data pointer used to prepare statements
 * for insertion into the database. See \ref stumpless_set_sqlite3_prepare
 * to change this function.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as a mutex is used to coordinate the retrieval
 * of the function with other target modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Thisi function is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the target with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock used for the target may not be
 * completed.
 *
 * @since release v2.2.0
 *
 * @param target The target to get the prepare function from.
 *
 * @param data A pointer to a variable where the data pointer should be written
 * to. If this is NULL, then it is ignored.
 *
 * @return The current prepare function for the target. If an error occurs
 * then NULL is returned and an error is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
stumpless_sqlite3_prepare_func_t
stumpless_get_sqlite3_prepare( const struct stumpless_target *target,
                               void **data );

/**
 * Opens a SQLite3 target.
 *
 * This is equivalent to calling \ref stumpless_open_sqlite3_target_with_options
 * with SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE as the flags and NULL as the
 * VFS module name.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not modified by
 * any other threads during execution.
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
 * @param name The name of the database to open.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_sqlite3_target( const char *name );

/**
 * Opens a SQLite3 target with an already-open database handle.
 *
 * This function allows a specialized database to be opened, or an existing
 * handle to be used. For example, if an in-memory database is needed, it
 * can be opened and then passed to this function for logging.
 *
 * Note that there are two close functions for SQLite3 targets:
 * \ref stumpless_close_sqlite3_target_and_db and
 * \ref stumpless_close_sqlite3_target_only. Be sure to call the appropriate
 * one depending on whether you want this handle to be closed when the target
 * is closed.
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
 * @param db The database handle to use. This should be a sqlite3 *, though it
 * is not declared as such so that sqlite3 headers are not required.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_sqlite3_target_from_db( void *db );

/**
 * Opens a SQLite3 target with the provided options. The three parameters are
 * passed directly to sqlite3_open_v2.
 *
 * **Thread Safety: MT-Safe race:name race:vfs**
 * This function is thread safe, of course assuming that name and vfs are not
 * modified by any other threads during execution.
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
 * @param name The name of the database to open.
 *
 * @param flags Flags as defined for sqlite3_open_v2.
 *
 * @param vfs The name of the VFS module to use as defined by sqlite3_open_v2.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_sqlite3_target_with_options( const char *name,
                                            int flags,
                                            const char *vfs );

/**
 * Sets the SQL statement used to insert entries into the database.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as a mutex is used to coordinate the changes
 * with other target modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Thisi function is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the target with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock used for the target may not be
 * completed.
 *
 * @since release v2.2.0
 *
 * @param target The target to set the insert SQL for.
 *
 * @param sql The new SQL insertion statement to use for the target. This string
 * must be valid for the duration of its use in the target, as a pointer to it
 * is kept internally.
 *
 * @return The modified target on success, or NULL on failure. In the event
 * of failure an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_sqlite3_insert_sql( struct stumpless_target *target,
                                  const char *sql );

/**
 * Set the function used to prepare statements for entries to this target.
 *
 * Preparation functions take three arguments: the entry that is being sent to
 * the database target, a pointer provided when the function is set, and an
 * output parameter where the number of prepared statements to use is written.
 * The function should return a pointer to an array of prepared statements that
 * should be committed to the database for the entry, or NULL if an error
 * occurs. The default prepare function is \ref stumpless_sqlite3_prepare, which
 * is a good place to look for an example.
 *
 * Note that the return type is a void * instead of the actual type of
 * sqlite3_stmt **. This is so that the SQLite3 headers are not needed.
 *
 * Be careful when using a custom prepare function in builds where SQLite was
 * directly embedded into Stumpless instead of dynamically linked. If this is
 * the case, using a single databse handle in both SQLite functions compiled
 * into Stumpless and SQLite functions compiled in a separate module may cause
 * serious issues, for example due to static data structures. The example
 * \ref sqlite3_example.c does this, and is a good way to check if you are in
 * this situation as it will fail in this scenario.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as a mutex is used to coordinate accesses of the
 * target structures.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Thisi function is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the target with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock used for the target may not be
 * completed.
 *
 * @since release v2.2.0
 *
 * @param target The target to set the function for.
 *
 * @param preparer The new prepare function to use in the target.
 *
 * @param data A pointer that will be passed to the prepare function on each
 * invocation.
 *
 * @return The modified target on success, or NULL on failure. In the event
 * of failure an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_sqlite3_prepare( struct stumpless_target *target,
                               stumpless_sqlite3_prepare_func_t preparer,
                               void *data );

/**
 * The default prepare function used for SQLite3 targets.
 *
 * This function will generate a single prepared statement based on the target's
 * current insert SQL statement. See \ref stumpless_set_sqlite3_insert_sql for
 * how to set the SQL used by this function.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe as a mutex is used to coordinate accesses of the
 * entry and target structures.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Thisi function is not signal safe, as a non-reentrant lock is used
 * to coordinate the read of the target with other potential accesses.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock used for the target may not be
 * completed.
 *
 * @since release v2.2.0
 *
 * @param entry The entry to prepare the statement based on.
 *
 * @param data The internal SQLite3 target structure.
 *
 * @param count A pointer to an output variable where the number of valid
 * prepared statements will be written to.
 *
 * @return A pointer to an array of sqlite3_stmt pointers on success, or NULL
 * on failure. In the event of failure an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
void *
stumpless_sqlite3_prepare( const struct stumpless_entry *entry,
                           void *data,
                           size_t *count );

#ifdef __cplusplus
}                               /* extern "C" */
#endif

#endif                          /* __STUMPLESS_TARGET_SQLITE3_H */
