// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2021 Joel E. Anderson
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
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"

namespace {

  TEST( GetDefaultTarget, SocketUnsupported ) {
    struct stumpless_target *target;

    target = stumpless_get_default_target(  );
    EXPECT_TRUE( target != NULL );

    if( target ) {
      EXPECT_NE( target->type, STUMPLESS_SOCKET_TARGET );
    }

    stumpless_free_all(  );
  }

  TEST( SocketTargetTest, GenericClose ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "fake-socket-target" );
    ASSERT_NOT_NULL( target );

    target->type = STUMPLESS_SOCKET_TARGET;

    stumpless_close_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_STREAM_TARGET;
    stumpless_close_stream_target( target );
    stumpless_free_all(  );
  }

  TEST( SocketTargetTest, Unsupported ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    const struct stumpless_error *error;
    int result;

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    target = stumpless_open_stdout_target( "fake-socket-target" );
    ASSERT_NOT_NULL( target );

    target->type = STUMPLESS_SOCKET_TARGET;

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_UNSUPPORTED );

    target->type = STUMPLESS_STREAM_TARGET;
    stumpless_close_stream_target( target );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }
}
