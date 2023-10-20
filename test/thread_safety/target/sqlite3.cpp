// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023 Joel E. Anderson
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
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 100;

  TEST( Sqlite3WriteConsistency, SimultaneousWrites ) {
    const char *filename = "test_thread_safety.sqlite3";
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT];

    remove( filename );

    // set up the target to log to
    target = stumpless_open_sqlite3_target( filename );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i]->join(  );
      delete threads[i];
    }

    // cleanup after the test
    stumpless_close_sqlite3_target( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );

    // check for consistency in the log file
    // TODO complete
    // std::ifstream log_file( filename );
    // std::string line;
    // i = 0;
    // while( std::getline( log_file, line ) ) {
    //   TestRFC5424Compliance( line.c_str() );
    //   i++;
    // }
    // EXPECT_EQ( i, THREAD_COUNT * MESSAGE_COUNT );

    // remove( filename );
  }
}
