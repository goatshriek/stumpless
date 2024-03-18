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

#include <benchmark/benchmark.h>
#include <stumpless.h>
#include "test/helper/fixture.hpp"
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( chain );

class ChainFixture : public::benchmark::Fixture {
protected:
  struct stumpless_target *chain_target;
  struct stumpless_target *sub_target;
  char buffer[4096];
  struct stumpless_entry *entry;

public:
  void SetUp( const ::benchmark::State &state ) {
    chain_target = stumpless_new_chain( "chain-perf" );
    sub_target = stumpless_open_buffer_target( "chain-perf-sub",
                                               buffer,
                                               sizeof( buffer ) );
    stumpless_add_target_to_chain( chain_target, sub_target );
    entry = create_entry();
    INIT_MEMORY_COUNTER( chain );
  }

  void TearDown( const ::benchmark::State &state ) {
    FINALIZE_MEMORY_COUNTER( chain );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_chain_and_contents( chain_target );
    stumpless_free_all();
  }
};

BENCHMARK_F( ChainFixture, AddEntry )( benchmark::State &state ) {
  for( auto _ : state ) {
    if( stumpless_add_entry( chain_target, entry ) < 0 ) {
      state.SkipWithError( "could not send an entry" );
    }
  }

  SET_STATE_COUNTERS( state, chain );
}
