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
  const char *log_server = "example.com"; // change this if you want to test
                                          // with your own server
  struct stumpless_target *udp_target;
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
                                     "This is an example message, but it is"
                                     " pretty long. It'll be truncated if the"
                                     " maximum message size is set too low." );
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
    stumpless_perror( "could not create and add a param to the element" );
    return EXIT_FAILURE;
  }


  // opening the target is straightforward
  udp_target = stumpless_open_udp4_target( "udp4-example", log_server );


  // if you wanted to use ipv6 instead, you would do this:
  //udp_target = stumpless_open_udp6_target( "udp6-example", log_server );


  if( !udp_target ) {
    stumpless_perror( "couldn't open up the udp4 target" );
    return EXIT_FAILURE;
  }


  // sending the entry is just like normal
  log_result = stumpless_add_entry( udp_target, basic_entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log an entry" );
    return EXIT_FAILURE;
  }


  // UDP messages will be truncated if they go over the maximum message size.
  // This is set to 1472 by default, assuming an MTU of 1500 and a typical
  // overhead of 28 bytes. However, you can tweak this setting if you need to.
  // Messages that go over are simply truncated and sent.
  target_result = stumpless_set_udp_max_message_size( udp_target, 200 );
  if( !target_result ) {
    stumpless_perror( "could not set the max message size of the target" );
    return EXIT_FAILURE;
  }


  // this entry will be truncated to 200 bytes, meaning that the message will
  // be cut off partways through
  log_result = stumpless_add_entry( udp_target, basic_entry );
  if( log_result < 0 ) {
    stumpless_perror( "could not log an entry" );
    return EXIT_FAILURE;
  }


  // closing the target is done as usual
  stumpless_close_network_target( udp_target );


  // destroying all the other resources before finishing up:
  stumpless_destroy_entry_and_contents( basic_entry );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
