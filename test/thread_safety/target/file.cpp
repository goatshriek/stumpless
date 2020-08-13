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
#include <fstream>
#include <gtest/gtest.h>
#include <pthread.h>
#include <stumpless.h>
#include "test/function/rfc5424.hpp"
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 100;
  struct stumpless_entry *shared_entry = NULL;

  void *
  write_messages( void *target ) {
    struct stumpless_target *file_target;

    file_target = ( struct stumpless_target * ) target;

    for( int i = 0; i < MESSAGE_COUNT; i++ ) {
      stumpless_set_entry_message( shared_entry, "message number #%d from thread #%d", i, pthread_self() );

      // this may not be the above message because of other threads
      stumpless_add_entry( file_target, shared_entry );
    }
  }

  TEST( WriteConsistency, SimultaneousWrites ) {
    const char *filename = "file_target_thread_safety.log";
    struct stumpless_target *target;
    size_t i;
    pthread_t threads[THREAD_COUNT];

    remove( filename );
    target = stumpless_open_file_target( filename,
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    shared_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                        STUMPLESS_SEVERITY_INFO,
                                        "file-target-thread-safety-test",
                                        "test-message",
                                        "this is a test message" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( shared_entry );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      pthread_create( &threads[i], NULL, write_messages, ( void * ) target );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      pthread_join( threads[i], NULL );
    }

    stumpless_destroy_entry( shared_entry );

    stumpless_close_file_target( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );

    // check for consistency in file
    std::ifstream infile( filename );
    std::string line;
    i = 0;
    while( std::getline( infile, line ) ) {
      //TestRFC5424Compliance( line.c_str() );
      i++;
    }

    EXPECT_EQ( i, THREAD_COUNT * MESSAGE_COUNT );

    //remove( filename );
  }
}
