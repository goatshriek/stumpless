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
#include <cstdlib>
#include <gtest/gtest.h>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"
#include "test/helper/rfc5424.hpp"

struct test_prepare_data {
  struct stumpless_target *target;
  sqlite3_stmt *insert_stmts[2];
};

static
void *
failing_prepare( const struct stumpless_entry *entry,
                 void *data,
                 size_t *count ) {
  return NULL;
}

static
void *
test_prepare( const struct stumpless_entry *entry, void *data, size_t *count ) {
  const char *insert_sql = "INSERT INTO "
                              STUMPLESS_DEFAULT_SQLITE3_TABLE_NAME_STRING
                           "  (prival, version, message) "
                           "VALUES (0, 1, ?)";
  int sql_result;
  struct test_prepare_data *test_data = ( struct test_prepare_data * ) data;
  sqlite3 *db = ( sqlite3 * ) stumpless_get_sqlite3_db( test_data->target );

  if( !test_data->insert_stmts[0] ) {
    sql_result = sqlite3_prepare_v2( db,
                                     insert_sql,
                                     -1,
                                     &test_data->insert_stmts[0],
                                     NULL );
    if( sql_result != SQLITE_OK ) {
      return NULL;
    }
  } else {
    sqlite3_reset( test_data->insert_stmts[0] );
  }

  if( !test_data->insert_stmts[1] ) {
    sql_result = sqlite3_prepare_v2( db,
                                     insert_sql,
                                     -1,
                                     &test_data->insert_stmts[1],
                                     NULL );
    if( sql_result != SQLITE_OK ) {
      return NULL;
    }
  } else {
    sqlite3_reset( test_data->insert_stmts[1] );
  }

  sql_result = sqlite3_bind_text( test_data->insert_stmts[0],
                                  1,
                                  "test-prepare-1",
                                  -1,
                                  SQLITE_STATIC );
  if( sql_result != SQLITE_OK ) {
    return NULL;
  }

  sql_result = sqlite3_bind_text( test_data->insert_stmts[1],
                                  1,
                                  "test-prepare-2",
                                  -1,
                                  SQLITE_STATIC );
  if( sql_result != SQLITE_OK ) {
    return NULL;
  }

  *count = 2;
  return &test_data->insert_stmts;
}

static
void
TestEntryInDatabase( std::string const &db_name,
                     std::string const &table_name,
                     const struct stumpless_entry *entry ) {
  sqlite3 *db;
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
  const char *structured_data;
  std::string const sd;

  std::ostringstream query_stream;
  query_stream << "SELECT prival, version, timestamp, hostname,"
                  "  app_name, procid, msgid, structured_data,"
                  "  message "
                  "FROM " << table_name;

  expected_message = stumpless_get_entry_message( entry );
  if( expected_message ) {
    query_stream << " WHERE message = ?";
  } else {
    query_stream << " WHERE message IS NULL";
  }
  std::string result_query = query_stream.str();

  sql_result = sqlite3_open_v2( db_name.c_str(),
                                &db,
                                SQLITE_OPEN_READONLY,
                                NULL );
  ASSERT_EQ( sql_result, SQLITE_OK );

  sql_result = sqlite3_prepare_v2( db,
                                   result_query.c_str(),
                                   -1,
                                   &result_stmt,
                                   NULL );
  EXPECT_EQ( sql_result, SQLITE_OK );

  if( expected_message ) {
    sql_result = sqlite3_bind_text( result_stmt,
                                    1,
                                    expected_message,
                                    -1,
                                    SQLITE_STATIC );
    EXPECT_EQ( sql_result, SQLITE_OK );
  }

  sql_result = sqlite3_step( result_stmt );
  EXPECT_EQ( sql_result, SQLITE_ROW );

  actual_prival = sqlite3_column_int( result_stmt, 0 );
  expected_prival = stumpless_get_entry_prival( entry );
  EXPECT_EQ( actual_prival, expected_prival );

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
  actual_hostname = stumpless_get_entry_hostname( entry );
  EXPECT_NOT_NULL( actual_hostname );
  EXPECT_STREQ( ( const char * ) hostname, actual_hostname );
  free( ( void * ) actual_hostname );

  app_name = sqlite3_column_text( result_stmt, 4 );
  if( !app_name ) {
    app_name = ( const unsigned char * ) "-";
  }
  actual_app_name = stumpless_get_entry_app_name( entry );
  EXPECT_NOT_NULL( actual_app_name );
  EXPECT_STREQ( ( const char * ) app_name, actual_app_name );
  free( ( void * ) actual_app_name );

  procid = sqlite3_column_text( result_stmt, 5 );
  if( !procid ) {
    procid = ( const unsigned char * ) "-";
  }
  actual_procid = stumpless_get_entry_procid( entry );
  EXPECT_NOT_NULL( actual_procid );
  EXPECT_STREQ( ( const char * ) procid, actual_procid );
  free( ( void * ) actual_procid );

  msgid = sqlite3_column_text( result_stmt, 6 );
  if( !msgid ) {
    msgid = ( const unsigned char * ) "-";
  }
  actual_msgid = stumpless_get_entry_msgid( entry );
  EXPECT_NOT_NULL( actual_msgid );
  EXPECT_STREQ( ( const char * ) msgid, actual_msgid );
  free( ( void * ) actual_msgid );

  structured_data = ( const char * ) sqlite3_column_text( result_stmt, 7 );
  if( !structured_data ) {
    structured_data = "-";
  }
  TestRFC5424StructuredData( structured_data );

  sqlite3_finalize( result_stmt );
  free( ( void * ) expected_message );
  sql_result = sqlite3_close_v2( db );
  EXPECT_EQ( sql_result, SQLITE_OK );
}

