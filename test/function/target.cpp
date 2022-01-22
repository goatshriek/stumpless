// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2021 Joel E. Anderson
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
#include <regex>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
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
    struct stumpless_target *target;
    const char *target_name = "test-target";
    const char *default_app_name = "target-default-app-name";
    const char *default_msgid = "target-default-msgid";
    char plain_buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *plain_target;

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
    const struct stumpless_error *error;

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
    EXPECT_NULL( result );
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
    const struct stumpless_error *error;

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
    EXPECT_NULL( result );
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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;
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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;
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

  TEST( AddLogTest, NullTarget ) {
    int priority;
    int result;
    const struct stumpless_error *error;

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    result = stumpless_add_log( NULL, priority , "test-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( AddMessageTest, NullTarget ) {
    int result;
    const struct stumpless_error *error;

    result = stumpless_add_message( NULL, "test-message" );
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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

    target.type = ( enum stumpless_target_type ) -1; // assuming this is invalid

    stumpless_close_target( &target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
    stumpless_free_all(  );
  }

  TEST( CloseTarget, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( ConsoleStream, StdoutDefault ) {
	FILE *cons_stream = stumpless_get_cons_stream();
	EXPECT_TRUE( cons_stream == stdout);
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
    stumpless_free_all(  );
  }

  TEST( GetDefaultAppName, NullTarget ) {
    const struct stumpless_error *error;
    const char *result;

    result = stumpless_get_target_default_app_name( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetDefaultFacility, NullTarget ) {
    const struct stumpless_error *error;
    int facility;

    facility = stumpless_get_default_facility( NULL );
    EXPECT_EQ( -1, facility );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( GetDefaultMsgid, NullTarget ) {
    const struct stumpless_error *error;
    const char *result;

    result = stumpless_get_target_default_msgid( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetFilter, NullTarget ) {
    const struct stumpless_error *error;
    stumpless_filter_func_t result;

    result = stumpless_get_target_filter( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetMask, NullTarget ) {
    const struct stumpless_error *error;
    int result;

    result = stumpless_get_target_mask( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
    stumpless_free_all(  );
  }

  TEST( GetName, NullTarget ) {
    const struct stumpless_error *error;
    const char *result;

    result = stumpless_get_target_name( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
    stumpless_free_all(  );
  }

  TEST( GetOption, NullTarget ) {
    const struct stumpless_error *error;
    int option;

    option = stumpless_get_option( NULL, STUMPLESS_OPTION_PID );
    EXPECT_EQ( option, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( OpenTarget, AlreadyOpenTarget ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    result = stumpless_open_target( target );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( OpenTarget, MemoryFailureOnName ) {
    const char *target_name = "test-target-name-of-known-length";
    char buffer[100];
    struct stumpless_target *target;
    const struct stumpless_error *error;
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
    const struct stumpless_error *error;

    target = stumpless_open_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetDefaultAppName, MemoryFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
   
    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target_result = stumpless_set_target_default_app_name( target, "app-name" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultAppName, NullName ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error* error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

    target_result = stumpless_set_default_facility( NULL, STUMPLESS_FACILITY_USER );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetDefaultFacility, TooHigh ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
   
    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target_result = stumpless_set_target_default_msgid( target, "msgid" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( SetDefaultMsgId, NullName ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

    target_result = stumpless_set_target_default_msgid( NULL, "msgid" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( SetDefaultMsgId, MsgIdTargetRejected ) {
    char buffer[100];
    struct stumpless_target* target;
    struct stumpless_target* target_result;
    const struct stumpless_error* error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;
    const struct stumpless_target *result;

    result = stumpless_set_target_filter( NULL, stumpless_mask_filter );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetMask, NullTarget ) {
    const struct stumpless_error *error;
    const struct stumpless_target *result;

    result = stumpless_set_target_mask( NULL, 0 );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( SetOption, NullTarget ) {
    const struct stumpless_error *error;
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
    ASSERT_TRUE( target != NULL );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PERROR );
    EXPECT_TRUE( option );

    stumpless_close_buffer_target( target );
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
    ASSERT_TRUE( target != NULL );

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
    ASSERT_TRUE( target != NULL );

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


  TEST( Stump, Basic ) {
    char buffer[1000];
    struct stumpless_target *target;
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
    ASSERT_TRUE( stumpless_get_current_target(  ) == target );

    result = stump( "test message" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( StumpTrace, Basic ) {
    char buffer[1000];
    struct stumpless_target *target;
    const char *filename = "fake_file.c";
    const char *function_name = "fake_function";
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
    ASSERT_TRUE( stumpless_get_current_target(  ) == target );

    result = stump_trace( filename, 377, function_name, "test message" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "377" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( StumpTrace, WithPreprocessorMacros ) {
    char buffer[1000];
    struct stumpless_target *target;
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );
    ASSERT_TRUE( stumpless_get_current_target(  ) == target );

    result = stump_trace( __FILE__, __LINE__, __func__, "test message" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( Stumplog, Basic ) {
    char buffer[1000];
    struct stumpless_target *target;
    int priority;

    buffer[0] = '\0';
    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_TRUE( target != NULL );

    ASSERT_TRUE( stumpless_get_current_target(  ) == target );

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    stumplog( priority, "test message" );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( StumplogTrace, Basic ) {
    char buffer[1000];
    struct stumpless_target *target;
    int priority;
    const char *filename = "stumplog-trace-file.c";
    const char *function_name = "StumplogTrace.Basic";

    buffer[0] = '\0';
    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_TRUE( target != NULL );

    ASSERT_TRUE( stumpless_get_current_target(  ) == target );

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    stumplog_trace( priority, filename, 377, function_name, "test message" );

    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "line=\"377\"" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );

    stumpless_close_buffer_target( target );
    stumpless_free_all(  );
  }

  TEST( TraceEntryTest, MallocFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    void *(*set_malloc_result)(size_t);
    int result;
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;
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
    const struct stumpless_error *error;

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

  TEST( TraceLogTest, NullTarget ) {
    int priority;
    int result;
    const struct stumpless_error *error;

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    result = stumpless_trace_log( NULL,
                                  priority,
                                  __FILE__,
                                  __LINE__,
                                  __func__,
                                  "test-trace-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( TraceMessageTest, NullTarget ) {
    int result;
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;

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
    const struct stumpless_error *error;
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
    ASSERT_TRUE( target != NULL );

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
}
