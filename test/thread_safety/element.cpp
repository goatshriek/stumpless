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
#include <cstdlib>
#include <gtest/gtest.h>
#include <sstream>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;
  std::vector<struct stumpless_param *> thread_params(THREAD_COUNT);

  void
  read_element( const struct stumpless_element *element ) {
    std::thread::id thread_id = std::this_thread::get_id(  );
    struct stumpless_element *copy;
    const char *result;

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );

    std::ostringstream param_value_stream;
    param_value_stream << "param-value-" << thread_id;
    std::string param_value( param_value_stream.str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      copy = stumpless_copy_element( element );

      result = stumpless_get_element_name( element );
      free( ( void * ) result );

      stumpless_element_has_param( element, param_name.c_str(  ) );

      stumpless_get_param_by_index( element, i % THREAD_COUNT );
      stumpless_get_param_by_name( element, param_name.c_str(  ) );
      stumpless_get_param_index( element, param_name.c_str(  ) );
      result = stumpless_get_param_name_by_index( element, i % THREAD_COUNT );
      free( ( void * ) result );
      stumpless_get_param_name_count( element, param_name.c_str(  ) );
      result = stumpless_get_param_value_by_index( element, i % THREAD_COUNT );
      free( ( void * ) result );
      result = stumpless_get_param_value_by_name( element,
                                                  param_name.c_str(  ) );
      free( ( void * ) result );

      stumpless_destroy_element_and_contents( copy );
    }
  }

  void
  write_element_external_params( struct stumpless_element *element ) {
    struct stumpless_param *thread_param;

    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream element_name_stream;
    element_name_stream << "element-name-" << thread_id;
    std::string element_name( element_name_stream.str(  ) );

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );

    std::ostringstream param_value_stream;
    param_value_stream << "param-value-" << thread_id;
    std::string param_value( param_value_stream.str(  ) );

    thread_param = stumpless_new_param( param_name.c_str(  ),
                                        param_value.c_str(  ) );

    stumpless_add_param( element, thread_param );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      size_t index = i % THREAD_COUNT;

      stumpless_set_element_name( element, element_name.c_str(  ) );

      stumpless_set_param_value_by_index( element,
                                          index,
                                          param_value.c_str(  ) );

      stumpless_set_param( element, index, thread_param );
    }

    thread_params.push_back( thread_param );
  }

  void
  write_element_internal_params( struct stumpless_element *element ) {
    struct stumpless_param *thread_param;

    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream element_name_stream;
    element_name_stream << "element-name-" << thread_id;
    std::string element_name( element_name_stream.str(  ) );

    std::ostringstream param_name_stream;
    param_name_stream << "param-name-" << thread_id;
    std::string param_name( param_name_stream.str(  ) );

    std::ostringstream param_value_stream;
    param_value_stream << "param-value-" << thread_id;
    std::string param_value( param_value_stream.str(  ) );

    stumpless_add_new_param( element,
                             param_name.c_str(  ),
                             param_value.c_str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      size_t index = i % THREAD_COUNT;

      stumpless_set_element_name( element, element_name.c_str(  ) );

      stumpless_set_param_value_by_index( element,
                                          index,
                                          param_value.c_str(  ) );

      stumpless_set_param_value_by_name( element,
                                         param_name.c_str(  ),
                                         param_value.c_str(  ) );
    }
  }

  TEST( ElementConsistency, SimultaneousReadsAndWrites ) {
    struct stumpless_element *element_external_params;
    struct stumpless_element *element_internal_params;
    int i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];

    element_external_params = stumpless_new_element( "initial-name" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element_external_params );

    element_internal_params = stumpless_new_element( "initial-name" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element_internal_params );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i] = new std::thread( read_element, element_external_params );
      writer_threads[i] = new std::thread( write_element_external_params,
                                           element_external_params );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i]->join(  );
      delete reader_threads[i];
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i] = new std::thread( read_element, element_internal_params );
      writer_threads[i] = new std::thread( write_element_internal_params,
                                           element_internal_params );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i]->join(  );
      delete reader_threads[i];
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    // cleanup after the tests
    stumpless_destroy_element_only( element_external_params );
    stumpless_destroy_element_and_contents( element_internal_params );
    for(auto it = thread_params.begin(); it != thread_params.end(); it++ ){
      stumpless_destroy_param( *it );
    }
    stumpless_free_all(  );
  }
}
