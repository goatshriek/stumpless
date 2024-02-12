// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2024 Joel E. Anderson
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
#include <test/helper/assert.hpp>
#include <test/helper/fixture.hpp>

namespace {
  class ChainTargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target = NULL;

      void
      SetUp( void ) override {
        target = stumpless_new_chain( "test-fixture" );
      }

      void
      TearDown( void ) override {
        stumpless_close_chain_and_contents( target );
        stumpless_free_all();
      }
  };

  TEST_F( ChainTargetTest, AddEntry ) {
    struct stumpless_entry *entry;
    int result;

    entry = create_entry();

    result = stumpless_add_entry( target, entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    stumpless_destroy_entry_and_contents( entry );
  }
}
