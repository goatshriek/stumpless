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
#include "test/helper/memory_counter.hpp"
#define MAX_BUFFER_SIZE (4ull * 1024ull) // 4 kB

NEW_MEMORY_COUNTER( buffer );

class BufferFixture : public::benchmark::Fixture {
protected:
  char buffer[MAX_BUFFER_SIZE];

public:
  void SetUp( const ::benchmark::State &state ) {
    INIT_MEMORY_COUNTER( buffer );
  }

  void TearDown( const ::benchmark::State &state ) {
    FINALIZE_MEMORY_COUNTER( buffer );
    stumpless_free_all();
  }
};

BENCHMARK_F( BufferFixture, OpenBufferTarget )( benchmark::State &state ) {
  for( auto _ : state ) {
    struct stumpless_target *target = stumpless_open_buffer_target( "buffer-perf",
                                                                    buffer,
                                                                    sizeof( buffer ) );
    if( !target ) {
      state.SkipWithError( "could not open buffer target" );
    }
    stumpless_close_buffer_target( target );
  }

  SET_STATE_COUNTERS( state, buffer );
}
