// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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
#include <cstdio>
#include <cstring>
#include <fstream>
#include <regex>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"
#include "test/helper/rfc5424.hpp"

using::testing::HasSubstr;

namespace {

  static const size_t TEST_BUFFER_LENGTH = 8192;

  class
    TargetTest:
    public::testing::Test {
  protected:
    char buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *target = NULL;
    const char *target_name = "test-target";
    const char *default_app_name = "target-default-app-name";
    const char *default_msgid = "target-default-msgid";
    char plain_buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *plain_target = NULL;

    virtual void
    SetUp( void ) {
      target = stumpless_open_buffer_target( target_name,
                                             buffer,
                                             sizeof( buffer ) );

      stumpless_set_target_default_app_name( target, default_app_name );
      stumpless_set_target_default_msgid( target, default_msgid );

      plain_target = stumpless_open_buffer_target( "plain-target",
                                                   plain_buffer,
                                                   sizeof( plain_buffer ) );
    }

    virtual void
    TearDown( void ) {
      stumpless_close_buffer_target( target );
      stumpless_close_buffer_target( plain_target );

      stumpless_free_all(  );
    }
  };

  TEST_F( TargetTest, FilterReject ) {
    const char *message = "filter-reject-message";
    int result;

    ASSERT_NOT_NULL( target );

    memset( buffer, 0, sizeof( buffer ) );

    stumpless_set_target_mask( target, 0 );
    EXPECT_NO_ERROR;

    result = stumpless_add_message( target, message );
    EXPECT_EQ( result, 0 );

    EXPECT_THAT( buffer, Not( HasSubstr( message ) ) );
  }

  TEST_F( TargetTest, GetDefaultAppName ) {
    const char *result;

    result = stumpless_get_target_default_app_name( target );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );
    EXPECT_NE( result, default_app_name );
    EXPECT_STREQ( result, default_app_name );

