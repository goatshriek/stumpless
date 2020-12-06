// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/memory_allocation.hpp"

using::testing::HasSubstr;

namespace {

  TEST( SocketTargetStartupTest, AddEntryMemoryFailure ) {
    const struct stumpless_error *error;
    void *(*set_result)(size_t);
    int add_result;
    struct stumpless_target *target;
    struct sockaddr_un test_socket_addr;
    struct stumpless_element *element;
    struct stumpless_param *param;
    struct timeval read_timeout;
    int test_socket;
    const char *socket_name = "sockettargettest";
    struct stumpless_entry *basic_entry;

    test_socket_addr.sun_family = AF_UNIX;
    memcpy(&test_socket_addr.sun_path, socket_name, strlen(socket_name)+1);
   
    test_socket = socket(test_socket_addr.sun_family, SOCK_DGRAM, 0);

    read_timeout.tv_sec = 2;
    read_timeout.tv_usec = 0;
    setsockopt(test_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
 
    bind(test_socket, (struct sockaddr *) &test_socket_addr, sizeof(test_socket_addr));

    target = stumpless_open_socket_target( socket_name, "test-function-target-socket" );
    ASSERT_NOT_NULL( target );

    basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                      "stumpless-unit-test",
                                      "basic-entry",
                                      "basic test message" );
  
    element = stumpless_new_element( "basic-element" );
    stumpless_add_element( basic_entry, element );
  
    param = stumpless_new_param( "basic-param-name", "basic-param-value" );
    stumpless_add_param( element, param );
   
    set_result = stumpless_set_malloc( MALLOC_FAIL );
    EXPECT_NOT_NULL( set_result );

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_LT( add_result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_result = stumpless_set_malloc( malloc );
    EXPECT_NOT_NULL( set_result );
    EXPECT_EQ( set_result, malloc );

    stumpless_close_socket_target( target );
    close( test_socket );
    unlink( socket_name );
  }

}
