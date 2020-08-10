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

#include <gtest/gtest.h>
#include <pthread.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"

namespace {
  void * write_messages( void *target ) {
    struct stumpless_target *file_target;

    file_target = ( struct stumpless_target * ) target;

    for( int i = 0; i < 100; i++ ) {
      stumpless_add_message( file_target, "thread message #%d", i );
    }
  }

  TEST( WriteConsistency, ThreadCount16 ) {
    const char *filename = "file_target_thread_safety.log";
    struct stumpless_target *target;
    size_t i;
    pthread_t threads[16];

    remove( filename );
    target = stumpless_open_file_target( filename,
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < 16; i++ ) {
      pthread_create( &threads[i], NULL, write_messages, ( void * ) target );
    }

    for( i = 0; i < 16; i++ ) {
      pthread_join( threads[i], NULL );
    }

    stumpless_close_file_target( target );
    EXPECT_NO_ERROR;

    // check for consistency in file

    remove( filename );
  }
}
