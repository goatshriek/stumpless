// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2019 Joel E. Anderson
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <stumpless.h>

using ::testing::HasSubstr;

namespace {

  class VersionTest : public ::testing::Test {};
  
  TEST(GetVersion, Defines){
    std::ostringstream current_version;

    #ifndef STUMPLESS_MAJOR_VERSION
      FAIL();
    #endif
  
    #ifndef STUMPLESS_MINOR_VERSION
      FAIL();
    #endif
  
    #ifndef STUMPLESS_PATCH_VERSION
      FAIL();
    #endif

    #ifndef STUMPLESS_VERSION
      FAIL();
    #endif

    current_version << STUMPLESS_MAJOR_VERSION << "." << STUMPLESS_MINOR_VERSION << "." << STUMPLESS_PATCH_VERSION;
    EXPECT_STREQ( STUMPLESS_VERSION, current_version.str(  ).c_str(  ) );
  }

  TEST( GetVersion, Function ) {
    struct stumpless_version *version;
  
    version = stumpless_get_version();
  
    ASSERT_TRUE(version != NULL);
    ASSERT_TRUE(version->major >= 0);
    ASSERT_TRUE(version->minor >= 0);
    ASSERT_TRUE(version->patch >= 0);
  }

  TEST( GetVersion, MemoryFailure ) {
    struct stumpless_version *version;
    struct stumpless_error *error;
    void *(*result)(size_t);

    // cause a failure so that the error struct can be created
    stumpless_new_param( NULL, NULL );
   
    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( result != NULL );

    version = stumpless_get_version(  );
    EXPECT_EQ( NULL, version );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    stumpless_set_malloc( malloc );
  }

  TEST( VersionCmp, BasicSame ) {
    struct stumpless_version version_x = {1, 5, 0};
    struct stumpless_version version_y = {1, 5, 0};

    EXPECT_EQ( stumpless_version_cmp( &version_x, &version_y ), 0 );
  }

  TEST( VersionCmp, BasicPatch ) {
    struct stumpless_version version_x = {1, 5, 2};
    struct stumpless_version version_y = {1, 5, 1};

    EXPECT_EQ( stumpless_version_cmp( &version_x, &version_y ), 1 );
  }

  TEST( VersionCmp, BasicMinor ) {
    struct stumpless_version version_x = {1, 5, 0};
    struct stumpless_version version_y = {1, 6, 0};

    EXPECT_EQ( stumpless_version_cmp( &version_x, &version_y ), -10 );
  }

  TEST( VersionCmp, BasicMajor ) {
    struct stumpless_version version_x = {1, 5, 0};
    struct stumpless_version version_y = {2, 6, 0};

    EXPECT_EQ( stumpless_version_cmp( &version_x, &version_y ), -100 );
  }

  TEST( VersionCmp, NullVersion ) {
    struct stumpless_version version_x = {1, 5, 0};
    struct stumpless_version * version_y = NULL;

    EXPECT_EQ( stumpless_version_cmp( &version_x, version_y ), INT_MAX );
  }

  TEST( VersionToString, Basic ) {
    struct stumpless_version version = {1, 5, 0};
    char *string_result;

    string_result = stumpless_version_to_string( &version );
    EXPECT_TRUE( string_result != NULL );
    EXPECT_STREQ( string_result, "1.5.0" );

    free( string_result );
  }

  TEST( VersionToString, Current ) {
    const struct stumpless_version *version;
    char *string_result;
    std::ostringstream current_version;

    version = stumpless_get_version(  );
    ASSERT_TRUE( version != NULL );

    string_result = stumpless_version_to_string( version );
    EXPECT_TRUE( string_result != NULL );

    current_version << STUMPLESS_MAJOR_VERSION << "." << STUMPLESS_MINOR_VERSION << "." << STUMPLESS_PATCH_VERSION;
    EXPECT_STREQ( string_result, current_version.str(  ).c_str(  ) );

    free( string_result );
    free( ( void * ) version );
  }

  TEST( VersionToString, MemoryFailure ) {
    void *(*malloc_result)(size_t);
    struct stumpless_version version = { 1, 5, 0};
    char *string_result;
    struct stumpless_error *error;

    malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( malloc_result != NULL );

    string_result = stumpless_version_to_string( &version );
    EXPECT_TRUE( string_result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    stumpless_set_malloc( malloc );
  }

  TEST( VersionToString, NullVersion ) {
    char *result;
    struct stumpless_error *error;

    result = stumpless_version_to_string( NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "version" ) );
    }
  }
}
