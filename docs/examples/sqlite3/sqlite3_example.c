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

  db_target = stumpless_open_sqlite3_target( "stumpless_example.sqlite3" );
  if( !db_target ) {
    stumpless_perror( "couldn't open sqlite3 target" );
    return EXIT_FAILURE;
  }

  // TODO we're just ignoring errors if this fails, assuming it already existed
  stumpless_create_default_sqlite3_table( db_target );

  stumpless_add_message( db_target, "goes to the sqlite3 database" );
  stumpless_add_message( db_target, "this one too" );

  stumpless_close_sqlite3_target( db_target );

  return EXIT_SUCCESS;
}