namespace {
  class Sqlite3TargetTest : public::testing::Test {
    protected:
      sqlite3 *db = NULL;
      const char *db_filename = "test_function_fixture.sqlite3";
      struct stumpless_target *target = NULL;
      struct stumpless_entry *basic_entry = NULL;
      struct stumpless_entry *empty_entry = NULL;

    virtual void
    SetUp( void ) {
      target = stumpless_open_sqlite3_target( db_filename );

      stumpless_create_default_sqlite3_table( target );

      stumpless_set_target_default_app_name( target, "sqlite3-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = create_entry();
      empty_entry = create_empty_entry();

      db = ( sqlite3 * ) stumpless_get_sqlite3_db( target );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_destroy_entry_only( empty_entry );
      stumpless_close_sqlite3_target_and_db( target );
      stumpless_free_all();
      remove( db_filename );
    }
  };

  TEST_F( Sqlite3TargetTest, AddBasicEntry ) {
    int add_result;

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    TestEntryInDatabase( std::string( db_filename ), "logs", basic_entry );
  }

  TEST_F( Sqlite3TargetTest, AddNullFieldEntry ) {
    struct stumpless_entry *entry;
    int add_result;

    entry = create_nil_entry();

    add_result = stumpless_add_entry( target, entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    TestEntryInDatabase( std::string( db_filename ), "logs", entry );
    stumpless_destroy_entry_only( entry );
  }

  TEST_F( Sqlite3TargetTest, AddTwoEntries ) {
    int add_result;

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    add_result = stumpless_add_entry( target, empty_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    TestEntryInDatabase( std::string( db_filename ), "logs", basic_entry );
    TestEntryInDatabase( std::string( db_filename ), "logs", empty_entry );
  }

  TEST_F( Sqlite3TargetTest, FailedPrepare ) {
    const struct stumpless_target *set_result;
    int add_result;
    const struct stumpless_error *error;

    set_result = stumpless_set_sqlite3_prepare( target, failing_prepare, NULL );
    ASSERT_EQ( set_result, target );
    EXPECT_NO_ERROR;

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_LT( add_result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_SQLITE3_CALLBACK_FAILURE );
  }

  TEST_F( Sqlite3TargetTest, CustomHardcodedInsert ) {
    const struct stumpless_target *set_result;
    const char *insert_sql = "INSERT INTO logs (prival, version, message) "
                             "VALUES (0, 1, 'hardcoded')";
    const char *current_sql;
    int add_result;
    const char *result_query = "SELECT prival, version, message "
                               "FROM logs WHERE message = 'hardcoded'";
    sqlite3_stmt *result_stmt;
    int sql_result;
    int prival;
    int version;

    set_result = stumpless_set_sqlite3_insert_sql( target, insert_sql );
    ASSERT_EQ( set_result, target );

    current_sql = stumpless_get_sqlite3_insert_sql( target );
    ASSERT_EQ( current_sql, insert_sql );

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    sql_result = sqlite3_prepare_v2( db, result_query, -1, &result_stmt, NULL );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_step( result_stmt );
    EXPECT_EQ( sql_result, SQLITE_ROW );

    prival = sqlite3_column_int( result_stmt, 0 );
    EXPECT_EQ( prival, 0 );

    version = sqlite3_column_int( result_stmt, 1 );
    EXPECT_EQ( version, 1 );

    sqlite3_finalize( result_stmt );
  }

  TEST_F( Sqlite3TargetTest, CustomPrepare ) {
    struct test_prepare_data data;
    const struct stumpless_target *target_result;
    int add_result;
    int sql_result;
    const char *result_query = "SELECT prival, version, message FROM logs "
                               "WHERE message = ?";
    sqlite3_stmt *result_stmt;
    int prival;
    int version;
    const unsigned char *message;

    data.target = target;
    data.insert_stmts[0] = NULL;
    data.insert_stmts[1] = NULL;
    target_result = stumpless_set_sqlite3_prepare( target,
                                                   test_prepare,
                                                   &data );
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

  TEST_F( Sqlite3TargetTest, CustomTableInsert ) {
    const char *create_sql = "CREATE TABLE l (log_id INTEGER PRIMARY KEY, "
                                             "prival INTEGER NOT NULL, "
                                             "version INTEGER NOT NULL, "
                                             "timestamp TEXT, "
                                             "hostname TEXT, "
                                             "app_name TEXT, "
                                             "procid TEXT, "
                                             "msgid TEXT, "
                                             "structured_data TEXT, "
                                             "message TEXT)";
    sqlite3_stmt *create_stmt = NULL;
    int sql_result;
    const char *insert_sql = "INSERT INTO l ( prival, version, timestamp,"
                             "                hostname, app_name, procid,"
                             "                msgid, structured_data,"
                             "                message ) "
                             "VALUES ( $prival, 1, $timestamp, $hostname,"
                             "         $app_name, $procid, $msgid, '-',"
                             "         $message )";
    const struct stumpless_target *result;
    const char *current_sql;
    int add_result;

    sql_result = sqlite3_prepare_v2( db, create_sql, -1, &create_stmt, NULL );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_step( create_stmt );
    EXPECT_EQ( sql_result, SQLITE_DONE );

    result = stumpless_set_sqlite3_insert_sql( target, insert_sql );
    ASSERT_EQ( result, target );

    current_sql = stumpless_get_sqlite3_insert_sql( target );
    ASSERT_EQ( current_sql, insert_sql );

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    TestEntryInDatabase( std::string( db_filename ), "l", basic_entry );

    sqlite3_finalize( create_stmt );
  }

  TEST_F( Sqlite3TargetTest, DefaultInsertSql ) {
    const char *insert_sql;

    insert_sql = stumpless_get_sqlite3_insert_sql( target );
    EXPECT_NO_ERROR;
    ASSERT_STREQ( insert_sql, STUMPLESS_DEFAULT_SQLITE3_INSERT_SQL );
  }

  TEST_F( Sqlite3TargetTest, DefaultTableAlreadyExists ) {
    const struct stumpless_target *result;
    const struct stumpless_error *error;

    result = stumpless_create_default_sqlite3_table( target );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_SQLITE3_FAILURE );
  }

  TEST_F( Sqlite3TargetTest, FacilityAndSeverityParameters ) {
    const char *create_sql = "CREATE TABLE priorities"
                             "( log_id INTEGER PRIMARY KEY,"
                             "  prival INTEGER NOT NULL,"
                             "  facility INTEGER NOT NULL,"
                             "  severity INTEGER NOT NULL,"
                             "  message TEXT )";
    sqlite3_stmt *create_stmt = NULL;
    int sql_result;
    const char *insert_sql = "INSERT INTO priorities (prival, facility,"
                             "  severity, message) "
                             "VALUES ($prival, $facility, $severity,"
                             "  'hardcoded')";
    const struct stumpless_target *result;
    const char *current_sql;
    int add_result;
    const char *result_query = "SELECT prival, facility, severity "
                               "FROM priorities WHERE message = 'hardcoded'";
    sqlite3_stmt *result_stmt = NULL;
    int prival;
    int facility;
    int severity;

    sql_result = sqlite3_prepare_v2( db, create_sql, -1, &create_stmt, NULL );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_step( create_stmt );
    EXPECT_EQ( sql_result, SQLITE_DONE );

    result = stumpless_set_sqlite3_insert_sql( target, insert_sql );
    ASSERT_EQ( result, target );

    current_sql = stumpless_get_sqlite3_insert_sql( target );
    ASSERT_EQ( current_sql, insert_sql );

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( add_result, 0 );
    EXPECT_NO_ERROR;

    sql_result = sqlite3_prepare_v2( db, result_query, -1, &result_stmt, NULL );
    EXPECT_EQ( sql_result, SQLITE_OK );

    sql_result = sqlite3_step( result_stmt );
    EXPECT_EQ( sql_result, SQLITE_ROW );

    prival = sqlite3_column_int( result_stmt, 0 );
    EXPECT_EQ( prival, stumpless_get_entry_prival( basic_entry ) );

    facility = sqlite3_column_int( result_stmt, 1 );
    EXPECT_EQ( facility, stumpless_get_entry_facility( basic_entry ) );

    severity = sqlite3_column_int( result_stmt, 2 );
    EXPECT_EQ( severity, stumpless_get_entry_severity( basic_entry ) );

    sqlite3_finalize( create_stmt );
    sqlite3_finalize( result_stmt );
  }

  TEST_F( Sqlite3TargetTest, GetPrepareWithAndWithoutNull ) {
    stumpless_sqlite3_prepare_func_t non_null_result;
    stumpless_sqlite3_prepare_func_t null_result;
    void *data;

    non_null_result = stumpless_get_sqlite3_prepare( target , &data );
    EXPECT_EQ( data, target->id );
    EXPECT_NO_ERROR;

    null_result = stumpless_get_sqlite3_prepare( target , NULL );
    EXPECT_EQ( null_result, non_null_result );
  }

  TEST_F( Sqlite3TargetTest, InvalidInsertSql ) {
    const struct stumpless_target *set_result;
    const char *bad_sql = "this isn't valid sql";
    const char *current_sql;
    int add_result;
    const struct stumpless_error *error;

    set_result = stumpless_set_sqlite3_insert_sql( target, bad_sql );
    ASSERT_EQ( set_result, target );

    current_sql = stumpless_get_sqlite3_insert_sql( target );
    ASSERT_EQ( current_sql, bad_sql );

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_LT( add_result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_SQLITE3_FAILURE );
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

  TEST( Sqlite3TargetCloseDbTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_sqlite3_target_and_db( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all();
  }

  TEST( Sqlite3TargetCloseDbTest, WrongTargetType ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-file-target" );

    stumpless_close_sqlite3_target_and_db( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
    stumpless_free_all();
  }

  TEST( Sqlite3TargetCloseTargetOnlyTest, General ) {
    sqlite3 *db;
    int sql_result;
    struct stumpless_target *target;

    sql_result = sqlite3_open_v2( "close_target_only_test.sqlite3",
                                  &db,
                                  SQLITE_OPEN_READWRITE | SQLITE_OPEN_MEMORY,
                                  NULL );
    ASSERT_EQ( sql_result, SQLITE_OK );

    target = stumpless_open_sqlite3_target_from_db( db );
    EXPECT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    stumpless_close_sqlite3_target_only( target );
    EXPECT_NO_ERROR;

    sqlite3_close( db );
    stumpless_free_all();
  }

  TEST( Sqlite3TargetCloseTargetOnlyTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_sqlite3_target_only( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all();
  }

  TEST( Sqlite3TargetCloseTargetOnlyTest, WrongTargetType ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-file-target" );

    stumpless_close_sqlite3_target_only( target );
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

    stumpless_close_sqlite3_target_and_db( target );
    stumpless_free_all();
    remove( db_filename );
  }

  TEST( Sqlite3TargetGetDbTest, WrongTargetType ) {
    void *result;
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-file-target" );

    result = stumpless_get_sqlite3_db( target );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
    stumpless_free_all();
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

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
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

  TEST( Sqlite3TargetOpenDbTest, MallocFailure ) {
    const char *db_filename = "malloc_fail_on_open.sqlite3";
    sqlite3 *db = NULL;
    int sql_result;
    struct stumpless_target *target;
    const struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    sql_result = sqlite3_open_v2( db_filename,
                                  &db,
                                  SQLITE_OPEN_READWRITE | SQLITE_OPEN_MEMORY,
                                  NULL );
    ASSERT_EQ( sql_result, SQLITE_OK );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target = stumpless_open_sqlite3_target_from_db( db );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
    stumpless_free_all();
    sqlite3_close( db );
  }

  TEST( Sqlite3TargetOpenDbTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_sqlite3_target_from_db( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all();
  }
}
