// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2021 Joel E. Anderson
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

#include <cstdlib>
#include <stddef.h>
#include <stdio.h>
#include <stumpless.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"
#include "test/function/target/udp.hpp"
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/network.hpp"
#include "test/helper/resolve.hpp"

#ifndef _WIN32
#  include <sys/socket.h>
#endif

using::testing::EndsWith;
using::testing::HasSubstr;
using::testing::Not;

namespace {

  class Udp4TargetTest : public::testing::Test {

    protected:
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;
      bool udp_fixtures_enabled = true;
      char buffer[2048];
      const char *port = "514";
      socket_handle_t handle;

    virtual void
    SetUp( void ) {
      // setting up to receive the sent messages
      handle = open_udp4_server_socket( "127.0.0.1", port );
      if( handle == BAD_HANDLE ) {
        printf( "WARNING: " BINDING_DISABLED_WARNING "\n" );
        udp_fixtures_enabled = false;
      }

      target = stumpless_open_udp4_target( "test-self", "127.0.0.1" );

      stumpless_set_target_default_app_name( target, "network-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );
      stumpless_set_udp_max_message_size( target, 500 );

      basic_entry = create_entry(  );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_close_network_target( target );
      close_server_socket( handle );
    }

    void
    GetNextMessage( void ) {
      recv_from_handle( handle, buffer, 2048 );
    }
  };

  TEST_F( Udp4TargetTest, AddEntry ) {
    int result;

    if( !udp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      ASSERT_NOT_NULL( target );
      ASSERT_TRUE( stumpless_target_is_open( target ) );
      ASSERT_NOT_NULL( basic_entry );

      result = stumpless_add_entry( target, basic_entry );
      EXPECT_GE( result, 0 );
      EXPECT_NO_ERROR;

      GetNextMessage(  );
      TestRFC5424Compliance( buffer );
    }
  }

  TEST_F( Udp4TargetTest, GetTransportPort ) {
    const char *port_result;

    if( !udp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      port_result = stumpless_get_transport_port( target );

      EXPECT_NOT_NULL( port_result );
      EXPECT_TRUE( port_result != port );
      EXPECT_STREQ( port_result, port );
    }
  }

  TEST_F( Udp4TargetTest, TruncatedMessage ) {
    if( !udp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      TestTruncatedMessage( target );
      GetNextMessage(  );
      TestRFC5424Compliance( buffer );
      EXPECT_THAT( buffer, Not( EndsWith( "truncated" ) ) );
      EXPECT_THAT( buffer, HasSubstr( "begin" ) );
    }
  }

  /* non-fixture tests */

  TEST( NetworkTargetNewTest, BasicUdp4 ) {
    struct stumpless_target *target;

    target = stumpless_new_udp4_target( "my-udp4-target" );
    EXPECT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    EXPECT_FALSE( stumpless_target_is_open( target ) );

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetOpenTest, BadAddress ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_udp4_target( "bad-ipv4-address",
                                         "256.256.256.256" );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ADDRESS_FAILURE );
  }

