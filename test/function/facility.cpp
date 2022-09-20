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

namespace {

  class FacilityTest : public::testing::Test {
  };

  // TODO: add stumpless_get_facility_enum test

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

}
