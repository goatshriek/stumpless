// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021-2024 Joel E. Anderson
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
#include "test/helper/memory_allocation.hpp"

namespace {
  const int EXPECTED_FAILURE_VALUE = -66;
  const int EXPECTED_RETURN_VALUE = 342;

  int
  basic_log_function( const struct stumpless_target *target,
                      const struct stumpless_entry *entry ) {
    EXPECT_NOT_NULL( target );
    EXPECT_NOT_NULL( entry );
    return EXPECTED_RETURN_VALUE;
  }

  int
  failing_log_function( const struct stumpless_target *target,
                        const struct stumpless_entry *entry ) {
    return EXPECTED_FAILURE_VALUE;
  }

  class FunctionTargetTest : public::testing::Test {
    protected:
      const char *target_name = "test-function-target";
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      target = stumpless_open_function_target( target_name,
                                               basic_log_function );

      stumpless_set_target_default_app_name( target, "function-target-test" );
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
      stumpless_close_function_target( target );
      stumpless_free_all( );
    }
  };

  TEST_F( FunctionTargetTest, AddEntry ) {
    int result;

    SCOPED_TRACE( "EntryTargetTest.AddEntry" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_EQ( result, EXPECTED_RETURN_VALUE );
    EXPECT_NO_ERROR;
  }

  /* non-fixture tests */

  TEST( FunctionTargetCloseTest, GenericCloseFunction ) {
    struct stumpless_target *target;

    target = stumpless_open_function_target( "basic-target", basic_log_function );
    stumpless_close_target( target );
    EXPECT_NO_ERROR;
    stumpless_free_all(  );
  }

  TEST( FunctionTargetCloseTest, NullTarget ) {
    stumpless_close_function_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( FunctionTargetCloseTest, WrongTargetType ) {
    const struct stumpless_target *target;

    target = stumpless_open_stdout_target( "not-a-function-target" );

    stumpless_close_function_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
  }

  TEST( FunctionTargetFailureTest, FunctionFailure ) {
    struct stumpless_target *target;
    int result;

    target = stumpless_open_function_target( "failing-function-target",
                                             failing_log_function );
    ASSERT_NOT_NULL( target );

    result = stumpless_add_message( target, "testing, 1, 2, 3..." );
    EXPECT_EQ( result, EXPECTED_FAILURE_VALUE );
    EXPECT_ERROR_ID_EQ( STUMPLESS_FUNCTION_TARGET_FAILURE );

    stumpless_close_function_target( target );
    stumpless_free_all( );
  }

  TEST( FunctionTargetOpenTest, MallocFailure ) {
    struct stumpless_target *target;
    void * ( *set_malloc_result )( size_t );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target = stumpless_open_function_target( "function-target-malloc-failure",
                                             basic_log_function );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
    stumpless_free_all( );
  }

  TEST( FunctionTargetOpenTest, MallocFailureOnFuncPointerSize ) {
    struct stumpless_target *target;
    void * ( *set_malloc_result )( size_t );

    set_malloc_result = stumpless_set_malloc(
      MALLOC_FAIL_ON_SIZE( sizeof( set_malloc_result ) ) );
    ASSERT_NOT_NULL( set_malloc_result );

    target = stumpless_open_function_target( "function-target-malloc-failure",
                                             basic_log_function );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
    stumpless_free_all( );
  }

  TEST( FunctionTargetOpenTest, NullFunction ) {
    struct stumpless_target *target;

    target = stumpless_open_function_target( "null-function-test", NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all( );
  }

  TEST( FunctionTargetOpenTest, NullName ) {
    struct stumpless_target *target;

    target = stumpless_open_function_target( NULL, basic_log_function );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all( );
  }
}
