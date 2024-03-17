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

#include <atomic>
#include <cstddef>
#include <cstdio>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/rfc5424.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 8;
  const int MESSAGE_COUNT = 20;
  const int READ_WRITE_RATIO = 4;
  const int LOG_BUFFER_SIZE = 65536;
  const int READ_BUFFER_SIZE = 1024;
  std::atomic_int read_count;

  void
  read_and_validate( struct stumpless_target *target ) {
    char read_buffer[READ_BUFFER_SIZE];
    size_t result;

    while( read_count < THREAD_COUNT * MESSAGE_COUNT ) {
      result = stumpless_read_buffer( target, read_buffer, READ_BUFFER_SIZE );

      if( result > 1 ) {
        TestRFC5424Compliance( read_buffer );
        read_count++;
      }
    }
  }

  void
  read_and_write_target( struct stumpless_target *target ) {
    size_t i;
    std::thread *writer_threads[THREAD_COUNT];
    std::thread *reader_threads[THREAD_COUNT * READ_WRITE_RATIO];

    read_count = 0;
    for( i = 0; i < THREAD_COUNT * READ_WRITE_RATIO; i++ ) {
      reader_threads[i] = new std::thread( read_and_validate, target );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      writer_threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    for( i = 0; i < THREAD_COUNT * READ_WRITE_RATIO; i++ ) {
      reader_threads[i]->join(  );
      delete reader_threads[i];
    }
  }

  TEST( BufferConsistency, SimultaneousReadsAndWrites ) {
    char log_buffer[LOG_BUFFER_SIZE];
    struct stumpless_target *target;

    // set up the target to log to
    target = stumpless_open_buffer_target( "thread-safety-test-buffer",
                                           log_buffer,
                                           LOG_BUFFER_SIZE );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    read_and_write_target( target );

    // cleanup after the test
    stumpless_close_buffer_target( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );
  }

  TEST( BufferConsistency, SimultaneousReadsAndWritesWithPerror ) {
    char log_buffer[LOG_BUFFER_SIZE];
    struct stumpless_target *target;
    const struct stumpless_target *result;
    const char *error_filename = "buffer_target_perror.log";
    FILE *error_stream;
    size_t line_count;

    // set up the error stream
    error_stream = fopen( error_filename, "w+" );
    ASSERT_NOT_NULL( error_stream );

    stumpless_set_error_stream( error_stream );

    // set up the target to log to
    target = stumpless_open_buffer_target( "thread-safety-test-buffer-perror",
                                           log_buffer,
                                           LOG_BUFFER_SIZE );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target ); 

    result = stumpless_set_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( result );

    // do the reads and writes
    read_and_write_target( target );

    // cleanup after the test
    stumpless_set_error_stream( stderr );
    fclose( error_stream );
    stumpless_close_buffer_target( target );
    EXPECT_NO_ERROR;

    // checking the perror file for consistency
    TestRFC5424File( error_filename, THREAD_COUNT * MESSAGE_COUNT );

    // final cleanup
    remove( error_filename );
    stumpless_free_all(  );
  }
}
