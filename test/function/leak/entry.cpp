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

#include <stddef.h>
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( set_app_name_leak )

namespace {

  TEST( SetAppNameLeakTest, TypicalUse ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    INIT_MEMORY_COUNTER( set_app_name_leak );
    stumpless_set_malloc( set_app_name_leak_memory_counter_malloc );
    stumpless_set_realloc( set_app_name_leak_memory_counter_realloc );
    stumpless_set_free( set_app_name_leak_memory_counter_free );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "initial-app-name",
                                 "msgid",
                                 "your message goes here" );
    EXPECT_NO_ERROR;
    ASSERT_TRUE( entry != NULL );

    result = stumpless_set_entry_app_name( entry, "new-app-name" );
    EXPECT_NO_ERROR;
    ASSERT_TRUE( result == entry );

    stumpless_destroy_entry( entry );

    stumpless_free_all(  );

    ASSERT_EQ( set_app_name_leak_memory_counter.alloc_total,
               set_app_name_leak_memory_counter.free_total );
  }
}
