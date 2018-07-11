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

        target = stumpless_open_socket_target( socket_name, 0, 0 );

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
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    GetNextMessage(  );

    EXPECT_THAT( buffer, HasSubstr( std::to_string( basic_entry->prival ) ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-element" ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-param-name" ) );
    EXPECT_THAT( buffer, HasSubstr( "basic-param-value" ) );

    TestRFC5424Compliance(buffer);
  }

  TEST_F( SocketTargetTest, AddEntryToBadIdTarget ) {
    struct stumpless_target target_copy;
    struct stumpless_error *error;
    int result;

    memcpy( &target_copy, target, sizeof( *target ) );
    target_copy.id = -33;

    result = stumpless_add_entry( &target_copy, basic_entry );
    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_INVALID_ID );
  }

  TEST( SocketTargetCloseTest, NullTarget ) {
    struct stumpless_error *error;

    stumpless_close_socket_target( NULL );
    
    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SocketTargetOpenTest, Basic ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_socket_target( "basic-socket-target", 0, 0 );
    ASSERT_TRUE( target != NULL );
    ASSERT_EQ( NULL, stumpless_get_error(  ) );

    stumpless_close_socket_target( target );
  }

  TEST( SocketTargetOpenTest, MemoryFailure ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    void *(*result)(size_t);
   
    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( result != NULL );

    target = stumpless_open_socket_target( "basic-socket-target", 0, 0 );
    EXPECT_EQ( NULL, target );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    stumpless_set_malloc( malloc );
  }

  TEST( SocketTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_socket_target( NULL, 0, 0 );
    ASSERT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

}

int
main( int argc, char **argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS(  );
}
