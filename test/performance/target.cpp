// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2021 Joel E. Anderson
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
#include "test/helper/fixture.hpp"
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( add_entry )
NEW_MEMORY_COUNTER( add_message )

static void AddEntry(benchmark::State& state){
  struct stumpless_entry *entry;
  char buffer[1024];
  struct stumpless_target *target;
  int result;

  INIT_MEMORY_COUNTER( add_entry );

  entry = create_entry(  );
  target = stumpless_open_buffer_target( "add-entry-perf",
                                         buffer,
                                         sizeof( buffer ) );

  for(auto _ : state){
    result = stumpless_add_entry( target, entry );
    if( result <= 0 ) {
      state.SkipWithError( "could not send an entry to the target" );
    }
  }

  stumpless_close_buffer_target( target );
  stumpless_destroy_entry_and_contents( entry );

  SET_STATE_COUNTERS( state, add_entry );
}

static void AddMessage(benchmark::State& state){
  char buffer[1024];
  struct stumpless_target *target;
  int i = 0;
  int result;

  INIT_MEMORY_COUNTER( add_message );

  target = stumpless_open_buffer_target( "add-message-perf",
                                         buffer,
                                         sizeof( buffer ) );

  for(auto _ : state){
    result = stumpless_add_message( target, "testing: %s, %d\n", "test-string", i++ );
    if( result <= 0 ) {
      state.SkipWithError( "could not send a message to the target" );
    }
  }

  stumpless_close_buffer_target( target );

  SET_STATE_COUNTERS( state, add_message );
}

BENCHMARK( AddEntry );
BENCHMARK( AddMessage );
