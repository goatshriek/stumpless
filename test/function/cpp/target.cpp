// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2022 Joel E. Anderson
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

#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.hpp>

using namespace stumpless;

namespace {

  class CppTargetTest : public::testing::Test {
  protected:
    StreamTarget *target;

    virtual void
    SetUp( void ) {
      target = new StreamTarget( "test-target", stdout );
    }

    virtual void
    TearDown( void ) {
      delete target;
    }

  };

  TEST_F( CppTargetTest, GetMask ) {
    target->GetMask(  );
  }

  TEST_F( CppTargetTest, SetMask ) {
    int old_mask = target->GetMask(  );
    int new_mask = STUMPLESS_SEVERITY_MASK_UPTO( STUMPLESS_SEVERITY_ERR );
    ASSERT_NE( old_mask, new_mask );

    target->SetMask( new_mask );

    int actual_mask = target->GetMask(  );
    EXPECT_EQ( actual_mask, new_mask );
  }
}
