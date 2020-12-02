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

#include <cstdlib>
#include <gtest/gtest.h>
#include <sstream>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;

  void
  read_param( const struct stumpless_param *param ) {
    struct stumpless_param *copy;
    const char *name;
    const char *value;
    const char *str;

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      copy = stumpless_copy_param( param );

      name = stumpless_get_param_name( param );
      value = stumpless_get_param_value( param );
      str = stumpless_param_to_string( param );

      stumpless_destroy_param( copy );
      free( ( void * ) name );
      free( ( void * ) value );
      free( ( void * ) str );
    }
  }

  void
  write_param( struct stumpless_param *param ) {
    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream name_stream;
    name_stream << "param-name-" << thread_id;
    std::string name( name_stream.str(  ) );

    std::ostringstream value_stream;
    value_stream << "param-value-" << thread_id;
    std::string value( value_stream.str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      stumpless_set_param_name( param, name.c_str(  ) );
      stumpless_set_param_value( param, value.c_str(  ) );
    }
  }

  TEST( ParamConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_param *param;
    int i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];

    param = stumpless_new_param( "initial-name", "initial-value" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( param );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i] = new std::thread( read_param, param );
      writer_threads[i] = new std::thread( write_param, param );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i]->join(  );
      delete reader_threads[i];
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    // cleanup after the test
    stumpless_destroy_param( param );
    stumpless_free_all(  );
  }
}
