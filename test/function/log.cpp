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
    char plain_buffer[TEST_BUFFER_LENGTH];

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

  TEST_F( LogTest, StumpStr ) {
    const char *message = "stump str test message";
    int result;

    result = stump_str( message );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_THAT( buffer, HasSubstr( message ) );
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

}
