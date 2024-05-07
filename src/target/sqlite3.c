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
#include <stumpless/config.h>
#include <stumpless/entry.h>
#include <stumpless/error.h>
#include <stumpless/target.h>
#include <stumpless/target/sqlite3.h>
#include "private/config.h"
#include "private/config/wrapper/locale.h"
#include "private/config/wrapper/get_now.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/entry.h"
#include "private/error.h"
#include "private/facility.h"
#include "private/formatter.h"
#include "private/inthelper.h"
#include "private/memory.h"
#include "private/severity.h"
#include "private/strbuilder.h"
#include "private/target.h"
#include "private/target/sqlite3.h"
#include "private/validate.h"


bool
stumpless_close_sqlite3_target_and_db( const struct stumpless_target *target ) {
  struct sqlite3_target *db_target;
  if( unlikely( !target ) ) {
    raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( "target" ) );
    return false;
  }

  if( target->type != STUMPLESS_SQLITE3_TARGET ) {
    raise_target_incompatible( L10N_INVALID_TARGET_TYPE_ERROR_MESSAGE );
    return false;
  }

  // we use v2 here to prevent close from being blocked by pending transactions
  db_target = target->id;
  int sql_result = sqlite3_close_v2( db_target->db );
  if( sql_result != SQLITE_OK ) {
    raise_sqlite3_failure( L10N_SQLITE3_CLOSE_FAILED_ERROR_MESSAGE,
                           sql_result );
    return false;
  }

  destroy_sqlite3_target( db_target );
  destroy_target( target );
  clear_error(  );
  return true;
}

