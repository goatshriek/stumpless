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

#include <benchmark/benchmark.h>
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( version_to_string )

static void VersionToString(benchmark::State& state){
  const struct stumpless_version *current_version;
  char *result;

  INIT_MEMORY_COUNTER( version_to_string );
  current_version = stumpless_get_version(  );

  for(auto _ : state){
    result = stumpless_version_to_string( current_version );
    if( !result ) {
      state.SkipWithError( "could not get the version as a string" );
    } else {
      version_to_string_memory_counter_free( ( void * ) result );
    }
  }

  version_to_string_memory_counter_free( ( void * ) current_version );
  SET_STATE_COUNTERS( state, version_to_string );
}

BENCHMARK( VersionToString );
