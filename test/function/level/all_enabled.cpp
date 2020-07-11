// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020 Joel E. Anderson
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

#include <cstdio>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"

#define TEST_LEVEL_ENABLED( LEVEL_NAME, LEVEL_LETTER )                         \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME ) {                                \
  int result;                                                                  \
  int expected_prival;                                                         \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER( "simple message id: glorious kumquat" );      \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "glorious kumquat" ) );                      \
                                                                               \
  expected_prival = STUMPLESS_DEFAULT_FACILITY |                               \
                    STUMPLESS_SEVERITY_##LEVEL_NAME;                           \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, StartsWith( prival ) );                                 \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Entry ) {                         \
  int result;                                                                  \
  int expected_prival;                                                         \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_entry( target, basic_entry );                \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( basic_message ) );                           \
                                                                               \
  expected_prival = stumpless_get_entry_prival( basic_entry );                 \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, StartsWith( prival ) );                                 \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##SideEffects ) {                   \
  int result;                                                                  \
  int before_val = 344;                                                        \
  int expected_prival;                                                         \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER( "simple message id #%d: glorious kumquat",    \
                    before_val++ );                                            \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "glorious kumquat" ) );                      \
  EXPECT_THAT( buffer, HasSubstr( "#344" ) );                                  \
                                                                               \
  expected_prival = STUMPLESS_DEFAULT_FACILITY |                               \
                    STUMPLESS_SEVERITY_##LEVEL_NAME;                           \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, StartsWith( prival ) );                                 \
                                                                               \
  EXPECT_EQ( before_val, 345 );                                                \
}

#define TEST_BUFFER_LENGTH 8192

using::testing::HasSubstr;
using::testing::StartsWith;

namespace {

  class LevelEnabledTest : public::testing::Test {
  protected:
    char buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *target;
    struct stumpless_entry *basic_entry;
    const char *basic_message = "basic test message";

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      buffer[0] = '\0';
      target = stumpless_open_buffer_target( "level enabled testing",
                                             buffer,
                                             TEST_BUFFER_LENGTH,
                                             STUMPLESS_OPTION_NONE,
                                             STUMPLESS_FACILITY_USER );

      stumpless_set_target_default_app_name( target, "level-enabled-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_WARNING,
                                        "stumpless-unit-test",
                                        "basic-entry",
                                        basic_message );

      element = stumpless_new_element( "basic-element" );
      stumpless_add_element( basic_entry, element );

      param = stumpless_new_param( "basic-param-name", "basic-param-value" );
      stumpless_add_param( element, param );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_close_buffer_target( target );
    }
  };

  TEST_LEVEL_ENABLED( INFO, i );

  TEST_F( LevelEnabledTest, StumpInfoLog ) {
    int result;
    int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;
    char prival[6];

    result = stump_i_log( target,
                          logged_prival,
                          "simple message id: lost primitive" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );
    snprintf( prival, 6, "<%d>", logged_prival );
    EXPECT_THAT( buffer, StartsWith( prival ) );
  }

  TEST_F( LevelEnabledTest, StumpInfoLogSideEffects ) {
    int result;
    int before_val = 6889;
    int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;
    char prival[6];

    result = stump_i_log( target,
                          logged_prival,
                          "simple message id #%d: lost primitive",
                          before_val++ );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );
    snprintf( prival, 6, "<%d>", logged_prival );
    EXPECT_THAT( buffer, StartsWith( prival ) );

    EXPECT_EQ( before_val, 6890 );
  }

  TEST_F( LevelEnabledTest, StumpInfoMessage ) {
    int result;
    int expected_prival = STUMPLESS_DEFAULT_FACILITY | STUMPLESS_SEVERITY_INFO;
    char prival[6];

    result = stump_i_message( target,
                              "simple message id: lost primitive" );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );
    snprintf( prival, 6, "<%d>", expected_prival );
    EXPECT_THAT( buffer, StartsWith( prival ) );
  }

  TEST_F( LevelEnabledTest, StumpInfoMessageSideEffects ) {
    int result;
    int before_val = 6889;
    int expected_prival = STUMPLESS_DEFAULT_FACILITY | STUMPLESS_SEVERITY_INFO;
    char prival[6];

    result = stump_i_message( target,
                              "simple message id #%d: lost primitive",
                              before_val++ );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );

    EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );
    snprintf( prival, 6, "<%d>", expected_prival );
    EXPECT_THAT( buffer, StartsWith( prival ) );

    EXPECT_EQ( before_val, 6890 );
  }

  TEST_F( LevelEnabledTest, StumplogInfo ) {
    int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;
    char prival[6];

    stumplog_i( logged_prival, "simple message id: lost primitive" );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );
    snprintf( prival, 6, "<%d>", logged_prival );
    EXPECT_THAT( buffer, StartsWith( prival ) );
  }

  TEST_F( LevelEnabledTest, StumplogInfoSideEffects ) {
    int before_val = 6889;
    int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;
    char prival[6];

    stumplog_i( logged_prival,
                "simple message id #%d: lost primitive",
                before_val++ );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );
    snprintf( prival, 6, "<%d>", logged_prival );
    EXPECT_THAT( buffer, StartsWith( prival ) );

    EXPECT_EQ( before_val, 6890 );
  }

}