void
stumpless_close_sqlite3_target_only( const struct stumpless_target *target ) {
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
  const char* create_sql = "CREATE TABLE "
                              STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING " "
                           "( log_id INTEGER PRIMARY KEY,"
                           "  prival INTEGER NOT NULL,"
                           "  version INTEGER NOT NULL,"
                           "  timestamp TEXT,"
                           "  hostname TEXT,"
                           "  app_name TEXT,"
                           "  procid TEXT,"
                           "  msgid TEXT,"
                           "  structured_data TEXT,"
                           "  message TEXT )";
  sqlite3_stmt *create_statement = NULL;
  int sql_result;
  size_t try_count = 0;
  bool busy;
  struct stumpless_target *return_result;

  VALIDATE_ARG_NOT_NULL( target );

  db_target = target->id;
  return_result = target;
  clear_error();

  config_lock_mutex( &db_target->db_mutex );

  sql_result = sqlite3_prepare_v2( db_target->db,
                                   create_sql,
                                   -1,
                                   &create_statement,
                                   NULL );
  if( sql_result != SQLITE_OK ) {
    raise_sqlite3_failure( L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE,
                           sql_result );
    return_result = NULL;
    goto cleanup_and_finish;
  }

  do {
    try_count++;
    sql_result = sqlite3_step( create_statement );

    busy = sql_result == SQLITE_BUSY;
    if( busy && try_count >= STUMPLESS_SQLITE3_RETRY_MAX ) {
      raise_sqlite3_busy();
      return_result = NULL;
      goto cleanup_and_finish;
    }
  } while( busy );

  if( sql_result != SQLITE_DONE ) {
    raise_sqlite3_failure( L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE,
                           sql_result );
    return_result = NULL;
  }

cleanup_and_finish:
  sqlite3_finalize( create_statement );
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

const char *
stumpless_get_sqlite3_insert_sql( const struct stumpless_target *target ) {
  const struct sqlite3_target *db_target;
  const char *result;

  VALIDATE_ARG_NOT_NULL( target );

  db_target = target->id;

  config_lock_mutex( &db_target->db_mutex );
  result = db_target->insert_sql;
  config_unlock_mutex( &db_target->db_mutex );

  return result;
}

stumpless_sqlite3_prepare_func_t
stumpless_get_sqlite3_prepare( const struct stumpless_target *target,
                               void **data ) {
  struct sqlite3_target *db_target;

  VALIDATE_ARG_NOT_NULL( target );

  db_target = target->id;

  if( data ) {
    *data = db_target->prepare_data;
  }

  clear_error();
  return db_target->prepare_func;
}

struct stumpless_target *
stumpless_open_sqlite3_target( const char *name ) {
  int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
  return stumpless_open_sqlite3_target_with_options( name, flags, NULL );
}

struct stumpless_target *
stumpless_open_sqlite3_target_from_db( void *db ) {
  struct stumpless_target *target;

  VALIDATE_ARG_NOT_NULL( db );

  target = new_target( STUMPLESS_SQLITE3_TARGET, "" );

  if( !target ) {
    goto fail;
  }

  target->id = new_sqlite3_target( db );
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
stumpless_open_sqlite3_target_with_options( const char *name,
                                            int flags,
                                            const char *vfs ) {
  struct stumpless_target *target;
  sqlite3 *db;
  int sql_result;

  VALIDATE_ARG_NOT_NULL( name );

  target = new_target( STUMPLESS_SQLITE3_TARGET, name );

  if( !target ) {
    goto fail;
  }

  db = NULL;
  sql_result = sqlite3_open_v2( name, &db, flags, vfs );
  if( sql_result != SQLITE_OK ) {
    raise_sqlite3_failure( L10N_SQLITE3_OPEN_FAILED_ERROR_MESSAGE, sql_result );
    goto fail_db;
  }

  target->id = new_sqlite3_target( db );
  if( !target->id ) {
    goto fail_db;
  }

  stumpless_set_current_target( target );
  return target;

fail_db:
  sqlite3_close( db );
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

  config_lock_mutex( &db_target->db_mutex );
  db_target->insert_sql = sql;
  sqlite3_finalize( db_target->insert_stmts[0] );
  db_target->insert_stmts[0] = NULL;
  config_unlock_mutex( &db_target->db_mutex );

  return target;
}

struct stumpless_target *
stumpless_set_sqlite3_prepare( struct stumpless_target *target,
                               stumpless_sqlite3_prepare_func_t preparer,
                               void *data ) {
  struct sqlite3_target *db_target;

  VALIDATE_ARG_NOT_NULL( target );
  VALIDATE_ARG_NOT_NULL( preparer );

  db_target = target->id;

  config_lock_mutex( &db_target->db_mutex );
  db_target->prepare_func = preparer;
  db_target->prepare_data = data;
  config_unlock_mutex( &db_target->db_mutex );

  return target;
}

void *
stumpless_sqlite3_prepare( const struct stumpless_entry *entry,
                           void *data,
                           size_t *count ) {
  struct sqlite3_target *target;
  int sql_result;
  int length;
  sqlite3_stmt *insert_stmt;
  int prival_index;
  int facility_index;
  int severity_index;
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
  const char *buffer;
  size_t buffer_size;
  const char *msg;

  buffer_size = config_get_now( timestamp );

  target = data;
  if( !target->insert_stmts[0] ) {
    sql_result = sqlite3_prepare_v2( target->db,
                                     target->insert_sql,
                                     -1,
                                     &target->insert_stmts[0],
                                     NULL );
    if( sql_result != SQLITE_OK ) {
      raise_sqlite3_failure( L10N_SQLITE3_PREPARE_FAILED_ERROR_MESSAGE,
                             sql_result );
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
  facility_index = sqlite3_bind_parameter_index( insert_stmt, "$facility" );
  severity_index = sqlite3_bind_parameter_index( insert_stmt, "$severity" );
  timestamp_index = sqlite3_bind_parameter_index( insert_stmt, "$timestamp" );
  hostname_index = sqlite3_bind_parameter_index( insert_stmt, "$hostname" );
  app_name_index = sqlite3_bind_parameter_index( insert_stmt, "$app_name" );
  procid_index = sqlite3_bind_parameter_index( insert_stmt, "$procid" );
  msgid_index = sqlite3_bind_parameter_index( insert_stmt, "$msgid" );
  structured_data_index = sqlite3_bind_parameter_index( insert_stmt,
                                                        "$structured_data" );
  message_index = sqlite3_bind_parameter_index( insert_stmt, "$message" );

  lock_entry( entry );

  if( prival_index != 0 ) {
    sql_result = sqlite3_bind_int( insert_stmt, prival_index, entry->prival );
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$prival" );
      goto fail_bind;
    }
  }

  if( facility_index != 0 ) {
    sql_result = sqlite3_bind_int( insert_stmt,
                                   facility_index,
                                   get_facility( entry->prival ) );
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$facility" );
      goto fail_bind;
    }
  }

  if( severity_index != 0 ) {
    sql_result = sqlite3_bind_int( insert_stmt,
                                   severity_index,
                                   get_severity( entry->prival ) );
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$severity" );
      goto fail_bind;
    }
  }

  if( timestamp_index != 0 ) {
    if( buffer_size == 1 && timestamp[0] == '-'  ) {
      sql_result = sqlite3_bind_null( insert_stmt, timestamp_index );
    } else {
      // transient since it lives on the stack for this function, which will
      // disappear before the step occurs
      sql_result = sqlite3_bind_text( insert_stmt,
                                      timestamp_index,
                                      timestamp,
                                      cap_size_t_to_int( buffer_size ),
                                      SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$timestamp" );
      goto fail_bind;
    }
  }

  if( hostname_index != 0 ) {
    strbuilder_result = strbuilder_append_hostname( builder );
    if( !strbuilder_result ) {
      goto fail;
    }
    buffer = strbuilder_get_buffer( builder, &buffer_size );
    if( buffer_size == 1 && buffer[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, hostname_index );
    } else {
      // transient since we reuse and destroy this strbuilder before the
      // statement is executed
      sql_result = sqlite3_bind_text( insert_stmt,
                                      hostname_index,
                                      buffer,
                                      cap_size_t_to_int( buffer_size ),
                                      SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$hostname" );
      goto fail_bind;
    }
  }

  if( app_name_index != 0 ) {
    if( entry->app_name_length == 1 && entry->app_name[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, app_name_index );
    } else {
      length = cap_size_t_to_int( entry->app_name_length );
      sql_result = sqlite3_bind_text( insert_stmt,
                                      app_name_index,
                                      entry->app_name,
                                      length,
                                      SQLITE_STATIC );
    }
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$app_name" );
      goto fail_bind;
    }
  }

  if( procid_index != 0 ) {
    strbuilder_reset( builder );
    strbuilder_result = strbuilder_append_procid( builder );
    if( !strbuilder_result ) {
      goto fail;
    }
    buffer = strbuilder_get_buffer( builder, &buffer_size );
    if( buffer_size == 1 && buffer[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, procid_index );
    } else {
      // transient since we reuse and destroy this strbuilder before the
      // statement is executed
      sql_result = sqlite3_bind_text( insert_stmt,
                                      procid_index,
                                      buffer,
                                      cap_size_t_to_int( buffer_size ),
                                      SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$procid" );
      goto fail_bind;
    }
  }

  if( msgid_index != 0 ) {
    if( entry->msgid_length == 1 && entry->msgid[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, msgid_index );
    } else {
      length = cap_size_t_to_int( entry->msgid_length );
      sql_result = sqlite3_bind_text( insert_stmt,
                                      msgid_index,
                                      entry->msgid,
                                      length,
                                      SQLITE_STATIC );
    }
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$msgid" );
      goto fail_bind;
    }
  }

  if( structured_data_index != 0 ) {
    strbuilder_reset( builder );
    strbuilder_result = strbuilder_append_structured_data( builder, entry );
    if( !strbuilder_result ) {
      goto fail;
    }
    buffer = strbuilder_get_buffer( builder, &buffer_size );
    if( buffer_size == 1 && buffer[0] == '-' ) {
      sql_result = sqlite3_bind_null( insert_stmt, structured_data_index );
    } else {
      // transient since we reuse and destroy this strbuilder before the
      // statement is executed
      sql_result = sqlite3_bind_text( insert_stmt,
                                      structured_data_index,
                                      buffer,
                                      cap_size_t_to_int( buffer_size ),
                                      SQLITE_TRANSIENT );
    }
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$structured_data" );
      goto fail_bind;
    }
  }

  if( message_index != 0 ) {
    if( entry->message ) {
      length = cap_size_t_to_int( entry->message_length );
      sql_result = sqlite3_bind_text( insert_stmt,
                                      message_index,
                                      entry->message,
                                      length,
                                      SQLITE_STATIC );
    } else {
      sql_result = sqlite3_bind_null( insert_stmt, message_index );
    }
    if( sql_result != SQLITE_OK ) {
      msg = L10N_SQLITE3_BIND_FAILED_ERROR_MESSAGE( "$message" );
      goto fail_bind;
    }
  }

  unlock_entry( entry );
  strbuilder_destroy( builder );

  *count = 1;
  return &target->insert_stmts;

fail_bind:
  raise_sqlite3_failure( msg, sql_result );
fail:
  unlock_entry( entry );
  strbuilder_destroy( builder );
  return NULL;
}

/* private definitions */

void
destroy_sqlite3_target( const struct sqlite3_target *target ) {
  sqlite3_finalize( target->insert_stmts[0] );
  config_destroy_mutex( &target->db_mutex );
  free_mem( target );
}

struct sqlite3_target *
new_sqlite3_target( sqlite3 *db ) {
  struct sqlite3_target *target;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    return NULL;
  }

  target->db = db;
  target->insert_sql = STUMPLESS_DEFAULT_SQLITE3_INSERT_SQL;
  target->prepare_func = stumpless_sqlite3_prepare;
  target->prepare_data = target;
  target->insert_stmts[0] = NULL;
  config_init_mutex( &target->db_mutex );

  return target;
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
  size_t try_count = 0;
  bool busy;

  db_target = target->id;

  config_lock_mutex( &db_target->db_mutex );

  statements = db_target->prepare_func( entry,
                                        db_target->prepare_data,
                                        &stmt_count );
  if( !statements ) {
    result = -1;
    if( db_target->prepare_func != &stumpless_sqlite3_prepare ) {
      raise_error( STUMPLESS_SQLITE3_CALLBACK_FAILURE,
                   L10N_SQLITE3_CUSTOM_PREPARE_FAILED_ERROR_MESSAGE,
                   0,
                   NULL );
    }
    goto cleanup_and_finish;
  }

  for( i = 0; i < stmt_count; i++ ) {
    do {
      try_count++;
      sql_result = sqlite3_step( statements[i] );

      busy = sql_result == SQLITE_BUSY;
      if( busy && try_count >= STUMPLESS_SQLITE3_RETRY_MAX ) {
        raise_sqlite3_busy();
        goto cleanup_and_finish;
      }
    } while( busy );

    if( sql_result != SQLITE_DONE ) {
      result = -1;
      raise_sqlite3_failure( L10N_SQLITE3_STEP_FAILED_ERROR_MESSAGE,
                             sql_result );
      goto cleanup_and_finish;
    }
  }

cleanup_and_finish:
  config_unlock_mutex( &db_target->db_mutex );
  return result;
}
