// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
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
#include <windows.h>
#include "docs/examples/wel/example_events.h"

int
main( int argc, char **argv ) {
  struct stumpless_entry *basic_entry;
  DWORD register_result;
  struct stumpless_target *wel_target;
  struct stumpless_entry *entry_with_params;
  struct stumpless_entry *result;
  struct stumpless_param *child_name;
  struct stumpless_param *tree_type;
  int log_result;


  // creating a basic entry
  basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "tree-identifier-app",
                                     "tree-identified-by-child",
                                     "a child found a tree!" );
  if( !basic_entry ) {
    stumpless_perror( "could not create the basic entry" );
    return EXIT_FAILURE;
  }


  // attempting to register the default event source
  register_result = stumpless_add_default_wel_event_source(  );
  if( register_result != ERROR_SUCCESS ) {
    stumpless_perror( "WARNING - couldn't register the default source" );
    // we wont fail our example if this happens, just warn the user
  }


  // opening an explicit Windows Event Log target to the default source
  wel_target = stumpless_open_local_wel_target( "Stumpless" );
  if( !wel_target ) {
    stumpless_perror( "could not open the default Windows Event Log" );
    return EXIT_FAILURE;
  }


  // sending an entry with default values to the default target
  // if the registration function succeeded, then this entry will be visible
  // in the Event Viewer under the Stumpless application
  log_result = stumpless_add_entry( wel_target, basic_entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log a default entry" );
    return EXIT_FAILURE;
  }


  // clean up by closing the target and unregistering the default source
  stumpless_close_wel_target( wel_target );
  register_result = stumpless_remove_default_wel_event_source(  );
  if( register_result != ERROR_SUCCESS ) {
    stumpless_perror( "WARNING - couldn't unregister the default source" );
    // again, we wont fail in this scenario either
  }


  // opening a Windows Event Log target in the "KidsAndTrees" log
  wel_target = stumpless_open_local_wel_target( "KidsAndTrees" );
  if( !wel_target ) {
    stumpless_perror( "could not open the local Windows Event Log" );
    return EXIT_FAILURE;
  }


  // setting the three wel-specific fields on the entry
  result = stumpless_set_wel_category( basic_entry, CATEGORY_TREE );
  if( !result ) {
    stumpless_perror( "could not set the basic entry category" );
    return EXIT_FAILURE;
  }

  result = stumpless_set_wel_event_id( basic_entry,
                                       MSG_TREE_IDENTIFIED_BY_CHILD );
  if( !result ) {
    stumpless_perror( "could not set the basic entry event id" );
    return EXIT_FAILURE;
  }

  result = stumpless_set_wel_type( basic_entry, EVENTLOG_SUCCESS );
  if( !result ) {
    stumpless_perror( "could not set the basic entry type" );
    return EXIT_FAILURE;
  }


  // logging a basic entry
  log_result = stumpless_add_entry( wel_target, basic_entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log a basic entry" );
    return EXIT_FAILURE;
  }


  // setting the insertion strings on the entry
  result = stumpless_set_wel_insertion_string( basic_entry, 0, "cynthia" );
  if( !result ) {
    stumpless_perror( "could not set the first insertion string of an entry" );
    return EXIT_FAILURE;
  }

  result = stumpless_set_wel_insertion_string( basic_entry, 1, "oak" );
  if( !result ) {
    stumpless_perror( "could not set the second insertion string of an entry" );
    return EXIT_FAILURE;
  }

  // the previous two strings could have been set with the following call:
  // stumpless_set_wel_insertion_strings( basic_entry, 2, "cynthia", "oak" );


  // logging the entry with insertion strings set
  // note that this is the same code as before
  log_result = stumpless_add_entry( wel_target, basic_entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log a basic entry" );
    return EXIT_FAILURE;
  }


  // creating another entry
  entry_with_params = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                           STUMPLESS_SEVERITY_INFO,
                                           "tree-identifier-app",
                                           "tree-identified-by-child",
                                           "a child found a tree!" );
  if( !entry_with_params ) {
    stumpless_perror( "could not create the second entry" );
    return EXIT_FAILURE;
  }


  // setting the three wel-specific fields on the entry
  result = stumpless_set_wel_category( entry_with_params, CATEGORY_TREE );
  if( !result ) {
    stumpless_perror( "could not set the second entry category" );
    return EXIT_FAILURE;
  }

  result = stumpless_set_wel_event_id( entry_with_params,
                                       MSG_TREE_IDENTIFIED_BY_CHILD );
  if( !result ) {
    stumpless_perror( "could not set the second entry event id" );
    return EXIT_FAILURE;
  }

  result = stumpless_set_wel_type( entry_with_params, EVENTLOG_SUCCESS );
  if( !result ) {
    stumpless_perror( "could not set the second entry type" );
    return EXIT_FAILURE;
  }


  // setting the insertion params on the entry
  child_name = stumpless_new_param( "child-name", "cynthia" );
  if( !child_name ) {
    stumpless_perror( "could not create the child name param" );
    return EXIT_FAILURE;
  }

  result = stumpless_set_wel_insertion_param( basic_entry, 0, child_name );
  if( !result ) {
    stumpless_perror( "could not set the first insertion string of an entry" );
    return EXIT_FAILURE;
  }

  tree_type = stumpless_new_param( "tree-type", "oak" );
  if( !tree_type ) {
    stumpless_perror( "could not create the child name param" );
    return EXIT_FAILURE;
  }

  result = stumpless_set_wel_insertion_param( basic_entry, 1, tree_type );
  if( !result ) {
    stumpless_perror( "could not set the second insertion string of an entry" );
    return EXIT_FAILURE;
  }


  // logging the entry with insertion params set
  // note that this is the same code as before once again
  log_result = stumpless_add_entry( wel_target, entry_with_params );
  if( log_result < 0 ) {
    stumpless_perror( "could not log a basic entry" );
    return EXIT_FAILURE;
  }


  // closing the target
  stumpless_close_wel_target( wel_target );


  // destroying all remaining resources
  stumpless_destroy_entry_and_contents( basic_entry );
  stumpless_destroy_entry_and_contents( entry_with_params );
  stumpless_destroy_param( child_name );
  stumpless_destroy_param( tree_type );

  return EXIT_SUCCESS;
}
