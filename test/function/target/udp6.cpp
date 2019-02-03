// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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

#include <regex>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stumpless.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"
#include "test/helper/server.hpp"

#ifndef _WIN32
#  include <sys/socket.h>
#endif

#define BINDING_DISABLED_WARNING "some network tests will not run without the" \
                                 " ability to listen on a local socket to"     \
                                 " receive messages."

using::testing::EndsWith;
using::testing::HasSubstr;
using::testing::Not;

namespace {

  class Udp6TargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;
      bool udp_fixtures_enabled = true;
      char buffer[2048];
      const char *port = "514";
      socket_handle_t handle;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      // setting up to receive the sent messages
      handle = open_udp_server_socket( AF_INET6, "::1", port );
      if( handle == BAD_HANDLE ) {
        printf( "WARNING: " BINDING_DISABLED_WARNING "\n" );
        udp_fixtures_enabled = false;
      }

      target = stumpless_open_udp6_target( "test-self",
                                           "::1",
                                           0,
                                           STUMPLESS_FACILITY_USER );

      stumpless_set_target_default_app_name( target, "network-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );
      stumpless_set_udp_max_message_size( target, 500 );

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
      stumpless_destroy_entry( basic_entry );
      stumpless_close_network_target( target );
      close_server_socket( handle );
    }

    void
    GetNextMessage( void ) {
      recv_from_handle( handle, buffer, 2048 );
    }
  };

  TEST_F( Udp6TargetTest, AddEntry ) {
    int result;
    struct stumpless_error *error;

    if( !udp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      ASSERT_TRUE( target != NULL );
      ASSERT_TRUE( stumpless_target_is_open( target ) );
      ASSERT_TRUE( basic_entry != NULL );

      result = stumpless_add_entry( target, basic_entry );
      EXPECT_GE( result, 0 );

      error = stumpless_get_error( );
      if( error ) {
        FAIL(  ) << error->message;
      }

      GetNextMessage(  );
      TestRFC5424Compliance( buffer );
    }
  }

  TEST_F( Udp6TargetTest, GetTransportPort ) {
    const char *port_result;

    if( !udp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      port_result = stumpless_get_transport_port( target );

      ASSERT_TRUE( port_result != NULL );
      EXPECT_TRUE( port_result != port );
      EXPECT_STREQ( port_result, port );
    }
  }

  TEST_F( Udp6TargetTest, TruncatedMessage ) {
    int result;
    struct stumpless_entry *long_entry;
    struct stumpless_error *error;
    char *message;
    size_t max_msg_size;
    size_t my_msg_size;

    if( !udp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      ASSERT_TRUE( target != NULL );
      ASSERT_TRUE( stumpless_target_is_open( target ) );

      max_msg_size = stumpless_get_udp_max_message_size( target );
      ASSERT_NE( max_msg_size, 0 );

      my_msg_size = max_msg_size + 10;
      message = ( char * ) malloc( my_msg_size );
      ASSERT_TRUE( message != NULL );
      memset( message, 'a', max_msg_size );
      strncpy( message, "present", 7 );
      message[7] = 'a';
      strncpy( message + max_msg_size, "truncated", 10 );
      message[my_msg_size-1] = '\0';

      // due to the message header more than just the word 'truncated' will be
      // taken from the message - this is just a basic test
      long_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                        STUMPLESS_SEVERITY_INFO,
                                        "stumpless-unit-test",
                                        "basic-entry",
                                        message );
      ASSERT_TRUE( long_entry != NULL );

      result = stumpless_add_entry( target, long_entry );
      EXPECT_GE( result, 0 );

      error = stumpless_get_error( );
      EXPECT_TRUE( error != NULL );
      if( error ) {
        EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_TOO_BIG );
      }

      GetNextMessage(  );
      TestRFC5424Compliance( buffer );
      EXPECT_THAT( buffer, Not( EndsWith( "truncated" ) ) );
      EXPECT_THAT( buffer, HasSubstr( "present" ) );

      free( message );
    }
  }

  /* non-fixture tests */

  TEST( NetworkTargetNewTest, Udp6 ) {
    struct stumpless_target *target;

    target = stumpless_new_network_target( "my-udp6",
                                           STUMPLESS_IPV6_NETWORK_PROTOCOL,
                                           STUMPLESS_UDP_TRANSPORT_PROTOCOL );
    EXPECT_TRUE( target != NULL );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    EXPECT_FALSE( stumpless_target_is_open( target ) );

    stumpless_close_network_target( target );
  }
}
