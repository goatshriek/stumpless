// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021-2023 Joel E. Anderson
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

#include <chrono>
#include <cstddef>
#include <gtest/gtest.h>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <stumpless.h>
#include <systemd/sd-journal.h>
#include <thread>
#include <unordered_set>
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

using namespace std;

namespace {
  const int THREAD_COUNT = 32;
  const int MESSAGE_COUNT = 256;
  unordered_set<string> app_names( THREAD_COUNT + 1 );
  mutex app_names_mutex;

  void
  modify_entry( struct stumpless_entry *entry ) {
    thread::id thread_id = this_thread::get_id(  );
    ostringstream app_name_stream;
    app_name_stream << "modified-by-" << thread_id;
    string thread_app_name = app_name_stream.str(  );

    app_names_mutex.lock(  );
    app_names.insert( thread_app_name );
    app_names_mutex.unlock(  );

    for( int i = 0; i < MESSAGE_COUNT; i++ ) {
      stumpless_set_entry_app_name( entry, thread_app_name.c_str(  ) );
    }
  }

  TEST( JournaldTargetConsistency, SimultaneousCalls ) {
    unsigned seed;
    struct stumpless_entry *entry;
    struct stumpless_target *target;
    size_t i;
    thread *adders[THREAD_COUNT];
    thread *modifiers[THREAD_COUNT];

    // set up the entry to log
    seed = chrono::system_clock::now(  ).time_since_epoch(  ).count(  );
    default_random_engine gen( seed );
    uniform_int_distribution<int> dist;
    ostringstream message_stream;
    message_stream << "journald-thread-safety-test-" << dist( gen );
    string message = message_stream.str(  );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "journald-thread-safety-test",
                                 "test-entry-initial",
                                 message.c_str(  ) );
    EXPECT_NO_ERROR;
    app_names.insert( string( "journald-thread-safety-test" ) );

    // set up the target to log to
    target = stumpless_open_journald_target( "thread-safety-test-journald" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      adders[i] = new thread( repeat_add_entry, target, entry, MESSAGE_COUNT );
      modifiers[i] = new thread( modify_entry, entry );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      adders[i]->join(  );
      delete adders[i];
      modifiers[i]->join(  );
      delete modifiers[i];
    }

    // cleanup after the test
    stumpless_close_journald_target( target );
    EXPECT_NO_ERROR;
    stumpless_free_all(  );

    // wait for the journald daemon to catch up
    this_thread::sleep_for(chrono::seconds(5));

    // consistency check
    sd_journal *jrnl;
    sd_journal_open( &jrnl, SD_JOURNAL_LOCAL_ONLY );
    string message_match = "MESSAGE=" + message;
    sd_journal_add_match( jrnl, message_match.c_str(  ), 0 );
    size_t count = 0;
    const void *data;
    size_t data_len;
    int result;
    SD_JOURNAL_FOREACH( jrnl ) {
      count++;

      result = sd_journal_get_data( jrnl, "SYSLOG_IDENTIFIER", &data, &data_len );
      EXPECT_GE( result, 0 );

      string app_name ( ( const char * ) data + 18 );
      EXPECT_EQ( app_names.count( app_name ), 1 );
    }
    EXPECT_EQ( count, THREAD_COUNT * MESSAGE_COUNT );
  }
}
