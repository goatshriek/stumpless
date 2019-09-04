// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>
#include <Version.hpp>

using namespace stumplesscpp;

namespace {

  class CppVersionTest : public ::testing::Test {};

  TEST( GetVersion, Function ) {
    Version current_version = Version::GetCurrent();

    EXPECT_STREQ(Version::CURRENT_VERSION, current_version.ToString().c_str());
  }
}
