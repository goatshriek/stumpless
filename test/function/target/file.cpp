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
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"
#include "test/helper/rfc5424.hpp"

namespace {
  class FileTargetTest : public::testing::Test {
    protected:
      const char *filename = "testfile.log";
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      target = stumpless_open_file_target( filename );

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
      stumpless_close_file_target( target );
      remove( filename );
    }
  };

  TEST_F( FileTargetTest, AddEntry ) {
    int result;

    SCOPED_TRACE( "EntryTargetTest.AddEntry" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_GE( result, 0 );
  }

  /* non-fixture tests */

  TEST( FileTargetCloseTest, Generic ) {
    const char *filename = "genericclosetest.log";
    struct stumpless_target *target;

    remove( filename );
    target = stumpless_open_file_target( filename );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_EQ( stumpless_get_current_target(  ), target );

    stumpless_close_target( target );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(  ),
               stumpless_get_default_target(  ) );
    EXPECT_STRNE( stumpless_get_current_target(  )->name,
                  filename );

    stumpless_free_all(  );
    remove( filename );
  }

  TEST( FileTargetCloseTest, NullTarget ) {
    stumpless_close_file_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( FileTargetCloseTest, WrongTargetType ) {
    struct stumpless_target *target;

    target = stumpless_open_stdout_target( "not-a-file-target" );

    stumpless_close_file_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
  }

  TEST( FileTargetFormat, NewlineSeparator ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    struct stumpless_param *param;
    const char *filename = "filetargetformattest.log";
    size_t line_count = 3;
    size_t i;

    remove( filename );
    target = stumpless_open_file_target( filename );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                "stumpless-unit-test",
                                "basic-entry",
                                "basic test message" );

    element = stumpless_new_element( "basic-element" );
    stumpless_add_element( entry, element );

    param = stumpless_new_param( "basic-param-name", "basic-param-value" );
    stumpless_add_param( element, param );

    for( i = 0; i < line_count; i++ ) {
      stumpless_add_entry( target, entry );
    }

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_file_target( target );

    TestRFC5424File( filename, line_count );
    remove( filename );
  }

  TEST( FileTargetOpenTest, Directory ) {
    struct stumpless_target *target;
   
    target = stumpless_open_file_target( "/" );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_FILE_OPEN_FAILURE );
  }

  TEST( FileTargetOpenTest, MallocFailure ) {
    const char *filename = "open-malloc-fail.log";
    struct stumpless_target *target;
    void *(*set_malloc_result)(size_t);

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );
   
    target = stumpless_open_file_target( filename );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
    remove( filename );
  }

  TEST( FileTargetOpenTest, NullName ) {
    struct stumpless_target *target;

    target = stumpless_open_file_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( FileTargetOpenTest, OptionOdelay ) {
    const char *filename = "option-odelay.log";
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    struct stumpless_param *param;
    size_t line_count = 3;
    size_t i;
    int default_options;

    default_options = stumpless_get_default_options(  );

    stumpless_set_default_options( STUMPLESS_OPTION_ODELAY );

    target = stumpless_open_file_target( filename );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_NOT_NULL( target->id );

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    for( i = 0; i < line_count; i++ ) {
      stumpless_add_entry( target, entry );
    }

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target->id );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_file_target( target );

    TestRFC5424File( filename, line_count );
    remove( filename );

    stumpless_set_default_options( default_options );
  }
}
