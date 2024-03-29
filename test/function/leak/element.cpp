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
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( add_new_param )
NEW_MEMORY_COUNTER( set_param_value_by_name )

namespace {

  TEST( AddNewParamLeakTest, ErrorCondition ) {
    struct stumpless_element *element;
    const struct stumpless_element *result;

    INIT_MEMORY_COUNTER( add_new_param );

    element = stumpless_new_element( "test-element" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element );

    result = stumpless_add_new_param( NULL, "param-name", "param-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    ASSERT_NULL( result );

    stumpless_destroy_element_and_contents( element );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( add_new_param );
  }

  TEST( SetParamValueByNameLeakTest, NewAndExisting ) {
    struct stumpless_element *element;
    const struct stumpless_element *result;

    INIT_MEMORY_COUNTER( set_param_value_by_name );

    element = stumpless_new_element( "test-element" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element );

    result = stumpless_set_param_value_by_name( element, "name", "val-1" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element );

    result = stumpless_set_param_value_by_name( element, "name", "val-2" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element );

    stumpless_destroy_element_and_contents( element );
    stumpless_free_all(  );

    ASSERT_NO_LEAK( set_param_value_by_name );
  }

}
