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

        target = stumpless_open_socket_target( socket_name, "test-function-target-socket", 0, 0 );

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

  TEST_F( SocketTargetTest, AddEntryMemoryFailure ) {
    struct stumpless_error *error;
    void *(*set_result)(size_t);
    int add_result;
   
    set_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    EXPECT_TRUE( set_result != NULL );

    add_result = stumpless_add_entry( target, basic_entry );
    EXPECT_LT( add_result, 0 );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    set_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_result != NULL );
    EXPECT_TRUE( set_result == malloc );
  }

  TEST_F( SocketTargetTest, AddEntryToBadIdTarget ) {
    struct stumpless_target target_copy;
    struct stumpless_error *error;
    int result;

    ASSERT_TRUE( target != NULL );
    memcpy( &target_copy, target, sizeof( *target ) );
    target_copy.id = -33;

    result = stumpless_add_entry( &target_copy, basic_entry );
    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_INVALID_ID );
  }

  /* non-fixture tests */

  TEST( SocketTargetAddTest, AddAfterClose ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    int result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                "stumpless-unit-test",
                                "basic-entry",
                                "basic test message" );

    target = stumpless_open_socket_target( "basic-socket-target", NULL, 0, 0 );
    ASSERT_TRUE( target != NULL );
    ASSERT_EQ( NULL, stumpless_get_error(  ) );


    stumpless_close_socket_target( target );

    result = stumpless_add_entry( target, entry );
    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_INVALID_ID );

    stumpless_destroy_entry( entry );
  }

  TEST( SocketTargetAddTest, Uninitialized ) {
    struct stumpless_target target;
    struct stumpless_entry *entry;
    struct stumpless_error *error;
    int result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                "stumpless-unit-test",
                                "basic-entry",
                                "basic test message" );

    target.type = STUMPLESS_SOCKET_TARGET;
    target.id = 4;
    result = stumpless_add_entry( &target, entry );
    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_INVALID_ID );

    stumpless_destroy_entry( entry );
  }

  TEST( SocketTargetCloseTest, BadIdTarget ) {
    struct stumpless_target *target;

    target = ( struct stumpless_target * ) malloc( sizeof( *target ) );
    ASSERT_TRUE( target != NULL );

    target->name = NULL;
    target->id = -33;

    stumpless_close_socket_target( target );
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

    target = stumpless_open_socket_target( "basic-socket-target", NULL, 0, 0 );
    ASSERT_TRUE( target != NULL );
    ASSERT_EQ( NULL, stumpless_get_error(  ) );

    stumpless_close_socket_target( target );
  }

  TEST( SocketTargetOpenTest, LocalSocketAlreadyExists ) {
    struct sockaddr_un local_socket_addr;
    struct stumpless_target *target;
    struct stumpless_error *error;
    const char *local_socket_name = "taken";
    int local_socket;

    local_socket_addr.sun_family = AF_UNIX;
    memcpy(&local_socket_addr.sun_path, local_socket_name, strlen(local_socket_name)+1);
    local_socket = socket(local_socket_addr.sun_family, SOCK_DGRAM, 0);
    bind(local_socket, (struct sockaddr *) &local_socket_addr, sizeof(local_socket_addr));

    target = stumpless_open_socket_target( "socket-taken-test", local_socket_name, 0, 0 );
    EXPECT_EQ( NULL, target );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_SOCKET_BIND_FAILURE );
    }

    close( local_socket );
    unlink( local_socket_name );
  }

  TEST( SocketTargetOpenTest, MemoryFailure ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    void *(*result)(size_t);
   
    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    EXPECT_TRUE( result != NULL );

    target = stumpless_open_socket_target( "basic-socket-target", NULL, 0, 0 );
    EXPECT_EQ( NULL, target );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( result == malloc );
  }

  TEST( SocketTargetOpenTest, Open200TargetsWithReallocFailure ) {
    struct stumpless_target *targets[200];
    struct stumpless_error *error;
    int i;
    void *(*result)(void *, size_t);
   
    result = stumpless_set_realloc( [](void *mem, size_t size)->void *{ return NULL; } );
    EXPECT_TRUE( result != NULL );
    ASSERT_TRUE( result != realloc );
 
    for( i=0; i < 200; i++ ) {
      targets[i] = stumpless_open_socket_target( "basic-socket-target", NULL, 0, 0 );
      if( targets[i] == NULL ) {
        error = stumpless_get_error(  );
        EXPECT_TRUE( error != NULL );
        if( error != NULL ) {
          EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
        }
    
        result = stumpless_set_realloc( realloc );
        EXPECT_TRUE( result == realloc );

        while( i > 0 ) {
          i--;
          stumpless_close_socket_target( targets[i] );
        }

        break;
      }

    }

    ASSERT_EQ( i, 0 );
  }

  /*
   * For some reason, having this test in the same suite as the other two tests
   * for stumpless_open_socket_target causes a segfault in os x travis build.
   * I haven't been able to reproduce this locally to troubleshoot, and the
   * segfault appears to happen before the test even runs (a test that just
   * asserts true still causes a segfault), and removing either the Basic test
   * or this test itself makes the error this go away. For now I've simply
   * renamed the test suite, but a more permanent solution would figure out why
   * this was happening and stop it.
   */
  TEST( SocketTargetOpenNullTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_socket_target( NULL, NULL, 0, 0 );
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
