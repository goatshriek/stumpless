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
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/memory_counter.hpp"
#include "test/helper/server.hpp"

#ifdef _WIN32
#  include <winsock2.h>
#else
#  include <sys/socket.h>
#endif

NEW_MEMORY_COUNTER( set_port )
NEW_MEMORY_COUNTER( udp4_leak )

namespace {

  TEST( Udp4TargetLeakTest, SetPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;

    INIT_MEMORY_COUNTER( set_port );
    stumpless_set_malloc( set_port_memory_counter_malloc );
    stumpless_set_realloc( set_port_memory_counter_realloc );
    stumpless_set_free( set_port_memory_counter_free );

    target = stumpless_open_udp4_target( "set-port-leak",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_set_transport_port( target, "6514" );
    ASSERT_TRUE( result != NULL );

    stumpless_close_network_target( target );

    stumpless_free_all(  );

    EXPECT_EQ( set_port_memory_counter.alloc_total,
               set_port_memory_counter.free_total );

  }

  TEST( Udp4TargetLeakTest, TypicalUse ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    struct stumpless_entry *result_entry;
    struct stumpless_element *element;
    struct stumpless_element *result_element;
    struct stumpless_param *param;
    size_t i;
    int add_result;
    struct stumpless_error *error;
    socket_handle_t handle;
    bool fixture_enabled = true;

    handle = open_udp_server_socket( AF_INET, "127.0.0.1", "514" );
    if( handle == BAD_HANDLE ) {
      fixture_enabled = false;
    }

    stumpless_set_malloc( udp4_leak_memory_counter_malloc );
    stumpless_set_realloc( udp4_leak_memory_counter_realloc );
    stumpless_set_free( udp4_leak_memory_counter_free );

    target = stumpless_open_udp4_target( "test-self",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "memory-leak-test",
                                 "basic-entry",
                                 "basic test message" );
    ASSERT_TRUE( entry != NULL );

    element = stumpless_new_element( "basic-element" );
    ASSERT_TRUE( element != NULL );

    result_entry = stumpless_add_element( entry, element );
    ASSERT_TRUE( result_entry != NULL );

    param = stumpless_new_param( "basic-param-name", "basic-param-value" );
    ASSERT_TRUE( param != NULL );

    result_element = stumpless_add_param( element, param );
    ASSERT_TRUE( result_element != NULL );

    for( i = 0; i < 1000; i++ ) {
      add_result = stumpless_add_entry( target, entry );
      if( fixture_enabled ) {
        EXPECT_GE( add_result, 0 );

        error = stumpless_get_error(  );
        EXPECT_TRUE( error == NULL );
      }
    }

    stumpless_destroy_entry( entry );
    stumpless_close_network_target( target );

    stumpless_free_all(  );

    EXPECT_EQ( udp4_leak_memory_counter.alloc_total,
               udp4_leak_memory_counter.free_total );

    close_server_socket( handle );
  }
}
