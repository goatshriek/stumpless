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
#include <stumpless.h>
#include "test/helper/assert.hpp"

namespace {

  TEST( NetworkTargetTest, Add ) {
    struct stumpless_target *target;
    char unused_buffer[100];
    struct stumpless_entry *entry;
    const struct stumpless_error *error;
    int result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );

    target = stumpless_open_buffer_target( "fake-network-target",
                                           unused_buffer,
                                           sizeof( unused_buffer ) );
    target->type = STUMPLESS_NETWORK_TARGET;

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    stumpless_destroy_entry_and_contents( entry );

    target->type = STUMPLESS_BUFFER_TARGET;
    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetTest, GenericClose ) {
    struct stumpless_target *target;
    char unused_buffer[100];
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "fake-network-target",
                                           unused_buffer,
                                           sizeof( unused_buffer ) );
    target->type = STUMPLESS_NETWORK_TARGET;

    stumpless_close_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_BUFFER_TARGET;
    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetTest, IsOpen ) {
    struct stumpless_target *target;
    char unused_buffer[100];
    const struct stumpless_target *result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "fake-network-target",
                                           unused_buffer,
                                           sizeof( unused_buffer ) );
    target->type = STUMPLESS_NETWORK_TARGET;

    result = stumpless_target_is_open( target );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_BUFFER_TARGET;
    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetTest, Open ) {
    struct stumpless_target *target;
    char unused_buffer[100];
    const struct stumpless_target *result;
    const struct stumpless_error *error;

    target = stumpless_open_buffer_target( "fake-network-target",
                                           unused_buffer,
                                           sizeof( unused_buffer ) );
    target->type = STUMPLESS_NETWORK_TARGET;

    result = stumpless_open_target( target );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_BUFFER_TARGET;
    stumpless_close_buffer_target( target );
  }
}
