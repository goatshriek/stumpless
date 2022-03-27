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

#ifndef __STUMPLESS_TEST_HELPER_LEVEL_ENABLED_HPP
#  define __STUMPLESS_TEST_HELPER_LEVEL_ENABLED_HPP

#  include <cstdio>
#  include <gmock/gmock.h>
#  include <gtest/gtest.h>
#  include <stumpless.h>
#  include "test/helper/assert.hpp"

#  define TEST_LEVEL_ENABLED( LEVEL_NAME, LEVEL_LETTER )                       \
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
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Str ) {                           \
  int result;                                                                  \
  int expected_prival;                                                         \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_str( "100% message id: glorious kumquat" );  \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "glorious kumquat" ) );                      \
                                                                               \
  expected_prival = STUMPLESS_DEFAULT_FACILITY |                               \
                    STUMPLESS_SEVERITY_##LEVEL_NAME;                           \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
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
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##SideEffects ) {                   \
  int result;                                                                  \
  int before_val = 344;                                                        \
  int expected_prival;                                                         \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER( "simple message id #%d: glorious kumquat",    \
                                 before_val++ );                               \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "glorious kumquat" ) );                      \
  EXPECT_THAT( buffer, HasSubstr( "#344" ) );                                  \
                                                                               \
  expected_prival = STUMPLESS_DEFAULT_FACILITY |                               \
                    STUMPLESS_SEVERITY_##LEVEL_NAME;                           \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
                                                                               \
  EXPECT_EQ( before_val, 345 );                                                \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Log ) {                           \
  int result;                                                                  \
  int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;    \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_log( target,                                 \
                                       logged_prival,                          \
                                       "simple message id: lost primitive" );  \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", logged_prival );                                \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##LogSideEffects ) {                \
  int result;                                                                  \
  int before_val = 6889;                                                       \
  int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;    \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_log( target,                                 \
                                       logged_prival,                          \
                                       "message id #%d: lost primitive",       \
                                       before_val++ );                         \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", logged_prival );                                \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
                                                                               \
  EXPECT_EQ( before_val, 6890 );                                               \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##LogStr ) {                        \
  int result;                                                                  \
  int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;    \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_log_str( target,                             \
                                           logged_prival,                      \
                                           "100% message: lost primitive" );   \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", logged_prival );                                \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##Message ) {                       \
  int result;                                                                  \
  int expected_prival = STUMPLESS_DEFAULT_FACILITY |                           \
                        STUMPLESS_SEVERITY_##LEVEL_NAME;                       \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_message( target,                             \
                                           "message id: lost primitive" );     \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##MessageSideEffects ) {            \
  int result;                                                                  \
  int before_val = 6889;                                                       \
  int expected_prival = STUMPLESS_DEFAULT_FACILITY |                           \
                        STUMPLESS_SEVERITY_##LEVEL_NAME;                       \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_message( target,                             \
                                           "message id #%d: lost primitive",   \
                                           before_val++ );                     \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
                                                                               \
  EXPECT_EQ( before_val, 6890 );                                               \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stump##LEVEL_NAME##MessageStr ) {                    \
  int result;                                                                  \
  int expected_prival = STUMPLESS_DEFAULT_FACILITY |                           \
                        STUMPLESS_SEVERITY_##LEVEL_NAME;                       \
  char prival[6];                                                              \
                                                                               \
  result = stump_##LEVEL_LETTER##_message_str( target,                         \
                                               "100% id: lost primitive" );    \
  EXPECT_NO_ERROR;                                                             \
  EXPECT_GE( result, 0 );                                                      \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", expected_prival );                              \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stumplog##LEVEL_NAME ) {                             \
  int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;    \
  char prival[6];                                                              \
                                                                               \
  stumplog_##LEVEL_LETTER( logged_prival,                                      \
                           "simple message id: lost primitive" );              \
  EXPECT_NO_ERROR;                                                             \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", logged_prival );                                \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stumplog##LEVEL_NAME##SideEffects ) {                \
  int before_val = 6889;                                                       \
  int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;    \
  char prival[6];                                                              \
                                                                               \
  stumplog_##LEVEL_LETTER( logged_prival,                                      \
                           "simple message id #%d: lost primitive",            \
                           before_val++ );                                     \
  EXPECT_NO_ERROR;                                                             \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", logged_prival );                                \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
                                                                               \
  EXPECT_EQ( before_val, 6890 );                                               \
}                                                                              \
                                                                               \
TEST_F( LevelEnabledTest, Stumplog##LEVEL_NAME##Str ) {                        \
  int logged_prival = STUMPLESS_FACILITY_KERN | STUMPLESS_SEVERITY_WARNING;    \
  char prival[6];                                                              \
                                                                               \
  stumplog_##LEVEL_LETTER##_str( logged_prival,                                \
                                 "100% message id: lost primitive" );          \
  EXPECT_NO_ERROR;                                                             \
                                                                               \
  EXPECT_THAT( buffer, HasSubstr( "lost primitive" ) );                        \
  snprintf( prival, 6, "<%d>", logged_prival );                                \
  EXPECT_THAT( buffer, ::testing::StartsWith( prival ) );                      \
}

#endif /* __STUMPLESS_TEST_HELPER_LEVEL_ENABLED_HPP */
