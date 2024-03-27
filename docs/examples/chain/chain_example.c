// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2024 Joel E. Anderson
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

#include <stdio.h>
#include <stdlib.h>
#include <stumpless.h>


int
main( void ){
  struct stumpless_target *simple_chain;
  struct stumpless_target *file_target;
  struct stumpless_target *stdout_target;
  int mask;
  char error_buffer[4096];
  struct stumpless_target *stderr_target;
  struct stumpless_target *error_buffer_target;
  struct stumpless_target *error_chain;
  struct stumpless_target *main_chain;
  char message_buffer[4096];
  size_t read_size;

  // a file target to hold all of our logs in one file
  file_target = stumpless_open_file_target( "chain-example.log" );

  // set up a target to log to stdout
  stdout_target = stumpless_open_stdout_target( "chain-example-stdout" );

  // only send "normal" messages to stdout though: from info to warning
  mask = STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_INFO )
           & ~STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR );
  stumpless_set_target_mask( stdout_target, mask );

  // create a new chain
  simple_chain = stumpless_new_chain( "example-simple-chain" );

  // add our targets to the chain
  stumpless_add_target_to_chain( simple_chain, stdout_target );
  stumpless_add_target_to_chain( simple_chain, file_target );

  // send a test message to both stdout and chain-example.log
  stumpless_add_message( simple_chain, "simple chain message" );

  // set up a target to handle errors
  stderr_target = stumpless_open_stderr_target( "chain-example-stderr" );
  error_buffer_target = stumpless_open_buffer_target( "chain-example-buffer",
                                                      error_buffer,
                                                      sizeof( error_buffer ) );
  error_chain = stumpless_new_chain( "example-error-chain" );
  stumpless_add_target_to_chain( error_chain, stderr_target );
  stumpless_add_target_to_chain( error_chain, error_buffer_target );
  mask = STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR );
  stumpless_set_target_mask( error_chain, mask );

  // make a top-level chain for all messages to go to
  main_chain = stumpless_new_chain( "example-main-chain" );
  stumpless_add_target_to_chain( main_chain, error_chain );
  stumpless_add_target_to_chain( main_chain, simple_chain );

  // since the main chain was the last target opened,
  // we can still just send messages to the default target
  stump_em( "emergency!" );
  stump_a( "alert!" );
  stump_c( "critical!" );
  stump_er( "error!" );
  stump_w( "warning..." );
  stump_n( "notice" );
  stump_i( "informational" );
  stump_d( "debug" );
  stump_t( "trace" );

  // print out the entries in the error buffer
  printf( "\nerrors logged in memory:\n" );
  do {
    read_size = stumpless_read_buffer( error_buffer_target,
                                       message_buffer,
                                       sizeof( message_buffer ) );
    printf( "%s\n", message_buffer );
  } while( read_size > 1 );

  // this closes all targets in the chain
  stumpless_close_chain_and_contents( main_chain );

  // some final cleanup
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
