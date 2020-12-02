// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2020 Joel E. Anderson
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

  TEST( ErrorLeakTest, FreeAllDeallocatesStaticError ) {
    INIT_MEMORY_COUNTER( free_all );

    // cause an error
    stumpless_new_param( NULL, NULL );
    ASSERT_TRUE( stumpless_has_error(  ) );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( free_all );
  }
}
