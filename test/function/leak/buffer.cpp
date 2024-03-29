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
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_counter.hpp"

#define TEST_BUFFER_LENGTH 2048

NEW_MEMORY_COUNTER( buffer_leak )

namespace {

  TEST( BufferTargetLeakTest, TypicalUse ) {
    struct stumpless_target *target;
    char buffer[TEST_BUFFER_LENGTH];
    struct stumpless_entry *entry;
    size_t i;
    int add_result;

    INIT_MEMORY_COUNTER( buffer_leak );

    target = stumpless_open_buffer_target( "buffer-leak-testing",
                                           buffer,
                                           TEST_BUFFER_LENGTH );
    ASSERT_NOT_NULL( target );

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    for( i = 0; i < 1000; i++ ) {
      add_result = stumpless_add_entry( target, entry );
      EXPECT_NO_ERROR;
    }

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_buffer_target( target );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( buffer_leak );
  }
}
