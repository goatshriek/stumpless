// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020 Joel E. Anderson
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

NEW_MEMORY_COUNTER( copy_element )

static void CopyElement(benchmark::State& state){
  struct stumpless_element *element;
  const struct stumpless_element *result;

  INIT_MEMORY_COUNTER( copy_element );
  stumpless_set_malloc( copy_element_memory_counter_malloc );
  stumpless_set_realloc( copy_element_memory_counter_realloc );
  stumpless_set_free( copy_element_memory_counter_free );

  element = stumpless_new_element( "copy-element-perf" );
  stumpless_add_new_param( element, "param-1", "value-1" );
  stumpless_add_new_param( element, "param-2", "value-2" );

  for(auto _ : state){
    result = stumpless_copy_element( element );
    if( result <= 0 ) {
      state.SkipWithError( "could not send an entry to the target" );
    } else {
      stumpless_destroy_element_and_contents( result );
    }
  }

  stumpless_destroy_element_and_contents( element );

  state.counters["CallsToAlloc"] = ( double ) copy_element_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) copy_element_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) copy_element_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) copy_element_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) copy_element_memory_counter.free_total;
}

BENCHMARK(CopyElement);
