// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2020 Joel E. Anderson
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

#include <cstdlib>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stumpless.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"
#include "test/helper/resolve.hpp"
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
                                           STUMPLESS_OPTION_NONE,
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

      EXPECT_TRUE( port_result != NULL );
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

  TEST( NetworkTargetNewTest, Basic ) {
    struct stumpless_target *target;

    target = stumpless_new_udp6_target( "my-udp6-target" );
    EXPECT_TRUE( target != NULL );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    EXPECT_FALSE( stumpless_target_is_open( target ) );

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetOpenTest, BadAddress ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp6_target( "bad-ipv6-address",
                                         "ff:fe::43::30:1",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ADDRESS_FAILURE );
    }
  }

  TEST( NetworkTargetOpenTest, Basic ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp6_target( "target-to-self",
                                         "::1",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetOpenTest, NullDestination ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp6_target( "no-name-provided",
                                         NULL,
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }
  }

  TEST( NetworkTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp6_target( NULL,
                                         "::1",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }
  }

  TEST( NetworkTargetSetDestination, OpenTarget ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *original_destination = "::1";
    const char *new_destination = "localhost";
    const char *destination_result;
    char buffer[2048];
    int add_result;
    socket_handle_t handle;

    if( !name_resolves( new_destination, AF_INET6 ) ) {
      printf( "WARNING: %s did not resolve, so this test will be skipped\n", new_destination );
      SUCCEED(  ) <<  "the hostname did not resolve, so this test will be skipped";

    } else {
      handle = open_udp_server_socket( AF_INET6, original_destination, "514" );

      target = stumpless_open_udp6_target( "target-to-self",
                                           original_destination,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
      ASSERT_TRUE( target != NULL );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error == NULL );

      destination_result = stumpless_get_destination( target );
      EXPECT_TRUE( destination_result != NULL );
      EXPECT_STREQ( destination_result, original_destination );

      EXPECT_TRUE( stumpless_target_is_open( target ) );
      target_result = stumpless_set_destination( target, new_destination );
      EXPECT_TRUE( target_result != NULL );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error == NULL );

      EXPECT_TRUE( stumpless_target_is_open( target ) );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error == NULL );

      destination_result = stumpless_get_destination( target );
      EXPECT_TRUE( destination_result != NULL );
      EXPECT_STREQ( destination_result, new_destination );

      if( handle != BAD_HANDLE ) {
        entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "stumpless-unit-test",
                                     "basic-entry",
                                     "basic test message" );
        EXPECT_TRUE( entry != NULL );

        add_result = stumpless_add_entry( target, entry );
        EXPECT_GE( add_result, 0 );

        recv_from_handle( handle, buffer, 1024 );
        EXPECT_TRUE( buffer[0] != '\0' );
        TestRFC5424Compliance( buffer );

        stumpless_destroy_entry( entry );
      }

      close_server_socket( handle );
      stumpless_close_network_target( target );
    }
  }

  TEST( NetworkTargetSetDestination, PausedTarget ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *destination = "::1";
    const char *destination_result;
    char buffer[2048];
    int add_result;
    socket_handle_t handle;

    handle = open_udp_server_socket( AF_INET6, destination, "514" );

    target = stumpless_new_udp6_target( "target-to-self" );
    ASSERT_TRUE( target != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    destination_result = stumpless_get_destination( target );
    EXPECT_TRUE( destination_result == NULL );

    EXPECT_FALSE( stumpless_target_is_open( target ) );
    target_result = stumpless_set_destination( target, destination );
    EXPECT_TRUE( target_result != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    EXPECT_FALSE( stumpless_target_is_open( target ) );

    destination_result = stumpless_get_destination( target );
    EXPECT_TRUE( destination_result != NULL );
    EXPECT_STREQ( destination_result, destination );

    target_result = stumpless_open_target( target );
    ASSERT_TRUE( target_result != NULL );
    EXPECT_TRUE( target_result == target );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    EXPECT_TRUE( stumpless_target_is_open( target ) );

    if( handle != BAD_HANDLE ) {
      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "stumpless-unit-test",
                                   "basic-entry",
                                   "basic test message" );
      EXPECT_TRUE( entry != NULL );

      add_result = stumpless_add_entry( target, entry );
      EXPECT_GE( add_result, 0 );

      recv_from_handle( handle, buffer, 1024 );
      EXPECT_TRUE( buffer[0] != '\0' );
      TestRFC5424Compliance( buffer );

      stumpless_destroy_entry( entry );
    }

    close_server_socket( handle );
    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, OpenTarget ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *new_port = "515";
    const char *default_port;
    const char *current_port;
    char buffer[2048];
    socket_handle_t handle;

    handle = open_udp_server_socket( AF_INET6, "::1", new_port );

    target = stumpless_open_udp6_target( "target-to-self",
                                         "::1",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    default_port = stumpless_get_transport_port( target );
    EXPECT_TRUE( default_port != NULL );
    ASSERT_STRNE( default_port, new_port );

    EXPECT_TRUE( stumpless_target_is_open( target ) );
    result = stumpless_set_transport_port( target, new_port );
    EXPECT_TRUE( result != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    EXPECT_TRUE( stumpless_target_is_open( target ) );

    current_port = stumpless_get_transport_port( target );
    EXPECT_TRUE( current_port != NULL );
    EXPECT_TRUE( current_port != new_port );
    EXPECT_STREQ( new_port, current_port );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    if( handle != BAD_HANDLE ) {
      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "stumpless-unit-test",
                                   "basic-entry",
                                   "basic test message" );
      stumpless_add_entry( target, entry );
      EXPECT_TRUE( result != NULL );

      recv_from_handle( handle, buffer, 1024 );
      EXPECT_TRUE( buffer[0] != '\0' );
      TestRFC5424Compliance( buffer );

      stumpless_destroy_entry( entry );
    }

    close_server_socket( handle );
    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, PausedTarget ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *destination = "::1";
    const char *new_port = "515";
    const char *default_port;
    const char *current_port;
    char buffer[2048];
    socket_handle_t handle;
    int add_result;

    handle = open_udp_server_socket( AF_INET6, destination, new_port );

    target = stumpless_new_udp6_target( "target-to-self" );
    ASSERT_TRUE( target != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    default_port = stumpless_get_transport_port( target );
    EXPECT_TRUE( default_port != NULL );
    ASSERT_STRNE( default_port, new_port );

    EXPECT_FALSE( stumpless_target_is_open( target ) );
    target_result = stumpless_set_transport_port( target, new_port );
    EXPECT_TRUE( target_result != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    EXPECT_FALSE( stumpless_target_is_open( target ) );

    current_port = stumpless_get_transport_port( target );
    EXPECT_TRUE( current_port != NULL );
    EXPECT_TRUE( current_port != new_port );
    EXPECT_STREQ( new_port, current_port );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    target_result = stumpless_set_destination( target, destination );
    EXPECT_TRUE( target_result != NULL );

    target_result = stumpless_open_target( target );
    ASSERT_TRUE( target_result != NULL );
    EXPECT_TRUE( target_result == target );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    EXPECT_TRUE( stumpless_target_is_open( target ) );

    if( handle != BAD_HANDLE ) {
      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "stumpless-unit-test",
                                   "basic-entry",
                                   "basic test message" );
      add_result = stumpless_add_entry( target, entry );
      EXPECT_GT( add_result, 0 );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error == NULL );

      recv_from_handle( handle, buffer, 1024 );
      EXPECT_TRUE( buffer[0] != '\0' );
      TestRFC5424Compliance( buffer );

      stumpless_destroy_entry( entry );
    }

    close_server_socket( handle );
    stumpless_close_network_target( target );
  }
}
