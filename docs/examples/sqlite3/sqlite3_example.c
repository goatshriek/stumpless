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
#include <stdlib.h>
#include <stumpless.h>

// an array of prepared statements to use in our custom prepare function
static sqlite3_stmt *card_stmts[2] = { NULL, NULL };

/**
 * A custom prepare function for a Stumpless SQLite3 target.
 *
 * Extracts structured data from the entry, and builds two insert statements
 * to put this data into custom tables.
 *
 * @param entry The entry to get the structured data from.
 *
 * @param data The SQLite3 database handle (sqlite3 *).
 *
 * @param count A pointer to an output variable where the number of valid
 * prepared statements will be written to. This will always be 2 unless an
 * error occurred.
 *
 * @return A pointer to an array of sqlite3_stmt pointers on success, or NULL
 * on failure.
 */
void *
card_played_prepare( const struct stumpless_entry *entry,
                     void *data,
                     size_t *count ) {
  sqlite3 *db = data;
  const char *card_insert_sql = "INSERT INTO played_cards ( suit, rank ) "
                                "VALUES ( $suite, $rank )";
  int sql_result;
  const char *player_insert_sql = "INSERT INTO taken_turns ( player_name ) "
                                  "VALUES ( $name )";
  const char *suit;
  const char *rank;
  const char *name;

  if( !card_stmts[0] ) {
    sql_result = sqlite3_prepare_v2( db,
                                     card_insert_sql,
                                     -1,
                                     &card_stmts[0],
                                     NULL );
    if( sql_result != SQLITE_OK ) {
      printf( "couldn't prepare the played_cards insert stmt: %s\n",
              sqlite3_errmsg( db ) );
      return NULL;
    }
  } else {
    sqlite3_reset( card_stmts[0] );
  }

  if( !card_stmts[1] ) {
    sql_result = sqlite3_prepare_v2( db,
                                     player_insert_sql,
                                     -1,
                                     &card_stmts[1],
                                     NULL );
    if( sql_result != SQLITE_OK ) {
      printf( "couldn't prepare the taken_turns insert stmt: %s\n",
              sqlite3_errmsg( db ) );
      return NULL;
    }
  } else {
    sqlite3_reset( card_stmts[1] );
  }

  suit = stumpless_get_entry_param_value_by_name( entry, "card", "suit" );
  rank = stumpless_get_entry_param_value_by_name( entry, "card", "rank" );
  name = stumpless_get_entry_param_value_by_name( entry, "player", "name" );

  sql_result = sqlite3_bind_text( card_stmts[0],
                                  1,
                                  suit,
                                  -1,
                                  SQLITE_TRANSIENT );
  if( sql_result != SQLITE_OK ) {
      printf( "couldn't bind the card suit: %s\n",
              sqlite3_errmsg( db ) );
      return NULL;
  }

  sql_result = sqlite3_bind_text( card_stmts[0],
                                  2,
                                  rank,
                                  -1,
                                  SQLITE_TRANSIENT );
  if( sql_result != SQLITE_OK ) {
      printf( "couldn't bind the card rank: %s\n",
              sqlite3_errmsg( db ) );
      return NULL;
  }

  sql_result = sqlite3_bind_text( card_stmts[1],
                                  1,
                                  name,
                                  -1,
                                  SQLITE_TRANSIENT );
  if( sql_result != SQLITE_OK ) {
      printf( "couldn't bind the player name: %s\n",
              sqlite3_errmsg( db ) );
      return NULL;
  }

  free( ( char * ) suit );
  free( ( char * ) rank );
  free( ( char * ) name );

  *count = 2;
  return &card_stmts;
}

