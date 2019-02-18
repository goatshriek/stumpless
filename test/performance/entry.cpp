// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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

NEW_MEMORY_COUNTER( add_message )

static void AddMessage(benchmark::State& state){
  char buffer[1000];
  struct stumpless_target *target;
  int i = 0;
  int result;

  INIT_MEMORY_COUNTER( add_message );
  stumpless_set_malloc( add_message_memory_counter_malloc );
  stumpless_set_realloc( add_message_memory_counter_realloc );
  stumpless_set_free( add_message_memory_counter_free );

  target = stumpless_open_buffer_target( "add-message-perf",
                                         buffer,
                                         sizeof( buffer ),
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );

  for(auto _ : state){
    result = stumpless_add_message( target, "testing: %s, %d\n", "test-string", i++ );
    if( result <= 0 ) {
      state.SkipWithError( "could not send an entry to the target" );
    }
  }

  stumpless_close_buffer_target( target );

  state.counters["CallsToAlloc"] = ( double ) add_message_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) add_message_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) add_message_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) add_message_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) add_message_memory_counter.free_total;
}

BENCHMARK(AddMessage);
