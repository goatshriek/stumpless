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

#ifdef _WIN32
#  include <winsock2.h>
#else
#  include <sys/socket.h>
#endif

#include <benchmark/benchmark.h>
#include <stdlib.h>
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"
#include "test/helper/server.hpp"

NEW_MEMORY_COUNTER( tcp4 );
NEW_MEMORY_COUNTER( tcp6 );
NEW_MEMORY_COUNTER( udp4 );
NEW_MEMORY_COUNTER( udp6 );

class Tcp4Fixture : public ::benchmark::Fixture {
  protected:
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    socket_handle_t handle = BAD_HANDLE;
    socket_handle_t accepted = BAD_HANDLE;

  public:
    void SetUp( const ::benchmark::State& state ) {
      handle = open_tcp_server_socket( AF_INET, "127.0.0.1", "514" );

      target = stumpless_open_tcp4_target( "tcp4-perf",
                                           "127.0.0.1",
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );

      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "add-entry-performance-test",
                                   "network-target",
                                   "this entry is for performance testing" );
      accepted = accept_tcp_connection( handle );

      stumpless_set_malloc( tcp4_memory_counter_malloc );
      stumpless_set_realloc( tcp4_memory_counter_realloc );
      stumpless_set_free( tcp4_memory_counter_free );
    }

    void TearDown( const ::benchmark::State& state ) {
      stumpless_set_malloc( malloc );
      stumpless_set_realloc( realloc );
      stumpless_set_free( free );

      close_server_socket( accepted );
      close_server_socket( handle );
      stumpless_destroy_entry( entry );
      stumpless_close_network_target( target );
    }
};

BENCHMARK_F( Tcp4Fixture, AddEntryToTcp4Target )( benchmark::State& state ) {
  char buffer[1024];

  for(auto _ : state){
    if( stumpless_add_entry( target, entry ) <= 0 ) {
      state.SkipWithError( "could not send an entry to the tcp target" );
    }

    recv_from_handle( accepted, buffer, 1024 );
  }

  state.counters["CallsToAlloc"] = ( double ) tcp4_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) tcp4_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) tcp4_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) tcp4_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) tcp4_memory_counter.free_total;
}

class Tcp6Fixture : public ::benchmark::Fixture {
  protected:
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    socket_handle_t handle = BAD_HANDLE;
    socket_handle_t accepted = BAD_HANDLE;

  public:
    void SetUp( const ::benchmark::State& state ) {
      handle = open_tcp_server_socket( AF_INET6, "::1", "514" );

      target = stumpless_open_tcp6_target( "tcp6-perf",
                                           "::1",
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );

      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "add-entry-performance-test",
                                   "network-target",
                                   "this entry is for performance testing" );
      accepted = accept_tcp_connection( handle );

      stumpless_set_malloc( tcp6_memory_counter_malloc );
      stumpless_set_realloc( tcp6_memory_counter_realloc );
      stumpless_set_free( tcp6_memory_counter_free );
    }

    void TearDown( const ::benchmark::State& state ) {
      stumpless_set_malloc( malloc );
      stumpless_set_realloc( realloc );
      stumpless_set_free( free );

      close_server_socket( accepted );
      close_server_socket( handle );
      stumpless_destroy_entry( entry );
      stumpless_close_network_target( target );
    }
};

BENCHMARK_F( Tcp6Fixture, AddEntryToTcp6Target )( benchmark::State& state ) {
  char buffer[1024];

  for(auto _ : state){
    if( stumpless_add_entry( target, entry ) <= 0 ) {
      state.SkipWithError( "could not send an entry to the tcp target" );
    }

    recv_from_handle( accepted, buffer, 1024 );
  }

  state.counters["CallsToAlloc"] = ( double ) tcp6_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) tcp6_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) tcp6_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) tcp6_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) tcp6_memory_counter.free_total;
}

class Udp4Fixture : public ::benchmark::Fixture {
  protected:
    struct stumpless_target *target;
    struct stumpless_entry *entry;

  public:
    void SetUp( const ::benchmark::State& state ) {
      target = stumpless_open_udp4_target( "udp4-perf",
                                           "127.0.0.1",
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );

      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "add-entry-performance-test",
                                   "network-target",
                                   "this entry is for performance testing" );

      stumpless_set_malloc( udp4_memory_counter_malloc );
      stumpless_set_realloc( udp4_memory_counter_realloc );
      stumpless_set_free( udp4_memory_counter_free );
    }

    void TearDown( const ::benchmark::State& state ) {
      stumpless_set_malloc( malloc );
      stumpless_set_realloc( realloc );
      stumpless_set_free( free );

      stumpless_destroy_entry( entry );
      stumpless_close_network_target( target );
    }
};

BENCHMARK_F( Udp4Fixture, AddEntryToUdp4Target )( benchmark::State& state ) {
  for(auto _ : state){
    stumpless_add_entry( target, entry );
  }

  state.counters["CallsToAlloc"] = ( double ) udp4_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) udp4_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) udp4_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) udp4_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) udp4_memory_counter.free_total;
}

class Udp6Fixture : public ::benchmark::Fixture {
  protected:
    struct stumpless_target *target;
    struct stumpless_entry *entry;

  public:
    void SetUp( const ::benchmark::State& state ) {
      target = stumpless_open_udp6_target( "udp6-perf",
                                           "::1",
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );

      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "add-entry-performance-test",
                                   "network-target",
                                   "this entry is for performance testing" );

      stumpless_set_malloc( udp6_memory_counter_malloc );
      stumpless_set_realloc( udp6_memory_counter_realloc );
      stumpless_set_free( udp6_memory_counter_free );
    }

    void TearDown( const ::benchmark::State& state ) {
      stumpless_set_malloc( malloc );
      stumpless_set_realloc( realloc );
      stumpless_set_free( free );

      stumpless_destroy_entry( entry );
      stumpless_close_network_target( target );
    }
};

BENCHMARK_F( Udp6Fixture, AddEntryToUdp6Target )( benchmark::State& state ) {
  for(auto _ : state){
    stumpless_add_entry( target, entry );
  }

  state.counters["CallsToAlloc"] = ( double ) udp6_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) udp6_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) udp6_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) udp6_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) udp6_memory_counter.free_total;
}
