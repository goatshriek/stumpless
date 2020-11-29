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

#include "test/helper/server.hpp"

#include <cstddef>
#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <thread>
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 16;
  const int MESSAGE_COUNT = 50;

  void
  read_network_target( const struct stumpless_target *target ) {
    const char *destination;
    const char *port;

    for( size_t i = 0; i < MESSAGE_COUNT; i++ ) {
      destination = stumpless_get_destination( target );
      EXPECT_NO_ERROR;
      port = stumpless_get_transport_port( target );
      EXPECT_NO_ERROR;
      stumpless_get_udp_max_message_size( target );
      EXPECT_NO_ERROR;
      stumpless_target_is_open( target );
      EXPECT_NO_ERROR;

      free( ( void * ) destination );
      free( ( void * ) port );
    }

    stumpless_free_thread(  );
  }

  void
  write_network_target( struct stumpless_target *target ) {
    for( size_t i = 0; i < MESSAGE_COUNT; i++ ) {
      stumpless_set_destination( target, "127.0.0.1" );
      EXPECT_NO_ERROR;
      //stumpless_set_transport_port( target, "514" );
      //EXPECT_NO_ERROR;
      //stumpless_set_udp_max_message_size( target, 3200 );
      //EXPECT_NO_ERROR;
    }

    stumpless_free_thread(  );
  }

#define BINDING_DISABLED_WARNING "some network tests will not run without the" \
                                 " ability to listen on a local socket to"     \
                                 " receive messages."

  TEST( Udp4WriteConsistency, SimultaneousWrites ) {
    bool udp_fixtures_enabled = true;
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT*3];
    socket_handle_t handle;

    // setting up to receive the sent messages
    handle = open_udp_server_socket( AF_INET, "127.0.0.1", "514" );
    if( handle == BAD_HANDLE ) {
      std::cout << "WARNING: " BINDING_DISABLED_WARNING << std::endl;
      udp_fixtures_enabled = false;
    }

    // set up the target to log to
    target = stumpless_open_udp4_target( "test-target",
                                         "127.0.0.1",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      if( udp_fixtures_enabled ) {
        std::cout << "using the server!" << std::endl;
        threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
      }

      threads[THREAD_COUNT + i] = new std::thread( read_network_target, target );
      threads[THREAD_COUNT*2 + i] = new std::thread( write_network_target, target );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      if( udp_fixtures_enabled ) {
        threads[i]->join(  );
        delete threads[i];
      }

      threads[THREAD_COUNT + i]->join(  );
      delete threads[THREAD_COUNT + i];
      threads[THREAD_COUNT*2 + i]->join(  );
      delete threads[THREAD_COUNT*2 + i];
    }

    // cleanup after the test
    stumpless_close_network_target( target );
    EXPECT_NO_ERROR;
    stumpless_free_all(  );

    close_server_socket( handle );
  }
}
