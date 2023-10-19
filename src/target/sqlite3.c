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
#include <stddef.h>
#include <stdio.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include <stumpless/target/sqlite3.h>
#include "private/config/locale/wrapper.h"
#include "private/config/wrapper/thread_safety.h"
#include "private/error.h"
#include "private/memory.h"
#include "private/target.h"
#include "private/target/sqlite3.h"
#include "private/validate.h"

static sqlite3_stmt *default_statement = NULL;
static const char *default_insert = "INSERT INTO logs (message) VALUES (?)";

// generic pointer here to prevent mandatory public API reliance on sqlite3.h
static
void *
prepare_statments( const struct stumpless_entry *entry, void *data, size_t *count ) {
  struct sqlite3_target *target;
  int bind_result;

  sqlite3_reset( default_statement );

  target = data;
  // TODO not thread safe!
  bind_result = sqlite3_bind_text( default_statement, 1, entry->message, entry->message_length, SQLITE_STATIC );
  printf( "bind result: %d\n", bind_result );

  *count = 1;
  return &default_statement;
}

static
void
after_steps( void *data ) {
  
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
  // we use v2 here to allow a close to not be blocked by pending transactions
  sqlite3_close_v2( target->db );
  config_destroy_mutex( &target->db_mutex );
  free_mem( target );
}

struct sqlite3_target *
new_sqlite3_target( const char *db_filename ) {
  struct sqlite3_target *target;
  int open_result;

  target = alloc_mem( sizeof( *target ) );
  if( !target ) {
    goto fail;
  }

  open_result = sqlite3_open( db_filename, &target->db );
  if( open_result != SQLITE_OK ) {
    // TODO raise appropriate error
    goto fail_db;
  }

  target->insert_statement = default_insert;
  sqlite3_prepare_v2( target->db, target->insert_statement, -1, &default_statement, NULL );

  config_init_mutex( &target->db_mutex );

  return target;

fail_db:
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

  db_target = target->id;

  config_lock_mutex( &db_target->db_mutex );

  statements = prepare_statments( entry, db_target, &stmt_count );
  for( i = 0; i < stmt_count; i++ ) {
    sqlite3_step( statements[i] );
  }

  printf( "wrote to a sqlite3 target with %zd statements!\n", stmt_count );
  config_unlock_mutex( &db_target->db_mutex );

  return -1;
}
