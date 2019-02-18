// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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
  struct stumpless_entry *basic_entry;
  struct stumpless_entry *formatted_entry;


  // creating a basic entry is done in a single call
  basic_entry = stumpless_new_entry( // the facility of the entry
                                     STUMPLESS_FACILITY_USER,
                                     // the severity of the entry
                                     STUMPLESS_SEVERITY_INFO,
                                     // the application name
                                     "example-app-name",
                                     // the message identifier
                                     "example-msgid",
                                     // the message itself
                                     "my simple message" );


  // the message can include format specifiers if needed
  formatted_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
                                         "example-app-name",
                                         "example-msgid",
                                         "string %s and int %d",
                                         "substituted",
                                         334 );


  // if you only need to change the message, you can do so like this:
  stumpless_set_entry_message( formatted_entry,
                               "string %s and int %d",
                               "new substitution",
                               42 );


  // destroying all the resources before finishing up
  stumpless_destroy_entry( basic_entry );
  stumpless_destroy_entry( formatted_entry );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
