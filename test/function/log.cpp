// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2022 Joel E. Anderson
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/rfc5424.hpp"

using::testing::HasSubstr;

namespace {

  static const size_t TEST_BUFFER_LENGTH = 8192;

  class
    LogTest:
    public::testing::Test {
  protected:
    char buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *target;
    const char *target_name = "test-target";
    const char *default_app_name = "target-default-app-name";
    const char *default_msgid = "target-default-msgid";

    virtual void
    SetUp( void ) {
      target = stumpless_open_buffer_target( target_name,
                                             buffer,
                                             sizeof( buffer ) );

      stumpless_set_target_default_app_name( target, default_app_name );
      stumpless_set_target_default_msgid( target, default_msgid );

      buffer[0] = '\0';
    }

    virtual void
    TearDown( void ) {
      stumpless_close_buffer_target( target );

      stumpless_free_all(  );
    }
  };

  TEST_F( LogTest, Stump ) {
    const char *format = "Stump test message: %s";
    const char *str = "this is the format string";
    int result;

    result = stump( format, str );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( str ) );
  }

  TEST_F( LogTest, Stumplog ) {
    int priority;
    const char *message_format = "Stumplog basic test: %s";
    const char *test_string = "with format specifiers!";

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    stumplog( priority, message_format, test_string );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( test_string ) );
  }

  TEST_F( LogTest, StumplogSetMask ) {
    int first_mask = 134;
    const struct stumpless_target *target_result;
    int second_mask = 245;
    int int_result;

    target_result = stumpless_set_target_mask( target, first_mask );
    EXPECT_NO_ERROR;
    EXPECT_EQ( target_result, target );

    int_result = stumplog_set_mask( second_mask );
    EXPECT_NO_ERROR;
    EXPECT_EQ( int_result, first_mask );

    int_result = stumpless_get_target_mask( target );
    EXPECT_NO_ERROR;
    EXPECT_EQ( int_result, second_mask );
  }

  TEST_F( LogTest, StumplogStr ) {
    int priority;
    const char *message = "Stumplog basic test message";

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    stumplog_str( priority, message );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( message ) );
  }

  TEST_F( LogTest, StumplogTrace ) {
    int priority;
    const char *filename = "stumplog-trace-file.c";
    const char *function_name = "LogTest.StumplogTrace";
    const char *format = "Stumplog trace test: %s";
    const char *str = "testing stumplog trace substitution!";

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    stumplog_trace( priority, filename, 377, function_name, format, str );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "line=\"377\"" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );
    EXPECT_THAT( buffer, HasSubstr( str ) );
  }

  TEST_F( LogTest, StumplogTraceStr ) {
    int priority;
    const char *filename = "stumplog-trace-file.c";
    const char *function_name = "LogTest.StumplogTrace";
    const char *message = "Stumplog Trace str test message";

    priority = STUMPLESS_SEVERITY_INFO | STUMPLESS_FACILITY_USER;
    stumplog_trace_str( priority, filename, 377, function_name, message );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "line=\"377\"" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );
    EXPECT_THAT( buffer, HasSubstr( message ) );
  }

  TEST_F( LogTest, StumpStr ) {
    const char *message = "stump str test message";
    int result;

    result = stump_str( message );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( message ) );
  }

  TEST_F( LogTest, StumpTrace ) {
    const char *filename = "fake_file.c";
    const char *function_name = "fake_function";
    const char *format = "stump_trace test message: %s";
    const char *str = "stump_trace format string";
    int result;

    result = stump_trace( filename, 377, function_name, format, str );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "377" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );
    EXPECT_THAT( buffer, HasSubstr( str ) );
  }

  TEST_F( LogTest, StumpTraceStr ) {
    const char *filename = "fake_file.c";
    const char *function_name = "fake_function";
    const char *message = "stump trace str test message";
    int result;

    result = stump_trace_str(filename, 377, function_name, message);
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( message ) );
    EXPECT_THAT( buffer, HasSubstr( filename ) );
    EXPECT_THAT( buffer, HasSubstr( "377" ) );
    EXPECT_THAT( buffer, HasSubstr( function_name ) );
  }

  TEST_F( LogTest, StumpTraceWithPreprocessorMacros ) {
    const char *format = "stump_trace test message: %s";
    const char *str = "stump_trace format string";
    int result;

    result = stump_trace( __FILE__, __LINE__, __func__, format, str );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( __FILE__ ) );
    EXPECT_THAT( buffer, HasSubstr( __func__ ) );
    EXPECT_THAT( buffer, HasSubstr( str ) );
  }

}
