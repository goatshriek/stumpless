/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2022 Joel E. Anderson
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

#ifndef __STUMPLESS_TEST_HELPER_LEVEL_DISABLED_HPP
#  define __STUMPLESS_TEST_HELPER_LEVEL_DISABLED_HPP

#  include <gtest/gtest.h>
#  include <stumpless.h>

#  define TEST_LEVEL_DISABLED( LEVEL_NAME, LEVEL_LETTER )                      \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME ) {                                \
  int result;                                                                  \
  result = stump_##LEVEL_LETTER( "simple message id: glorious kumquat" );      \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##SideEffects ) {                   \
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
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Str ) {                           \
  int result;                                                                  \
  result = stump_##LEVEL_LETTER##_str( "100% message id: glorious kumquat" );  \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Entry ) {                         \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_entry( target,                               \
                                         basic_entry );                        \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Log ) {                           \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_log( target,                                 \
                                       STUMPLESS_FACILITY_KERN |               \
                                       STUMPLESS_SEVERITY_INFO,                \
                                       "message id: inchworm bingo" );         \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##LogSideEffects ) {                \
  int result;                                                                  \
  int before_val = 555;                                                        \
                                                                               \
  result = stump_##LEVEL_LETTER##_log( target,                                 \
                                       STUMPLESS_FACILITY_KERN |               \
                                       STUMPLESS_SEVERITY_INFO,                \
                                       "message id #%d: inchworm bingo",       \
                                       before_val++ );                         \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
  EXPECT_EQ( before_val, 555 );                                                \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##LogStr ) {                        \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_log_str( target,                             \
                                           STUMPLESS_FACILITY_KERN |           \
                                           STUMPLESS_SEVERITY_INFO,            \
                                           "100% id: inchworm bingo" );        \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Message ) {                       \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_message( target,                             \
                                           "message id: inchworm bingo" );     \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##MessageSideEffects ) {            \
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
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##MessageStr ) {                    \
  int result;                                                                  \
                                                                               \
  result = stump_##LEVEL_LETTER##_message_str( target,                         \
                                               "100% id: inchworm bingo" );    \
  EXPECT_EQ( result, 0 );                                                      \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stumplog##LEVEL_NAME ) {                             \
  stumplog_##LEVEL_LETTER( STUMPLESS_FACILITY_KERN |                           \
                           STUMPLESS_SEVERITY_INFO,                            \
                           "message id: inchworm bingo" );                     \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stumplog##LEVEL_NAME##SideEffects ) {                \
  int before_val = 555;                                                        \
                                                                               \
  stumplog_##LEVEL_LETTER( STUMPLESS_FACILITY_KERN |                           \
                           STUMPLESS_SEVERITY_INFO,                            \
                           "message id #%d: inchworm bingo",                   \
                           before_val++ );                                     \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
  EXPECT_EQ( before_val, 555 );                                                \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stumplog##LEVEL_NAME##Str ) {                        \
  stumplog_##LEVEL_LETTER##_str( STUMPLESS_FACILITY_KERN |                     \
                                 STUMPLESS_SEVERITY_INFO,                      \
                                 "100% message id: inchworm bingo" );          \
                                                                               \
  EXPECT_TRUE( buffer[0] == '\0' );                                            \
}

#endif /* __STUMPLESS_TEST_HELPER_LEVEL_DISABLED_HPP */
