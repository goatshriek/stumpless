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
#include <Entry.hpp>
#include <WelTarget.hpp>

using namespace stumplesscpp;

namespace {
  TEST( CppSetEntryCategories, Basics ) {
    Entry basic_entry( STUMPLESS_FACILITY_USER,
                       STUMPLESS_SEVERITY_INFO,
                       "cpp-wel-test",
                       "simple-entry",
                       "my message" );

    // use dummy values as this won't actually be logged
    basic_entry.SetCategory( 12 );
    basic_entry.SetEventId( 13 );
    basic_entry.SetType( 14 );
  }
}
