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

NEW_MEMORY_COUNTER( tcp4_leak )

namespace {

  TEST( Tcp4TargetLeakTest, TypicalUse ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    size_t i;
    socket_handle_t handle;
    socket_handle_t accepted = BAD_HANDLE;
    char buffer[1024];

    handle = open_tcp4_server_socket( "127.0.0.1", "514" );
    if( handle != BAD_HANDLE ) {
      INIT_MEMORY_COUNTER( tcp4_leak );

      target = stumpless_open_tcp4_target( "test-self", "127.0.0.1" );
      ASSERT_NOT_NULL( target );

      entry = create_entry(  );
      ASSERT_NOT_NULL( entry );

      for( i = 0; i < 1000; i++ ) {
        stumpless_add_entry( target, entry );
        EXPECT_NO_ERROR;

        if( accepted == BAD_HANDLE ) {
          accepted = accept_tcp_connection( handle );
        }

        recv_from_handle( accepted, buffer, 1024 );
      }

      stumpless_destroy_entry_and_contents( entry );
      stumpless_close_network_target( target );

      stumpless_free_all(  );

      close_server_socket( handle );
      close_server_socket( accepted );

      ASSERT_NO_LEAK( tcp4_leak );
    }
  }
}
