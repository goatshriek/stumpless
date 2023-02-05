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

#include <windows.h>

#include <cstddef>
#include <cstdlib>
#include <gtest/gtest.h>
#include <mutex>
#include <sstream>
#include <string>
#include <stumpless.h>
#include <thread>
#include "test/function/windows/events.h"
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;
  std::vector<struct stumpless_param *> thread_params(THREAD_COUNT);
  std::mutex thread_params_mutex;

  void
  read_entry_wel_data( const struct stumpless_entry *entry ) {
    const struct stumpless_entry *copy;
    WORD index;
    WORD category;
    DWORD event_id;
    WORD type;
    const struct stumpless_param *insertion_param;
    LPCSTR insertion_string;
    LPCWSTR insertion_string_w;

    std::thread::id thread_id = std::this_thread::get_id(  );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      index = i % THREAD_COUNT;

      copy = stumpless_copy_entry( entry );

      category = stumpless_get_wel_category( entry );
      event_id = stumpless_get_wel_event_id( entry );
      type = stumpless_get_wel_type( entry );
      insertion_param = stumpless_get_wel_insertion_param( entry, index );
      insertion_string = stumpless_get_wel_insertion_string( entry, index );
      insertion_string_w = stumpless_get_wel_insertion_string_w( entry, index );

      stumpless_destroy_entry_and_contents( copy );
      free( ( void * ) insertion_string );
      free( ( void * ) insertion_string_w );
    }

    stumpless_free_thread(  );
  }

  void
  write_entry_wel_data( struct stumpless_entry *entry ) {
    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream insertion_string_1_stream;
    insertion_string_1_stream << "insertion-string-1-" << thread_id;
    std::string insertion_string_1( insertion_string_1_stream.str(  ) );
    std::wstring insertion_string_1_w( insertion_string_1.begin(  ),
                                       insertion_string_1.end(  ) );

    std::ostringstream insertion_string_2_stream;
    insertion_string_2_stream << "insertion-string-2-" << thread_id;
    std::string insertion_string_2( insertion_string_2_stream.str(  ) );
    std::wstring insertion_string_2_w( insertion_string_2.begin(  ),
                                       insertion_string_2.end(  ) );

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );
    std::ostringstream param_value_stream;
    param_value_stream << "param-value-" << thread_id;
    std::string param_value( param_value_stream.str(  ) );
    struct stumpless_param *param = stumpless_new_param( param_name.c_str(  ),
                                                         param_value.c_str(  ) );

    for( WORD i = 0; i < ITERATION_COUNT; i++ ) {
      WORD index = i % THREAD_COUNT;

      stumpless_set_wel_insertion_string( entry,
                                          index,
                                          insertion_string_1.c_str(  ) );

      stumpless_set_wel_insertion_string_w( entry,
                                            index,
                                            insertion_string_1_w.c_str(  ) );

      stumpless_set_wel_insertion_param( entry,
                                         ( index + 1 ) % THREAD_COUNT,
                                         param );

      stumpless_set_wel_insertion_strings( entry,
                                           2,
                                           insertion_string_1.c_str(  ),
                                           insertion_string_2.c_str(  ) );

      stumpless_set_wel_insertion_strings_w( entry,
                                             2,
                                             insertion_string_1_w.c_str(  ),
                                             insertion_string_2_w.c_str(  ) );

      stumpless_set_wel_category( entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( entry, MSG_SIMPLE );
      stumpless_set_wel_type( entry, EVENTLOG_SUCCESS );
    }

    thread_params_mutex.lock(  );
    thread_params.push_back( param );
    thread_params_mutex.unlock(  );

    stumpless_free_thread(  );
  }

  TEST( WelEntryConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_entry *entry;
    size_t i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];

    entry = create_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i] = new std::thread( read_entry_wel_data, entry );
      writer_threads[i] = new std::thread( write_entry_wel_data, entry );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i]->join(  );
      delete reader_threads[i];
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    // cleanup after the test
    for(auto it = thread_params.begin(); it != thread_params.end(); it++ ){
      stumpless_destroy_param( *it );
    }
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }
}
