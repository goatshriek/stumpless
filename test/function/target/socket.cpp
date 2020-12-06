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
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/function/rfc5424.hpp"
#include "test/helper/assert.hpp"

using::testing::HasSubstr;

namespace {

  class SocketTargetTest: public::testing::Test {

    protected:
      int test_socket;
      const char *socket_name = "sockettargettest";
      char buffer[1024];
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

      virtual void
      SetUp( void ) {
        struct sockaddr_un test_socket_addr;
        struct stumpless_element *element;
        struct stumpless_param *param;
        struct timeval read_timeout;

        test_socket_addr.sun_family = AF_UNIX;
        memcpy(&test_socket_addr.sun_path, socket_name, strlen(socket_name)+1);
      
        test_socket = socket(test_socket_addr.sun_family, SOCK_DGRAM, 0);

        read_timeout.tv_sec = 2;
        read_timeout.tv_usec = 0;
        setsockopt(test_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
 
        bind(test_socket, (struct sockaddr *) &test_socket_addr, sizeof(test_socket_addr));

        target = stumpless_open_socket_target( socket_name,
                                               "test-function-target-socket" );

        basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                           STUMPLESS_SEVERITY_INFO,
                                          "stumpless-unit-test",
                                          "basic-entry",
                                          "basic test message" );
  
        element = stumpless_new_element( "basic-element" );
        stumpless_add_element( basic_entry, element );
  
        param = stumpless_new_param( "basic-param-name", "basic-param-value" );
        stumpless_add_param( element, param );
      }

      virtual void
      TearDown( void ) {
        stumpless_close_socket_target( target );
        close( test_socket );
        unlink( socket_name );
      }

      void
      GetNextMessage( void ) {
        ssize_t msg_len;
        struct sockaddr_un from_addr;
        socklen_t size = 100;

        msg_len = recvfrom(test_socket, buffer, 1024, 0, (struct sockaddr *) &from_addr, &size);
        if( msg_len < 0 ) {
          buffer[0] = '\0';
        } else {
          buffer[msg_len] = '\0';
        }
      }

  };

  TEST_F( SocketTargetTest, AddEntry ) {
    stumpless_add_entry( target, basic_entry );
    EXPECT_NO_ERROR;
    GetNextMessage(  );

    EXPECT_THAT( buffer, HasSubstr( std::to_string( basic_entry->prival ) ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-element" ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-param-name" ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-param-value" ) );

    TestRFC5424Compliance(buffer);
  }

  TEST_F( SocketTargetTest, AddEntryToBadIdTarget ) {
    struct stumpless_target target_copy;
    const struct stumpless_error *error;
    int result;

    ASSERT_TRUE( target != NULL );
    memcpy( &target_copy, target, sizeof( *target ) );
    target_copy.id = NULL;

    result = stumpless_add_entry( &target_copy, basic_entry );
    EXPECT_LT( result, 0 );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ID );
  }

  /* non-fixture tests */

  TEST( SocketTargetAddTest, DestinationMissing ) {
    struct stumpless_target *target;
    int result;
    const struct stumpless_error *error;

    target = stumpless_open_socket_target( "/dev/not/there", NULL );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    result = stumpless_add_message( target, "test message" );
    EXPECT_LT( result, 0 );

    EXPECT_ERROR_ID_EQ( STUMPLESS_SOCKET_SEND_FAILURE );

    stumpless_close_socket_target( target );
  }

  TEST( SocketTargetAddTest, Uninitialized ) {
    struct stumpless_target target;
    struct stumpless_entry *entry;
    const struct stumpless_error *error;
    int result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                "stumpless-unit-test",
                                "basic-entry",
                                "basic test message" );

    target.type = STUMPLESS_SOCKET_TARGET;
    target.id = NULL;
    result = stumpless_add_entry( &target, entry );
    EXPECT_LT( result, 0 );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ID );

    stumpless_destroy_entry( entry );
  }

  TEST( SocketTargetCloseTest, Generic ) {
    const char *target_name = "generic-close-test";
    struct stumpless_target *target;

    target = stumpless_open_socket_target( target_name, NULL );

    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );
    EXPECT_EQ( stumpless_get_current_target(  ), target );

    stumpless_close_target( target );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(  ),
               stumpless_get_default_target(  ) );
    EXPECT_STRNE( stumpless_get_current_target(  )->name,
                  target_name );

    stumpless_free_all(  );
  }

  TEST( SocketTargetCloseTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_socket_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SocketTargetOpenTest, Basic ) {
    const struct stumpless_target *target;

    target = stumpless_open_socket_target( "basic-socket-target", NULL );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    stumpless_close_socket_target( target );
    EXPECT_NO_ERROR;
  }

  TEST( SocketTargetOpenTest, LocalSocketAlreadyExists ) {
    struct sockaddr_un local_socket_addr;
    struct stumpless_target *target;
    const struct stumpless_error *error;
    const char *local_socket_name = "taken";
    int local_socket;

    local_socket_addr.sun_family = AF_UNIX;
    memcpy(&local_socket_addr.sun_path, local_socket_name, strlen(local_socket_name)+1);
    local_socket = socket(local_socket_addr.sun_family, SOCK_DGRAM, 0);
    bind(local_socket, (struct sockaddr *) &local_socket_addr, sizeof(local_socket_addr));

    target = stumpless_open_socket_target( "socket-taken-test",
                                           local_socket_name );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_SOCKET_BIND_FAILURE );

    close( local_socket );
    unlink( local_socket_name );
  }

  TEST( SocketTargetOpenTest, MemoryFailure ) {
    const struct stumpless_error *error;
    struct stumpless_target *target;
    void *(*result)(size_t);
   
    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    EXPECT_TRUE( result != NULL );

    target = stumpless_open_socket_target( "basic-socket-target", NULL );
    EXPECT_EQ( NULL, target );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( result == malloc );
  }

  TEST( SocketTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_socket_target( NULL, NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }
}
