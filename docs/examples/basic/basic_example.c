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
  struct stumpless_target *file_target;
  struct stumpless_target *net_target;
  const char *username = "example-username";


  // opens a file target to example.log
  file_target = stumpless_open_file_target( "example.log",
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );


  // logs to the last opened target
  stumpless( "The hello world of stumpless." );


  // logs a more complex message to the last target
  stumpless( "Login failed for username %s", username );


  // opens a network target to example.com using UDP over IPv4
  net_target = stumpless_open_udp4_target( "network-target",
                                           "example.com",
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );


  // sends a message to the network target
  stumpless_add_message( net_target, "Login failed for username %s", username );


  // destroying all the resources before finishing up
  stumpless_close_file_target( file_target );
  stumpless_close_network_target( net_target );
  stumpless_free_all(  );


  return EXIT_SUCCESS;
}