int
main( int argc, char **argv ) {
  struct stumpless_target *db_target;
  int result = EXIT_SUCCESS;
  sqlite3 *db;
  const char *card_logs_create_sql = "CREATE TABLE card_logs ("
                                     "  log_id INTEGER PRIMARY KEY,"
                                     "  facility INTEGER NOT NULL,"
                                     "  severity INTEGER NOT NULL,"
                                     "  timestamp TEXT,"
                                     "  structured_data TEXT,"
                                     "  message TEXT )";
  sqlite3_stmt *card_logs_create_stmt = NULL ;
  int sql_result;
  const char *card_logs_insert = "INSERT INTO card_logs ( facility, severity,"
                                 "                        timestamp,"
                                 "                        structured_data,"
                                 "                        message )"
                                 "VALUES ( $facility, $severity, $timestamp,"
                                 "         $structured_data, $message )";
  struct stumpless_entry *entry = NULL;
  const char *played_cards_create_sql = "CREATE TABLE played_cards ("
                                        "  played_card_id INTEGER PRIMARY KEY,"
                                        "  suit TEXT,"
                                        "  rank TEXT"
                                        ")";
  sqlite3_stmt *played_cards_create_stmt = NULL;
  const char *taken_turns_create_sql = "CREATE TABLE taken_turns ("
                                       "  taken_turn_id INTEGER PRIMARY KEY,"
                                       "  player_name TEXT"
                                       ")";
  sqlite3_stmt *taken_turns_create_stmt = NULL;


  // create the new database (or open the existing one)
  db_target = stumpless_open_sqlite3_target( "stumpless_example.sqlite3" );
  if( !db_target ) {
    stumpless_perror( "couldn't open sqlite3 target" );
    result = EXIT_FAILURE;
    goto cleanup_and_finish;
  }

  // create the default logs table (if it doesn't exist)
  stumpless_create_default_sqlite3_table( db_target );
  if( stumpless_has_error() ) {
    // for simplicity, if this fails we simply print a warning and continue
    puts( "could not create default table, perhaps it already exists?" );
  }

  // send a simple message to our new logs table
  stumpless_add_message( db_target, "cards are on the table" );
  if( stumpless_has_error() ) {
    stumpless_perror( "couldn't send a message to a default SQLite target" );
    result = EXIT_FAILURE;
    goto cleanup_and_finish;
  }

  // after this, an initially empty database would look like this:
  // sqlite> SELECT * FROM logs;
  // log_id      prival      version     timestamp                    hostname    app_name    procid      msgid       structured_data  message
  // ----------  ----------  ----------  ---------------------------  ----------  ----------  ----------  ----------  ---------------  ----------------------
  // 1           14          1           2023-11-22T04:35:02.909888Z  Angus                   3090                                     cards are on the table

  // now, let's use our own insertion statement
  // we'll need to create a table
  db = stumpless_get_sqlite3_db( db_target );
  if( !db ) {
    stumpless_perror( "couldn't get the underlying database connection!" );
    result = EXIT_FAILURE;
    goto cleanup_and_finish;
  }

  sql_result = sqlite3_prepare_v2( db,
                                   card_logs_create_sql,
                                   -1,
                                   &card_logs_create_stmt,
                                   NULL );
  if( sql_result != SQLITE_OK ) {
    // for simplicity, if this fails we simply print a warning and continue
    puts( "could not create card_logs table, perhaps it already exists?" );
  } else {
    sql_result = sqlite3_step( card_logs_create_stmt );
    if( sql_result != SQLITE_DONE ) {
      printf( "couldn't create the card_logs table: %s\n",
              sqlite3_errmsg( db ) );
      result = EXIT_FAILURE;
      goto cleanup_and_finish;
    }
  }

  // set the target to use our custom insert SQL instead
  stumpless_set_sqlite3_insert_sql( db_target, card_logs_insert );
  if( stumpless_has_error() ) {
    stumpless_perror( "couldn't set the custom insert sql" );
    result = EXIT_FAILURE;
    goto cleanup_and_finish;
  }

  // create a new entry with some structured data
  // we ignore the error checking here for brevity
  entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                               STUMPLESS_SEVERITY_INFO,
                               "card-counter",
                               "card-played",
                               "a card was played" );

  stumpless_add_new_param_to_entry( entry, "card", "suit", "hearts" );
  stumpless_add_new_param_to_entry( entry, "card", "rank", "5" );
  stumpless_add_new_param_to_entry( entry, "player", "name", "bill" );

  // use our custom insert SQL to add to the card_logs table
  stumpless_add_entry( db_target, entry );

  // here's what the database looks like after this:
  // sqlite> SELECT * FROM card_logs;
  // log_id      facility    severity    timestamp                    structured_data                                    message
  // ----------  ----------  ----------  ---------------------------  -------------------------------------------------  -----------------
  // 1           8           6           2023-11-23T19:05:33.234523Z  [card suit="hearts" rank="5"][player name="bill"]  a card was played

  // finally, let's use a custom preparation function for more structure
  // first we create our new tables
  sql_result = sqlite3_prepare_v2( db,
                                   played_cards_create_sql,
                                   -1,
                                   &played_cards_create_stmt,
                                   NULL );
  if( sql_result != SQLITE_OK ) {
    // for simplicity, if this fails we simply print a warning and continue
    puts( "could not create played_cards table, perhaps it already exists?" );
  } else {
    sql_result = sqlite3_step( played_cards_create_stmt );
    if( sql_result != SQLITE_DONE ) {
      printf( "couldn't create the played_cards table: %s\n",
              sqlite3_errmsg( db ) );
      result = EXIT_FAILURE;
      goto cleanup_and_finish;
    }
  }
  
  sql_result = sqlite3_prepare_v2( db,
                                   taken_turns_create_sql,
                                   -1,
                                   &taken_turns_create_stmt,
                                   NULL );
  if( sql_result != SQLITE_OK ) {
    // for simplicity, if this fails we simply print a warning and continue
    puts( "could not create taken_turns table, perhaps it already exists?" );
  } else {
    sql_result = sqlite3_step( taken_turns_create_stmt );
    if( sql_result != SQLITE_DONE ) {
      printf( "couldn't create the taken_turns table: %s\n",
              sqlite3_errmsg( db ) );
      result = EXIT_FAILURE;
      goto cleanup_and_finish;
    }
  }

  // we only need the db, so we use this as our custom data pointer
  stumpless_set_sqlite3_prepare( db_target, &card_played_prepare, db );
  if( stumpless_has_error() ) {
    stumpless_perror( "couldn't set the custom prepare function" );
    result = EXIT_FAILURE;
    goto cleanup_and_finish;
  }

  // add the same entry again to see it in our new tables
  stumpless_add_entry( db_target, entry );

  // sqlite> SELECT * FROM played_cards;
  // played_card_id  suit        rank
  // --------------  ----------  ----------
  // 1               hearts      5
  // sqlite> SELECT * FROM taken_turns;
  // taken_turn_id  player_name
  // -------------  -----------
  // 1              bill

cleanup_and_finish:
  sqlite3_finalize( card_logs_create_stmt );
  sqlite3_finalize( played_cards_create_stmt );
  sqlite3_finalize( taken_turns_create_stmt );
  sqlite3_finalize( card_stmts[0] );
  sqlite3_finalize( card_stmts[1] );
  stumpless_destroy_entry_and_contents( entry );
  stumpless_close_sqlite3_target_and_db( db_target );
  stumpless_free_all();

  return result;
}
