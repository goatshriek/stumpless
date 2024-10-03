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

namespace {

  class PrivalTest : public::testing::Test {};

  TEST( GetPrivalFromString, NumValidPriority ) {
    int result;

    result = stumpless_prival_from_string( "119" );
    EXPECT_EQ( result, 119 );
  }

  TEST( GetPrivalFromString, NumTooHighPriority ) {
    int result;

    result = stumpless_prival_from_string( "192" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPrivalFromString, NumInvalidPriority ) {
    int result;

    result = stumpless_prival_from_string( "119aa" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPrivalFromString, UpperValidPriority ) {
    int result;

    result = stumpless_prival_from_string( "USER.INFO" );
    EXPECT_EQ( result, 14 );
  }

  TEST( GetPrivalFromString, LowerValidPriority ) {
    int result;

    result = stumpless_prival_from_string( "user.info" );
    EXPECT_EQ( result, 14 );
  }

  TEST( GetPrivalFromString, EmptyPriority ) {
    int result;

    result = stumpless_prival_from_string( "" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( GetPrivalFromString, NullPriority ) {
    int result;

    result = stumpless_prival_from_string( NULL );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( GetPrivalFromString, InvalidFacilityPriority ) {
    int result;

    result = stumpless_prival_from_string( "umer.info" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPrivalFromString, InvalidSeverityPriority ) {
    int result;

    result = stumpless_prival_from_string( "user.imfo" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPrivalFromString, InvalidNoPeriodPriority ) {
    int result;

    result = stumpless_prival_from_string( "userinfo" );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST( GetPrivalFromString, InvalidMorePeriodPriority ) {
    int result;

    result = stumpless_prival_from_string( "user.info." );
    EXPECT_EQ( result, -1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
  }

  TEST(GetPrivalString, ValidPrival) {
    int prival;
    const char *result;

    prival = STUMPLESS_SEVERITY_ERR | STUMPLESS_FACILITY_USER;
    result = stumpless_get_prival_string( prival );
    EXPECT_STREQ( result, "STUMPLESS_SEVERITY_ERR | STUMPLESS_FACILITY_USER" );

    free( ( void * ) result );
  }

  TEST(GetPriorityString, ValidPrival) {
    int prival;
    const char *result;

    prival = STUMPLESS_SEVERITY_ERR | STUMPLESS_FACILITY_USER;
    result = stumpless_get_priority_string( prival );
    EXPECT_STREQ( result, "STUMPLESS_FACILITY_USER.STUMPLESS_SEVERITY_ERR" );

    free( ( void * ) result );
  }
}
