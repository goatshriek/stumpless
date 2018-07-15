// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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

#include <stddef.h>
#include <string.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/function/rfc5424.hpp"

#define TEST_BUFFER_LENGTH 1024

using::testing::HasSubstr;

namespace {

  class
    BufferTargetTest:
    public::testing::Test {
  protected:
    char buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *target;
    struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      buffer[0] = '\0';
      target = stumpless_open_buffer_target( "buffer target testing", buffer,
                                             TEST_BUFFER_LENGTH, 0, 0 );

      stumpless_set_target_default_app_name( target, "buffer-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
                                        "stumpless-unit-test",
                                        "basic-entry",
                                        "basic test message" );

      element = stumpless_new_element( "basic-element" );
      stumpless_add_element( basic_entry, element );

      param = stumpless_new_param( "basic-param-name", "basic-param-value" );
      stumpless_add_param( element, param );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry( basic_entry );
      stumpless_close_buffer_target( target );
    }
  };

  TEST_F( BufferTargetTest, AddEntry ) {
    int result;

    SCOPED_TRACE( "BufferTargetTest.AddEntry" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    EXPECT_THAT( buffer, HasSubstr( std::to_string( basic_entry->prival ) ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-element" ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-param-name" ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-param-value" ) );

    TestRFC5424Compliance(buffer);
  }

  TEST_F( BufferTargetTest, Basic ) {
    int result;

    SCOPED_TRACE( "BufferTargetTest.Basic" );

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    result = stumpless( "\xef\xbb\xbftesting 1 \xfc\x88\x81\x8f\x8f\x8f" );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    EXPECT_THAT( buffer, HasSubstr( std::to_string( target->default_prival ) ) );
    EXPECT_THAT( buffer, HasSubstr( "buffer-target-test" ) );
    EXPECT_THAT( buffer, HasSubstr( "default-message" ) );

    TestRFC5424Compliance( buffer );
  }

  TEST_F( BufferTargetTest, OverFill ) {
    char
      test_string[TEST_BUFFER_LENGTH + 1];
    struct stumpless_error *
      error;

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    memset( test_string, 'g', TEST_BUFFER_LENGTH );
    test_string[TEST_BUFFER_LENGTH] = '\0';
    ASSERT_EQ( -1, stumpless( test_string ) );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_TOO_BIG );
  }

  TEST_F( BufferTargetTest, WrapAround ) {
    const char *test_string = "smash the stack for fun and profit";
    size_t test_string_len = strlen( test_string );
    int result;

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    for( size_t bytes_written = 0; bytes_written <= TEST_BUFFER_LENGTH;
         bytes_written += test_string_len ) {
      result = stumpless( test_string );
      EXPECT_GE( result, 0 );
      ASSERT_EQ( NULL, stumpless_get_error(  ) );
    }

    EXPECT_EQ( NULL, stumpless_get_error(  ) );
  }

  /* non-fixture tests */

  TEST( BufferTargetAddTest, AddAfterClose ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    int result;
    char buffer[100];

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                "stumpless-unit-test",
                                "basic-entry",
                                "basic test message" );

    target = stumpless_open_buffer_target( "normal target", buffer, 100, 0, 0 );
    ASSERT_TRUE( target != NULL );
    ASSERT_EQ( NULL, stumpless_get_error(  ) );

    stumpless_close_buffer_target( target );

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_INVALID_ID );

    stumpless_destroy_entry( entry );
  }

  TEST( BufferTargetCloseTest, NullTarget ) {
    struct stumpless_error *error;

    stumpless_close_buffer_target( NULL );
    
    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetOpenTest, Basic ) {
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( "normal target", buffer, 100, 0, 0 );
    ASSERT_TRUE( target != NULL );

    EXPECT_EQ( target, stumpless_get_current_target(  ) );

    stumpless_close_buffer_target( target );
  }

  TEST( BufferTargetOpenTest, NullBuffer ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_buffer_target( "null-buffer", NULL, 100, 0, 0 );
    ASSERT_TRUE( target == NULL );
    
    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    char buffer[100];

    target = stumpless_open_buffer_target( NULL, buffer, 100, 0, 0 );
    ASSERT_TRUE( target == NULL );
    
    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

}

int
main( int argc, char **argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS(  );
}
