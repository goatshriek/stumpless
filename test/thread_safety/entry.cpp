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

#include <cstddef>
#include <gtest/gtest.h>
#include <pthread.h>
#include <sstream>
#include <stumpless.h>
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;

  void *
  read_entry( void *entry_pointer ) {
    struct stumpless_entry *entry;
    int thread_id;

    entry = ( struct stumpless_entry * ) entry_pointer;

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      stumpless_get_entry_app_name( entry );
      stumpless_get_entry_msgid( entry );
      stumpless_get_entry_message( entry );
    }

    return NULL;
  }

  void *
  write_entry( void *entry_pointer ) {
    struct stumpless_entry *entry;
    int thread_id;

    entry = ( struct stumpless_entry * ) entry_pointer;
    thread_id = pthread_self(  );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      std::ostringstream app_stream;
      app_stream << "app-" << thread_id;
      stumpless_set_entry_app_name( entry, app_stream.str(  ).c_str(  ) );

      std::ostringstream msgid_stream;
      msgid_stream << "msgid-" << thread_id;
      stumpless_set_entry_msgid( entry, msgid_stream.str(  ).c_str(  ) );

      stumpless_set_entry_message( entry, "message number #%d from thread %d", i, thread_id );
    }

    return NULL;
  }

  TEST( EntryConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_entry *entry;
    size_t i;
    pthread_t reader_threads[THREAD_COUNT];
    pthread_t writer_threads[THREAD_COUNT];

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "file-target-thread-safety-test",
                                 "test-message",
                                 "this is a test message" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      pthread_create( &reader_threads[i], NULL, read_entry, ( void * ) entry );
      pthread_create( &writer_threads[i], NULL, write_entry, ( void * ) entry );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      pthread_join( reader_threads[i], NULL );
      pthread_join( writer_threads[i], NULL );
    }

    // cleanup after the test
    stumpless_destroy_entry( entry );

    stumpless_free_all(  );
  }
}
