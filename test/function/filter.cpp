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

#include <cstddef>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"

namespace {

  static const size_t TEST_BUFFER_LENGTH = 8192;

  class FilterTest : public::testing::Test {
  protected:
    char buffer[TEST_BUFFER_LENGTH];
    struct stumpless_target *target;
    struct stumpless_entry *entry;

    virtual void
    SetUp( void ) {
      target = stumpless_open_buffer_target( "filter-target",
                                             buffer,
                                             sizeof( buffer ) );

      entry = create_entry(  );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( entry );
      stumpless_close_buffer_target( target );
      stumpless_free_all(  );
    }
  };

  TEST_F( FilterTest, MaskFilterAccept ) {
    int mask;

    ASSERT_NOT_NULL( entry );
    ASSERT_NOT_NULL( target );

    mask = STUMPLESS_SEVERITY_MASK( STUMPLESS_SEVERITY_INFO_VALUE );
    stumpless_set_target_mask( target, mask );
    EXPECT_NO_ERROR;

    stumpless_set_entry_severity( entry, STUMPLESS_SEVERITY_INFO );
    EXPECT_NO_ERROR;

    EXPECT_TRUE( stumpless_mask_filter( target, entry ) );

  }

  TEST_F( FilterTest, MaskFilterReject ) {
    int mask;

    ASSERT_NOT_NULL( entry );
    ASSERT_NOT_NULL( target );

    mask = ~STUMPLESS_SEVERITY_MASK( STUMPLESS_SEVERITY_INFO_VALUE );
    stumpless_set_target_mask( target, mask );
    EXPECT_NO_ERROR;

    stumpless_set_entry_severity( entry, STUMPLESS_SEVERITY_INFO );
    EXPECT_NO_ERROR;

    EXPECT_FALSE( stumpless_mask_filter( target, entry ) );
  }
}
