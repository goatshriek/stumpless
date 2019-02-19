// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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

#include <gtest/gtest.h>
#include <stddef.h>
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( free_all )

namespace {

  TEST( ErrorLeakTest, FreeAll ) {
    struct stumpless_error *error;

    INIT_MEMORY_COUNTER( free_all );
    stumpless_set_malloc( free_all_memory_counter_malloc );
    stumpless_set_realloc( free_all_memory_counter_realloc );
    stumpless_set_free( free_all_memory_counter_free );

    // cause an error
    stumpless_new_param( NULL, NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );

    stumpless_free_all(  );

    EXPECT_EQ( free_all_memory_counter.alloc_total,
               free_all_memory_counter.free_total );
  }

}
