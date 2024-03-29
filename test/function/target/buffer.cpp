// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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
#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"
#include "test/helper/rfc5424.hpp"

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
                                             TEST_BUFFER_LENGTH );

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
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_close_buffer_target( target );
    }
  };

  TEST_F( BufferTargetTest, AddEntry ) {
    int write_result;
    size_t read_result;

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
    size_t read_result;

    SCOPED_TRACE( "BufferTargetTest.Basic" );

    ASSERT_NOT_NULL( stumpless_get_current_target(  ) );

    write_result = stump( "\xef\xbb\xbftesting 1 \xfc\x88\x81\x8f\x8f\x8f" );
    EXPECT_GE( write_result, 0 );
    EXPECT_NO_ERROR;

    read_result = stumpless_read_buffer( target,
                                         read_buffer,
                                         READ_BUFFER_LENGTH );
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
    int write_result;
    size_t read_result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 NULL );
    ASSERT_TRUE( entry != NULL );

    write_result = stumpless_add_entry( target, entry );
    EXPECT_GE( write_result, 0 );

    read_result = stumpless_read_buffer( target,
                                         read_buffer,
                                         READ_BUFFER_LENGTH );
    EXPECT_EQ( read_result, write_result );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( read_buffer );
    EXPECT_NE( read_buffer[read_result-1], ' ' );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( BufferTargetTest, IsOpen ) {
    EXPECT_TRUE( stumpless_target_is_open( target ) );
  }

  TEST_F( BufferTargetTest, NullReadBuffer ) {
    size_t result;

    result = stumpless_read_buffer( target, NULL, sizeof( read_buffer ) );
    EXPECT_EQ( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( BufferTargetTest, OverFill ) {
    char test_string[TEST_BUFFER_LENGTH + 1];

    ASSERT_NOT_NULL( stumpless_get_current_target() );

    memset( test_string, 'g', TEST_BUFFER_LENGTH );
    test_string[TEST_BUFFER_LENGTH] = '\0';
    EXPECT_EQ( -1, stump( test_string ) );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
  }

  TEST_F( BufferTargetTest, ReadBufferSizeZero ) {
    size_t result;

    result = stumpless_read_buffer( target, read_buffer, 0 );
    EXPECT_EQ( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( BufferTargetTest, ReadBufferOneCharacterTooSmall ) {
    int write_result;
    size_t read_size;
    size_t read_result;

    write_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GT( write_result, 0 );
    EXPECT_NO_ERROR;

    read_size = static_cast<size_t>( write_result ) - 1;
    read_result = stumpless_read_buffer( target, read_buffer, read_size );
    EXPECT_EQ( read_result, read_size );
    EXPECT_EQ( read_buffer[read_result - 1], '\0' );
  }

  TEST_F( BufferTargetTest, ReadBufferWayTooSmall ) {
    int write_result;
    size_t read_result;

    write_result = stumpless_add_entry( target, basic_entry );
    EXPECT_GT( write_result, 0 );
    EXPECT_NO_ERROR;

    read_result = stumpless_read_buffer( target, read_buffer, 5 );
    EXPECT_EQ( read_result, 5 );
    EXPECT_EQ( read_buffer[4], '\0' );
  }

  TEST_F( BufferTargetTest, WrapAround ) {
    int result;
    size_t bytes_written = 0;
    size_t write_count = 0;
    size_t read_count = 0;

    while( bytes_written <= TEST_BUFFER_LENGTH ) {
      result = stumpless_add_entry( target, basic_entry );
      EXPECT_GE( result, 0 );
      EXPECT_NO_ERROR;

      write_count++;
      bytes_written += result;
    }

    while( stumpless_read_buffer( target,
                                  read_buffer,
                                  READ_BUFFER_LENGTH ) > 1 ) {
      EXPECT_NO_ERROR;
      read_count++;
    }

    EXPECT_NO_ERROR;
    EXPECT_TRUE( read_count == write_count || read_count == write_count - 1 );
  }

  /* non-fixture tests */

  TEST( BufferTargetCloseTest, Generic ) {
    const char *target_name = "normal target";
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( target_name,
                                           buffer,
                                           sizeof( buffer ) );
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
    stumpless_close_buffer_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetCloseTest, WrongTargetType ) {
    const struct stumpless_target *target;

    target = stumpless_open_stdout_target( "not-a-buffer-target" );

    stumpless_close_buffer_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
  }

  TEST( BufferTargetOpenTest, Basic ) {
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( "normal target",
                                           buffer,
                                           sizeof( buffer ) );
    ASSERT_NOT_NULL( target );

    EXPECT_EQ( target, stumpless_get_current_target(  ) );

    stumpless_close_buffer_target( target );
  }

  TEST( BufferTargetOpenTest, MemoryAllocationFailure ) {
    void * ( *set_malloc_result )( size_t );
    char buffer[100];
    struct stumpless_target *target;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target = stumpless_open_buffer_target( "malloc-fail-buffer",
                                           buffer,
                                           sizeof( buffer ) );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST( BufferTargetOpenTest, NullBuffer ) {
    const struct stumpless_target *target;

    target = stumpless_open_buffer_target( "null-buffer",
                                           NULL,
                                           100 );
    ASSERT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( NULL,
                                           buffer,
                                           sizeof( buffer ) );
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
                                                 sizeof( buffer ) );
      EXPECT_NO_ERROR;
      ASSERT_NOT_NULL( targets[i] );
    }

    for( i=0; i < 100; i++ ) {
      stumpless_close_buffer_target( targets[i] );
    }
  }

  TEST( BufferTargetReadTest, NullTarget ) {
    char buffer[100];
    size_t result;

    result = stumpless_read_buffer( NULL, buffer, sizeof( buffer ) );
    EXPECT_EQ( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetWriteTest, WrapAroundToEndOfPreviousMessage ) {
    char buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *target;
    const struct stumpless_entry *entry;
    int write_result;
    char read_buffer[READ_BUFFER_LENGTH];
    size_t read_result;

    target = stumpless_open_buffer_target( "wrap-around-test",
                                           buffer,
                                           sizeof( buffer ) );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    entry = create_entry(  );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    write_result = stumpless_add_entry( target, entry );
    EXPECT_NO_ERROR;
    EXPECT_GT( write_result, 0 );

    stumpless_close_buffer_target( target );

    target = stumpless_open_buffer_target( "wrap-around-test",
                                           buffer,
                                           write_result + 2 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );

    write_result = stumpless_add_entry( target, entry );
    EXPECT_NO_ERROR;
    EXPECT_GT( write_result, 0 );

    write_result = stumpless_add_entry( target, entry );
    EXPECT_NO_ERROR;
    EXPECT_GT( write_result, 0 );

    read_result = stumpless_read_buffer( target,
                                         read_buffer,
                                         READ_BUFFER_LENGTH );
    EXPECT_NO_ERROR;
    EXPECT_GT( read_result, 1 );

    stumpless_close_buffer_target( target );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }
}
