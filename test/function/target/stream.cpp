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

#include <fstream>
#include <stddef.h>
#include <stdlib.h>
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"

namespace {
  class StreamTargetTest : public::testing::Test {
    protected:
      const char *filename = "testfile.log";
      FILE *stream;
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      stream = fopen( filename, "w+" );

      target = stumpless_open_stream_target( filename, stream, 0, 0 );

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
      stumpless_close_stream_target( target );
      fclose( stream );
    }
  };

  TEST_F( StreamTargetTest, AddEntry ) {
    int result;

    SCOPED_TRACE( "EntryTargetTest.AddEntry" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
  }

  /* non-fixture tests */

  TEST( StreamTargetCloseTest, NullTarget ) {
    struct stumpless_error *error;

    stumpless_close_stream_target( NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( StreamTargetFormat, NewlineSeparator ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    struct stumpless_param *param;
    const char *filename = "filetargetformattest.log";
    FILE *stream;
    size_t line_count = 3;
    size_t i;

    remove( filename );

    stream = fopen( filename, "w+" );
    ASSERT_TRUE( stream != NULL );

    target = stumpless_open_stream_target( filename, stream, 0, 0 );
    ASSERT_TRUE( target != NULL );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                "stumpless-unit-test",
                                "basic-entry",
                                "basic test message" );
    ASSERT_TRUE( entry != NULL );

    element = stumpless_new_element( "basic-element" );
    ASSERT_TRUE( element != NULL );
    stumpless_add_element( entry, element );

    param = stumpless_new_param( "basic-param-name", "basic-param-value" );
    ASSERT_TRUE( param != NULL );
    stumpless_add_param( element, param );

    for( i = 0; i < line_count; i++ ) {
      stumpless_add_entry( target, entry );
    }

    stumpless_destroy_entry( entry );
    stumpless_close_stream_target( target );
    fclose( stream );

    std::ifstream infile( filename );
    std::string line;
    i = 0;
    while( std::getline( infile, line ) ) {
      TestRFC5424Compliance( line.c_str() );
      i++;
    }

    EXPECT_EQ( i, line_count );
  }

  TEST( StreamTargetOpenTest, MallocFailure ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    const char *filename = "open-malloc-fail.log";
    FILE *stream;
    void *(*set_malloc_result)(size_t);

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    stream = fopen( filename, "w+" );
    EXPECT_TRUE( stream != NULL );

    target = stumpless_open_stream_target( filename, stream, 0, 0 );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    fclose( stream );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
  }

  TEST( StreamTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    const char *filename = "null-name.log";
    FILE *stream;

    stream = fopen( filename, "w+" );
    ASSERT_TRUE( stream != NULL );

    target = stumpless_open_stream_target( NULL, stream, 0, 0 );
    EXPECT_TRUE( target == NULL );

    fclose( stream );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( StreamTargetOpenTest, NullStream ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_stream_target( "no-stream-provided", NULL, 0, 0 );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( StreamTargetWriteTest, ReadOnlyStream ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    struct stumpless_entry *basic_entry;
    const char *filename = "null-name.log";
    FILE *stream;
    int result;

    basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                      "stumpless-unit-test",
                                      "basic-entry",
                                      "basic test message" );
    ASSERT_TRUE( basic_entry != NULL );

    stream = fopen( filename, "r" );
    ASSERT_TRUE( stream != NULL );

    target = stumpless_open_stream_target( filename, stream, 0, 0 );
    ASSERT_TRUE( target != NULL );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_STREAM_WRITE_FAILURE );

    stumpless_destroy_entry( basic_entry );
    fclose( stream );
    stumpless_close_stream_target( target );
  }
}
