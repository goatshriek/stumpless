// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2021 Joel E. Anderson
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

#include <gtest/gtest.h>
#include <stumpless.h>

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
  }

  TEST( GetSeverityEnum, EachValidSeverity ) {
    int severity_count = 0;
    int result;

    #define CHECK_SEVERITY_ENUM( STRING, ENUM ) \
      result = stumpless_get_severity_enum( #STRING ); \
      EXPECT_EQ( result, ENUM );
    STUMPLESS_FOREACH_SEVERITY( CHECK_SEVERITY_ENUM )
  }

  TEST( GetSeverityEnum, NoSuchSeverity ) {
    int severity_count = 0;
    int result;

    result = stumpless_get_severity_enum( "an_invalid_severity" );
    EXPECT_EQ( result, -1 );
  }

}
