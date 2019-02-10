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
#include <stdio.h>
#include <stumpless.h>

int
main( int argc, char **argv ) {
  const char *log_server = "192.168.1.9"; // change this if you want to test
                                          // with your own server
  struct stumpless_target *udp4_target;
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
                                     "this is an example message, but it is"
                                     " pretty long. It'll be truncated if the"
                                     " maximum message size is set too low." );
  if( !basic_entry ) {
    printf( "could not create a basic entry" );
    return EXIT_FAILURE;
  }

  element = stumpless_new_element( "basic-element" );
  result = stumpless_add_element( basic_entry, element );
  if( !result ) {
    printf( "could not create and add an element to the entry" );
    return EXIT_FAILURE;
  }


  param = stumpless_new_param( "basic-param-name", "basic-param-value" );
  element_result = stumpless_add_param( element, param );
  if( !element_result ) {
    printf( "could not create and add a param to he element" );
    return EXIT_FAILURE;
  }


  // opening the target is straightforward
  udp4_target = stumpless_open_udp4_target( "udp4-example",
                                            log_server,
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
  if( !udp4_target ) {
    printf( "couldn't open up the udp4 target" );
    return EXIT_FAILURE;
  }


  // sending the entry is just like normal:
  log_result = stumpless_add_entry( udp4_target, basic_entry );
  if( log_result < 0 ) {
    printf( "could not log an entry" );
    return EXIT_FAILURE;
  }


  // closing the target is done as usual
  stumpless_close_network_target( udp4_target );


  // destroying all the other resources before finishing up:
  stumpless_destroy_entry( basic_entry );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
