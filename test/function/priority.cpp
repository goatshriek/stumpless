// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2024 Joel E. Anderson
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
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/memory_allocation.hpp"

namespace {

  class PriorityTest : public::testing::Test {
  };

  TEST( GetPriorityValue, NumValidPriority ) {
    int result;

    result = stumpless_prival_from_string( "119" );
    EXPECT_EQ( result, 119 );
  }

  TEST( GetPriorityValue, NumTooHighPriority ) {
    int result;

    result = stumpless_prival_from_string( "192" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPriorityValue, NumInvalidPriority ) {
    int result;

    result = stumpless_prival_from_string( "119aa" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPriorityValue, UpperValidPriority ) {
    int result;

    result = stumpless_prival_from_string( "USER.INFO" );
    EXPECT_EQ( result, 14 );
  }

  TEST( GetPriorityValue, LowerValidPriority ) {
    int result;

    result = stumpless_prival_from_string( "user.info" );
    EXPECT_EQ( result, 14 );
  }

  TEST( GetPriorityValue, EmptyPriority ) {
    int result;

    result = stumpless_prival_from_string( "" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( GetPriorityValue, NullPriority ) {
    int result;

    result = stumpless_prival_from_string( NULL );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( GetPriorityValue, InvalidFacilityPriority ) {
    int result;

    result = stumpless_prival_from_string( "umer.info" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPriorityValue, InvalidSeverityPriority ) {
    int result;

    result = stumpless_prival_from_string( "user.imfo" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPriorityValue, InvalidNoPeriodPriority ) {
    int result;

    result = stumpless_prival_from_string( "userinfo" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPriorityValue, InvalidMorePeriodPriority ) {
    int result;

    result = stumpless_prival_from_string( "user.info." );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPriorityValue, InvalidMemFacilityPriority ) {
    int result;
    void * (*set_malloc_result)(size_t);
    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_prival_from_string( "user.err" );
    EXPECT_EQ( result, -1 );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST( GetPriorityValue, InvalidMemSeverityPriority ) {
    int result;
    void * (*set_malloc_result)(size_t);
    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 4 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_prival_from_string( "syslog.err" );
    EXPECT_EQ( result, -1 );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

}
