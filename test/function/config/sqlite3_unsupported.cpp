// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2023-2024 Joel E. Anderson
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
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"

namespace {

  TEST( Sqlite3TargetTest, CloseTargetAndDb ) {
    struct stumpless_target *target;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    stumpless_close_sqlite3_target_only( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, CloseTargetOnly ) {
    struct stumpless_target *target;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    stumpless_close_sqlite3_target_and_db( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, CreateDefaultDatabase ) {
    struct stumpless_target *target;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    stumpless_create_default_sqlite3_table( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, DefaultPrepare ) {
    void *result;

    result = stumpless_sqlite3_prepare( NULL, NULL, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( result );
  }

  TEST( Sqlite3TargetTest, GenericClose ) {
    struct stumpless_target *target;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    target->type = STUMPLESS_SQLITE3_TARGET;

    stumpless_close_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_STREAM_TARGET;
    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, GetDb ) {
    struct stumpless_target *target;
    void *result;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    result = stumpless_get_sqlite3_db( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( result );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, GetInsertSql ) {
    struct stumpless_target *target;
    const char *result;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    result = stumpless_get_sqlite3_insert_sql( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( result );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, GetPrepare ) {
    struct stumpless_target *target;
    stumpless_sqlite3_prepare_func_t result;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    result = stumpless_get_sqlite3_prepare( target, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, Open ) {
    const struct stumpless_target *target;

    target = stumpless_open_sqlite3_target( "open-please" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( target );

    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, OpenFromDb ) {
    const struct stumpless_target *target;

    target = stumpless_open_sqlite3_target_from_db( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( target );

    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, OpenWithOptions ) {
    const struct stumpless_target *target;

    target = stumpless_open_sqlite3_target_with_options( "optional", 0, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( target );

    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, SetInsertSql ) {
    struct stumpless_target *target;
    struct stumpless_target *result;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    result = stumpless_set_sqlite3_insert_sql( target, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( result );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, SetPrepare ) {
    struct stumpless_target *target;
    struct stumpless_target *result;

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    result = stumpless_set_sqlite3_prepare( target,
                                            &stumpless_sqlite3_prepare,
                                            NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    EXPECT_NULL( result );

    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( Sqlite3TargetTest, Unsupported ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    int result;

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    target = stumpless_open_stdout_target( "fake-sqlite3-target" );
    ASSERT_NOT_NULL( target );

    target->type = STUMPLESS_SQLITE3_TARGET;

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_STREAM_TARGET;
    stumpless_close_stream_target( target );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }
}
