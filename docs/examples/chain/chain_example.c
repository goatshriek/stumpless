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

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stumpless.h>
#include <time.h>


int
main( void ){
  struct stumpless_target *chain;

  // creating an empty chain
  chain = stumpless_new_chain( "chain-example" );
  if( !chain ){
    stumpless_perror( "could not create a new chain" );
  }

  // this closes all targets in the chain too
  stumpless_close_chain_and_contents( chain );

  // some final cleanup
  stumpless_free_all(  );

  return EXIT_SUCCESS;
}
