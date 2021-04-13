// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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

#include <atomic>
#include <cstddef>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 32;
  const int MESSAGE_COUNT = 1024;
  std::atomic_int call_count;

  int
  atomic_increment_func( const struct stumpless_target *target,
                         const struct stumpless_entry *entry ) {
    return call_count++;
  }

  TEST( FunctionTargetConsistency, SimultaneousCalls ) {
    struct stumpless_target *target;
    size_t i;
    std::thread *caller_threads[THREAD_COUNT];

    // set up the target to log to
    target = stumpless_open_function_target( "thread-safety-test-function",
                                             atomic_increment_func );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    call_count = 0;
    for( i = 0; i < THREAD_COUNT; i++ ) {
      caller_threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      caller_threads[i]->join(  );
      delete caller_threads[i];
    }

    EXPECT_EQ( call_count, THREAD_COUNT * MESSAGE_COUNT );

    // cleanup after the test
    stumpless_close_function_target( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );
  }
}
