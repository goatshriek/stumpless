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

#include <cstddef>
#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.hpp>

using namespace stumplesscpp;

namespace {

  TEST( SetFreeTest, CustomFunction ) {
    void (*result)(void *);

    result = MemoryManager::SetFree( [](void *ptr){ return; } );
    EXPECT_TRUE( result != NULL );

    result = MemoryManager::SetFree( free );
    ASSERT_TRUE( result == free );
  }

  TEST( SetFreeTest, NullFunction ) {
    void (*result)(void *);

    result = MemoryManager::SetFree( NULL );
    ASSERT_EQ( NULL, result );
  }

  TEST( SetMallocTest, NullFunction ) {
    void * (*result)(size_t);

    result = MemoryManager::SetMalloc( NULL );
    ASSERT_EQ( NULL, result );
  }

  TEST( SetReallocTest, NullFunction ) {
    void * (*result)(void *, size_t);

    result = MemoryManager::SetRealloc( NULL );
    ASSERT_EQ( NULL, result );
  }

}
