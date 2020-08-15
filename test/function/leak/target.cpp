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

#include <stddef.h>
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/memory_counter.hpp"

#define TEST_BUFFER_LENGTH 2048

NEW_MEMORY_COUNTER( add_message_leak )

namespace {

  TEST( AddMessageLeakTest, TypicalUse ) {
    struct stumpless_target *target;
    char buffer[TEST_BUFFER_LENGTH];
    int i;
    int add_result;

    INIT_MEMORY_COUNTER( add_message_leak );

    target = stumpless_open_buffer_target( "add-message-leak-testing",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    for( i = 0; i < 1000; i++ ) {
      add_result = stumpless_add_message( target, "temp message %d", i );
      ASSERT_GE( add_result, 0 );
    }

    stumpless_close_buffer_target( target );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( add_message_leak );
  }
}
