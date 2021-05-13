// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"

namespace {

  class JournaldTargetTest : public::testing::Test {
    protected:
      const char *target_name = "test-journald-target";
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      target = stumpless_open_journald_target( target_name );

      stumpless_set_target_default_app_name( target, "journald-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = create_entry(  );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_close_function_target( target );
      stumpless_free_all( );
    }
  };

  TEST_F( JournaldTargetTest, AddEntry ) {
    int result;

    SCOPED_TRACE( "EntryTargetTest.AddEntry" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_EQ( result, EXPECTED_RETURN_VALUE );
    EXPECT_NO_ERROR;
  }

  /* non-fixture tests */

  TEST( JournaldTargetCloseTest, GenericCloseFunction ) {
    struct stumpless_target *target;

    target = stumpless_open_journald_target( "basic-target" );
    stumpless_close_target( target );
    EXPECT_NO_ERROR;
    stumpless_free_all(  );
  }

  TEST( JournaldTargetCloseTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_function_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( JournaldTargetCloseTest, WrongTargetType ) {
    const struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-journald-target" );
    stumpless_close_function_target( target );

    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );
  }

  TEST( JournaldTargetOpenTest, MallocFailure ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;
    void * ( *set_malloc_result )( size_t );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target = stumpless_open_journald_target( "function-target-malloc-failure" );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
    stumpless_free_all( );
  }

  TEST( JournaldTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_journald_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all( );
  }
}
