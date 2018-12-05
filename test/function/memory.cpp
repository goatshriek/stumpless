// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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
#include <gtest/gtest.h>
#include <stumpless.h>

namespace {

  class MemoryTest : public ::testing::Test {};

  TEST( FreeAllTest, SimpleCall ) {
    stumpless_free_all(  );
  }

  TEST( SetFreeTest, CustomFunction ) {
    void (*result)(void *);

    result = stumpless_set_free( [](void *ptr){ return; } );
    EXPECT_TRUE( result != NULL );

    result = stumpless_set_free( free );
    ASSERT_TRUE( result == free );
  }

  TEST( SetFreeTest, NullFunction ) {
    void (*result)(void *);

    result = stumpless_set_free( NULL );
    ASSERT_EQ( NULL, result );
  }

  TEST( SetMallocTest, NullFunction ) {
    void * (*result)(size_t);

    result = stumpless_set_malloc( NULL );
    ASSERT_EQ( NULL, result );
  }

  TEST( SetReallocTest, NullFunction ) {
    void * (*result)(void *, size_t);
    struct stumpless_error *error;

    result = stumpless_set_realloc( NULL );
    ASSERT_EQ( NULL, result );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

}
