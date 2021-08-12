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

#include <cstddef>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <stumpless.hpp>

using namespace stumpless;

namespace {

  class CppJournaldTargetTest : public::testing::Test {
  protected:
    Entry *basic_entry;
    JournaldTarget *target;
    const char *target_name = "cpp-journald-test";

    virtual void
    SetUp( void ) {
      basic_entry = new Entry( Facility::USER,
                               Severity::INFO,
                               "stumpless-cpp-testing",
                               "basic-msg",
                               "This is a basic entry." );

      target = new JournaldTarget( target_name );
    }

    virtual void
    TearDown( void ) {
      delete target;
      delete basic_entry;
    }
  };

  TEST_F( CppJournaldTargetTest, BasicLog ) {
    target->Log( *basic_entry );
  }

  TEST_F( CppJournaldTargetTest, SetDefaultAppNameNull ) {
    EXPECT_THROW( target->SetDefaultAppName( NULL ), StumplessException * );
  }

  /* non-fixture tests */

  TEST( JournaldConstructor, NullName ) {
    EXPECT_THROW( JournaldTarget test( ( const char * ) NULL ),
                  StumplessException * );
  }

}
