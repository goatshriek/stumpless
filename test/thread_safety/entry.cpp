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
#include <sstream>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;

  void
  read_entry( struct stumpless_entry *entry ) {
    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      stumpless_get_entry_app_name( entry );
      stumpless_get_entry_msgid( entry );
      stumpless_get_entry_message( entry );
    }
  }

  void
  write_entry( struct stumpless_entry *entry ) {
    std::thread::id thread_id = std::this_thread::get_id(  );
    struct stumpless_element *element;

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      std::ostringstream app_stream;
      app_stream << "app-" << thread_id;
      stumpless_set_entry_app_name( entry, app_stream.str(  ).c_str(  ) );

      std::ostringstream msgid_stream;
      msgid_stream << "msgid-" << thread_id;
      stumpless_set_entry_msgid( entry, msgid_stream.str(  ).c_str(  ) );

      stumpless_set_entry_message( entry, "message number #%d from thread %d", i, thread_id );

      if( i == ITERATION_COUNT / 2 ) {
        std::ostringstream element_stream;
        element_stream << "element-" << thread_id;
        element = stumpless_new_element( element_stream.str(  ).c_str(  ) );
      }
    }
  }

  TEST( EntryConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_entry *entry;
    size_t i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "file-target-thread-safety-test",
                                 "test-message",
                                 "this is a test message" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i] = new std::thread( read_entry, entry );
      writer_threads[i] = new std::thread( write_entry, entry );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i]->join(  );
      writer_threads[i]->join(  );
    }

    // cleanup after the test
    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }
}
