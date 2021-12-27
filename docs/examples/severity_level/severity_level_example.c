// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2021 Joel E. Anderson
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
  struct stumpless_target *target;

  // setting up a target to the console for quick and easy results
  target = stumpless_open_stdout_target( "severity level example" );


  // this message will be logged with a severity level of INFO because there is
  // no severity provided
  stump_i( "this message will have INFO severity" );


  // this message will have a severity level of EMERG because it takes the
  // severity as one of its arguments
  stumplog_i( STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_EMERG,
              "THE SYSTEM IS DOWN!!!" );


  // logging a message at each severity level
  stump_em( "emergency!" );
  stump_a( "alert!" );
  stump_c( "critical!" );
  stump_er( "error!" );
  stump_w( "warning!" );
  stump_n( "notice" );
  stump_i( "informational" );
  stump_d( "debug" );
  stump_t( "trace" );


  // the output of the above statements depends on what symbols are defined:
  // without any extra symbols defined, this will result in these messages:
  // <8>1 2020-07-14T20:01:30.930277Z Angus - 6505 - - emergency!
  // <9>1 2020-07-14T20:01:30.931151Z Angus - 6505 - - alert!
  // <10>1 2020-07-14T20:01:30.932863Z Angus - 6505 - - critical!
  // <11>1 2020-07-14T20:01:30.933504Z Angus - 6505 - - error!
  // <12>1 2020-07-14T20:01:30.935897Z Angus - 6505 - - warning!
  // <13>1 2020-07-14T20:01:30.936486Z Angus - 6505 - - notice
  // <14>1 2020-07-14T20:01:30.937814Z Angus - 6505 - - informational
  // <15>1 2020-07-14T20:01:30.938356Z Angus - 6505 - - debug
  // <15>1 2020-07-14T20:01:30.938627Z Angus - 6505 - [trace file="stumpless/docs/examples/severity_level/severity_level_example.c" line="50" function="main"] trace

  // if you define the following symbols:
  //    STUMPLESS_DISABLE_WARNING_LEVEL
  //    STUMPLESS_DISABLE_CRIT_LEVEL
  //    STUMPLESS_DISABLE_EMERG_LEVEL
  // this will result in these messages (note the missing ones):
  // <9>1 2020-07-14T20:07:41.088757Z Angus - 6680 - - alert!
  // <11>1 2020-07-14T20:07:41.089744Z Angus - 6680 - - error!
  // <13>1 2020-07-14T20:07:41.090743Z Angus - 6680 - - notice
  // <14>1 2020-07-14T20:07:41.093912Z Angus - 6680 - - informational
  // <15>1 2020-07-14T20:07:41.094765Z Angus - 6680 - - debug
  // <15>1 2020-07-14T20:07:41.094987Z Angus - 6505 - [trace file="stumpless/docs/examples/severity_level/severity_level_example.c" line="50" function="main"] trace

  // if you define the STUMPLESS_ENABLE_UPTO_INFO symbol (or the equivalent
  // STUMPLESS_DISABLE_DOWNTO_DEBUG symbol), this will result in these messages:
  // <8>1 2020-07-14T20:08:57.060259Z Angus - 6686 - - emergency!
  // <9>1 2020-07-14T20:08:57.061415Z Angus - 6686 - - alert!
  // <10>1 2020-07-14T20:08:57.062374Z Angus - 6686 - - critical!
  // <11>1 2020-07-14T20:08:57.063497Z Angus - 6686 - - error!
  // <12>1 2020-07-14T20:08:57.064536Z Angus - 6686 - - warning!
  // <13>1 2020-07-14T20:08:57.065685Z Angus - 6686 - - notice
  // <14>1 2020-07-14T20:08:57.066834Z Angus - 6686 - - informational

  // if you define STUMPLESS_DISABLE_ALL_LEVELS, then there will be no messages!


  // closing our target
  stumpless_close_target( target );


  // final call required to completely free all resources (caches, etc.)
  stumpless_free_all(  );


  return EXIT_SUCCESS;
}
