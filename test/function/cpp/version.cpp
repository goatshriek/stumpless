// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020 Joel E. Anderson
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
#include <stumpless.hpp>

using namespace stumpless;

namespace {

  class CppVersionTest : public ::testing::Test {};

  TEST( Compare, MajorDifference ) {
    Version old_version( 1, 6, 0 );
    Version new_version( 2, 0, 0 );

    EXPECT_EQ( 100, new_version.Compare( old_version ) );
    EXPECT_EQ( -100, old_version.Compare( new_version ) );
  }

  TEST( Compare, MinorDifference ) {
    Version old_version( 1, 5, 0 );
    Version new_version( 1, 6, 0 );

    EXPECT_EQ( 10, new_version.Compare( old_version ) );
    EXPECT_EQ( -10, old_version.Compare( new_version ) );
  }

  TEST( Compare, PatchDifference ) {
    Version old_version( 1, 6, 1 );
    Version new_version( 1, 6, 2 );

    EXPECT_EQ( 1, new_version.Compare( old_version ) );
    EXPECT_EQ( -1, old_version.Compare( new_version ) );
  }

  TEST( GetVersion, Function ) {
    Version current_version = Version::GetCurrent();

    EXPECT_STREQ(Version::CURRENT_VERSION, current_version.ToString().c_str());
  }
}
