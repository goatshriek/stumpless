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

NEW_MEMORY_COUNTER( vload_entry )
NEW_MEMORY_COUNTER( load_entry_str )
NEW_MEMORY_COUNTER( vnew_entry )
NEW_MEMORY_COUNTER( new_entry_str )
NEW_MEMORY_COUNTER( set_app_name )
NEW_MEMORY_COUNTER( set_hostname )
NEW_MEMORY_COUNTER( set_msgid )
NEW_MEMORY_COUNTER( set_procid )

static void LoadEntry( benchmark::State &state ) {
  struct stumpless_entry entry;
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( vload_entry );

  for(auto _ : state){
    result = stumpless_load_entry( &entry,
                                   STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "entry-perf-test",
                                   "load-entry-test",
                                   "stumpless_load_entry iteration" );
    if( !result ) {
      state.SkipWithError( "the entry load failed" );
    } else {
      stumpless_unload_entry_only( &entry );
    }
  }

  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, vload_entry );
}

static void LoadEntryStr( benchmark::State &state ) {
  struct stumpless_entry entry;
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( load_entry_str );

  for(auto _ : state){
    result = stumpless_load_entry_str( &entry,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       "entry-perf-test",
                                       "load-entry-test",
                                       "stumpless_load_entry iteration" );
    if( !result ) {
      state.SkipWithError( "the entry load failed" );
    } else {
      stumpless_unload_entry_only( &entry );
    }
  }

  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, load_entry_str );
}

static void NewEntry(benchmark::State &state){
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( vnew_entry );

  for(auto _ : state){
    result = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                  STUMPLESS_SEVERITY_INFO,
                                  "entry-perf-test",
                                  "new-entry-test",
                                  "%s iteration",
                                  "stumpless_new_entry" );
    if( !result ) {
      state.SkipWithError( "the param creation failed" );
    } else {
      stumpless_destroy_entry_only( result );
    }
  }

  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, vnew_entry );
}

static void NewEntryStr(benchmark::State &state){
  const struct stumpless_entry *result;

  INIT_MEMORY_COUNTER( new_entry_str );

  for(auto _ : state){
    result = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                      STUMPLESS_SEVERITY_INFO,
                                      "entry-perf-test",
                                      "new-entry-test",
                                      "stumpless_new_entry iteration" );
    if( !result ) {
      state.SkipWithError( "the param creation failed" );
    } else {
      stumpless_destroy_entry_only( result );
    }
  }

  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, new_entry_str );
}

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
  stumpless_free_all(  );

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
  stumpless_free_all(  );

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
  stumpless_free_all(  );

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
  stumpless_free_all(  );

  SET_STATE_COUNTERS( state, set_procid );
}

BENCHMARK( LoadEntry );
BENCHMARK( LoadEntryStr );
BENCHMARK( NewEntry );
BENCHMARK( NewEntryStr );
BENCHMARK( SetAppName );
BENCHMARK( SetHostname );
BENCHMARK( SetMsgid );
BENCHMARK( SetProcid );
