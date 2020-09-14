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
#include <stdlib>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 100;

  void
  read_network_target( const struct stumpless_target *target ) {
    const char *destination;

    for( size_t i = 0; i < MESSAGE_COUNT; i++ ) {
      destination = stumpless_get_destination( target );

      free( ( void * ) destination );
    }
  }

  void
  write_network_target( struct stumpless_target *target ) {

  }

  TEST( WriteConsistency, SimultaneousWrites ) {
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT*3];

    // set up the target to log to
    target = stumpless_open_udp4_target( "test-target",
                                         "127.0.0.1",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
      threads[THREAD_COUNT+i] = new std::thread( read_network_target, target );
      threads[THREAD_COUNT*2 + i] = new std::thread( write_network_target, target );
    }

    for( i = 0; i < THREAD_COUNT*3; i++ ) {
      threads[i]->join(  );
      delete threads[i];
    }

    // cleanup after the test
    stumpless_close_network_target( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );
  }
}
