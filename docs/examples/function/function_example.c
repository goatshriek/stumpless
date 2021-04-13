// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stumpless.h>
#include <time.h>

int red_count = 0;
int green_count = 0;
int blue_count = 0;

// this function provides our color-counting logic
int
count_balls( const struct stumpless_target *target,
             const struct stumpless_entry *entry ) {
  const char *color;
  int result;

  color = stumpless_get_entry_param_value_by_name( entry, "ball", "color" );
  if( strcmp( color, "red" ) == 0 ) {
    result = ++red_count;
  } else if( strcmp( color, "green" ) == 0 ) {
    result = ++green_count;
  } else if( strcmp( color, "blue" ) == 0 ) {
    result = ++blue_count;
  } else {
    result = -1;
  }

  free( ( void * ) color );
  return result;
}

int
main( void ) {
  struct stumpless_target *target;
  struct stumpless_entry *entry;
  int i;
  const char *ball_colors[] = {"red", "green" , "blue"};
  const char *color;

  // creating a target using our custom function
  target = stumpless_open_function_target( "ball-counter", count_balls );

  // creating an entry for ball processing events
  entry = stumpless_new_entry( STUMPLESS_FACILITY_DAEMON,
                               STUMPLESS_SEVERITY_INFO,
                               "ball-processing-machine",
                               "processed-ball",
                               "a ball has finished processing" );

  // processing a bunch of of fake balls
  srand( time( NULL ) );
  for( i = 0; i < 1024; i++ ) {
    color = ball_colors[rand(  ) % 3];
    stumpless_set_entry_param_value_by_name( entry, "ball", "color", color );

    // this line calls our custom function with the same target and entry
    stumpless_add_entry( target, entry );
  }

  // printing out the final counts
  printf( "red ball count: %d\n", red_count );
  printf( "green ball count: %d\n", green_count );
  printf( "blue ball count: %d\n", blue_count );

  // some final cleanup before we finish
  stumpless_destroy_entry_and_contents( entry );
  stumpless_close_function_target( target );
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
