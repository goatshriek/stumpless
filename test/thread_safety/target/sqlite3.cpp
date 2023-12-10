// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023 Joel E. Anderson
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
#include <sqlite3.h>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 100;

  TEST( Sqlite3WriteConsistency, SimultaneousWrites ) {
    const char *filename = "test_thread_safety.sqlite3";
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT];
    sqlite3 *db;
    int sql_result;
    sqlite3_stmt *stmt;
    const char *result_query = "SELECT * FROM logs";

    target = stumpless_open_sqlite3_target( filename );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    stumpless_create_default_sqlite3_table( target );
    EXPECT_NO_ERROR;

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i]->join();
      delete threads[i];
    }

    // cleanup after the test
    stumpless_close_sqlite3_target_and_db( target );
    EXPECT_NO_ERROR;

    stumpless_free_all(  );

    // check for consistency in the database
    sql_result = sqlite3_open( filename, &db );
    ASSERT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_prepare_v2( db, result_query, -1, &stmt, NULL );
    ASSERT_EQ( sql_result, SQLITE_OK );

    for( i = 0; i < THREAD_COUNT * MESSAGE_COUNT; i++ ) {
      sql_result = sqlite3_step( stmt );
      EXPECT_EQ( sql_result, SQLITE_ROW );
    }

    sql_result = sqlite3_step( stmt );
    EXPECT_EQ( sql_result, SQLITE_DONE );

    sql_result = sqlite3_close_v2( db );
    EXPECT_EQ( sql_result, SQLITE_OK );

    remove( filename );
  }
}
