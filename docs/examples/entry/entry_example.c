// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2020 Joel E. Anderson
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

#include <stdio.h>
#include <stdlib.h>
#include <stumpless.h>

int
main( int argc, char **argv ) {
  struct stumpless_entry *basic_entry;
  struct stumpless_entry *formatted_entry;
  struct stumpless_entry *failed_login_entry;
  struct stumpless_target *stdout_target;
  struct stumpless_param *user;
  struct stumpless_param *token;
  struct stumpless_element *context;
  struct stumpless_entry *refresh_entry;
  struct stumpless_entry *logout_entry;


  // creating a logging target for standard out to see the result of logging
  // each of the example entries
  stdout_target = stumpless_open_stdout_target( "entry-example" );


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
  printf( "a basic entry:\n" );
  stumpless_add_entry( stdout_target, basic_entry );
  printf( "\n" );


  // the message can include format specifiers if needed
  formatted_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
                                         "example-app-name",
                                         "example-msgid",
                                         "string %s and int %d",
                                         "substituted",
                                         334 );
  printf( "an entry with format specifiers:\n" );
  stumpless_add_entry( stdout_target, formatted_entry );
  printf( "\n" );


  // if you only need to change the message, you can do so like this:
  stumpless_set_entry_message( formatted_entry,
                               "string %s and int %d",
                               "new substitution",
                               42 );
  printf( "the same entry after the message was reset:\n" );
  stumpless_add_entry( stdout_target, formatted_entry );
  printf( "\n" );


  // creating a failed login attempt event with structured data
  failed_login_entry = stumpless_new_entry( STUMPLESS_FACILITY_AUTH,
                                            STUMPLESS_SEVERITY_NOTICE,
                                            "company-web-portal",
                                            "failed-login-attempt",
                                            "user failed to authenticate" );


  // logging code to update the entry and log it for each event
  // entries and params are automatically created if they are not present
  stumpless_set_entry_param_value_by_name( failed_login_entry,
                                           "user", "name", "chester" );
  stumpless_set_entry_param_value_by_name( failed_login_entry,
                                           "user", "id", "5763332" );
  stumpless_set_entry_param_value_by_name( failed_login_entry,
                                           "user", "locked", "true" );
  stumpless_set_entry_param_value_by_name( failed_login_entry,
                                           "try", "number", "3" );
  printf( "an entry with structured data:\n" );
  stumpless_add_entry( stdout_target, failed_login_entry );


  // closing the target once we are finished
  stumpless_close_target( stdout_target );


  // destroying all the resources before finishing up
  stumpless_destroy_entry_and_contents( basic_entry );
  stumpless_destroy_entry_and_contents( formatted_entry );
  stumpless_destroy_entry_and_contents( failed_login_entry );


  // creating two entries with shared elements and params
  user = stumpless_new_param( "username", "thomas" );
  token = stumpless_new_param( "token", "0xdeadbeef" );
  context = stumpless_new_element( "context" );
  stumpless_add_param( context, user );
  stumpless_add_param( context, token );
  refresh_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_NOTICE,
                                       "company-web-portal",
                                       "refresh-request",
                                       "user requested a refresh" );
  stumpless_add_element( refresh_entry, context );

  logout_entry = stumpless_new_entry( STUMPLESS_FACILITY_AUTH,
                                      STUMPLESS_SEVERITY_NOTICE,
                                      "company-web-portal",
                                      "logout",
                                      "user logged out" );
  stumpless_add_element( logout_entry, context );


  // destroying the shared resources individually
  stumpless_destroy_entry_only( logout_entry );
  stumpless_destroy_entry_only( refresh_entry );
  stumpless_destroy_element_and_contents( context );


  // final call required to completely free all resources (caches, etc.)
  stumpless_free_all(  );


  return EXIT_SUCCESS;
}
