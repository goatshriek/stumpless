// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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
#include <regex>
#include <string.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "private/target/buffer.h"
#include "test/function/rfc5424.hpp"
#include "test/helper/assert.hpp"
#include "test/helper/memory_allocation.hpp"

using::testing::HasSubstr;

namespace {

  TEST( AddEntryTest, NullEntry ) {
    int result;
    struct stumpless_target *target;
    const struct stumpless_error *error;
    char buffer[10];

    target = stumpless_open_buffer_target( "null entry testing",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );

    result = stumpless_add_entry( target, NULL );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
  }

  TEST( AddEntryTest, NullTarget ) {
    int result;
    struct stumpless_entry *entry;
    const struct stumpless_error *error;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );

    result = stumpless_add_entry( NULL, entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry( entry );
  }

  TEST( AddEntryTest, UnsupportedType ) {
    struct stumpless_entry *entry;
    const struct stumpless_error *error;
    struct stumpless_target *target;
    int result;
    char buffer[10];

    target = stumpless_open_buffer_target( "unsupported type testing",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );
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

    stumpless_close_buffer_target( target );
    stumpless_destroy_entry( entry );
  }

  TEST( AddLogTest, NullTarget ) {
    int priority;
    int result;
    const struct stumpless_error *error;

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    result = stumpless_add_log( NULL, priority , "test-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( AddMessageTest, NullTarget ) {
    int result;
    const struct stumpless_error *error;

    result = stumpless_add_message( NULL, "test-message" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
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
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    set_realloc_result = stumpless_set_realloc( [](void *ptr, size_t size)->void *{ return NULL; } );
    EXPECT_NOT_NULL( set_realloc_result );

    result = stumpless_add_message( target, long_message );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_realloc( realloc );
    stumpless_close_buffer_target( target );
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
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
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
  }

  TEST( CloseTarget, BadTargetType ) {
    struct stumpless_target target;
    const struct stumpless_error *error;

    target.type = ( enum stumpless_target_type ) -1; // assuming this is invalid

    stumpless_close_target( &target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );
  }

  TEST( CloseTarget, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( GetDefaultFacility, NullTarget ) {
    const struct stumpless_error *error;
    int facility;

    facility = stumpless_get_default_facility( NULL );
    EXPECT_EQ( -1, facility );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( GetOption, NullTarget ) {
    const struct stumpless_error *error;
    int option;

    option = stumpless_get_option( NULL, STUMPLESS_OPTION_PID );
    EXPECT_EQ( option, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( OpenTarget, AlreadyOpenTarget ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    result = stumpless_open_target( target );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );
  }

  TEST( OpenTarget, NullTarget ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( SetDefaultAppName, MemoryFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );
   
    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target_result = stumpless_set_target_default_app_name( target, "app-name" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultAppName, NullName ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_target_default_app_name( target, NULL );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultAppName, NullTarget ) {
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target_result = stumpless_set_target_default_app_name( NULL, "app-name" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SetDefaultFacility, Local1 ) {
    char buffer[100];
    struct stumpless_target *target_result;
    struct stumpless_target *target;
    int current_facility;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    target_result = stumpless_set_default_facility( target, STUMPLESS_FACILITY_LOCAL1 );
    EXPECT_EQ( target_result, target );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    current_facility = stumpless_get_default_facility( target );
    EXPECT_EQ( current_facility, STUMPLESS_FACILITY_LOCAL1 );

    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultFacility, NotDivisibleBy8 ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_default_facility( target, 3 );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );

    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultFacility, NullTarget ) {
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target_result = stumpless_set_default_facility( NULL, STUMPLESS_FACILITY_USER );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( SetDefaultFacility, TooHigh ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_default_facility( target, 800 );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );

    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultFacility, TooLow ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_default_facility( target, -800 );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );

    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultMsgId, MemoryFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );
   
    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target_result = stumpless_set_target_default_msgid( target, "msgid" );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultMsgId, NullName ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    target_result = stumpless_set_target_default_msgid( target, NULL );
    EXPECT_NULL( target_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultMsgId, NullTarget ) {
    struct stumpless_target *target_result;
    const struct stumpless_error *error;

    target_result = stumpless_set_target_default_msgid( NULL, "msgid" );
    EXPECT_NULL( target_result );

    error = stumpless_get_error(  );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SetOption, NullTarget ) {
    const struct stumpless_error *error;
    const struct stumpless_target *result;

    result = stumpless_set_option( NULL, STUMPLESS_OPTION_PID );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( SetOption, Pid ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PID );
    EXPECT_FALSE( option );

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    option = stumpless_get_option( target, STUMPLESS_OPTION_PID );
    EXPECT_TRUE( option );

    stumpless_close_buffer_target( target );
  }

  TEST( WithPid, Pid) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct buffer_target* internal_buffer;
    char buffer[300];
    int result;
    std::cmatch matches;
    std::regex pid_regex(RFC_5424_REGEX_STRING);

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    internal_buffer = (struct buffer_target*) target->id;

    result = stump( "test message" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    if( !std::regex_match( buffer, matches, pid_regex ) ) {
      FAIL(  ) << "produced invalid procid";
    } else {
      EXPECT_EQ( matches[RFC_5424_PROCID_MATCH_INDEX], '-' );
    }

    // reset buffer
    memset(buffer, 0, sizeof(buffer));
    internal_buffer->position = 0;

    target_result = stumpless_set_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    result = stump( "test message 1" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    if( !std::regex_match( buffer, matches, pid_regex ) ) {
      FAIL(  ) << "produced invalid procid";
    } else {
      EXPECT_NE( matches[RFC_5424_PROCID_MATCH_INDEX], '-' );
      std::stoi( matches[RFC_5424_PROCID_MATCH_INDEX] );
    }

    // reset buffer
    memset(buffer, 0, sizeof(buffer));
    internal_buffer->position = 0;

    target_result = stumpless_unset_option( target, STUMPLESS_OPTION_PID );
    EXPECT_EQ( target_result, target );

    result = stump( "test message 2" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    if( !std::regex_match( buffer, matches, pid_regex ) ) {
      FAIL(  ) << "produced invalid procid";
    } else {
      EXPECT_EQ( matches[RFC_5424_PROCID_MATCH_INDEX], '-' );
    }

    stumpless_close_buffer_target( target );
  }

  TEST( Stump, Basic ) {
    char buffer[1000];
    struct stumpless_target *target;
    int result;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );
    ASSERT_TRUE( stumpless_get_current_target(  ) == target );

    result = stump( "test message" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );

    stumpless_close_buffer_target( target );
  }

  TEST( Stumplog, Basic ) {
    char buffer[1000];
    struct stumpless_target *target;
    int priority;

    buffer[0] = '\0';
    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    ASSERT_TRUE( stumpless_get_current_target(  ) == target );

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    stumplog( priority, "test message" );

    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    TestRFC5424Compliance( buffer );

    stumpless_close_buffer_target( target );
  }

  TEST( UnsetOption, NullTarget ) {
    const struct stumpless_error *error;
    const struct stumpless_target *result;

    result = stumpless_unset_option( NULL, STUMPLESS_OPTION_PID );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "target" ) );
  }

  TEST( UnsetOption, Pid ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    char buffer[100];
    int option;

    target = stumpless_open_buffer_target( "test target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
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
  }
}
