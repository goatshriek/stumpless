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
 */

#ifndef __STUMPLESS_TARGET_SQLITE3_H
#define __STUMPLESS_TARGET_SQLITE3_H

#include <stdbool.h>
#include <stddef.h>
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>

/**
 * A string literal with the name of the table used by default for SQLite3
 * targets.
 */
#define STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING "logs"

/**
 * The default SQL statement used to insert entries into a SQLite3 database.
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
 * TODO update
 */
typedef
void *
( *stumpless_sqlite3_prepare_func_t )( const struct stumpless_entry *entry,
                                       void *data,
                                       size_t *count );

/**
 * Closes a SQLite3 target and its database handle.
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
 * @since release v2.2.0.
 *
 * @param target The SQLite3 target to close.
 *
 * @return
 */
STUMPLESS_PUBLIC_FUNCTION
bool
stumpless_close_sqlite3_target_and_db( struct stumpless_target *target );

/**
 * TODO
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_sqlite3_target_only( struct stumpless_target *target );

/**
 * TODO update
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_create_default_sqlite3_table( struct stumpless_target *target );

/**
 * TODO update
 *
 * The database handle is used by stumpless sqlite3 routines, and serialized
 * using an internal mutex. When you use this handle outside of the library, you
 * must ensure that your operations are also thread safe without this mutex, for
 * example by using the SQLITE_OPEN_NOMUTEX or SQLITE_OPEN_FULLMUTEX options.
 *
 * @return The sqlite3 database handle for this target, a sqlite3 *. The return
 * type is void * so that all users of stumpless do not have to have sqlite3
 * types defined in order to include the headers.
 */
STUMPLESS_PUBLIC_FUNCTION
void *
stumpless_get_sqlite3_db( const struct stumpless_target *target );

/**
 * TODO update
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_sqlite3_insert_sql( const struct stumpless_target *target );

/**
 * TODO update
 */
STUMPLESS_PUBLIC_FUNCTION
stumpless_sqlite3_prepare_func_t
stumpless_get_sqlite3_prepare( const struct stumpless_target *target,
                               void **data );

/**
 * Opens a SQLite3 target.
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
 * @param name The filename of the database to open.
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
 * stumpless_close_sqlite_target_and_db and stumpless_close_sqlite3_target_only.
 * Be sure to call the appropriate one depending on whether you want this handle
 * to be closed when the target is closed.
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
 * TODO update
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_sqlite3_insert_sql( struct stumpless_target *target,
                                  const char *sql );

/**
 * TODO update
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_set_sqlite3_prepare( struct stumpless_target *target,
                               stumpless_sqlite3_prepare_func_t preparer,
                               void *data );

/**
 * TODO update
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
