// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2022 Joel E. Anderson
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

#include <stdbool.h>
#include <stdlib.h>
#include <stumpless.h>

// this is our custom filter that rejects entries with an element named 'ignore'
// in them, as well as honoring the default target mask behavior
bool
ignore_element_filter( const struct stumpless_target *target,
                       const struct stumpless_entry *entry ) {
  return !stumpless_get_element_by_name( entry, "ignore" )
           && stumpless_mask_filter( target, entry );
}

int
main( int argc, char **argv ) {
  struct stumpless_target *target;
  int new_mask;
  struct stumpless_entry *entry;


  // opens a target to stdout
  target = stumpless_open_stdout_target( "filter-example-target" );


  // by default, all of these will be logged to the target
  stump_em( "emergency!" );
  stump_a( "alert!" );
  stump_c( "critical!" );
  stump_er( "error!" );
  stump_w( "warning!" );
  stump_n( "notice" );
  stump_i( "informational" );
  stump_d( "debug" );
  stump_d( "trace" );

  // the resulting output looks something like this:
  // <8>1 2022-01-26T02:00:54.250910Z Angus - - - - emergency!
  // <9>1 2022-01-26T02:00:54.251708Z Angus - - - - alert!
  // <10>1 2022-01-26T02:00:54.251989Z Angus - - - - critical!
  // <11>1 2022-01-26T02:00:54.252183Z Angus - - - - error!
  // <12>1 2022-01-26T02:00:54.252845Z Angus - - - - warning!
  // <13>1 2022-01-26T02:00:54.253226Z Angus - - - - notice
  // <14>1 2022-01-26T02:00:54.253634Z Angus - - - - informational
  // <15>1 2022-01-26T02:00:54.254015Z Angus - - - - debug
  // <15>1 2022-01-26T02:00:54.254347Z Angus - - - - trace



  // if we want to change the mask to be more complex, we can create our new
  // mask and assign it to the target (or use the stumplog_set_mask shortcut
  // if it happens to be the current target)
  new_mask  = STUMPLESS_SEVERITY_MASK( STUMPLESS_SEVERITY_DEBUG )
                | STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR );
  stumplog_set_mask( new_mask );


  //. now, we'll only see the first four of these and the debug one
  stump_em( "emergency!" );
  stump_a( "alert!" );
  stump_c( "critical!" );
  stump_er( "error!" );
  stump_w( "warning!" );
  stump_n( "notice" );
  stump_i( "informational" );
  stump_d( "debug" );
  stump_d( "trace" );

  // the mask filtered output:
  // <8>1 2022-01-26T02:00:54.254749Z Angus - - - - emergency!
  // <9>1 2022-01-26T02:00:54.255044Z Angus - - - - alert!
  // <10>1 2022-01-26T02:00:54.255394Z Angus - - - - critical!
  // <11>1 2022-01-26T02:00:54.255691Z Angus - - - - error!
  // <15>1 2022-01-26T02:00:54.256015Z Angus - - - - debug
  // <15>1 2022-01-26T02:00:54.256365Z Angus - - - - trace


  // if we want to customize the filtering even more, then we can set the filter
  // to our own custom function
  stumpless_set_target_filter( target, ignore_element_filter );


  // let's create an entry to send to our target
  entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                               STUMPLESS_SEVERITY_ERR,
                               "filter-example",
                               "annoying-msg",
                               "hey! listen!" );


  // this message will be allowed through
  stumpless_add_entry( target, entry );

  // message logged to the target:
  // <11>1 2022-01-26T02:00:54.256697Z Angus filter-example - annoying-msg - hey! listen!


  // now, let's add the special element and try again
  stumpless_add_new_element( entry, "ignore" );


  // this time, it'll be filtered out!
  stumpless_add_entry( target, entry );

  // there's no output to be seen!


  // destroying all the resources before finishing up
  stumpless_destroy_entry_and_contents( entry );
  stumpless_close_stream_target( target );
  stumpless_free_all(  );


  return EXIT_SUCCESS;
}
