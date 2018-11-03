// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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
#include "docs/examples/wel/example_events.h"

int
main( int argc, char **argv ) {
  struct stumpless_target *wel_target;
  struct stumpless_entry *entry;
  struct stumpless_param *child_name;
  struct stumpless_param *tree_type;

  // opening a Windows Event Log target in the "KidsAndTrees" log
  wel_target = stumpless_open_local_wel_target( "KidsAndTrees", 0, 0 );
  if( !wel_target ) {
    printf( "could not open the local Windows Event Log" );
    return EXIT_FAILURE;
  }

  // creating a basic entry

  // closing the target
  stumpless_close_wel_target( wel_target );

  return EXIT_SUCCESS;
}
