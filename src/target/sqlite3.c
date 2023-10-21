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

#include <sqlite3.h>
#include <stdbool.h>
#include <stddef.h>
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/target.h>
#include <stumpless/target/sqlite3.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/sqlite3.h"
#include "private/validate.h"

static sqlite3_stmt *default_statement = NULL; // TODO needs to be per-target (for multiple target support)
static sqlite3_stmt *default_statements[1];
static const char *default_insert_sql = "INSERT INTO logs (prival, version, timestamp, hostname, app_name, procid, msgid, structured_data, message) VALUES (3, 3, NULL, NULL, NULL, NULL, NULL, NULL, ?);";

// generic pointer here to prevent mandatory public API reliance on sqlite3.h
// this is called while the db mutex is held, so thread safety is not a concern
static
void *
prepare_statments( const struct stumpless_entry *entry, void *data, size_t *count ) {
  struct sqlite3_target *target;
  int sql_result;
  
  target = data;
  if( !default_statement) {
    sql_result = sqlite3_prepare_v2( target->db, target->insert_sql, -1, &default_statement, NULL );
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not prepare the insert statement", sql_result ); // TODO l10n
      return NULL;
    }
  } else {
    sqlite3_reset( default_statement );
  }

  sql_result = sqlite3_bind_text( default_statement, 1, entry->message, entry->message_length, SQLITE_STATIC );
  if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the message to the statement", sql_result ); // TODO l10n
      return NULL;
  }

  *count = 1;
  default_statements[0] = default_statement;
  return default_statements;
}

void
stumpless_close_sqlite3_target( struct stumpless_target *target ) {
  VALIDATE_ARG_NOT_NULL_VOID_RETURN( target );

  if( target->type != STUMPLESS_SQLITE3_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return;
  }

  destroy_sqlite3_target( target->id );
  destroy_target( target );
  clear_error(  );
}

struct stumpless_target *
stumpless_create_default_sqlite3_table( struct stumpless_target *target ) {
  struct sqlite3_target *db_target;
  const char *create_sql = "CREATE TABLE logs (log_id INTEGER PRIMARY KEY, prival INTEGER NOT NULL, version INTEGER NOT NULL, timestamp TEXT, hostname TEXT, app_name TEXT, procid TEXT, msgid TEXT, structured_data TEXT, message TEXT);";
  sqlite3_stmt *create_statement = NULL;
  int sql_result;
  size_t try_count = 0;
  struct stumpless_target *return_result;

  VALIDATE_ARG_NOT_NULL( target );

  db_target = target->id;
  return_result = target;
  clear_error();

  config_lock_mutex( &db_target->db_mutex );

  // TODO assuming that the target is open already
  sql_result = sqlite3_prepare_v2( db_target->db, create_sql, -1, &create_statement, NULL );
  if( sql_result != SQLITE_OK ) {
    raise_sqlite3_error( "sqlite3_prepare_v2 failed on the table creation statement", sql_result );  // TODO l10n
    return_result = NULL;
    goto cleanup_and_finish;
  }

  while( true ) {
    try_count++;
    sql_result = sqlite3_step( create_statement );

    if( sql_result == SQLITE_BUSY ) {
      if( try_count > 3 ) { // TODO arbitrary retry count ceiling
        // TODO make code more specific, STUMPLESS_SQLITE3_BUSY
        raise_error(STUMPLESS_SQLITE3_FAILURE, "the database was busy and could not complete the transaction", cap_size_t_to_int(try_count), "the number of attempts made" );
        return_result = NULL;
        goto cleanup_and_finish;
      }
    }

    if( sql_result == SQLITE_DONE ) {
      goto cleanup_and_finish;
    }

    raise_sqlite3_error( "sqlite3_step failed on the table creation statement", sql_result );  // TODO l10n
    return_result = NULL;
    goto cleanup_and_finish;
  }


cleanup_and_finish:
  sqlite3_finalize( create_statement ); // todo capture errors
  config_unlock_mutex( &db_target->db_mutex );
  return return_result;
}

struct stumpless_target *
stumpless_open_sqlite3_target( const char *db_filename ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( db_filename );

  target = new_target( STUMPLESS_SQLITE3_TARGET, db_filename );

  if( !target ) {
    goto fail;
  }

  target->id = new_sqlite3_target( db_filename );
  if( !target->id ) {
    goto fail_id;
  }

  stumpless_set_current_target( target );
  return target;

fail_id:
  destroy_target( target );
fail:
  return NULL;
}

/* private definitions */

void
destroy_sqlite3_target( struct sqlite3_target *target ) {
  sqlite3_finalize( default_statement );
  default_statement = NULL; // TODO can remove later
  // we use v2 here to allow a close to not be blocked by pending transactions
  int sql_result = sqlite3_close_v2( target->db );
  if( sql_result != SQLITE_OK ) {
    // TODO raise an error
    //printf("couldn't close the database\n");
  } else {
    //printf("closed the database\n");
  }
  config_destroy_mutex( &target->db_mutex );
  free_mem( target );
}

struct sqlite3_target *
new_sqlite3_target( const char *db_filename ) {
  struct sqlite3_target *target;
  int sql_result;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }
  target->db = NULL;

  sql_result = sqlite3_open( db_filename, &target->db );
  if( sql_result != SQLITE_OK ) {
    raise_sqlite3_error( "could not open the provided database name", sql_result ); // TODO l10n
    goto fail_db;
  }

  target->insert_sql = default_insert_sql;
  config_init_mutex( &target->db_mutex );

  return target;

fail_db:
  sqlite3_close( target->db );
  free_mem( target );
fail:
  return NULL;
}

int
send_entry_to_sqlite3_target( const struct stumpless_target *target,
                              const struct stumpless_entry *entry ) {
  struct sqlite3_target *db_target;
  size_t stmt_count;
  size_t i;
  sqlite3_stmt **statements;
  int result = 1;
  int sql_result;

  db_target = target->id;

  config_lock_mutex( &db_target->db_mutex );

  statements = prepare_statments( entry, db_target, &stmt_count );
  if( !statements ) {
    result = -1;
    // TODO create an error for sqlite3 callback failure
    // TODO only do this if we didn't use our built-in prepare
    raise_sqlite3_error ( "the prepare statements callback failed", 0 ); // TODO make more specific
    goto cleanup_and_finish;
  }

  for( i = 0; i < stmt_count; i++ ) {
    sql_result = sqlite3_step( statements[i] );
    if( sql_result != SQLITE_DONE ) {
      result = -1;
      raise_sqlite3_error( "sqlite3_step failed", sql_result );  // TODO l10n
      goto cleanup_and_finish;
    }
  }

cleanup_and_finish:
  config_unlock_mutex( &db_target->db_mutex );
  return result;
}
