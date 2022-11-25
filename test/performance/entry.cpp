// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2022 Joel E. Anderson
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

NEW_MEMORY_COUNTER( set_app_name )
NEW_MEMORY_COUNTER( set_hostname )
NEW_MEMORY_COUNTER( set_msgid )
NEW_MEMORY_COUNTER( set_procid )

static void SetAppName(benchmark::State& state){
  struct stumpless_entry *entry;
  const char *app_name = "new-app-name";
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( set_app_name );

  entry = create_entry(  ); 

  for(auto _ : state){
    result = stumpless_set_entry_app_name( entry, app_name );
    if( !result ) {
      state.SkipWithError( "could not set the entry app name" );
    }
  }

  stumpless_destroy_entry_and_contents( entry );

  SET_STATE_COUNTERS( state, set_app_name );
}

static void SetHostname(benchmark::State& state){
  struct stumpless_entry *entry;
  const char *hostname = "new-hostname";
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( set_hostname );

  entry = create_entry(  ); 

  for(auto _ : state){
    result = stumpless_set_entry_hostname( entry, hostname );
    if( !result ) {
      state.SkipWithError( "could not set the entry hostname" );
    }
  }

  stumpless_destroy_entry_and_contents( entry );

  SET_STATE_COUNTERS( state, set_hostname );
}

static void SetMsgid(benchmark::State& state){
  struct stumpless_entry *entry;
  const char *msgid = "new-msgid";
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( set_msgid );

  entry = create_entry(  ); 

  for(auto _ : state){
    result = stumpless_set_entry_msgid( entry, msgid );
    if( !result ) {
      state.SkipWithError( "could not set the entry msgid" );
    }
  }

  stumpless_destroy_entry_and_contents( entry );

  SET_STATE_COUNTERS( state, set_msgid );
}

static void SetProcid(benchmark::State& state){
  struct stumpless_entry *entry;
  const char *procid = "new-procid";
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( set_procid );

  entry = create_entry(  ); 

  for(auto _ : state){
    result = stumpless_set_entry_procid( entry, procid );
    if( !result ) {
      state.SkipWithError( "could not set the entry procid" );
    }
  }

  stumpless_destroy_entry_and_contents( entry );

  SET_STATE_COUNTERS( state, set_procid );
}

BENCHMARK( SetAppName );
BENCHMARK( SetHostname );
BENCHMARK( SetMsgid );
BENCHMARK( SetProcid );
