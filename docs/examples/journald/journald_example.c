// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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
main( void ) {
  struct stumpless_target *my_journal;
  struct stumpless_entry *entry;

  // creating a target to send messages to the local journald service
  my_journal = stumpless_open_journald_target( "daily-journal" );

  // this is optional, but makes our messages easier to find later
  stumpless_set_target_default_app_name( my_journal, "daily-journal" );

  stumpless_add_message( my_journal, "rode my bike with no handlebars" );
  stumpless_add_message( my_journal, "curled up with a book to read" );
  stumpless_add_message( my_journal, "designed an engine with 64 mpg" );

  // creating an entry with structured data
  entry = stumpless_new_entry( STUMPLESS_FACILITY_DAEMON,
                               STUMPLESS_SEVERITY_INFO,
                               "daily-journal",
                               "detailed-status",
                               "alive and on top" );
  stumpless_add_new_param_to_entry( entry, "my", "reach", "global" );
  stumpless_add_new_param_to_entry( entry, "my", "tower", "secure" );
  stumpless_add_new_param_to_entry( entry, "my", "cause", "noble" );
  stumpless_add_new_param_to_entry( entry, "my", "power", "pure" );

  // send our custom entry to the local journald service
  stumpless_add_entry( my_journal, entry );

  // some final cleanup before we finish
  stumpless_destroy_entry_and_contents( entry );
  stumpless_close_journald_target( my_journal );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