    free( ( void * ) result );
  }

  TEST_F( TargetTest, GetDefaultAppNameMallocFailure ) {
    void * ( *set_malloc_result )( size_t );
    const char *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_get_target_default_app_name( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( TargetTest, GetDefaultAppNameNotSet ) {
    const char *result;

    result = stumpless_get_target_default_app_name( plain_target );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    EXPECT_STREQ( result, "-" );

    free( ( void * ) result );
  }

  TEST_F( TargetTest, GetDefaultMsgid ) {
    const char *result;

    result = stumpless_get_target_default_msgid( target );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );
    EXPECT_NE( result, default_msgid );
    EXPECT_STREQ( result, default_msgid );

    free( ( void * ) result );
  }

  TEST_F( TargetTest, GetDefaultMsgidMallocFailure ) {
    void * ( *set_malloc_result )( size_t );
    const char *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_get_target_default_msgid( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( TargetTest, GetDefaultMsgidNotSet ) {
    const char *result;

    result = stumpless_get_target_default_msgid( plain_target );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, "-" );

    free( ( void * ) result );
  }

  TEST_F( TargetTest, GetName ) {
    const char *name;

    name = stumpless_get_target_name( target );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( name );
    EXPECT_NE( name, target_name );
    EXPECT_STREQ( name, target_name );

    free( ( void * ) name );
  }

  TEST_F( TargetTest, GetNameMallocFailure ) {
    void * ( *set_malloc_result )( size_t );
    const char *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_get_target_name( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( TargetTest, TraceEntry ) {
    struct stumpless_entry *entry;
    const char *filename = "trace_entry_test.c";
    const char *function_name = "TargetTest.TraceEntry";
    int result;

    entry = create_entry(  );
    EXPECT_NO_ERROR;

    result = stumpless_trace_entry( target,
                                    entry,
                                    filename,
                                    377,
                                    function_name );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "line=\"377\"" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( TargetTest, TraceEntryLineZero ) {
    struct stumpless_entry *entry;
    const char *filename = "trace_entry_test.c";
    const char *function_name = "TargetTest.TraceEntry";
    int result;

    entry = create_entry(  );
    EXPECT_NO_ERROR;

    result = stumpless_trace_entry( target,
                                    entry,
                                    filename,
                                    0,
                                    function_name );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "line=\"0\"" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( TargetTest, TraceEntryMallocFailureOnFile ) {
    void * ( *set_malloc_result )( size_t );
    struct stumpless_entry *entry;
    const char *filename = "trace_entry_test_malloc_failure.c";
    const char *function_name = "TargetTest.TraceEntryMallocFailureOnFile";
    int result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 34 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    entry = create_entry(  );
    EXPECT_NO_ERROR;

    result = stumpless_trace_entry( target,
                                    entry,
                                    filename,
                                    377,
                                    function_name );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( TargetTest, TraceEntryMallocFailureOnFunction ) {
    void * ( *set_malloc_result )( size_t );
    struct stumpless_entry *entry;
    const char *filename = "trace_entry_test_malloc_failure.c";
    const char *function_name = "TargetTest.TraceEntryMallocFailureOnFunction";
    int result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 45 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    entry = create_entry(  );
    EXPECT_NO_ERROR;

    result = stumpless_trace_entry( target,
                                    entry,
                                    filename,
                                    377,
                                    function_name );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( TargetTest, TraceEntryNullFile ) {
    struct stumpless_entry *entry;
    const char *function_name = "TargetTest.TraceEntry";
    int result;

    entry = create_entry(  );
    EXPECT_NO_ERROR;

    result = stumpless_trace_entry( target,
                                    entry,
                                    NULL,
                                    377,
                                    function_name );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( TargetTest, TraceEntryNullFunction ) {
    struct stumpless_entry *entry;
    const char *filename = "trace_entry_test.c";
    int result;

    entry = create_entry(  );
    EXPECT_NO_ERROR;

    result = stumpless_trace_entry( target,
                                    entry,
                                    filename,
                                    377,
                                    NULL );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry_and_contents( entry );
  }

  /* non-fixture tests */

  TEST( AddEntryTest, NullEntry ) {
    int result;
    struct stumpless_target *target;
    char buffer[10];

    target = stumpless_open_buffer_target( "null entry testing",
                                           buffer,
                                           sizeof( buffer ) );

    result = stumpless_add_entry( target, NULL );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( AddEntryTest, NullTarget ) {
    int result;
    const struct stumpless_entry *entry;

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_add_entry( NULL, entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( AddEntryTest, UnsupportedType ) {
    struct stumpless_entry *entry;
    struct stumpless_target *target;
    int result;
    char buffer[10];

    target = stumpless_open_buffer_target( "unsupported type testing",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
    // assuming this isn't a valid type
    target->type = ( enum stumpless_target_type ) -1;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );
    ASSERT_NOT_NULL( entry );

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_BUFFER_TARGET;
    stumpless_close_buffer_target( target );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( AddLogStrTest, NullTarget ) {
    int priority;
    int result;

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    result = stumpless_add_log_str( NULL, priority , "test-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( AddLogTest, NullTarget ) {
    int priority;
    int result;

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    result = stumpless_add_log( NULL, priority , "test-message-%s", "null" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( AddMessageStrTest, NullTarget ) {
    int result;

    result = stumpless_add_message_str( NULL, "test-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( AddMessageTest, NullTarget ) {
    int result;

    result = stumpless_add_message( NULL, "test-message-%s", "null-target" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( AddMessageTest, ReallocFailure ) {
    char buffer[1000];
    struct stumpless_target *target;
    void *(*set_realloc_result)(void *, size_t);
    const char *long_message = "This message is longer than 128 characters, "
                               "which is the starting buffer size in the "
                               "format string function. If the call to realloc "
                               "fails when it tries to increase the buffer "
                               "size, then a memory allocation failure will be "
                               "raised.";
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    EXPECT_NOT_NULL( set_realloc_result );

    result = stumpless_add_message( target, long_message );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_realloc( realloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( AddMessageTest, SecondMemoryFailure ) {
    char buffer[1000];
    struct stumpless_target *target;
    void *(*set_malloc_result)(size_t);
    void *(*set_realloc_result)(void *, size_t);
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    result = stumpless_add_message( target, "test message" );
    EXPECT_GE( result, 0 );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    EXPECT_NOT_NULL( set_malloc_result );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    EXPECT_NOT_NULL( set_realloc_result );

    result = stumpless_add_message( target, "second test message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
    stumpless_set_realloc( realloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( CloseTarget, BadTargetType ) {
    struct stumpless_target target;

    target.type = ( enum stumpless_target_type ) -1; // assuming this is invalid

    stumpless_close_target( &target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    stumpless_free_all(  );
  }

  TEST( CloseTarget, NullTarget ) {

    stumpless_close_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( ConsoleStream, StdoutDefault ) {
	FILE *cons_stream = stumpless_get_cons_stream();
	EXPECT_TRUE( cons_stream == stdout );
    stumpless_free_all(  );
  }

  TEST( ConsoleStream, NullStream ) {
    FILE *cons_stream;
	stumpless_set_cons_stream( NULL );
	cons_stream = stumpless_get_cons_stream();
	EXPECT_TRUE( cons_stream == NULL );
    stumpless_free_all(  );
  }

  TEST( ConsoleStream, FileStream ) {
	const char *filename = "cons_stream.txt";
	FILE *file = fopen(filename, "w+");
    stumpless_set_cons_stream( file );
	EXPECT_TRUE( stumpless_get_cons_stream() == file );
	fclose( file );
    remove( filename );
    stumpless_free_all(  );
  }

  TEST( GetDefaultAppName, NullTarget ) {
    const char *result;

    result = stumpless_get_target_default_app_name( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetDefaultFacility, NullTarget ) {
    int facility;

    facility = stumpless_get_default_facility( NULL );
    EXPECT_EQ( -1, facility );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( GetDefaultMsgid, NullTarget ) {
    const char *result;

    result = stumpless_get_target_default_msgid( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetFilter, NullTarget ) {
    stumpless_filter_func_t result;

    result = stumpless_get_target_filter( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetMask, NullTarget ) {
    int result;

    result = stumpless_get_target_mask( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
    stumpless_free_all(  );
  }

  TEST( GetName, NullTarget ) {
    const char *result;

    result = stumpless_get_target_name( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetOption, NullTarget ) {
    int option;

    option = stumpless_get_option( NULL, STUMPLESS_OPTION_PID );
    EXPECT_EQ( option, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( GetDefaultOption, DefaultValue ) {
    int option;

    option = stumpless_get_default_options(  );
    EXPECT_EQ( option, STUMPLESS_OPTION_NDELAY );
  }

  TEST( OpenTarget, AlreadyOpenTarget ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    result = stumpless_open_target( target );
    EXPECT_NOT_NULL( result );
    EXPECT_NO_ERROR;

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( OpenTarget, MemoryFailureOnName ) {
    const char *target_name = "test-target-name-of-known-length";
    char buffer[100];
    struct stumpless_target *target;
    void *(*set_malloc_result)(size_t);

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 33 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    target = stumpless_open_buffer_target( target_name,
                                           buffer,
                                           sizeof( buffer ) );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
    stumpless_free_all(  );
  }

  TEST( OpenTarget, NullTarget ) {
    struct stumpless_target *target;

    target = stumpless_open_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( PerrorOption, FileErrorStream ) {
    char log_buffer[100];
    struct stumpless_target *target;
    const struct stumpless_target *target_result;
    const char *error_filename = "target_with_perror.log";
    FILE *error_stream;
    int result;
    size_t line_count;

    // set up the error stream
    error_stream = fopen( error_filename, "w+" );
    ASSERT_NOT_NULL( error_stream );

    stumpless_set_error_stream( error_stream );

    // set up the target to log to
    target = stumpless_open_buffer_target( "function-test-buffer-perror",
                                           log_buffer,
                                           sizeof( log_buffer) );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target_result );

    result = stumpless_add_message( target, "message with perror" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    // cleanup after the test
    stumpless_set_error_stream( stderr );
    fclose( error_stream );
    stumpless_close_buffer_target( target );
    EXPECT_NO_ERROR;

    // checking the perror file for consistency
    std::ifstream error_file( error_filename );
    std::string line;
    line_count = 0;
    while( std::getline( error_file, line ) ) {
      TestRFC5424Compliance( line.c_str() );
      line_count++;
    }
    EXPECT_EQ( line_count, 1 );

    stumpless_free_all(  );
    remove( error_filename );
  }

  TEST( PerrorOption, NullErrorStream ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[300];
    char message_buffer[300];
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    result = stumpless_add_message( target, "message without perror" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    TestRFC5424Compliance( message_buffer );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_NO_ERROR;
    EXPECT_EQ( target_result, target );

    stumpless_set_error_stream( NULL );
    result = stumpless_add_message( target,
                                    "message with perror and null stream" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    TestRFC5424Compliance( message_buffer );

    target_result = stumpless_unset_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_EQ( target_result, target );

    result = stumpless_add_message( target, "message without perror again" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    TestRFC5424Compliance( message_buffer );

    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultAppName, MemoryFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target_result = stumpless_set_target_default_app_name( target, "app-name" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( target_result, target );

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultAppName, NullName ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_target_default_app_name( target, NULL );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultAppName, NullTarget ) {
    struct stumpless_target *target_result;

    target_result = stumpless_set_target_default_app_name( NULL, "app-name" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetDefaultAppName, AppNameTargetRejected ) {
    char buffer[100];
    struct stumpless_target* target;
    struct stumpless_target* target_result;
    const char *app_name = "app-name-that-is-too-long-to-be-accepted-it-should-"
                           "be-rejected";

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_target_default_app_name( target, app_name );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultFacility, Local1 ) {
    char buffer[100];
    struct stumpless_target *target_result;
    struct stumpless_target *target;
    int current_facility;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_default_facility( target, STUMPLESS_FACILITY_LOCAL1 );
    EXPECT_EQ( target_result, target );
    EXPECT_NO_ERROR;

    current_facility = stumpless_get_default_facility( target );
    EXPECT_EQ( current_facility, STUMPLESS_FACILITY_LOCAL1 );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultFacility, NotDivisibleBy8 ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_default_facility( target, 3 );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultFacility, NullTarget ) {
    struct stumpless_target *target_result;

    target_result = stumpless_set_default_facility( NULL, STUMPLESS_FACILITY_USER );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetDefaultFacility, TooHigh ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_default_facility( target, 800 );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultFacility, TooLow ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_default_facility( target, -800 );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultMsgId, MemoryFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target_result = stumpless_set_target_default_msgid( target, "msgid" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( target_result, target );

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultMsgId, NullName ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_target_default_msgid( target, NULL );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultMsgId, NullTarget ) {
    struct stumpless_target *target_result;

    target_result = stumpless_set_target_default_msgid( NULL, "msgid" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( SetDefaultMsgId, MsgIdTargetRejected ) {
    char buffer[100];
    struct stumpless_target* target;
    struct stumpless_target* target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_target_default_msgid( target, "msgid-that-is-too-long-to-be-accepted" );
    ASSERT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultMsgId, MsgidSetTargetFormatRejected ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );


    target_result = stumpless_set_target_default_msgid( target, "msgid-wro\ng-format" );
    ASSERT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultAppName, AppNameSetTargetFormatRejected ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_target_default_app_name( target, "appname-wro\ng-format" );
    ASSERT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetFilter, AlwaysAccept ) {
    char buffer[100];
    struct stumpless_target *target;
    stumpless_filter_func_t first_filter;
    const struct stumpless_target *result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    first_filter = stumpless_get_target_filter( target );
    EXPECT_NOT_NULL( first_filter );

    result = stumpless_set_target_filter( target,
      []( const struct stumpless_target *target,
          const struct stumpless_entry *entry) -> bool { return true; } );
    EXPECT_EQ( result, target );
    EXPECT_NO_ERROR;

    EXPECT_NE( stumpless_get_target_filter( target ), first_filter );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetFilter, NullTarget ) {
    const struct stumpless_target *result;

    result = stumpless_set_target_filter( NULL, stumpless_mask_filter );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetMask, NullTarget ) {
    const struct stumpless_target *result;

    result = stumpless_set_target_mask( NULL, 0 );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetOption, Cons ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_CONS );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_CONS );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_CONS );
    EXPECT_TRUE( option );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetOption, NullTarget ) {
    const struct stumpless_target *result;

    result = stumpless_set_option( NULL, STUMPLESS_OPTION_PID );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetOption, Pid ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PID );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PID );
    EXPECT_TRUE( option );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetOption, Perror ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_TRUE( option );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetOption, Odelay ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_ODELAY );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_ODELAY );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_ODELAY );
    EXPECT_TRUE( option );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultOption, Odelay ) {
    struct stumpless_target *target;
    char buffer[100];
    int option;
    int default_options;

    default_options = stumpless_get_default_options(  );

    stumpless_set_default_options( STUMPLESS_OPTION_ODELAY );

    option = stumpless_get_default_options(  );
    ASSERT_EQ( option, STUMPLESS_OPTION_ODELAY );

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );

    option = stumpless_get_option( target, STUMPLESS_OPTION_ODELAY );
    EXPECT_TRUE( option );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );

    stumpless_set_default_options( default_options );
  }

  TEST( WithCons, ConsDisabled ) {
    struct stumpless_target *target;
    struct stumpless_entry *basic_entry;

    int result;

    const char *ro_filename = "cons-ro-stream.log";
    const char *cons_filename = "cons-stream.log";

    FILE *ro_stream;
    FILE *cons_stream;

    char buffer[300];
    // Ensure that the buffer is cleared
    memset( buffer, 0, 300 );

    // Create the temporary file, then open as read only
    ro_stream = fopen( ro_filename, "w+" );
    fclose( ro_stream );

    ro_stream = fopen( ro_filename, "r" );
    ASSERT_NOT_NULL( ro_stream );

    // Open fallback to capture output
    cons_stream = fopen( cons_filename, "w+" );
    ASSERT_NOT_NULL( cons_stream );

    // Use this to capture the fallback output
    stumpless_set_cons_stream( cons_stream );
    ASSERT_TRUE( cons_stream == stumpless_get_cons_stream( ) );

    target = stumpless_open_stream_target( ro_filename, ro_stream );
    ASSERT_NOT_NULL( target );

    basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       "stumpless-unit-test",
                                       "basic-entry",
                                       "STUMPLESS_OPTION_CONS::01" );
    ASSERT_NOT_NULL( basic_entry );
    result = stumpless_add_entry( target, basic_entry );

    // Expect the write to fail and underlying error preserved
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_STREAM_WRITE_FAILURE );

    // Confirm that we didn't write to the console stream
    ASSERT_NULL( fgets( buffer, 300, cons_stream ) );
    EXPECT_STREQ( buffer, "" );
    EXPECT_GT( feof( cons_stream ), 0 );

    stumpless_destroy_entry_and_contents( basic_entry );

    fclose( ro_stream );
    fclose( cons_stream );

    stumpless_close_stream_target( target );

    remove( ro_filename );
    remove( cons_filename );

    stumpless_free_all(  );
  }

  TEST( WithCons, ConsEnabled ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_entry *basic_entry;

    const char *message = "STUMPLESS_OPTION_CONS::enabled";
    char buffer[300];
    int result;

    const char *ro_filename = "cons-ro-stream.log";
    const char *cons_filename = "cons-stream.log";

    FILE *ro_stream;
    FILE *cons_stream;

    // Create the temporary file, then open as read only
    ro_stream = fopen( ro_filename, "w+" );
    fclose( ro_stream );

    ro_stream = fopen( ro_filename, "r" );
    ASSERT_NOT_NULL( ro_stream );

    cons_stream = fopen( cons_filename, "w+" );
    ASSERT_NOT_NULL( cons_stream );

    // Use this to capture the fallback output
    stumpless_set_cons_stream( cons_stream );
    ASSERT_TRUE( cons_stream == stumpless_get_cons_stream( ) );

    target = stumpless_open_stream_target( ro_filename, ro_stream );
    ASSERT_NOT_NULL( target );

    // Enable the CONS option, which will use the console stream as a
    // fallback if logging to the target failed
    target_result = stumpless_set_option( target, STUMPLESS_OPTION_CONS );
    EXPECT_EQ( target_result, target );

    basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       "stumpless-unit-test",
                                       "basic-entry",
                                       message );
    ASSERT_NOT_NULL( basic_entry );
    result = stumpless_add_entry( target, basic_entry );

    // Write should fail because the target is read only!
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_STREAM_WRITE_FAILURE );

    // Ensure that the buffer is cleared
    memset( buffer, 0, 300 );
    rewind( cons_stream );

    // Confirm that the cons_stream is not empty
    ASSERT_NOT_NULL( fgets( buffer, 300, cons_stream ) );
    EXPECT_THAT( buffer, HasSubstr( message ) );
    EXPECT_EQ( feof( cons_stream ), 0 );

    stumpless_destroy_entry_and_contents( basic_entry );

    fclose( ro_stream );

    stumpless_close_stream_target( target );

    remove( ro_filename );
    remove( cons_filename );

    stumpless_free_all(  );
  }

  TEST( WithCons, ConsNull ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_entry *basic_entry;

    const char *message = "STUMPLESS_OPTION_CONS::null";
    const char *ro_filename = "cons-ro-stream.log";
    int result;

    FILE *ro_stream;

    // Create the temporary file, then open as read only
    ro_stream = fopen( ro_filename, "w+" );
    fclose( ro_stream );

    ro_stream = fopen( ro_filename, "r" );
    ASSERT_NOT_NULL( ro_stream );

    // Use this to capture the fallback output
    stumpless_set_cons_stream( NULL );

    target = stumpless_open_stream_target( ro_filename, ro_stream );
    ASSERT_NOT_NULL( target );

    // Enable the CONS option, which will use the console stream as a
    // fallback if logging to the target failed
    target_result = stumpless_set_option( target, STUMPLESS_OPTION_CONS );
    EXPECT_EQ( target_result, target );

    basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       "stumpless-unit-test",
                                       "basic-entry",
                                       message );
    ASSERT_NOT_NULL( basic_entry );
    result = stumpless_add_entry( target, basic_entry );

    // Write should fail because the target is read only!
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_STREAM_WRITE_FAILURE );

    // Confirm that our custom console is null (but did not segfault)
    ASSERT_NULL( stumpless_get_cons_stream( ) );

    stumpless_close_stream_target( target );
    stumpless_destroy_entry_and_contents( basic_entry );

    fclose( ro_stream );
    remove( ro_filename );

    stumpless_free_all(  );
  }

  TEST( WithPid, Pid) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[300];
    char message_buffer[300];
    int result;
    std::cmatch matches;
    std::regex pid_regex(RFC_5424_REGEX_STRING);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    result = stump( "test message" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    if( !std::regex_match( message_buffer, matches, pid_regex ) ) {
      FAIL(  ) << "produced invalid procid";
    } else {
      EXPECT_EQ( matches[RFC_5424_PROCID_MATCH_INDEX], '-' );
    }

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    result = stump( "test message 1" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    if( !std::regex_match( message_buffer, matches, pid_regex ) ) {
      FAIL(  ) << "produced invalid procid";
    } else {
      EXPECT_NE( matches[RFC_5424_PROCID_MATCH_INDEX], '-' );
    }

    target_result = stumpless_unset_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    result = stump( "test message 2" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    if( !std::regex_match( message_buffer, matches, pid_regex ) ) {
      FAIL(  ) << "produced invalid procid";
    } else {
      EXPECT_EQ( matches[RFC_5424_PROCID_MATCH_INDEX], '-' );
    }

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( WithPerror, Perror) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[300];
    char message_buffer[300];
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    result = stump( "test message without perror" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    TestRFC5424Compliance( message_buffer );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_EQ( target_result, target );

    result = stump( "test message with perror" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    TestRFC5424Compliance( message_buffer );
    target_result = stumpless_unset_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_EQ( target_result, target );

    result = stump( "test message without perror 2" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    stumpless_read_buffer( target, message_buffer, 300 );
    TestRFC5424Compliance( message_buffer );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( TraceEntryTest, MallocFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    void *(*set_malloc_result)(size_t);
    int result;

    target = stumpless_open_buffer_target( "trace-fail-target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    entry = create_entry(  );
    EXPECT_NOT_NULL( entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    EXPECT_NOT_NULL( set_malloc_result );

    result = stumpless_trace_entry( target,
                                    entry,
                                    __FILE__,
                                    __LINE__,
                                    __func__ );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_buffer_target( target );
    stumpless_set_malloc( malloc );
    stumpless_free_all(  );
  }

  TEST( TraceEntryTest, NullEntry ) {
    int result;
    struct stumpless_target *target;
    char buffer[10];

    target = stumpless_open_buffer_target( "null entry testing",
                                           buffer,
                                           sizeof( buffer ) );

    result = stumpless_trace_entry( target,
                                    NULL,
                                    __FILE__,
                                    __LINE__,
                                    __func__ );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( TraceEntryTest, NullTarget ) {
    int result;
    struct stumpless_entry *entry;

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_trace_entry( NULL,
                                    entry,
                                    __FILE__,
                                    __LINE__,
                                    __func__ );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( TraceLogStrTest, NullTarget ) {
    int priority;
    int result;

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    result = stumpless_trace_log_str( NULL,
                                      priority,
                                      __FILE__,
                                      __LINE__,
                                      __func__,
                                      "test-trace-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( TraceLogTest, NullTarget ) {
    int priority;
    int result;

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    result = stumpless_trace_log( NULL,
                                  priority,
                                  __FILE__,
                                  __LINE__,
                                  __func__,
                                  "test-trace-message-%s",
                                  "null-target" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( TraceMessageStrTest, NullTarget ) {
    int result;

    result = stumpless_trace_message_str( NULL,
                                          __FILE__,
                                          __LINE__,
                                          __func__,
                                          "test-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( TraceMessageTest, NullTarget ) {
    int result;

    result = stumpless_trace_message( NULL,
                                      __FILE__,
                                      __LINE__,
                                      __func__,
                                      "test-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( TraceMessageTest, ReallocFailure ) {
    char buffer[1000];
    struct stumpless_target *target;
    void *(*set_realloc_result)(void *, size_t);
    const char *long_message = "This message is longer than 128 characters, "
                               "which is the starting buffer size in the "
                               "format string function. If the call to realloc "
                               "fails when it tries to increase the buffer "
                               "size, then a memory allocation failure will be "
                               "raised.";
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    set_realloc_result = stumpless_set_realloc( [](void *ptr, size_t size)->void *{ return NULL; } );
    EXPECT_NOT_NULL( set_realloc_result );

    result = stumpless_trace_message( target,
                                      __FILE__,
                                      __LINE__,
                                      __func__,
                                      long_message );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_realloc( realloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( TraceMessageTest, SecondMemoryFailure ) {
    char buffer[1000];
    struct stumpless_target *target;
    void *(*set_malloc_result)(size_t);
    void *(*set_realloc_result)(void *, size_t);
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    result = stumpless_trace_message( target,
                                      __FILE__,
                                      __LINE__,
                                      __func__,
                                      "test trace message" );
    EXPECT_GE( result, 0 );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    EXPECT_NOT_NULL( set_malloc_result );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    EXPECT_NOT_NULL( set_realloc_result );

    result = stumpless_trace_message( target,
                                      __FILE__,
                                      __LINE__,
                                      __func__,
                                      "second test trace message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
    stumpless_set_realloc( realloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( UnsetOption, NullTarget ) {
    const struct stumpless_target *result;

    result = stumpless_unset_option( NULL, STUMPLESS_OPTION_PID );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( UnsetOption, Pid ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PID );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PID );
    EXPECT_TRUE( option );

    target_result = stumpless_unset_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PID );
    EXPECT_FALSE( option );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( UnsetOption, Perror ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_TRUE( option );

    target_result = stumpless_unset_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_FALSE( option );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( GetTargetString, EachValidTarget ) {
    const char *result;

    #define CHECK_TARGET( STRING, ENUM ) \
      result = stumpless_get_target_type_string( STRING ); \
      EXPECT_STREQ( result, #STRING );
    STUMPLESS_FOREACH_TARGET_TYPE( CHECK_TARGET )
  }
  
  TEST( GetTargetString, NoSuchTarget ) {
    int target_count = 0;
    const char *result;

    #define COUNT_TARGET( STRING, ENUM ) ++target_count;
    STUMPLESS_FOREACH_TARGET_TYPE( COUNT_TARGET )

    stumpless_target_type wrong_target =
        static_cast<stumpless_target_type>(target_count + 1);

    result = stumpless_get_target_type_string( wrong_target );
    EXPECT_STREQ( result, "NO_SUCH_TARGET_TYPE" );
  }
}
