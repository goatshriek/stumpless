// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2019 Joel E. Anderson
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
#include <stdio.h>
#include <stumpless.h>

int
main( int argc, char **argv ) {
  FILE *logfile;
  struct stumpless_target *stream_target;
  struct stumpless_entry *basic_entry;
  struct stumpless_element *element;
  struct stumpless_element *element_result;
  struct stumpless_param *param;
  struct stumpless_entry *result;
  int log_result;


  // building the entry is done as usual
  basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "stumpless-unit-test",
                                     "basic-entry",
                                     "basic test message" );
  if( !basic_entry ) {
    stumpless_perror( "could not create a basic entry" );
    return EXIT_FAILURE;
  }

  element = stumpless_new_element( "basic-element" );
  result = stumpless_add_element( basic_entry, element );
  if( !result ) {
    stumpless_perror( "could not create and add an element to the entry" );
    return EXIT_FAILURE;
  }


  param = stumpless_new_param( "basic-param-name", "basic-param-value" );
  element_result = stumpless_add_param( element, param );
  if( !element_result ) {
    stumpless_perror( "could not create and add a param to he element" );
    return EXIT_FAILURE;
  }


  // if you want to log to a file, then the log file must be opened first
  logfile = tmpfile();
  if( !logfile ) {
    stumpless_perror( "could not open a log file" );
    return EXIT_FAILURE;
  }


  // opening the stream target with an open stream is straightforward:
  stream_target = stumpless_open_stream_target( "stream-example", logfile );


  // logging an entry is just like with any target
  log_result = stumpless_add_entry( stream_target, basic_entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log an entry" );
    return EXIT_FAILURE;
  }


  // closing the target is done as usual
  stumpless_close_stream_target( stream_target );


  // after closing the target, you need to close the stream
  fclose( logfile );


  // destroying all remaining resources
  stumpless_destroy_entry_and_contents( basic_entry );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
