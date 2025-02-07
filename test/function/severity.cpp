// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2024 Joel E. Anderson
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

namespace {

  class SeverityTest : public::testing::Test {
  };

  TEST( GetSeverityString, EachValidSeverity ) {
    int severity_count = 0;
    const char *result;

    #define CHECK_SEVERITY( STRING, ENUM ) \
      result = stumpless_get_severity_string( STRING ); \
      EXPECT_STREQ( result, #STRING );
    STUMPLESS_FOREACH_SEVERITY( CHECK_SEVERITY )
  }
  
  TEST( GetSeverityString, NoSuchSeverity ) {
    int severity_count = 0;
    const char *result;

    #define COUNT_SEVERITY( STRING, ENUM ) ++severity_count;
    STUMPLESS_FOREACH_SEVERITY( COUNT_SEVERITY )

    stumpless_severity wrong_severity =
        static_cast<stumpless_severity>(severity_count + 1);

    result = stumpless_get_severity_string( wrong_severity );
    EXPECT_STREQ( result, "NO_SUCH_SEVERITY" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
  }

  TEST( GetSeverityString, ClearError ) {
    int severity_count = 0;
    const char *result;
    const char *version;
    
    version = stumpless_version_to_string( NULL );
    EXPECT_NULL( version );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    #define COUNT_SEVERITY( STRING, ENUM ) ++severity_count;
    STUMPLESS_FOREACH_SEVERITY( COUNT_SEVERITY )

    stumpless_severity correct_severity =
        static_cast<stumpless_severity>(severity_count - 1);

    result = stumpless_get_severity_string( correct_severity );
    EXPECT_NO_ERROR;
  }

  TEST( GetSeverityEnum, EachValidSeverity ) {
    int severity_count = 0;
    int result;

    #define CHECK_SEVERITY_ENUM( STRING, ENUM ) \
      result = stumpless_get_severity_enum( #STRING + 19 ); \
      EXPECT_EQ( result, ENUM );
    STUMPLESS_FOREACH_SEVERITY( CHECK_SEVERITY_ENUM )
  }

  TEST( GetSeverityEnum, LowercaseValidSeverity ) {
    int result;

    result = stumpless_get_severity_enum( "emerg" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_EMERG );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "alert" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_ALERT );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "crit" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_CRIT );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "err" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_ERR );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "warning" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_WARNING );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "notice" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_NOTICE );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "info" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_INFO );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "debug" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_DEBUG );
    EXPECT_NO_ERROR;
    // deprecated
    result = stumpless_get_severity_enum( "panic" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_EMERG );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "error" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_ERR );
    EXPECT_NO_ERROR;
    result = stumpless_get_severity_enum( "warn" );
    EXPECT_EQ( result, STUMPLESS_SEVERITY_WARNING );
    EXPECT_NO_ERROR;
  }

  TEST( GetSeverityEnum, NoSuchSeverity ) {
    int severity_count = 0;
    int result;

    result = stumpless_get_severity_enum( "an_invalid_severity" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
  }

  TEST( GetSeverityEnum, ClearError ) {
    int severity_count = 0;
    int result;
    const char *version;
    
    version = stumpless_version_to_string( NULL );
    EXPECT_NULL( version );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    result = stumpless_get_severity_enum( "EMERG" );
    EXPECT_NO_ERROR;
  }

  TEST( GetSeverityEnumFromBuffer, NoSuchSeverity ) {
    int result;

    result = stumpless_get_severity_enum_from_buffer( "an_invalid_severity", 10 );
    EXPECT_EQ( result, -1 );
  }

  TEST( GetSeverityEnumFromBuffer, IncompleteSeverity ) {
    enum stumpless_severity result = stumpless_get_severity_enum( "war" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
    
    result = stumpless_get_severity_enum( "not" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
  }	


  TEST( GetSeverityEnumFromBuffer, OverextendedSeverity ) {
    enum stumpless_severity result = stumpless_get_severity_enum( "warnings are neat" );
    EXPECT_EQ( result, -1 );
    
    result = stumpless_get_severity_enum( "notices are bad" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );

    result = stumpless_get_severity_enum( "panic you should not" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );

  }	

  TEST( GetSeverityEnumFromBuffer, ClearError ) {
    int result;
    const char *version;
    
    version = stumpless_version_to_string( NULL );
    EXPECT_NULL( version );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    result = stumpless_get_severity_enum_from_buffer( "EMERG", 5 );
    EXPECT_NO_ERROR;
  }


}
