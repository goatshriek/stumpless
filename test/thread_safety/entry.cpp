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
  read_entry( const struct stumpless_entry *entry ) {
    size_t element_count;
    const char *app_name;

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      element_count = stumpless_get_element_count( entry );
      for( int j = 0; j < element_count; j++ ) {
        stumpless_get_element_by_index( entry, j );
      }

      app_name = stumpless_get_entry_app_name( entry );
      stumpless_get_entry_msgid( entry );
      stumpless_get_entry_message( entry );

      free( ( void * ) app_name );
    }
  }

  void
  write_entry( struct stumpless_entry *entry ) {
    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream element_stream;
    element_stream << "element-" << thread_id;
    std::string element_name( element_stream.str(  ) );
    stumpless_add_new_element( entry, element_name.c_str(  ) );

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );
    std::ostringstream param_value_stream;
    param_value_stream << "param-value-" << thread_id;
    std::string param_value( param_value_stream.str(  ) );
    stumpless_add_new_param_to_entry( entry,
                                      element_name.c_str(  ),
                                      param_name.c_str(  ),
                                      param_value.c_str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      std::ostringstream app_stream;
      app_stream << "app-" << thread_id;
      stumpless_set_entry_app_name( entry, app_stream.str(  ).c_str(  ) );

      std::ostringstream msgid_stream;
      msgid_stream << "msgid-" << thread_id;
      stumpless_set_entry_msgid( entry, msgid_stream.str(  ).c_str(  ) );

      stumpless_set_entry_message( entry, "message number #%d from thread %d", i, thread_id );
    }
  }

  TEST( EntryConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_entry *entry;
    size_t i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];
    const struct stumpless_element *element;

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
      delete reader_threads[i];
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    // check the entry for consistency
    size_t element_count = stumpless_get_element_count( entry );
    EXPECT_EQ( element_count, THREAD_COUNT );

    for( i = 0; i < element_count; i++ ) {
      element = stumpless_get_element_by_index( entry, i );
      EXPECT_EQ( stumpless_get_param_count( element ), 1 );
    }

    // cleanup after the test
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }
}
