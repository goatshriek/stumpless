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

#include <cstdlib>
#include <sqlite3.h>
#include <stddef.h>
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/rfc5424.hpp"

namespace {
  class Sqlite3TargetTest : public::testing::Test {
    protected:
      const char *db_filename = "test_function_fixture.sqlite3";
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      remove( db_filename );
      target = stumpless_open_sqlite3_target( db_filename );

      stumpless_create_default_sqlite3_table( target );

      stumpless_set_target_default_app_name( target, "sqlite3-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = create_entry(  );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_close_sqlite3_target( target );
      stumpless_free_all();
      remove( db_filename );
    }
  };

  TEST_F( Sqlite3TargetTest, AddEntry ) {
    int add_result;
    sqlite3 *db;
    const char *result_query = "SELECT prival, version, timestamp, hostname, "
                               "app_name, procid, msgid, structured_data, "
                               "message FROM logs WHERE message = ?";
    sqlite3_stmt *result_stmt;
    int sql_result;
    const char *expected_message;
    int expected_prival;
    int actual_prival;
    int actual_version;
    const unsigned char *timestamp;

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    db = ( sqlite3 * ) stumpless_get_sqlite3_db( target );
    ASSERT_NOT_NULL( db );
    EXPECT_NO_ERROR;

    sql_result = sqlite3_prepare_v2( db, result_query, -1, &result_stmt, NULL );
    EXPECT_EQ( sql_result, SQLITE_OK );

    expected_message = stumpless_get_entry_message( basic_entry );
    ASSERT_NOT_NULL( expected_message );
    sql_result = sqlite3_bind_text( result_stmt,
                                    1,
                                    expected_message,
                                    -1,
                                    SQLITE_STATIC );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_step( result_stmt );
    EXPECT_EQ( sql_result, SQLITE_ROW );

    actual_prival = sqlite3_column_int( result_stmt, 0 );
    expected_prival = stumpless_get_entry_prival( basic_entry );
    EXPECT_EQ( actual_prival, expected_prival );

    actual_version = sqlite3_column_int( result_stmt, 1 );
    EXPECT_EQ( actual_version, 1 );

    timestamp = sqlite3_column_text( result_stmt, 2 );
    EXPECT_NOT_NULL( timestamp );
    TestRFC5424Timestamp( reinterpret_cast<char const *>( timestamp ) );

    // hostname

    // app_name

    // procid

    // msgid

    // structured data

    // message

    sqlite3_finalize( result_stmt );
    free( ( void * ) expected_message );
  }

  /* non-fixture tests */

  TEST( Sqlite3TargetCloseTest, Generic ) {
    const char *db_filename = "test_function_close.sqlite3";
    struct stumpless_target *target;

    remove( db_filename );
    target = stumpless_open_sqlite3_target( db_filename );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_EQ( stumpless_get_current_target(  ), target );

    stumpless_close_target( target );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(  ),
               stumpless_get_default_target(  ) );
    EXPECT_STRNE( stumpless_get_current_target(  )->name,
                  db_filename );

    stumpless_free_all(  );
    remove( db_filename );
  }

  TEST( Sqlite3TargetCloseTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_sqlite3_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all();
  }

  TEST( Sqlite3TargetCloseTest, WrongTargetType ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-file-target" );

    stumpless_close_sqlite3_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
    stumpless_free_all();
  }

  TEST( Sqlite3TargetCreateDefaultTableTest, Normal ) {
    const char *db_filename = "test_function_default_table.sqlite3";
    struct stumpless_target *target;
    struct stumpless_target *result;
    
    remove( db_filename );
    target = stumpless_open_sqlite3_target( db_filename );
    ASSERT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    result = stumpless_create_default_sqlite3_table( target );
    EXPECT_EQ( result, target );
    EXPECT_NO_ERROR;

    stumpless_close_sqlite3_target( target );
    stumpless_free_all();
    remove( db_filename );
  }

  TEST( Sqlite3TargetOpenTest, Directory ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;
   
    target = stumpless_open_sqlite3_target( "./" );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_SQLITE3_FAILURE );

    stumpless_free_all();
  }

  TEST( Sqlite3TargetOpenTest, MallocFailure ) {
    const char *db_filename = "malloc_fail_on_open.sqlite3";
    struct stumpless_target *target;
    const struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_NOT_NULL( set_malloc_result );
   
    target = stumpless_open_sqlite3_target( db_filename );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
    stumpless_free_all();
    remove( db_filename );
  }

  TEST( Sqlite3TargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_sqlite3_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all();
  }
}
