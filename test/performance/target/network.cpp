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

#include <stddef.h>
#include <stdlib.h>
#include <benchmark/benchmark.h>
#include <stumpless.h>
#include "test/helper/server.hpp"

static size_t alloc_count = 0;

void *malloc_counter( size_t size ){
  alloc_count += size;
  return malloc( size );
}

static void AddEntryToTcp4Target( benchmark::State& state ) {
  struct stumpless_target *target;
  struct stumpless_entry *entry;
  socket_handle_t handle;
  socket_handle_t accepted = BAD_HANDLE;
  char buffer[1024];

  handle = open_tcp_server_socket( "127.0.0.1", "514" );

  target = stumpless_open_tcp4_target( "tcp4-perf",
                                       "127.0.0.1",
                                       0,
                                       STUMPLESS_FACILITY_USER );

  entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                               STUMPLESS_SEVERITY_INFO,
                               "add-entry-performance-test",
                               "network-target",
                               "this entry is for performance testing" );
  accepted = accept_tcp_connection( handle );

  stumpless_set_malloc( malloc_counter );

  alloc_count = 0;
  for(auto _ : state){
    if( stumpless_add_entry( target, entry ) < 0 ) {
      state.SkipWithError( "could not send an entry to the tcp target" );
    }

    recv_from_handle( accepted, buffer, 1024 );
  }
  state.counters["MemoryAllocated"] = ( double ) alloc_count;

  close_server_socket( accepted );
  close_server_socket( handle );
  stumpless_destroy_entry( entry );
  stumpless_close_network_target( target );
  stumpless_set_malloc( malloc );
}

static void AddEntryToUdp4Target( benchmark::State& state ) {
  struct stumpless_target *target;
  struct stumpless_entry *entry;

  stumpless_set_malloc( malloc_counter );

  target = stumpless_open_udp4_target( "udp4-perf",
                                       "127.0.0.1",
                                       0,
                                       STUMPLESS_FACILITY_USER );

  entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                               STUMPLESS_SEVERITY_INFO,
                               "add-entry-performance-test",
                               "network-target",
                               "this entry is for performance testing" );

  alloc_count = 0;
  for(auto _ : state){
    stumpless_add_entry( target, entry );
  }
  state.counters["MemoryAllocated"] = ( double ) alloc_count;

  stumpless_destroy_entry( entry );
  stumpless_close_network_target( target );
  stumpless_set_malloc( malloc );
}

BENCHMARK( AddEntryToTcp4Target );
BENCHMARK( AddEntryToUdp4Target );

BENCHMARK_MAIN();
