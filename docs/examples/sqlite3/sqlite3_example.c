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

#include <stdlib.h>
#include <stumpless.h>

int
main( int argc, char **argv ) {
  struct stumpless_target *db_target;

  // create the new database (or open the existing one)
  db_target = stumpless_open_sqlite3_target( "stumpless_example.sqlite3" );
  if( !db_target ) {
    stumpless_perror( "couldn't open sqlite3 target" );
    return EXIT_FAILURE;
  }

  // create the default logs table (if it doesn't exist)
  stumpless_create_default_sqlite3_table( db_target );
  if( stumpless_has_error() ) {
    // for simplicity, if this fails we simply print a warning and continue
    puts( "could not create default table, perhaps it already exists?\n" );
  }

  // send a simple message to our new logs table
  stumpless_add_message( db_target, "cards are on the table" );

  // after this, an initially empty database would look like this:
  // sqlite> SELECT * FROM logs;
  // log_id      prival      version     timestamp                    hostname    app_name    procid      msgid       structured_data  message
  // ----------  ----------  ----------  ---------------------------  ----------  ----------  ----------  ----------  ---------------  ----------------------
  // 1           14          1           2023-11-22T04:35:02.909888Z  Angus                   3090                                     cards are on the table

  // clean up on the way out
  stumpless_close_sqlite3_target( db_target );
  stumpless_free_all();

  return EXIT_SUCCESS;
}