  TEST( NetworkTargetOpenTest, Basic ) {
    struct stumpless_target *target;

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1" );
    EXPECT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetOpenTest, NullDestination ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_udp4_target( "no-name-provided", NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_udp4_target( NULL, "127.0.0.1" );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetSetDestination, OpenUdp4Target ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_entry *entry;
    const char *original_destination = "127.0.0.1";
    const char *new_destination = "localhost";
    const char *destination_result;
    char buffer[2048];
    int add_result;
    socket_handle_t handle;

    if( !name_resolves( new_destination, AF_INET ) ) {
      printf( "WARNING: %s did not resolve, so this test will be skipped\n", new_destination );
      SUCCEED(  ) <<  "the hostname did not resolve, so this test will be skipped";

    } else {
      handle = open_udp4_server_socket( original_destination, "514" );

      target = stumpless_open_udp4_target( "target-to-self",
                                           original_destination );
      ASSERT_NOT_NULL( target );
      EXPECT_NO_ERROR;

      destination_result = stumpless_get_destination( target );
      EXPECT_NOT_NULL( destination_result );
      EXPECT_STREQ( destination_result, original_destination );
      free( ( void * ) destination_result );

      EXPECT_TRUE( stumpless_target_is_open( target ) );
      target_result = stumpless_set_destination( target, new_destination );
      EXPECT_NOT_NULL( target_result );
      EXPECT_NO_ERROR;

      EXPECT_TRUE( stumpless_target_is_open( target ) );

      destination_result = stumpless_get_destination( target );
      EXPECT_NOT_NULL( destination_result );
      EXPECT_STREQ( destination_result, new_destination );
      free( ( void * ) destination_result );

      if( handle != BAD_HANDLE ) {
        entry = create_entry(  );
        EXPECT_NOT_NULL( entry );

        add_result = stumpless_add_entry( target, entry );
        EXPECT_GE( add_result, 0 );

        recv_from_handle( handle, buffer, 1024 );
        EXPECT_TRUE( buffer[0] != '\0' );
        TestRFC5424Compliance( buffer );

        stumpless_destroy_entry_and_contents( entry );
        close_server_socket( handle );
      }

      stumpless_close_network_target( target );
    }
  }

  TEST( NetworkTargetSetDestination, PausedUdp4Target ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_entry *entry;
    const char *destination = "127.0.0.1";
    const char *destination_result;
    char buffer[2048];
    int add_result;
    socket_handle_t handle;

    handle = open_udp4_server_socket( destination, "514" );

    target = stumpless_new_udp4_target( "target-to-self" );
    ASSERT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    destination_result = stumpless_get_destination( target );
    EXPECT_NULL( destination_result );

    EXPECT_FALSE( stumpless_target_is_open( target ) );
    target_result = stumpless_set_destination( target, destination );
    EXPECT_NOT_NULL( target_result );
    EXPECT_NO_ERROR;

    EXPECT_FALSE( stumpless_target_is_open( target ) );

    destination_result = stumpless_get_destination( target );
    EXPECT_NOT_NULL( destination_result );
    EXPECT_STREQ( destination_result, destination );
    free( ( void * ) destination_result );

    target_result = stumpless_open_target( target );
    ASSERT_NOT_NULL( target_result );
    EXPECT_TRUE( target_result == target );
    EXPECT_NO_ERROR;

    EXPECT_TRUE( stumpless_target_is_open( target ) );

    if( handle != BAD_HANDLE ) {
      entry = create_entry(  );
      EXPECT_NOT_NULL( entry );

      add_result = stumpless_add_entry( target, entry );
      EXPECT_GE( add_result, 0 );

      recv_from_handle( handle, buffer, 1024 );
      EXPECT_TRUE( buffer[0] != '\0' );
      TestRFC5424Compliance( buffer );

      stumpless_destroy_entry_and_contents( entry );
      close_server_socket( handle );
    }

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, OpenUdp4Target ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_entry *entry;
    const char *new_port = "515";
    const char *default_port;
    const char *current_port;
    char buffer[2048];
    socket_handle_t handle;

    handle = open_udp4_server_socket( "127.0.0.1", new_port );

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1" );
    ASSERT_NOT_NULL( target );

    default_port = stumpless_get_transport_port( target );
    EXPECT_NOT_NULL( default_port );
    ASSERT_STRNE( default_port, new_port );
    free( ( void * ) default_port );

    EXPECT_TRUE( stumpless_target_is_open( target ) );
    result = stumpless_set_transport_port( target, new_port );
    EXPECT_NOT_NULL( result );
    EXPECT_NO_ERROR;

    EXPECT_TRUE( stumpless_target_is_open( target ) );

    current_port = stumpless_get_transport_port( target );
    EXPECT_NOT_NULL( current_port );
    EXPECT_TRUE( current_port != new_port );
    EXPECT_STREQ( new_port, current_port );
    EXPECT_NO_ERROR;
    free( ( void * ) current_port );

    if( handle != BAD_HANDLE ) {
      entry = create_entry(  );
      stumpless_add_entry( target, entry );
      EXPECT_NOT_NULL( result );

      recv_from_handle( handle, buffer, 1024 );
      EXPECT_TRUE( buffer[0] != '\0' );
      TestRFC5424Compliance( buffer );

      stumpless_destroy_entry_and_contents( entry );
      close_server_socket( handle );
    }

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, PausedUdp4Target ) {
    struct stumpless_target *target;
    const char *destination = "127.0.0.1";
    const char *new_port = "515";
    socket_handle_t handle;

    handle = open_udp4_server_socket( destination, new_port );

    target = stumpless_new_udp4_target( "target-to-self" );
    ASSERT_NOT_NULL( target );
    EXPECT_NO_ERROR;

    TestSetTransportPortOnPausedTarget( target, destination, new_port, handle );

    close_server_socket( handle );
    stumpless_close_network_target( target );
  }
}
