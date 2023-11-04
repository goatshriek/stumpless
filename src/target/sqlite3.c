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
#include "private/config/wrapper/get_now.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/formatter.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/strbuilder.h"
#include "private/target.h"
#include "private/target/sqlite3.h"
#include "private/validate.h"

// generic pointer here to prevent mandatory public API reliance on sqlite3.h
// this is called while the db mutex is held, so thread safety is not a concern
static
void *
prepare_statements( const struct stumpless_entry *entry, void *data, size_t *count ) {
  struct sqlite3_target *target;
  int sql_result;
  sqlite3_stmt *insert_stmt;
  int prival_index;
  int timestamp_index;
  int hostname_index;
  int app_name_index;
  int procid_index;
  int msgid_index;
  int structured_data_index;
  int message_index;
  char timestamp[RFC_5424_TIMESTAMP_BUFFER_SIZE];
  struct strbuilder *builder;
  const struct strbuilder *strbuilder_result;
  char *buffer;
  size_t buffer_size;

  buffer_size = config_get_now( timestamp );

  target = data;
  if( !target->insert_stmts[0] ) {
    sql_result = sqlite3_prepare_v2( target->db, target->insert_sql, -1, &target->insert_stmts[0], NULL );
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not prepare the insert statement", sql_result ); // TODO l10n
      return NULL;
    }
  } else {
    sqlite3_reset( target->insert_stmts[0] );
  }

  builder = strbuilder_new();
  if( !builder ) {
    return NULL;
  }

  insert_stmt = target->insert_stmts[0];

  // we can gather the indexes before we need to lock the entry
  prival_index = sqlite3_bind_parameter_index( insert_stmt, "$prival" );
  timestamp_index = sqlite3_bind_parameter_index( insert_stmt, "$timestamp" );
  hostname_index = sqlite3_bind_parameter_index( insert_stmt, "$hostname" );
  app_name_index = sqlite3_bind_parameter_index( insert_stmt, "$app_name" );
  procid_index = sqlite3_bind_parameter_index( insert_stmt, "$procid" );
  msgid_index = sqlite3_bind_parameter_index( insert_stmt, "$msgid" );
  structured_data_index = sqlite3_bind_parameter_index( insert_stmt, "$structured_data" );
  message_index = sqlite3_bind_parameter_index( insert_stmt, "$message" );

  lock_entry( entry );

  if( prival_index != 0 ) {
    sql_result = sqlite3_bind_int( insert_stmt, prival_index, entry->prival );
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the prival to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  if( timestamp_index != 0 ) {
    if( buffer_size == 1 && timestamp[0] == '-'  ) {
      sql_result = sqlite3_bind_null( insert_stmt, timestamp_index );
    } else {
      // transient since it lives on the stack for this function, which will
      // disappear before the step occurs
      sql_result = sqlite3_bind_text( insert_stmt, timestamp_index, timestamp, buffer_size, SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the timestamp to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  if( hostname_index != 0 ) {
    strbuilder_result = strbuilder_append_hostname( builder );
    if( !strbuilder_result ) {
      goto fail_bind;
    }
    buffer = strbuilder_get_buffer( builder, &buffer_size );
    if( buffer_size == 1 && buffer[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, hostname_index );
    } else {
      // transient since we reuse and destroy this strbuilder before the statement
      // is executed
      sql_result = sqlite3_bind_text( insert_stmt, hostname_index, buffer, buffer_size, SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the hostname to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  if( app_name_index != 0 ) {
    if( entry->app_name_length == 1 && entry->app_name[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, app_name_index );
    } else {
      sql_result = sqlite3_bind_text( insert_stmt, app_name_index, entry->app_name, entry->app_name_length, SQLITE_STATIC );
    }
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the app_name to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  if( procid_index != 0 ) {
    strbuilder_reset( builder );
    strbuilder_result = strbuilder_append_procid( builder );
    if( !strbuilder_result ) {
      goto fail_bind;
    }
    buffer = strbuilder_get_buffer( builder, &buffer_size );
    if( buffer_size == 1 && buffer[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, procid_index );
    } else {
      // transient since we reuse and destroy this strbuilder before the statement
      // is executed
      sql_result = sqlite3_bind_text( insert_stmt, procid_index, buffer, buffer_size, SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the procid to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  if( msgid_index != 0 ) {
    if( entry->msgid_length == 1 && entry->msgid[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, msgid_index );
    } else {
      sql_result = sqlite3_bind_text( insert_stmt, msgid_index, entry->msgid, entry->msgid_length, SQLITE_STATIC );
    }
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the msgid to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  if( structured_data_index != 0 ) {
    strbuilder_reset( builder );
    strbuilder_result = strbuilder_append_structured_data( builder, entry );
    if( !strbuilder_result ) {
      goto fail_bind;
    }
    buffer = strbuilder_get_buffer( builder, &buffer_size );
    if( buffer_size == 1 && buffer[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, structured_data_index );
    } else {
      // transient since we reuse and destroy this strbuilder before the statement
      // is executed
      sql_result = sqlite3_bind_text( insert_stmt, structured_data_index, buffer, buffer_size, SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the structured data to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  if( message_index != 0 ) {
    if( entry->message_length == 1 && entry->message[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, message_index );
    } else {
      sql_result = sqlite3_bind_text( insert_stmt, message_index, entry->message, entry->message_length, SQLITE_STATIC );
    }
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_error( "could not bind the message to the statement", sql_result ); // TODO l10n
      goto fail_bind;
    }
  }

  unlock_entry( entry );
  strbuilder_destroy( builder );

  *count = 1;
  return &target->insert_stmts;

fail_bind:
  unlock_entry( entry );
  strbuilder_destroy( builder );
  return NULL;
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

void *
stumpless_get_sqlite3_db( const struct stumpless_target *target ) {
  struct sqlite3_target *db_target;

  VALIDATE_ARG_NOT_NULL( target );

  if( target->type != STUMPLESS_SQLITE3_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return NULL;
  }

  db_target = target->id;
  return db_target->db;
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

struct stumpless_target *
stumpless_set_sqlite3_insert_sql( struct stumpless_target *target,
                                  const char *sql ) {
  struct sqlite3_target *db_target;

  VALIDATE_ARG_NOT_NULL( target );

  db_target = target->id;
  db_target->insert_sql = sql;
  sqlite3_finalize( db_target->insert_stmts[0] );
  db_target->insert_stmts[0] = NULL;

  return target;
}

/* private definitions */

void
destroy_sqlite3_target( struct sqlite3_target *target ) {
  sqlite3_finalize( target->insert_stmts[0] );
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

  target->insert_sql = STUMPLESS_DEFAULT_SQLITE3_INSERT_SQL;
  target->prepare_func = prepare_statements;
  target->prepare_data = target;
  target->insert_stmts[0] = NULL;
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

  statements = db_target->prepare_func( entry, db_target->prepare_data, &stmt_count );
  if( !statements ) {
    result = -1;
    if( db_target->prepare_func != prepare_statements ) {
      // TODO create an error for sqlite3 callback failure
      raise_sqlite3_error ( "the prepare statements callback failed", 0 ); // TODO make more specific
    }
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
