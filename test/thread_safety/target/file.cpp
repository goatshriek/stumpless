// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2024 Joel E. Anderson
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
#include "test/helper/rfc5424.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 100;

  TEST( FileWriteConsistency, SimultaneousWrites ) {
    const char *filename = "file_target_thread_safety.log";
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT];

    remove( filename );

    // set up the target to log to
    target = stumpless_open_file_target( filename );
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
    stumpless_close_file_target( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );

    // check for consistency in the log file
    TestRFC5424File( filename, THREAD_COUNT * MESSAGE_COUNT );
    remove( filename );
  }
}
