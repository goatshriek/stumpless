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
#include <gtest/gtest.h>
#include <limits.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"

extern "C" {
#include "private/inthelper.h"
}

namespace {

  class InthelperTest : public ::testing::Test {};

  TEST( CapSizeTToInt, Zero ) {
    int result = cap_size_t_to_int( 0 );
    EXPECT_EQ( result, 0 );
  }

  TEST( CapSizeTToInt, One ) {
    int result = cap_size_t_to_int( 1 );
    EXPECT_EQ( result, 1 );
  }

  TEST( CapSizeTToInt, SmallValue ) {
    int result = cap_size_t_to_int( 100 );
    EXPECT_EQ( result, 100 );
  }

  TEST( CapSizeTToInt, IntMax ) {
    int result = cap_size_t_to_int( ( size_t ) INT_MAX );
    EXPECT_EQ( result, INT_MAX );
  }

  TEST( CapSizeTToInt, JustOverIntMax ) {
    int result = cap_size_t_to_int( ( size_t ) INT_MAX + 1 );
    EXPECT_EQ( result, INT_MAX );
  }

  TEST( CapSizeTToInt, LargeValue ) {
    int result = cap_size_t_to_int( ( size_t ) INT_MAX * 2 );
    EXPECT_EQ( result, INT_MAX );
  }

  TEST( CapSizeTToInt, SizeMax ) {
    int result = cap_size_t_to_int( SIZE_MAX );
    EXPECT_EQ( result, INT_MAX );
  }

  TEST( SizeTToInt, Zero ) {
    int result = size_t_to_int( 0 );
    EXPECT_EQ( result, 0 );
  }

  TEST( SizeTToInt, One ) {
    int result = size_t_to_int( 1 );
    EXPECT_EQ( result, 1 );
  }

  TEST( SizeTToInt, SmallValue ) {
    int result = size_t_to_int( 100 );
    EXPECT_EQ( result, 100 );
  }

  TEST( SizeTToInt, IntMax ) {
    int result = size_t_to_int( ( size_t ) INT_MAX );
    EXPECT_EQ( result, INT_MAX );
  }

  TEST( SizeTToInt, JustOverIntMax ) {
    int result = size_t_to_int( ( size_t ) INT_MAX + 1 );
    EXPECT_EQ( result, -1 );
  }

  TEST( SizeTToInt, LargeValue ) {
    int result = size_t_to_int( ( size_t ) INT_MAX * 2 );
    EXPECT_EQ( result, -1 );
  }

  TEST( SizeTToInt, SizeMax ) {
    int result = size_t_to_int( SIZE_MAX );
    EXPECT_EQ( result, -1 );
  }

}
