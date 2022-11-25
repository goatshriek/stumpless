// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2019 Joel E. Anderson
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

NEW_MEMORY_COUNTER( stump )
NEW_MEMORY_COUNTER( stumplog )

static void Stump(benchmark::State& state){
  char buffer[1000];
  struct stumpless_target *target;

  INIT_MEMORY_COUNTER( stump );
  stumpless_set_malloc( stump_memory_counter_malloc );
  stumpless_set_realloc( stump_memory_counter_realloc );
  stumpless_set_free( stump_memory_counter_free );

  target = stumpless_open_buffer_target( "stump-perf",
                                         buffer,
                                         sizeof( buffer ) );
  stumpless_set_current_target( target );

  for(auto _ : state){
    stump( "testing" );
  }

  stumpless_close_buffer_target( target );
  stumpless_free_all(  );

  state.counters["CallsToAlloc"] = ( double ) stump_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) stump_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) stump_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) stump_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) stump_memory_counter.free_total;
}

static void Stumplog( benchmark::State& state ) {
  int i = 0;

  INIT_MEMORY_COUNTER( stumplog );
  stumpless_set_malloc( stumplog_memory_counter_malloc );
  stumpless_set_realloc( stumplog_memory_counter_realloc );
  stumpless_set_free( stumplog_memory_counter_free );

  // ensure that the current target is the default target
  stumpless_set_current_target( stumpless_get_default_target(  ) );

  for(auto _ : state){
    stumplog( STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER,
              "testing message %d\n",
              i++ );
  }

  stumpless_free_all(  );

  state.counters["CallsToAlloc"] = ( double ) stumplog_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) stumplog_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) stumplog_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) stumplog_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) stumplog_memory_counter.free_total;
}

BENCHMARK( Stump );
BENCHMARK( Stumplog );
