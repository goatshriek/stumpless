// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2024 Joel E. Anderson
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
#include "test/helper/fixture.hpp"
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( add_new_element_leak )
NEW_MEMORY_COUNTER( set_app_name_leak )
NEW_MEMORY_COUNTER( set_param_value_by_name )

namespace {

  TEST( AddNewElementLeakTest, ErrorCondition ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    INIT_MEMORY_COUNTER( add_new_element_leak );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "app-name",
                                 "msgid",
                                 "the message" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_add_new_element( NULL, "new-element" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    ASSERT_NULL( result );

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( add_new_element_leak );
  }

  TEST( SetAppNameLeakTest, TypicalUse ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    INIT_MEMORY_COUNTER( set_app_name_leak );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "initial-app-name",
                                 "msgid",
                                 "your message goes here" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_app_name( entry, "new-app-name" );
    EXPECT_NO_ERROR;
    ASSERT_EQ( result, entry );

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( set_app_name_leak );
  }

  TEST( SetParamValueByNameLeakTest, NewAndExisting ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    INIT_MEMORY_COUNTER( set_param_value_by_name );

    entry = create_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_param_value_by_name( entry,
                                                      "element-name",
                                                      "param-name",
                                                      "new-value-1" );
    EXPECT_NO_ERROR;
    ASSERT_EQ( result, entry );

    result = stumpless_set_entry_param_value_by_name( entry,
                                                      "element-name",
                                                      "param-name",
                                                      "new-value-2" );
    EXPECT_NO_ERROR;
    ASSERT_EQ( result, entry );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );

    ASSERT_NO_LEAK( set_param_value_by_name );
  }
}
