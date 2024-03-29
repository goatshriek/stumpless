// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2024 Joel E. Anderson
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
#include <string>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/rfc5424.hpp"
#include "test/helper/usage.hpp"

namespace {
  const size_t TARGET_COUNT = 8;
  const size_t THREAD_COUNT = 16;
  const size_t MESSAGE_COUNT = 100;

  TEST( ChainWriteConsistency, SimultaneousWrites ) {
    struct stumpless_target *chain_target;
    struct stumpless_target *sub_target;
    size_t i;
    std::thread *threads[THREAD_COUNT];
    std::string filenames[TARGET_COUNT];

    // set up the chain of targets
    chain_target = stumpless_new_chain( "thread-safety-test-chain" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( chain_target );
    for( i = 0; i < TARGET_COUNT; i++ ) {
      std::ostringstream filename_stream;
      filename_stream << "thread-safety-test-file-" << i;
      filenames[i] = filename_stream.str();

      remove( filenames[i].c_str() );

      sub_target = stumpless_open_file_target( filenames[i].c_str() );
      EXPECT_NO_ERROR;

      stumpless_add_target_to_chain( chain_target, sub_target );
      EXPECT_NO_ERROR;
    }

    // send messages to the chain
    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i] = new std::thread( add_messages, chain_target, MESSAGE_COUNT );
    }

    // wait for the logs to finish
    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i]->join(  );
      delete threads[i];
    }

    // cleanup after the test
    stumpless_close_chain_and_contents( chain_target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );

    // check for consistency in the log files
    for( i = 0; i < TARGET_COUNT; i++ ) {
      TestRFC5424File( filenames[i], THREAD_COUNT * MESSAGE_COUNT );
      remove( filenames[i].c_str() );
    }
  }
}
