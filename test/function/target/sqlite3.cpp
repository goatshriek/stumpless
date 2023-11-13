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

struct test_prepare_data {
  struct stumpless_target *target;
  sqlite3_stmt *insert_stmts[2];
};

static
void *
test_prepare( const struct stumpless_entry *entry, void *data, size_t *count ) {
  const char *insert_sql = "INSERT INTO logs (prival, version, message) "
                           "VALUES (0, 1, ?);";
  int sql_result;
  struct test_prepare_data *test_data = ( struct test_prepare_data * ) data;
  sqlite3 *db = ( sqlite3 * ) stumpless_get_sqlite3_db( test_data->target );

  if( !test_data->insert_stmts[0] ) {
    sql_result = sqlite3_prepare_v2( db, insert_sql, -1, &test_data->insert_stmts[0], NULL );
    if( sql_result != SQLITE_OK ) {
      return NULL;
    }
  } else {
    sqlite3_reset( test_data->insert_stmts[0] );
  }

  if( !test_data->insert_stmts[1] ) {
    sql_result = sqlite3_prepare_v2( db, insert_sql, -1, &test_data->insert_stmts[1], NULL );
    if( sql_result != SQLITE_OK ) {
      return NULL;
    }
  } else {
    sqlite3_reset( test_data->insert_stmts[1] );
  }

  sql_result = sqlite3_bind_text( test_data->insert_stmts[0], 1, "test-prepare-1", -1, SQLITE_STATIC );
  if( sql_result != SQLITE_OK ) {
    return NULL;
  }

  sql_result = sqlite3_bind_text( test_data->insert_stmts[1], 1, "test-prepare-2", -1, SQLITE_STATIC );
  if( sql_result != SQLITE_OK ) {
    return NULL;
  }

  *count = 2;
  return &test_data->insert_stmts;
}

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
    const char *result_query = "SELECT prival, version, timestamp, hostname,"
                               "  app_name, procid, msgid, structured_data,"
                               "  message "
                               "FROM logs WHERE message = ?";
    sqlite3_stmt *result_stmt;
    int sql_result;
    const char *expected_message;
    int expected_prival;
    int actual_prival;
    int actual_version;
    const unsigned char *timestamp;
    const unsigned char *hostname;
    const char *actual_hostname;
    const unsigned char *app_name;
    const char *actual_app_name;
    const unsigned char *procid;
    const char *actual_procid;
    const unsigned char *msgid;
    const char *actual_msgid;
    const unsigned char *structured_data;

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
    TestRFC5424Timestamp( reinterpret_cast<const char *>( timestamp ) );

    hostname = sqlite3_column_text( result_stmt, 3 );
    EXPECT_NOT_NULL( hostname );
    actual_hostname = stumpless_get_entry_hostname( basic_entry );
    EXPECT_NOT_NULL( actual_hostname );
    EXPECT_STREQ( ( const char * ) hostname, actual_hostname );
    free( ( void * ) actual_hostname );

    app_name = sqlite3_column_text( result_stmt, 4 );
    EXPECT_NOT_NULL( app_name );
    actual_app_name = stumpless_get_entry_app_name( basic_entry );
    EXPECT_NOT_NULL( actual_app_name );
    EXPECT_STREQ( ( const char * ) app_name, actual_app_name );
    free( ( void * ) actual_app_name );

    procid = sqlite3_column_text( result_stmt, 5 );
    EXPECT_NOT_NULL( procid );
    actual_procid = stumpless_get_entry_procid( basic_entry );
    EXPECT_NOT_NULL( actual_procid );
    EXPECT_STREQ( ( const char * ) procid, actual_procid );
    free( ( void * ) actual_procid );

    msgid = sqlite3_column_text( result_stmt, 6 );
    EXPECT_NOT_NULL( msgid );
    actual_msgid = stumpless_get_entry_msgid( basic_entry );
    EXPECT_NOT_NULL( actual_msgid );
    EXPECT_STREQ( ( const char * ) msgid, actual_msgid );
    free( ( void * ) actual_msgid );

    structured_data = sqlite3_column_text( result_stmt, 7 );
    EXPECT_NOT_NULL( structured_data );
    TestRFC5424StructuredData( reinterpret_cast<const char *>( structured_data ) );

    sqlite3_finalize( result_stmt );
    free( ( void * ) expected_message );
  }

  TEST_F( Sqlite3TargetTest, CustomInsert ) {
    const char *insert_sql = "INSERT INTO logs (prival, version,"
                             "  timestamp, hostname, app_name,"
                             "  procid, msgid, structured_data,"
                             "  message) "
                             "VALUES (0, 1, $timestamp,"
                             "  $hostname, $app_name, $procid,"
                             "  $msgid, '-',"
                             "  $message);";
    const struct stumpless_target *result;
    const char *current_sql;
    int add_result;
    sqlite3 *db;
    const char *result_query = "SELECT prival, version, timestamp, hostname,"
                               "  app_name, procid, msgid, structured_data,"
                               "  message "
                               "FROM logs WHERE message = ?";
    sqlite3_stmt *result_stmt;
    int sql_result;
    const char *expected_message;
    int prival;
    int actual_version;
    const unsigned char *timestamp;
    const unsigned char *hostname;
    const char *actual_hostname;
    const unsigned char *app_name;
    const char *actual_app_name;
    const unsigned char *procid;
    const char *actual_procid;
    const unsigned char *msgid;
    const char *actual_msgid;
    const unsigned char *structured_data;

    result = stumpless_set_sqlite3_insert_sql( target, insert_sql );
    ASSERT_EQ( result, target );

    current_sql = stumpless_get_sqlite3_insert_sql( target );
    ASSERT_EQ( current_sql, insert_sql );

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

    prival = sqlite3_column_int( result_stmt, 0 );
    EXPECT_EQ( prival, 0 );

    actual_version = sqlite3_column_int( result_stmt, 1 );
    EXPECT_EQ( actual_version, 1 );

    timestamp = sqlite3_column_text( result_stmt, 2 );
    EXPECT_NOT_NULL( timestamp );
    TestRFC5424Timestamp( reinterpret_cast<const char *>( timestamp ) );

    hostname = sqlite3_column_text( result_stmt, 3 );
    // hostname might be NULL if it couldn't be retrieved
    if( !hostname ) {
      hostname = ( const unsigned char * ) "-";
    }
    actual_hostname = stumpless_get_entry_hostname( basic_entry );
    EXPECT_NOT_NULL( actual_hostname );
    EXPECT_STREQ( ( const char * ) hostname, actual_hostname );
    free( ( void * ) actual_hostname );

    app_name = sqlite3_column_text( result_stmt, 4 );
    EXPECT_NOT_NULL( app_name );
    actual_app_name = stumpless_get_entry_app_name( basic_entry );
    EXPECT_NOT_NULL( actual_app_name );
    EXPECT_STREQ( ( const char * ) app_name, actual_app_name );
    free( ( void * ) actual_app_name );

    procid = sqlite3_column_text( result_stmt, 5 );
    EXPECT_NOT_NULL( procid );
    actual_procid = stumpless_get_entry_procid( basic_entry );
    EXPECT_NOT_NULL( actual_procid );
    EXPECT_STREQ( ( const char * ) procid, actual_procid );
    free( ( void * ) actual_procid );

    msgid = sqlite3_column_text( result_stmt, 6 );
    EXPECT_NOT_NULL( msgid );
    actual_msgid = stumpless_get_entry_msgid( basic_entry );
    EXPECT_NOT_NULL( actual_msgid );
    EXPECT_STREQ( ( const char * ) msgid, actual_msgid );
    free( ( void * ) actual_msgid );

    structured_data = sqlite3_column_text( result_stmt, 7 );
    EXPECT_NOT_NULL( structured_data );
    EXPECT_STREQ( ( const char * ) structured_data, "-" );

    sqlite3_finalize( result_stmt );
    free( ( void * ) expected_message );
  }

  TEST_F( Sqlite3TargetTest, CustomPrepare ) {
    sqlite3 *db;
    struct test_prepare_data data;
    const struct stumpless_target *target_result;
    int add_result;
    int sql_result;
    const char *result_query = "SELECT prival, version, message FROM logs "
                               "WHERE message = ?;";
    sqlite3_stmt *result_stmt;
    int prival;
    int version;
    const unsigned char *message;

    db = ( sqlite3 * ) stumpless_get_sqlite3_db( target );
    ASSERT_NOT_NULL( db );
    EXPECT_NO_ERROR;

    data.target = target;
    data.insert_stmts[0] = NULL;
    data.insert_stmts[1] = NULL;
    target_result = stumpless_set_sqlite3_prepare( target, test_prepare, &data );
    ASSERT_EQ( target_result, target );
    EXPECT_NO_ERROR;

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    sql_result = sqlite3_prepare_v2( db, result_query, -1, &result_stmt, NULL );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_bind_text( result_stmt,
                                    1,
                                    "test-prepare-1",
                                    -1,
                                    SQLITE_STATIC );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_step( result_stmt );
    EXPECT_EQ( sql_result, SQLITE_ROW );

    prival = sqlite3_column_int( result_stmt, 0 );
    EXPECT_EQ( prival, 0 );

    version = sqlite3_column_int( result_stmt, 1 );
    EXPECT_EQ( version, 1 );

    message = sqlite3_column_text( result_stmt, 2 );
    EXPECT_NOT_NULL( message );
    EXPECT_STREQ( ( const char * ) message, "test-prepare-1" );

    sqlite3_reset( result_stmt );

    sql_result = sqlite3_bind_text( result_stmt,
                                    1,
                                    "test-prepare-2",
                                    -1,
                                    SQLITE_STATIC );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_step( result_stmt );
    EXPECT_EQ( sql_result, SQLITE_ROW );

    prival = sqlite3_column_int( result_stmt, 0 );
    EXPECT_EQ( prival, 0 );

    version = sqlite3_column_int( result_stmt, 1 );
    EXPECT_EQ( version, 1 );

    message = sqlite3_column_text( result_stmt, 2 );
    EXPECT_NOT_NULL( message );
    EXPECT_STREQ( ( const char * ) message, "test-prepare-2" );

    sqlite3_finalize( data.insert_stmts[0] );
    sqlite3_finalize( data.insert_stmts[1] );
    sqlite3_finalize( result_stmt );
  }

  TEST_F( Sqlite3TargetTest, DefaultInsertSql ) {
    const char *insert_sql;

    insert_sql = stumpless_get_sqlite3_insert_sql( target );
    EXPECT_NO_ERROR;
    ASSERT_STREQ( insert_sql, STUMPLESS_DEFAULT_SQLITE3_INSERT_SQL );
  }

  TEST_F( Sqlite3TargetTest, GetPrepare ) {
    stumpless_sqlite3_prepare_func_t result;
    void *data;

    result = stumpless_get_sqlite3_prepare( target , &data );
    EXPECT_EQ( result, stumpless_sqlite3_prepare );
    EXPECT_EQ( data, target->id );
    EXPECT_NO_ERROR;
  }

  TEST_F( Sqlite3TargetTest, GetPrepareNullData ) {
    stumpless_sqlite3_prepare_func_t result;

    result = stumpless_get_sqlite3_prepare( target , NULL );
    EXPECT_EQ( result, stumpless_sqlite3_prepare );
    EXPECT_NO_ERROR;
  }

  TEST_F( Sqlite3TargetTest, NullPreparer ) {
    const struct stumpless_target *result;
    const struct stumpless_error *error;

    result = stumpless_set_sqlite3_prepare( target, NULL, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
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
