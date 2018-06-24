
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
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/socket.h>
#include <stumpless/error.h>
#include "test/function/rfc5424.hpp"

#define TEST_BUFFER_LENGTH 1024

using::testing::HasSubstr;

namespace {

class BufferTargetTest:
  public::testing::Test {
  protected:
    char
      buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *
      target;
    struct stumpless_entry *
      basic_entry;

    virtual void
      SetUp( void ) {
      buffer[0] = '\0';
      target =
        stumpless_open_buffer_target( "buffer target testing", buffer,
                                      TEST_BUFFER_LENGTH, 0, 0 );

      basic_entry =
        stumpless_new_entry( 3, 3, "stumpless-unit-test", "basic-entry",
                             "basic test message" );
    } virtual void
      TearDown( void ) {
      stumpless_destroy_entry( basic_entry );
      stumpless_close_buffer_target( target );
    }
  };

  TEST_F( BufferTargetTest, AddEntry ) {
    SCOPED_TRACE( "BufferTargetTest.AddEntry" );

    EXPECT_EQ( 0, stumpless_add_entry( target, basic_entry ) );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    EXPECT_THAT( buffer, HasSubstr( "<27>" ) );
  }

  TEST_F( BufferTargetTest, Basic ) {
    SCOPED_TRACE( "BufferTargetTest.Basic" );

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    EXPECT_EQ( 0,
               stumpless( "\xef\xbb\xbftesting 1 \xfc\x88\x81\x8f\x8f\x8f" ) );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

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
    const char *
      test_string = "smash the stack for fun and profit";
    size_t test_string_len = strlen( test_string );

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    for( size_t bytes_written = 0; bytes_written <= TEST_BUFFER_LENGTH;
         bytes_written += test_string_len ) {
      ASSERT_EQ( 0, stumpless( test_string ) );
      ASSERT_EQ( NULL, stumpless_get_error(  ) );
    }

    EXPECT_EQ( NULL, stumpless_get_error(  ) );
  }

class BufferTargetOpenTest:
  public::testing::Test {

  };

  TEST( BufferTargetOpenTest, NormalOpenTarget ) {
    struct stumpless_target *
      target;
    char
      buffer[100];

    target = stumpless_open_buffer_target( "normal target", buffer, 100, 0, 0 );
    ASSERT_TRUE( target != NULL );

    EXPECT_EQ( target, stumpless_get_current_target(  ) );

    stumpless_close_buffer_target( target );
  }

}

int
main( int argc, char **argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS(  );
}
