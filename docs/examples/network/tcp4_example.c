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
  const char *port = "5514"; // change this if your server is listening on a
                             // port other than 5514
  struct stumpless_target *tcp4_target;
  struct stumpless_target *target_result;
  struct stumpless_entry *basic_entry;
  struct stumpless_element *element;
  struct stumpless_element *element_result;
  struct stumpless_param *param;
  struct stumpless_entry *result;
  int log_result;
  

  // building the entry is done as usual
  basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "example-app-name",
                                     "example-msgid",
                                     "This is an example message." );
  if( !basic_entry ) {
    printf( "could not create a basic entry\n" );
    return EXIT_FAILURE;
  }

  element = stumpless_new_element( "basic-element" );
  result = stumpless_add_element( basic_entry, element );
  if( !result ) {
    printf( "could not create and add an element to the entry\n" );
    return EXIT_FAILURE;
  }


  param = stumpless_new_param( "basic-param-name", "basic-param-value" );
  element_result = stumpless_add_param( element, param );
  if( !element_result ) {
    printf( "could not create and add a param to the element\n" );
    return EXIT_FAILURE;
  }


  // to use the builder style, first we create a new target
  tcp4_target = stumpless_new_tcp4_target( "tcp4-example" );
  if( !tcp4_target ) {
    printf( "couldn't create a new tcp4 target\n" );
    return EXIT_FAILURE;
  }


  // next we set the destination
  target_result = stumpless_set_destination( tcp4_target, log_server );
  if( !target_result ) {
    printf( "couldn't set the destination for the target\n" );
    return EXIT_FAILURE;
  }


  // and the transport port
  target_result = stumpless_set_transport_port( tcp4_target, port );
  if( !target_result ) {
    printf( "couldn't set the port for the target\n" );
    return EXIT_FAILURE;
  }


  // and finally the default facility
  target_result = stumpless_set_default_facility( tcp4_target,
                                                  STUMPLESS_FACILITY_LOCAL0 );
  if( !target_result ) {
    printf( "couldn't set the default facility of the target\n" );
    return EXIT_FAILURE;
  }


  // after we've set all of the options, we open the target
  // this won't work if the server isn't listening and responding
  target_result = stumpless_open_target( tcp4_target );
  if( !target_result ) {
    printf( "couldn't open the target. are you sure that the server is listening on the right port?\n" );
    return EXIT_FAILURE;
  }


  // sending the entry is just like normal
  log_result = stumpless_add_entry( tcp4_target, basic_entry );
  if( log_result < 0 ) {
    printf( "could not log an entry\n" );
    return EXIT_FAILURE;
  }


  // closing the target is done as usual
  stumpless_close_network_target( tcp4_target );


  // destroying all the other resources before finishing up:
  stumpless_destroy_entry( basic_entry );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
