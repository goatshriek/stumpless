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

#include <stdlib.h>
#include <benchmark/benchmark.h>
#include <stumpless.h>

static size_t alloc_count=0;

void *malloc_counter(size_t size){
  alloc_count += size;
  return malloc(size);
}

static void Stumpless(benchmark::State& state){
  char buffer[1000];
  struct stumpless_target *target;

  alloc_count = 0;
  stumpless_set_malloc( malloc_counter );

  target = stumpless_open_buffer_target( "stumpless-perf", buffer, 1000, 0, 0 );
  stumpless_set_current_target( target );

  for(auto _ : state){
    stumpless("testing");
  }

  stumpless_close_buffer_target( target );
  stumpless_set_malloc( malloc );

  state.counters["MemoryAllocated"] = alloc_count;
}

BENCHMARK(Stumpless);

BENCHMARK_MAIN();
