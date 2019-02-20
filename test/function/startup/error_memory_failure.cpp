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

#include <stddef.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include <stumpless.h>

namespace {

  TEST( ErrorMemoryAllocationFailureTest, Initialization ) {
    void *(*result)(size_t);
    struct stumpless_param *param;
   
    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( result != NULL );

    // this will create an immediate failure
    param = stumpless_new_param( NULL, NULL );

    EXPECT_TRUE( param == NULL );

    // this is fine - really we just want to ensure this doesn't crash
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    stumpless_set_malloc( malloc );
  }

}
