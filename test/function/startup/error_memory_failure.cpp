// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2024 Joel E. Anderson
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
#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/memory_allocation.hpp"

namespace {

  TEST( ErrorMemoryAllocationFailureTest, Initialization ) {
    void *(*result)(size_t);
    const struct stumpless_param *param;
    const struct stumpless_error *error;

    result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( result );

    // this will create an immediate failure
    param = stumpless_new_param( NULL, NULL );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_set_malloc( malloc );
  }

}
