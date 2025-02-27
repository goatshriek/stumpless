// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/rfc5424.hpp"

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

        basic_entry = create_entry(  );
      }

      virtual void
      TearDown( void ) {
        stumpless_destroy_entry_and_contents( basic_entry );
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
    EXPECT_THAT( buffer, HasSubstr( "fixture-element" ) );
    EXPECT_THAT( buffer, HasSubstr( "fixture-param-1" ) );
    EXPECT_THAT( buffer, HasSubstr( "fixture-value-1" ) );
    EXPECT_THAT( buffer, HasSubstr( "fixture-param-2" ) );
    EXPECT_THAT( buffer, HasSubstr( "fixture-value-2" ) );

    TestRFC5424Compliance(buffer);
  }

  TEST_F( SocketTargetTest, AddEntryToBadIdTarget ) {
    struct stumpless_target target_copy;
    const struct stumpless_error *error;
    int result;

    ASSERT_NOT_NULL( target );
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

  TEST( SocketTargetCloseTest, WrongTargetType ) {
    const struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-socket-target" );

    stumpless_close_socket_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
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

  TEST( SocketTargetOpenTest, LocalSocketAlreadyExistsWithOdelay ) {
    struct sockaddr_un local_socket_addr;
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    const struct stumpless_error *error;
    const char *local_socket_name = "taken";
    int local_socket;
    int result;
    int default_options;

    default_options = stumpless_get_default_options(  );

    stumpless_set_default_options( STUMPLESS_OPTION_ODELAY );

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    local_socket_addr.sun_family = AF_UNIX;
    memcpy(&local_socket_addr.sun_path, local_socket_name, strlen(local_socket_name)+1);
    local_socket = socket(local_socket_addr.sun_family, SOCK_DGRAM, 0);
    bind(local_socket, (struct sockaddr *) &local_socket_addr, sizeof(local_socket_addr));

    target = stumpless_open_socket_target( "socket-taken-test",
                                           local_socket_name );
    EXPECT_NOT_NULL( target );

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );

    stumpless_set_default_options( default_options );

    close( local_socket );
    unlink( local_socket_name );

    stumpless_close_target( target );

    stumpless_destroy_entry_and_contents( entry );
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

  TEST( SocketTargetOpenTest, Odelay ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    int result;
    int default_options;

    default_options = stumpless_get_default_options(  );

    stumpless_set_default_options( STUMPLESS_OPTION_ODELAY );

    target = stumpless_open_socket_target( "odelay-target", NULL );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_NULL( stumpless_target_is_open( target ) );

    entry = create_entry(  );
    EXPECT_NOT_NULL( entry );

    result = stumpless_add_entry( target, entry );
    EXPECT_NOT_NULL( stumpless_target_is_open( target ) );

    stumpless_close_socket_target( target );
    EXPECT_NO_ERROR;

    stumpless_set_default_options( default_options );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST( SocketTargetAddTest, NullId ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    stumpless_id_t real_id;
    const struct stumpless_error *error;
    int result;

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    target = stumpless_open_socket_target( "null-id", NULL );
    ASSERT_NOT_NULL( target );

    real_id = target->id;
    target->id = NULL;

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ID );

    target->id = real_id;
    stumpless_close_socket_target( target );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST( SocketTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_socket_target( NULL, NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }
}
