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


#ifdef _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
#else
#  include <errno.h>
#  include <netdb.h>
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <unistd.h>
#endif

#include <stddef.h>
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"

#define TCP_FIXTURES_DISABLED_WARNING "TCP fixture tests will not run without permissions to bind" \
                                      " to a local socket to receive messages."

namespace {
  class Tcp4TargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;
      bool tcp_fixtures_enabled = true;
      char buffer[2048];
#ifdef _WIN32
      SOCKET handle;
#else
      int handle;
#endif

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      // setting up to receive the sent messages
#ifdef _WIN32
      PADDRINFOA addr_result;
      WSADATA wsa_data;
      WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
      handle = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
      getaddrinfo( "127.0.0.1", "514", NULL, &addr_result );
      bind(handle, addr_result->ai_addr, ( int ) addr_result->ai_addrlen );
      listen( handle, 1 );
      freeaddrinfo( addr_result );
#else
      struct addrinfo *addr_result;
      handle = socket( AF_INET, SOCK_STREAM, 0 );
      getaddrinfo( "127.0.0.1", "514", NULL, &addr_result );
      if( bind(handle, addr_result->ai_addr, addr_result->ai_addrlen ) == -1 ){
        if( errno == EACCES ) {
          printf( "WARNING: " TCP_FIXTURES_DISABLED_WARNING "\n" );
          tcp_fixtures_enabled = false;
        }
      }
      listen( handle, 1 );
      freeaddrinfo( addr_result );
#endif

      target = stumpless_open_tcp4_target( "test-self",
                                           "127.0.0.1",
                                           0,
                                           STUMPLESS_FACILITY_USER );

      stumpless_set_target_default_app_name( target, "network-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

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

#ifdef _WIN32
      closesocket( handle );
#else
      close( handle );
#endif
    }

    void
    GetNextMessage( void ) {
#ifdef _WIN32
      SOCKET accepted;
      int msg_len;
      struct sockaddr_storage fromaddr;
      int fromaddr_len = sizeof( sockaddr_storage );

      accepted = accept( handle, ( struct sockaddr * ) &fromaddr, &fromaddr_len );
      if( accepted == INVALID_SOCKET ) {
        printf( "could not accept connection: %d\n", WSAGetLastError(  ) );
      }

      msg_len = recv( accepted, buffer, 1024, 0 );
      if( msg_len == SOCKET_ERROR ) {
        buffer[0] = '\0';
        printf( "could not receive message: %d\n", WSAGetLastError(  ) );
      } else {
        buffer[msg_len] = '\0';
      }

      printf( "%s\n", buffer );
      closesocket( accepted );
#else
      ssize_t msg_len;
      int accepted;
      struct sockaddr_storage fromaddr;
      socklen_t fromaddr_len = sizeof( struct sockaddr_storage );

      accepted = accept( handle, ( struct sockaddr * ) &fromaddr, &fromaddr_len );

      msg_len = recv( accepted, buffer, 1024, 0 );
      if( msg_len < 0 ) {
        buffer[0] = '\0';
      } else {
        buffer[msg_len] = '\0';
      }
#endif
    }
  };

  TEST_F( Tcp4TargetTest, AddEntry ) {
    int result;
    struct stumpless_error *error;

    if( !tcp_fixtures_enabled ) {
      SUCCEED(  ) << TCP_FIXTURES_DISABLED_WARNING;

    } else {
      ASSERT_TRUE( target != NULL );
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

  class Udp4TargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      target = stumpless_open_udp4_target( "test-self",
                                           "127.0.0.1",
                                           0,
                                           STUMPLESS_FACILITY_USER );

      stumpless_set_target_default_app_name( target, "network-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

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
    }
  };

  TEST_F( Udp4TargetTest, AddEntry ) {
    int result;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
  }

  /* non-fixture tests */

  TEST( NetworkTargetCloseTest, NullTarget ) {
    struct stumpless_error *error;

    stumpless_close_network_target( NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenTest, BadNetworkProtocol ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "bad-network",
                                            "127.0.0.1",
                                            // assuming this isn't a valid protocol
                                            ( enum stumpless_network_protocol ) -1,
                                            STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                            0,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED );
  }

  TEST( NetworkTargetOpenTest, BadTransportProtocol ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "bad-network",
                                            "127.0.0.1",
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            // assuming this isn't a valid protocol
                                            ( enum stumpless_transport_protocol ) -1,
                                            0,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED );
  }

  TEST( NetworkTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( NULL,
                                            "127.0.0.1",
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                            0,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenTest, NullDestination ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "no-name-provided",
                                            NULL,
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                            0,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenTcp4Test, BadAddress ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_tcp4_target( "bad-ipv4-address",
                                         "256.256.256.256",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ADDRESS_FAILURE );
    }
  }

  TEST( NetworkTargetOpenTcp4Test, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_tcp4_target( NULL,
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenTcp4Test, NullDestination ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_tcp4_target( "no-destination-provided",
                                         NULL,
                                         0,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenUdp4Test, BadAddress ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp4_target( "bad-ipv4-address",
                                         "256.256.256.256",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ADDRESS_FAILURE );
    }
  }

  TEST( NetworkTargetOpenUdp4Test, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp4_target( NULL,
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenUdp4Test, NullDestination ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp4_target( "no-name-provided",
                                         NULL,
                                         0,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetOpenUdp4Test, ToSelf ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );

    ASSERT_TRUE( target != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    stumpless_close_network_target( target );
  }
}
