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

#include <cstdlib>
#include <gtest/gtest.h>
#include <sstream>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int ITERATION_COUNT = 1000;

  void
  read_target( const struct stumpless_target *target ) {
    const char *name;
    const char *app_name;
    const char *msgid;

    for( int i = 0; i < ITERATION_COUNT; i++ ) {
      name = stumpless_get_target_name( target );
      //app_name = stumpless_get_target_default_app_name( target );
      //msgid = stumpless_get_target_default_msgid( target );

      stumpless_get_default_facility( target );
      stumpless_get_option( target, STUMPLESS_OPTION_PID );

      free( ( void * ) name );
      //free( ( void * ) app_name );
      //free( ( void * ) msgid );
    }
  }

  void
  write_target( struct stumpless_target *target ) {
    std::thread::id thread_id = std::this_thread::get_id(  );

    std::ostringstream app_name_stream;
    app_name_stream << "app-name-" << thread_id;
    std::string app_name( app_name_stream.str(  ) );

    std::ostringstream msgid_stream;
    msgid_stream << "msgid-" << thread_id;
    std::string msgid( msgid_stream.str(  ) );

    for( int i = 0; i < ITERATION_COUNT; i++ ) {

      stumpless_set_target_default_app_name( target, app_name.c_str(  ) );
      stumpless_set_target_default_msgid( target, msgid.c_str(  ) );

      stumpless_set_default_facility( target, STUMPLESS_FACILITY_USER );
      stumpless_set_option( target, STUMPLESS_OPTION_PID );
    }
  }

  TEST( TargetConsistency, SimultaneousReadsAndWrites ) {
    const char *filename = "file_target_thread_safety.log";
    struct stumpless_target *target;
    int i;
    std::thread *reader_threads[THREAD_COUNT];
    std::thread *writer_threads[THREAD_COUNT];

    remove( filename );

    target = stumpless_open_file_target( filename,
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i] = new std::thread( read_target, target );
      writer_threads[i] = new std::thread( write_target, target );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      reader_threads[i]->join(  );
      delete reader_threads[i];
      writer_threads[i]->join(  );
      delete writer_threads[i];
    }

    // cleanup after the test
    stumpless_close_file_target( target );
    stumpless_free_all(  );
    remove( filename );
  }
}
