// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2021 Joel E. Anderson
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

#include <gtest/gtest.h>
#include <stumpless.h>
#include <stddef.h>
#include <stdlib.h>
#include "test/helper/assert.hpp"
#include "test/helper/memory_allocation.hpp"

namespace {

  class FacilityTest : public::testing::Test {
  };

  TEST( GetFacilityString, EachValidFacility ) {
    int facility_count = 0;
    const char *result;

    #define CHECK_FACILITY( STRING, ENUM ) \
      result = stumpless_get_facility_string( STRING ); \
      EXPECT_STREQ( result, #STRING );
    STUMPLESS_FOREACH_FACILITY( CHECK_FACILITY )
  }

  TEST( GetFacilityString, NoSuchFacility ) {
    int facility_count = 0;
    const char *result;

    #define COUNT_FACILITY( STRING, ENUM ) ++facility_count;
    STUMPLESS_FOREACH_FACILITY( COUNT_FACILITY )

    stumpless_facility wrong_facility =
        static_cast<stumpless_facility>(facility_count + 1);

    result = stumpless_get_facility_string( wrong_facility );
    EXPECT_STREQ( result, "NO_SUCH_FACILITY" );
  }

  TEST( GetFacilityEnum, EachValidFacility ) {
    int facility_count = 0;
    int result;

    #define CHECK_FACILITY_ENUM( STRING, ENUM ) \
      result = stumpless_get_facility_enum( #STRING + 19 ); \
      EXPECT_EQ( result, ENUM );
    STUMPLESS_FOREACH_FACILITY( CHECK_FACILITY_ENUM )
  }

  TEST( GetFacilityEnum, LowercaseFacility ) {
    int result;

    result = stumpless_get_facility_enum( "user" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_USER );
    result = stumpless_get_facility_enum( "mail" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_MAIL );
    result = stumpless_get_facility_enum( "daemon" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_DAEMON );
    result = stumpless_get_facility_enum( "auth" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_AUTH );
    result = stumpless_get_facility_enum( "security" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_AUTH );
    result = stumpless_get_facility_enum( "syslog" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_SYSLOG );
    result = stumpless_get_facility_enum( "lpr" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_LPR );
    result = stumpless_get_facility_enum( "news" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_NEWS );
    result = stumpless_get_facility_enum( "uucp" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_UUCP );
    result = stumpless_get_facility_enum( "cron" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_CRON );
    result = stumpless_get_facility_enum( "authpriv" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_AUTH2 );
    result = stumpless_get_facility_enum( "ftp" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_FTP );
    result = stumpless_get_facility_enum( "ntp" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_NTP );
    result = stumpless_get_facility_enum( "audit" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_AUDIT );
    result = stumpless_get_facility_enum( "alert" );
    EXPECT_EQ( result, STUMPLESS_FACILITY_ALERT );
  }

  TEST( GetFacilityEnum, InvalidMemFacility ) {
    int result;
    void * (*set_malloc_result)(size_t);
    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_get_facility_enum( "user" );
    EXPECT_EQ( result, -1 );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST( GetFacilityEnum, NoSuchFacility ) {
    int result;

    result = stumpless_get_facility_enum( "an_invalid_facility" );
    EXPECT_EQ( result, -1 );
  }

}
