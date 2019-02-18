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

#include <benchmark/benchmark.h>
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( stumpless )

static void Stumpless(benchmark::State& state){
  char buffer[1000];
  struct stumpless_target *target;

  INIT_MEMORY_COUNTER( stumpless );
  stumpless_set_malloc( stumpless_memory_counter_malloc );
  stumpless_set_realloc( stumpless_memory_counter_realloc );
  stumpless_set_free( stumpless_memory_counter_free );

  target = stumpless_open_buffer_target( "stumpless-perf", buffer, 1000, 0, 0 );
  stumpless_set_current_target( target );

  for(auto _ : state){
    stumpless("testing");
  }

  stumpless_close_buffer_target( target );

  state.counters["CallsToAlloc"] = ( double ) stumpless_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) stumpless_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) stumpless_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) stumpless_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) stumpless_memory_counter.free_total;
}

BENCHMARK(Stumpless);
