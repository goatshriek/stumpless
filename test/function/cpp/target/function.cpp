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

  const int EXPECTED_FAILURE_VALUE = -687;
  const int EXPECTED_RETURN_VALUE = 645;

  int
  basic_function( const struct stumpless_target *target,
                  const struct stumpless_entry *entry ) {
    return EXPECTED_RETURN_VALUE;
  }

  int
  failing_log_function( const struct stumpless_target *target,
                        const struct stumpless_entry *entry ) {
    return EXPECTED_FAILURE_VALUE;
  }

  class CppFunctionTargetTest : public::testing::Test {
  protected:
    Entry *basic_entry;
    FunctionTarget *target;
    const char *target_name = "cpp-function-test";

    virtual void
    SetUp( void ) {
      basic_entry = new Entry( Facility::USER,
                               Severity::INFO,
                               "stumpless-cpp-testing",
                               "basic-msg",
                               "This is a basic entry." );

      target = new FunctionTarget( target_name, basic_function );
    }
  };

  TEST_F( CppFunctionTargetTest, BasicLog ) {
    target->Log( *basic_entry );
  }

  TEST_F( CppFunctionTargetTest, SetDefaultAppNameNull ) {
    EXPECT_THROW( target->SetDefaultAppName( NULL ), StumplessException * );
  }

  /* non-fixture tests */

  TEST( Constructor, NullFunction ) {
    EXPECT_THROW( FunctionTarget test( "null-function-test", NULL ), StumplessException * );
  }

  TEST( Constructor, NullName ) {
    EXPECT_THROW( FunctionTarget test( NULL, basic_function ), StumplessException * );
  }

  TEST( FunctionTargetFailure, BasicFailure ) {
    FunctionTarget test( "failing-function-target", failing_log_function );
    EXPECT_THROW( test.Log( "this will FAIL" ), StumplessException * );
  }

}
