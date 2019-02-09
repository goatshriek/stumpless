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
#include <stdlib.h>
#include <string.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/function/rfc5424.hpp"

#define TEST_BUFFER_LENGTH 8192

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

  TEST_F( BufferTargetTest, LargeReallocFailure ) {
    char test_string[4096];
    void * (*realloc_result)(void *, size_t);
    int result;
    struct stumpless_error *error;

    ASSERT_EQ( target, stumpless_get_current_target(  ) );

    realloc_result = stumpless_set_realloc( [](void *, size_t)->void *{ return NULL; } );
    EXPECT_TRUE( realloc_result != NULL );

    memset( test_string, 'h', 4095 );
    test_string[4095] = '\0';
    result = stumpless( test_string );

    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    realloc_result = stumpless_set_realloc( realloc );
    ASSERT_TRUE( realloc == realloc_result );
  }

  TEST_F( BufferTargetTest, OverFill ) {
    char test_string[TEST_BUFFER_LENGTH + 1];
    struct stumpless_error *error;

    ASSERT_TRUE( stumpless_get_current_target(  ) != NULL );

    memset( test_string, 'g', TEST_BUFFER_LENGTH );
    test_string[TEST_BUFFER_LENGTH] = '\0';
    ASSERT_EQ( -1, stumpless( test_string ) );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_TOO_BIG );
  }

  TEST_F( BufferTargetTest, WrapAround ) {
    size_t bytes_written=0, write_count=0, null_count=0, i;
    int result;

    memset( buffer, 0, TEST_BUFFER_LENGTH );

    while( bytes_written <= TEST_BUFFER_LENGTH ) {
      result = stumpless_add_entry( target, basic_entry );
      EXPECT_GT( result, 0 );
      EXPECT_EQ( NULL, stumpless_get_error(  ) );

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

    target = stumpless_open_buffer_target( "normal target",
                                           buffer,
                                           100,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    EXPECT_EQ( target, stumpless_get_current_target(  ) );

    stumpless_close_buffer_target( target );
  }

  TEST( BufferTargetOpenTest, NullBuffer ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_buffer_target( "null-buffer",
                                           NULL,
                                           100,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( BufferTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    char buffer[100];

    target = stumpless_open_buffer_target( NULL,
                                           buffer,
                                           100,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
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
      ASSERT_TRUE( targets[i] != NULL );
      ASSERT_EQ( NULL, stumpless_get_error(  ) );
    }

    for( i=0; i < 100; i++ ) {
      stumpless_close_buffer_target( targets[i] );
    }
  }
}
