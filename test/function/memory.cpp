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
#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"

namespace {

  class MemoryTest : public ::testing::Test {};

  TEST( FreeAllTest, SimpleCall ) {
    stumpless_free_all(  );
  }

  TEST( SetFreeTest, CustomFunction ) {
    void (*result)(void *);

    result = stumpless_set_free( [](void *ptr){ return; } );
    EXPECT_NOT_NULL( result );

    result = stumpless_set_free( free );
    ASSERT_TRUE( result == free );
  }

  TEST( SetFreeTest, NullFunction ) {
    void (*result)(void *);

    result = stumpless_set_free( NULL );
    ASSERT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SetMallocTest, NullFunction ) {
    void * (*result)(size_t);

    result = stumpless_set_malloc( NULL );
    ASSERT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SetReallocTest, NullFunction ) {
    void * (*result)(void *, size_t);

    result = stumpless_set_realloc( NULL );
    ASSERT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST(MemoryFunctionsTest, GetMalloc) {
    auto malloc_function = stumpless_get_malloc();
    EXPECT_EQ(malloc_function, malloc);
  }

  TEST(MemoryFunctionsTest, GetFree) {
    auto free_function = stumpless_get_free();
    EXPECT_EQ(free_function, free);
  }

  TEST(MemoryFunctionsTest, GetRealloc) {
    auto realloc_function = stumpless_get_realloc();
    EXPECT_EQ(realloc_function, realloc);
  }

}
