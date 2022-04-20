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

#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_counter.hpp"

#define TEST_BUFFER_LENGTH 2048

NEW_MEMORY_COUNTER( wel_entry_leak )

namespace {

  TEST( WelEntryLeakTest, AfterInsertionStringSet ) {
    struct stumpless_entry *entry;

    INIT_MEMORY_COUNTER( wel_entry_leak );

    entry = create_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    stumpless_set_wel_insertion_string( entry, 0, "testing" );
    EXPECT_NO_ERROR;

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );

    ASSERT_NO_LEAK( wel_entry_leak );
  }
}
