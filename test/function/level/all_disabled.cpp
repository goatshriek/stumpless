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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>

#define TEST_LEVEL_DISABLED( LEVEL_NAME, LEVEL_LETTER )                        \
TEST_F( LevelDisabledTest, Stump##LEVEL_NAME ) {                               \
  int result;                                                                  \
  result = stump_i( "simple message id: glorious kumquat" );                   \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stump##LEVEL_NAME##SideEffects ) {                  \
  int result;                                                                  \
  int before_val = 3;                                                          \
                                                                               \
  result = stump_##LEVEL_LETTER( "simple message id #%d: glorious kumquat",    \
                                 before_val++ );                               \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
  EXPECT_EQ( before_val, 3 );                                                  \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stump##LEVEL_NAME##Entry ) {                        \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_entry( target,                               \
                                         basic_entry );                        \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stump##LEVEL_NAME##Log ) {                          \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_log( target,                                 \
                                       STUMPLESS_FACILITY_KERN |               \
                                       STUMPLESS_SEVERITY_INFO                 \
                                       "message id: inchworm bingo" );         \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stump##LEVEL_NAME##LogSideEffects ) {               \
  int result;                                                                  \
  int before_val = 555;                                                        \
                                                                               \
  result = stump_##LEVEL_LETTER##_log( target,                                 \
                                       STUMPLESS_FACILITY_KERN |               \
                                       STUMPLESS_SEVERITY_INFO                 \
                                       "message id #%d: inchworm bingo",       \
                                       before_val++ );                         \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
  EXPECT_EQ( before_val, 555 );                                                \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stump##LEVEL_NAME##Message ) {                      \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_message( target,                             \
                                           "message id: inchworm bingo" );     \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stump##LEVEL_NAME##MessageSideEffects ) {           \
  int result;                                                                  \
  int before_val = 555;                                                        \
                                                                               \
  result = stump_##LEVEL_LETTER##_message( target,                             \
                                           "message id #%d: inchworm bingo",   \
                                           before_val++ );                     \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
  EXPECT_EQ( before_val, 555 );                                                \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stumplog##LEVEL_NAME ) {                            \
  stumplog_##LEVEL_LETTER( STUMPLESS_FACILITY_KERN |                           \
                           STUMPLESS_SEVERITY_INFO                             \
                           "message id: inchworm bingo" );                     \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelDisabledTest, Stumplog##LEVEL_NAME##SideEffects ) {               \
  int result;                                                                  \
  int before_val = 555;                                                        \
                                                                               \
  stumplog_##LEVEL_LETTER( STUMPLESS_FACILITY_KERN |                           \
                           STUMPLESS_SEVERITY_INFO                             \
                           "message id #%d: inchworm bingo",                   \
                           before_val++ );                                     \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
  EXPECT_EQ( before_val, 555 );                                                \
}

#define TEST_BUFFER_LENGTH 8192

using::testing::HasSubstr;

namespace {

  class LevelDisabledTest : public::testing::Test {
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
      target = stumpless_open_buffer_target( "info level testing",
                                             buffer,
                                             TEST_BUFFER_LENGTH,
                                             STUMPLESS_OPTION_NONE,
                                             STUMPLESS_FACILITY_USER );

      stumpless_set_target_default_app_name( target, "info-level-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
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

  TEST_LEVEL_DISABLED( INFO, i );

}
