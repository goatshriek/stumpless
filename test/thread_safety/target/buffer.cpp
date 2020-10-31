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

#include <atomic>
#include <cstddef>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <thread>
#include "test/function/rfc5424.hpp"
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 2;
  const int MESSAGE_COUNT = 10;
  std::atomic_int read_count;

  void
  read_and_validate( struct stumpless_target *target, int message_count ) {
    char read_buffer[1024];
    size_t result;

    while( read_count < THREAD_COUNT * MESSAGE_COUNT ) {
      result = stumpless_read_buffer( target, read_buffer, 1024 );

      if( result > 1 ) {
        TestRFC5424Compliance( read_buffer );
        read_count++;
      }
    }
  }

  TEST( WriteConsistency, SimultaneousWrites ) {
    char log_buffer[16384];
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT];
    std::thread reader_thread;

    read_count = 0;

    // set up the target to log to
    target = stumpless_open_buffer_target( "thread-safety-test-buffer",
                                           log_buffer,
                                           16384,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
    }

    reader_thread = std::thread( read_and_validate,
                                 target,
                                 MESSAGE_COUNT * THREAD_COUNT );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i]->join(  );
      delete threads[i];
    }
    reader_thread.join(  );

    // cleanup after the test
    stumpless_close_buffer_target( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );
  }
}
