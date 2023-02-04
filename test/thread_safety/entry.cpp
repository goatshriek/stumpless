// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2023 Joel E. Anderson
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
#include <cstdlib>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;

  void
  read_entry( const struct stumpless_entry *entry ) {
    const struct stumpless_entry *copy;
    size_t element_count;
    const char *param_value;
    const char *app_name;
    const char *hostname;
    const char *msgid;
    const char *message;
    const char *procid;

    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream element_stream;
    element_stream << "element-" << thread_id;
    std::string element_name( element_stream.str(  ) );

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      size_t index = i % THREAD_COUNT;

      copy = stumpless_copy_entry( entry );

      element_count = stumpless_get_element_count( entry );
      for( int j = 0; j < element_count; j++ ) {
        stumpless_get_element_by_index( entry, j );
      }

      stumpless_get_entry_facility( entry );
      stumpless_get_entry_prival( entry );
      stumpless_get_entry_severity( entry );

      stumpless_get_element_by_index( entry, index );
      stumpless_get_element_by_name( entry, element_name.c_str(  ) );
      stumpless_get_element_index( entry, element_name.c_str(  ) );

      stumpless_get_entry_param_by_index( entry, index, index );
      stumpless_get_entry_param_by_name( entry,
                                         element_name.c_str(  ),
                                         param_name.c_str(  ) );

      param_value = stumpless_get_entry_param_value_by_index( entry, index, index );
      free( ( void * ) param_value );

      param_value = stumpless_get_entry_param_value_by_name( entry,
                                                             element_name.c_str(  ),
                                                             param_name.c_str(  ) );
      free( ( void * ) param_value );

      app_name = stumpless_get_entry_app_name( entry );
      hostname = stumpless_get_entry_hostname( entry );
      msgid = stumpless_get_entry_msgid( entry );
      message = stumpless_get_entry_message( entry );
      procid = stumpless_get_entry_procid( entry );

      stumpless_entry_has_element( entry, element_name.c_str(  ) );

      stumpless_destroy_entry_and_contents( copy );
      free( ( void * ) app_name );
      free( ( void * ) hostname );
      free( ( void * ) msgid );
      free( ( void * ) message );
      free( ( void * ) procid );
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
      size_t index = i % THREAD_COUNT;

      std::ostringstream app_stream;
      app_stream << "app-" << thread_id;
      stumpless_set_entry_app_name( entry, app_stream.str(  ).c_str(  ) );

      std::ostringstream hostname_stream;
      hostname_stream << "hostname-" << thread_id;
      stumpless_set_entry_hostname( entry, hostname_stream.str(  ).c_str(  ) );

      std::ostringstream msgid_stream;
      msgid_stream << "msgid-" << thread_id;
      stumpless_set_entry_msgid( entry, msgid_stream.str(  ).c_str(  ) );

      stumpless_set_entry_message( entry, "message number #%d from thread %d", i, thread_id );

      std::ostringstream procid_stream;
      procid_stream << "procid-" << thread_id;
      stumpless_set_entry_procid( entry, procid_stream.str(  ).c_str(  ) );

      stumpless_set_entry_facility( entry, STUMPLESS_FACILITY_USER);
      stumpless_set_entry_priority( entry,
                                    STUMPLESS_FACILITY_USER,
                                    STUMPLESS_SEVERITY_INFO );
      stumpless_set_entry_prival( entry,
                                  STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO );
      stumpless_set_entry_severity( entry, STUMPLESS_SEVERITY_INFO );

      stumpless_set_entry_param_value_by_index( entry,
                                                index,
                                                index,
                                                param_value.c_str(  ) );

      stumpless_set_entry_param_value_by_name( entry,
                                               element_name.c_str(  ),
                                               param_name.c_str(  ),
                                               param_value.c_str(  ) );
    }
  }

  TEST( EntryConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_entry *entry;
    size_t i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];
    const struct stumpless_element *element;

    entry = create_empty_entry(  );
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
