// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2021 Joel E. Anderson
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

#include <stddef.h>
#include <stdlib.h>
#include <stumpless.h>

int
main( int argc, char **argv ) {
  const char *socket = "/dev/log";
  struct stumpless_entry *entry;
  struct stumpless_element *element;
  struct stumpless_entry *entry_result;
  struct stumpless_param *param;
  struct stumpless_element *element_result;
  struct stumpless_target *socket_target;
  struct stumpless_target *manual_target;
  int log_result;


  // building the entry is done as usual
  entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                               STUMPLESS_SEVERITY_INFO,
                               "example-app-name",
                               "example-msgid",
                               "This is an example message." );
  if( !entry ) {
    stumpless_perror( "could not create a basic entry" );
    return EXIT_FAILURE;
  }

  element = stumpless_new_element( "basic-element" );
  entry_result = stumpless_add_element( entry, element );
  if( !entry_result ) {
    stumpless_perror( "could not create and add an element to the entry" );
    return EXIT_FAILURE;
  }


  param = stumpless_new_param( "basic-param-name", "basic-param-value" );
  element_result = stumpless_add_param( element, param );
  if( !element_result ) {
    stumpless_perror( "could not create and add a param to the element" );
    return EXIT_FAILURE;
  }


  // opening the target is straightforward
  socket_target = stumpless_open_socket_target( socket,
                                                // making this argument NULL
                                                // means that a randomized local
                                                // socket will be created
                                                NULL );
  if( !socket_target ) {
    stumpless_perror( "couldn't create a new socket target" );
    return EXIT_FAILURE;
  }


  // if you want to specify the local socket used to connect to the target
  // socket, then you can specify it in the local_socket parameter
  manual_target = stumpless_open_socket_target( socket, "logfromthis" );
  if( !manual_target ) {
    stumpless_perror( "couldn't create a new socket target with a manual local"
                      " socket" );
    return EXIT_FAILURE;
  }


  // sending the entry is just like normal
  log_result = stumpless_add_entry( socket_target, entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log an entry to a simple target, maybe"
                      " /dev/log doesn't exist" );
  }

  log_result = stumpless_add_entry( manual_target, entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log an entry to a manual local socket, maybe"
                      " /dev/log doesn't exist" );
  }


  // closing the targets is done as usual
  stumpless_close_socket_target( socket_target );
  stumpless_close_socket_target( manual_target );


  // destroying all the other resources before finishing up:
  stumpless_destroy_entry_and_contents( entry );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
