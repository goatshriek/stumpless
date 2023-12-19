// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2022 Joel E. Anderson
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
NEW_MEMORY_COUNTER( load_element )
NEW_MEMORY_COUNTER( new_element )
NEW_MEMORY_COUNTER( set_element_name )
NEW_MEMORY_COUNTER( element_to_string )

static void CopyElement(benchmark::State& state){
  struct stumpless_element *element;
  const struct stumpless_element *result;

  INIT_MEMORY_COUNTER( copy_element );

  element = stumpless_new_element( "copy-element-perf" );
  stumpless_add_new_param( element, "param-1", "value-1" );
  stumpless_add_new_param( element, "param-2", "value-2" );

  for(auto _ : state){
    result = stumpless_copy_element( element );
    if( !result ) {
      state.SkipWithError( "the element copy failed" );
    } else {
      stumpless_destroy_element_and_contents( result );
    }
  }

  stumpless_destroy_element_and_contents( element );
  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, copy_element );
}

static void LoadElement(benchmark::State& state){
  const char *element_name = "new-element-perf";
  struct stumpless_element element;
  const struct stumpless_element *result;

  INIT_MEMORY_COUNTER( load_element );

  for(auto _ : state){
    result = stumpless_load_element( &element, element_name );
    if( !result ) {
      state.SkipWithError( "the element creation failed" );
    } else {
      stumpless_unload_element_and_contents( &element );
    }
  }

  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, load_element );
}

static void NewElement(benchmark::State& state){
  const char *element_name = "new-element-perf";
  const struct stumpless_element *result;

  INIT_MEMORY_COUNTER( new_element );

  for(auto _ : state){
    result = stumpless_new_element( element_name );
    if( !result ) {
      state.SkipWithError( "the element creation failed" );
    } else {
      stumpless_destroy_element_and_contents( result );
    }
  }

  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, new_element );
}

static void SetElementName(benchmark::State& state){
  struct stumpless_element *element;
  const char *name = "new-element-name";
  const struct stumpless_element *result;

  INIT_MEMORY_COUNTER( set_element_name );

  element = stumpless_new_element( "original-name" );

  for(auto _ : state){
    result = stumpless_set_element_name( element, name );
    if( !result ) {
      state.SkipWithError( "could not set the element name" );
    }
  }

  stumpless_destroy_element_and_contents( element );
  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, set_element_name );
}

static void ElementToString(benchmark::State& state){
  struct stumpless_element *element;
  const char *result;

  INIT_MEMORY_COUNTER( element_to_string );

  element = stumpless_new_element( "new-element-name" );

  for(auto _ : state){
    result = stumpless_element_to_string( element );
    if( !result ) {
      state.SkipWithError( "could not convert the element to string" );
    }
    else {
      element_to_string_memory_counter_free( ( void * ) result );
    }
  }

  stumpless_destroy_element_and_contents( element );
  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, element_to_string );
}

BENCHMARK( CopyElement );
BENCHMARK( LoadElement );
BENCHMARK( NewElement );
BENCHMARK( SetElementName );
BENCHMARK( ElementToString );
