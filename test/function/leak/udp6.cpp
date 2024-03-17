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

#include "test/helper/server.hpp"

#include <cstddef>
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( set_port )
NEW_MEMORY_COUNTER( udp6_leak )

namespace {

  TEST( Udp6TargetLeakTest, SetPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;

    INIT_MEMORY_COUNTER( set_port );

    target = stumpless_open_udp6_target( "set-port-leak", "::1" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    result = stumpless_set_transport_port( target, "6514" );
    ASSERT_NOT_NULL( result );

    stumpless_close_network_target( target );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( set_port );
  }

  TEST( Udp6TargetLeakTest, TypicalUse ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    size_t i;
    int add_result;
    socket_handle_t handle;
    bool fixture_enabled = true;

    handle = open_udp6_server_socket( "::1", "514" );
    if( handle == BAD_HANDLE ) {
      fixture_enabled = false;
    }

    INIT_MEMORY_COUNTER( udp6_leak );

    target = stumpless_open_udp6_target( "test-self", "::1" );
    ASSERT_NOT_NULL( target );

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    for( i = 0; i < 1000; i++ ) {
      add_result = stumpless_add_entry( target, entry );
      if( fixture_enabled ) {
        EXPECT_GE( add_result, 0 );
        EXPECT_NO_ERROR;
      }
    }

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_network_target( target );

    stumpless_free_all(  );

    close_server_socket( handle );

    ASSERT_NO_LEAK( udp6_leak );
  }
}
