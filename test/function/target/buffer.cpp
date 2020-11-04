// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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
#include "test/helper/assert.hpp"

using::testing::HasSubstr;

namespace {

  static const size_t TEST_BUFFER_LENGTH = 8192;
  static const size_t READ_BUFFER_LENGTH = 1024;

  class
    BufferTargetTest:
    public::testing::Test {
  protected:
    char buffer[TEST_BUFFER_LENGTH];
    char read_buffer[READ_BUFFER_LENGTH];
    struct stumpless_target *target;
    struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      buffer[0] = '\0';
      target = stumpless_open_buffer_target( "buffer target testing",
                                             buffer,
                                             TEST_BUFFER_LENGTH,
                                             STUMPLESS_OPTION_NONE,
                                             STUMPLESS_FACILITY_USER );

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
    int write_result;
    int read_result;

    SCOPED_TRACE( "BufferTargetTest.AddEntry" );

    write_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( write_result, 0 );
    EXPECT_NO_ERROR;

    read_result = stumpless_read_buffer( target,
                                         read_buffer,
                                         READ_BUFFER_LENGTH );
    EXPECT_EQ( read_result, write_result );
    EXPECT_NO_ERROR;

    EXPECT_THAT( read_buffer,
                 HasSubstr( std::to_string( basic_entry->prival ) ) );
    EXPECT_THAT( read_buffer, HasSubstr( "basic-element" ) );
    EXPECT_THAT( read_buffer, HasSubstr( "basic-param-name" ) );
    EXPECT_THAT( read_buffer, HasSubstr( "basic-param-value" ) );

    TestRFC5424Compliance(buffer);
  }

  TEST_F( BufferTargetTest, Basic ) {
    int write_result;
    int read_result;

    SCOPED_TRACE( "BufferTargetTest.Basic" );

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    write_result = stump( "\xef\xbb\xbftesting 1 \xfc\x88\x81\x8f\x8f\x8f" );
    EXPECT_GE( write_result, 0 );
    EXPECT_NO_ERROR;

    read_result = stumpless_read_buffer( target, read_buffer, READ_BUFFER_LENGTH );
    EXPECT_EQ( read_result, write_result );
    EXPECT_NO_ERROR;

    EXPECT_THAT( read_buffer, HasSubstr( std::to_string( target->default_prival ) ) );
    EXPECT_THAT( read_buffer, HasSubstr( "buffer-target-test" ) );
    EXPECT_THAT( read_buffer, HasSubstr( "default-message" ) );

    TestRFC5424Compliance( read_buffer );
  }

  TEST_F( BufferTargetTest, EmptyMessage ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    int result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 NULL );
    ASSERT_TRUE( entry != NULL );

    result = stumpless_add_entry( target, entry );
    EXPECT_GE( result, 0 );

    TestRFC5424Compliance( buffer );
    EXPECT_NE( buffer[result-1], ' ' );

    stumpless_destroy_entry( entry );
  }

  TEST_F( BufferTargetTest, IsOpen ) {
    EXPECT_TRUE( stumpless_target_is_open( target ) );
  }

  TEST_F( BufferTargetTest, OverFill ) {
    char test_string[TEST_BUFFER_LENGTH + 1];
    const struct stumpless_error *error;

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    memset( test_string, 'g', TEST_BUFFER_LENGTH );
    test_string[TEST_BUFFER_LENGTH] = '\0';
    ASSERT_EQ( -1, stump( test_string ) );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
  }

  TEST_F( BufferTargetTest, ReadBufferTooSmall ) {
    size_t result;
    char read_buffer[5];

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GT( result, 0 );
    EXPECT_NO_ERROR;

    result = stumpless_read_buffer( target, read_buffer, 5 );
    EXPECT_EQ( result, 5 );
    EXPECT_EQ( read_buffer[4], '\0' );
  }

  TEST_F( BufferTargetTest, WrapAround ) {
    size_t bytes_written=0, write_count=0, null_count=0, i;
    int result;

    memset( buffer, 0, TEST_BUFFER_LENGTH );

    while( bytes_written <= TEST_BUFFER_LENGTH ) {
      result = stumpless_add_entry( target, basic_entry );
      EXPECT_GT( result, 0 );
      EXPECT_NO_ERROR;

      write_count++;
      bytes_written += result;
    }

    for( i=0; i < TEST_BUFFER_LENGTH; i++ ) {
      if( buffer[i] == '\0' ) {
        null_count++;
      }
    }

    ASSERT_EQ( null_count, write_count );
  }

  /* non-fixture tests */

  TEST( BufferTargetCloseTest, Generic ) {
    const char *target_name = "normal target";
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( target_name,
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_EQ( stumpless_get_current_target(  ), target );

    stumpless_close_target( target );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(  ),
               stumpless_get_default_target(  ) );
    EXPECT_STRNE( stumpless_get_current_target(  )->name,
                  target_name );

    stumpless_free_all(  );
  }

  TEST( BufferTargetCloseTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_buffer_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetOpenTest, Basic ) {
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( "normal target",
                                           buffer,
                                           100,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NOT_NULL( target );

    EXPECT_EQ( target, stumpless_get_current_target(  ) );

    stumpless_close_buffer_target( target );
  }

  TEST( BufferTargetOpenTest, NullBuffer ) {
    const struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "null-buffer",
                                           NULL,
                                           100,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;
    char buffer[100];

    target = stumpless_open_buffer_target( NULL,
                                           buffer,
                                           100,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetOpenTest, Open100Targets ) {
    char buffer[100];
    struct stumpless_target *targets[100];
    size_t i;

    for( i=0; i < 100; i++ ) {
      targets[i] = stumpless_open_buffer_target( "many target test",
                                                 buffer,
                                                 100,
                                                 STUMPLESS_OPTION_NONE,
                                                 STUMPLESS_FACILITY_USER );
      EXPECT_NO_ERROR;
      ASSERT_NOT_NULL( targets[i] );
    }

    for( i=0; i < 100; i++ ) {
      stumpless_close_buffer_target( targets[i] );
    }
  }
}
