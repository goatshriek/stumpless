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

#include <regex>
#include <stddef.h>
#include <stumpless.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"
#include "test/helper/resolve.hpp"
#include "test/helper/server.hpp"

#define BINDING_DISABLED_WARNING "some network tests will not run without the" \
                                 " ability to listen on a local socket to"     \
                                 " receive messages."

using::testing::EndsWith;
using::testing::HasSubstr;
using::testing::Not;

namespace {
  class Tcp4TargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;
      bool tcp_fixtures_enabled = true;
      char buffer[2048];
      const char *port = "514";
      socket_handle_t handle;
      socket_handle_t accepted = BAD_HANDLE;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      // setting up to receive the sent messages
      handle = open_tcp_server_socket( "127.0.0.1", port );
      if( handle == BAD_HANDLE ) {
        printf( "WARNING: " BINDING_DISABLED_WARNING "\n" );
        tcp_fixtures_enabled = false;
      }

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
      close_server_socket( handle );

      if( accepted != BAD_HANDLE ) {
        close_server_socket( accepted );
      }
    }

    void
    GetNextMessage( void ) {
      if( accepted == BAD_HANDLE ) {
        accepted = accept_tcp_connection( handle );
      }

      recv_from_handle( accepted, buffer, 1024 );
    }
  };

  TEST_F( Tcp4TargetTest, AddEntry ) {
    int result;
    int octet_count;
    struct stumpless_error *error;
    char *syslog_msg;
    std::cmatch matches;
    std::regex octet_count_regex( "^(\\d+) (.*)$" );

    if( !tcp_fixtures_enabled ) {
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

      if( !std::regex_match( buffer, matches, octet_count_regex ) ) {
        FAIL(  ) << "octet count was not at the beginning of the message";
      } else {
        octet_count = std::stoi( matches[1] );
        EXPECT_EQ( octet_count + 1 + matches[1].length(  ), strlen( buffer ) );
      }

      syslog_msg = buffer + matches[1].length(  ) + 1;
      TestRFC5424Compliance( syslog_msg );
    }
  }

  TEST_F( Tcp4TargetTest, GetTransportPort ) {
    const char *port_result;

    if( !tcp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      port_result = stumpless_get_transport_port( target );

      ASSERT_TRUE( port_result != NULL );
      EXPECT_TRUE( port_result != port );
      EXPECT_STREQ( port_result, port );
    }
  }

  TEST_F( Tcp4TargetTest, GetUdpMaxMessageSize ) {
    size_t result;
    struct stumpless_error *error;

    if( !tcp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      ASSERT_TRUE( target != NULL );
      ASSERT_TRUE( stumpless_target_is_open( target ) );

      result = stumpless_get_udp_max_message_size( target );
      EXPECT_EQ( result, 0 );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error != NULL );
      if( error ) {
        EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
      }
    }
  }

  TEST_F( Tcp4TargetTest, SetUdpMaxMessageSize ) {
    struct stumpless_target *result;
    struct stumpless_error *error;

    if( !tcp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

    } else {
      ASSERT_TRUE( target != NULL );
      ASSERT_TRUE( stumpless_target_is_open( target ) );

      result = stumpless_set_udp_max_message_size( target, 1500 );
      EXPECT_TRUE( result == NULL );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error != NULL );
      if( error ) {
        EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
      }
    }
  }

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
      struct stumpless_element *element;
      struct stumpless_param *param;

      // setting up to receive the sent messages
      handle = open_udp_server_socket( "127.0.0.1", port );
      if( handle == BAD_HANDLE ) {
        printf( "WARNING: " BINDING_DISABLED_WARNING "\n" );
        udp_fixtures_enabled = false;
      }

      target = stumpless_open_udp4_target( "test-self",
                                           "127.0.0.1",
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

  TEST_F( Udp4TargetTest, AddEntry ) {
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

  TEST_F( Udp4TargetTest, GetTransportPort ) {
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

  TEST_F( Udp4TargetTest, TruncatedMessage ) {
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

  TEST( NetworkTargetCloseTest, NullTarget ) {
    struct stumpless_error *error;

    stumpless_close_network_target( NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NetworkTargetGetDestination, NullTarget ) {
    const char *result;
    struct stumpless_error *error;

    result = stumpless_get_destination( NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "target" ) );
    }
  }

  TEST( NetworkTargetGetDestination, BadTargetType ) {
    const char *result;
    struct stumpless_error *error;
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( "not-a-network-target",
                                           buffer,
                                           100,
                                           0,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_get_destination( target );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
    }

    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetGetTransportPort, NullTarget ) {
    const char *result;
    struct stumpless_error *error;

    result = stumpless_get_transport_port( NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "target" ) );
    }
  }

  TEST( NetworkTargetGetTransportProtocol, BadTargetType ) {
    const char *result;
    struct stumpless_error *error;
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( "not-a-udp-target",
                                           buffer,
                                           100,
                                           0,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_get_transport_port( target );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
    }

    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetGetUdpMaxMessage, BadTargetType ) {
    size_t result;
    struct stumpless_error *error;
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target( "not-a-udp-target",
                                           buffer,
                                           100,
                                           0,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_get_udp_max_message_size( target );
    EXPECT_EQ( result, 0 );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
    }

    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetGetUdpMaxMessage, NullTarget ) {
    size_t result;
    struct stumpless_error *error;

    result = stumpless_get_udp_max_message_size( NULL );
    EXPECT_TRUE( result == 0 );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "target" ) );
    }
  }

  TEST( NetworkTargetIsOpen, NullTarget ) {
    const struct stumpless_target *result;
    struct stumpless_error *error;

    result = stumpless_target_is_open( NULL );
    EXPECT_TRUE( !result );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "target" ) );
    }
  }

  TEST( NetworkTargetNewTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_new_network_target( NULL,
                                           STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                           STUMPLESS_UDP_TRANSPORT_PROTOCOL );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_THAT( error->message, HasSubstr( "name" ) );
  }

  TEST( NetworkTargetOpenTest, BadHostname ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    const char *hostname = "this-doesnt-exist.net";

    if( name_resolves( hostname ) ) {
      printf( "WARNING: the bad hostname resolved, so this test will be skipped\n" );
      SUCCEED(  ) << "the bad hostname resolved, so this test will be skipped";

    } else {
      target = stumpless_open_network_target( "bad-hostname",
                                              hostname,
                                              STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                              STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                              0,
                                              STUMPLESS_FACILITY_USER );
      EXPECT_TRUE( target == NULL );

      error = stumpless_get_error(  );
      ASSERT_TRUE( error != NULL );
      ASSERT_EQ( error->id, STUMPLESS_ADDRESS_FAILURE );

    }
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

  TEST( NetworkTargetOpenTest, Hostname ) {
    struct stumpless_target *target;
    const char *hostname = "localhost";

    if( !name_resolves( hostname ) ) {
      printf( "WARNING: %s did not resolve, so this test will be skipped\n", hostname );
      SUCCEED(  ) <<  "the hostname did not resolve, so this test will be skipped";

    } else {
      target = stumpless_open_network_target( "local-hostname",
                                              hostname,
                                              STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                              STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                              0,
                                              STUMPLESS_FACILITY_USER );
      EXPECT_TRUE( target != NULL );

      ASSERT_TRUE( stumpless_get_error(  ) == NULL );

      stumpless_close_network_target( target );

    }
  }

  TEST( NetworkTargetOpenTest, MallocFailure ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    void * ( *set_malloc_result ) ( size_t );

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    target = stumpless_open_network_target( "malloc-failure-target",
                                            "127.0.0.1",
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                            0,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
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
    EXPECT_TRUE( target != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );
    if( error ) {
      printf( "error message: %s\n", error->message );
      printf( "error code: %d\n", error->code );
    }

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetDestination, AfterTcpTargetOpen ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *original_destination = "127.0.0.1";
    const char *new_destination = "localhost";
    const char *destination_result;
    bool could_bind = true;
    char buffer[2048];
    int add_result;
    socket_handle_t accepted;
    socket_handle_t port_handle;


    if( !name_resolves( new_destination ) ) {
      printf( "WARNING: %s did not resolve, so this test will be skipped\n", new_destination );
      SUCCEED(  ) <<  "the hostname did not resolve, so this test will be skipped";

    } else {
      port_handle = open_tcp_server_socket( original_destination, "514" );

      if( port_handle == BAD_HANDLE ) {
        printf( "WARNING: " BINDING_DISABLED_WARNING "\n" );
        SUCCEED(  ) <<  BINDING_DISABLED_WARNING;

      } else {
        target = stumpless_open_tcp4_target( "target-to-self",
                                             original_destination,
                                             0,
                                             STUMPLESS_FACILITY_USER );
        ASSERT_TRUE( target != NULL );

        error = stumpless_get_error(  );
        EXPECT_TRUE( error == NULL );

        destination_result = stumpless_get_destination( target );
        EXPECT_TRUE( destination_result != NULL );
        EXPECT_STREQ( destination_result, original_destination );

        entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "stumpless-unit-test",
                                     "basic-entry",
                                     "basic test message" );
        EXPECT_TRUE( entry != NULL );

        add_result = stumpless_add_entry( target, entry );
        EXPECT_GE( add_result, 0 );

        accepted = accept_tcp_connection( port_handle );
        recv_from_handle( accepted, buffer, 2048 );
        EXPECT_TRUE( buffer[0] != '\0' );
        close_server_socket( accepted );

        target_result = stumpless_set_destination( target, new_destination );
        EXPECT_TRUE( target_result != NULL );

        destination_result = stumpless_get_destination( target );
        EXPECT_TRUE( destination_result != NULL );
        EXPECT_STREQ( destination_result, new_destination );

        add_result = stumpless_add_entry( target, entry );
        EXPECT_GE( add_result, 0 );

        accepted = accept_tcp_connection( port_handle );
        recv_from_handle( accepted, buffer, 2048 );
        EXPECT_TRUE( buffer[0] != '\0' );
        close_server_socket( accepted );

        stumpless_close_network_target( target );
        stumpless_destroy_entry( entry );
      }

      close_server_socket( port_handle );
    }
  }

  TEST( NetworkTargetSetDestination, AfterUdpTargetOpen ) {
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *original_destination = "127.0.0.1";
    const char *new_destination = "localhost";
    const char *destination_result;
    char buffer[2048];
    int add_result;
    socket_handle_t handle;

    if( !name_resolves( new_destination ) ) {
      printf( "WARNING: %s did not resolve, so this test will be skipped\n", new_destination );
      SUCCEED(  ) <<  "the hostname did not resolve, so this test will be skipped";

    } else {
      handle = open_udp_server_socket( original_destination, "514" );

      target = stumpless_open_udp4_target( "target-to-self",
                                           original_destination,
                                           0,
                                           STUMPLESS_FACILITY_USER );
      ASSERT_TRUE( target != NULL );

      destination_result = stumpless_get_destination( target );
      EXPECT_TRUE( destination_result != NULL );
      EXPECT_STREQ( destination_result, original_destination );

      target_result = stumpless_set_destination( target, new_destination );
      EXPECT_TRUE( target_result != NULL );

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

        stumpless_destroy_entry( entry );
      }

      close_server_socket( handle );
      stumpless_close_network_target( target );
    }
  }

  TEST( NetworkTargetSetDestination, BadTargetType ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_target *result;
    char buffer[100];

    target = stumpless_open_buffer_target( "not-a-udp-target",
                                           buffer,
                                           100,
                                           0,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_set_destination( target, "localhost" );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
    }

    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetSetDestination, MallocFailure ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    const char *original_destination = "127.0.0.1";
    const char *new_destination = "localhost";
    void * ( *set_malloc_result ) ( size_t );

    target = stumpless_open_udp4_target( "target-to-self",
                                         original_destination,
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    result = stumpless_set_destination( target, new_destination );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetDestination, NullDestination ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_target *result;

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_set_destination( target, NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "destination" ) );
    }

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetDestination, NullTarget ) {
    struct stumpless_error *error;
    struct stumpless_target *result;

    result = stumpless_set_destination( NULL, "localhost" );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "target" ) );
    }
  }

  TEST( NetworkTargetSetTransportPort, AfterTcpTargetOpen ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *new_port = "515";
    const char *default_port;
    const char *current_port;
    bool could_bind = true;
    char buffer[2048];
    int add_result;
    socket_handle_t accepted;
    socket_handle_t default_port_handle;
    socket_handle_t new_port_handle;

    default_port_handle = open_tcp_server_socket( "127.0.0.1", "514" );
    new_port_handle = open_tcp_server_socket( "127.0.0.1", new_port );

    if( default_port_handle != BAD_HANDLE && new_port_handle != BAD_HANDLE ) {
      target = stumpless_open_tcp4_target( "target-to-self",
                                           "127.0.0.1",
                                           0,
                                           STUMPLESS_FACILITY_USER );
      ASSERT_TRUE( target != NULL );

      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "stumpless-unit-test",
                                   "basic-entry",
                                   "basic test message" );
      ASSERT_TRUE( entry != NULL );

      add_result = stumpless_add_entry( target, entry );
      EXPECT_GE( add_result, 0 );

      accepted = accept_tcp_connection( default_port_handle );
      recv_from_handle( accepted, buffer, 2048 );
      EXPECT_TRUE( buffer[0] != '\0' );
      close_server_socket( accepted );

      default_port = stumpless_get_transport_port( target );
      EXPECT_TRUE( default_port != NULL );
      ASSERT_STRNE( default_port, new_port );

      result = stumpless_set_transport_port( target, new_port );
      EXPECT_TRUE( result != NULL );

      current_port = stumpless_get_transport_port( target );
      EXPECT_TRUE( current_port != NULL );
      EXPECT_TRUE( current_port != new_port );
      EXPECT_STREQ( new_port, current_port );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error == NULL );

      add_result = stumpless_add_entry( target, entry );
      EXPECT_GE( add_result, 0 );

      accepted = accept_tcp_connection( new_port_handle );
      recv_from_handle( accepted, buffer, 2048 );
      EXPECT_TRUE( buffer[0] != '\0' );
      close_server_socket( accepted );
      stumpless_close_network_target( target );

    }

    close_server_socket( default_port_handle );
    close_server_socket( new_port_handle );
  }

  TEST( NetworkTargetSetTransportPort, AfterUdpTargetOpen ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *new_port = "515";
    const char *default_port;
    const char *current_port;
    char buffer[2048];
    socket_handle_t handle;

    handle = open_udp_server_socket( "127.0.0.1", new_port );

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    default_port = stumpless_get_transport_port( target );
    EXPECT_TRUE( default_port != NULL );
    ASSERT_STRNE( default_port, new_port );

    result = stumpless_set_transport_port( target, new_port );
    EXPECT_TRUE( result != NULL );

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
    }

    close_server_socket( handle );
    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, BadTcpPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    const char *default_port;
    const char *bad_port = "337zrat";
    socket_handle_t handle;

    handle = open_tcp_server_socket( "127.0.0.1", "514" );
    if( handle != BAD_HANDLE ) {
      target = stumpless_open_tcp4_target( "target-to-self",
                                           "127.0.0.1",
                                           0,
                                           STUMPLESS_FACILITY_USER );
      EXPECT_TRUE( target != NULL );
      error = stumpless_get_error(  );
      if( error ) {
        printf( "%s\n%d\n", error->message, error->code );
      }

      default_port = stumpless_get_transport_port( target );
      ASSERT_TRUE( default_port != NULL );
      ASSERT_STRNE( default_port, bad_port );

      result = stumpless_set_transport_port( target, bad_port );
      EXPECT_TRUE( result == NULL );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error != NULL );
      if( error ) {
        EXPECT_EQ( error->id, STUMPLESS_ADDRESS_FAILURE );
      }

      stumpless_close_network_target( target );
    }

    close_server_socket( handle );
  }

  TEST( NetworkTargetSetTransportPort, BadUdpPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    const char *default_port;
    const char *bad_port = "337zrat";

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    default_port = stumpless_get_transport_port( target );
    ASSERT_TRUE( default_port != NULL );
    ASSERT_STRNE( default_port, bad_port );

    result = stumpless_set_transport_port( target, bad_port );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ADDRESS_FAILURE );
    }

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, BadTargetType ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_target *result;
    char buffer[100];

    target = stumpless_open_buffer_target( "not-a-udp-target",
                                           buffer,
                                           100,
                                           0,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_set_transport_port( target, "5514" );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
    }

    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetSetTransportPort, MallocFailure ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    const char *default_port;
    const char *new_port = "5514";
    void * ( *set_malloc_result ) ( size_t );

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    default_port = stumpless_get_transport_port( target );
    ASSERT_TRUE( default_port != NULL );
    ASSERT_STRNE( default_port, new_port );

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    result = stumpless_set_transport_port( target, new_port );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, NullPort ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_target *result;

    target = stumpless_open_udp4_target( "target-to-self",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_set_transport_port( target, NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "port" ) );
    }

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, NullTarget ) {
    struct stumpless_error *error;
    struct stumpless_target *result;

    result = stumpless_set_transport_port( NULL, "5514" );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "target" ) );
    }
  }

  TEST( NetworkTargetSetUdpMaxMessage, BadTargetType ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_target *result;
    char buffer[100];

    target = stumpless_open_buffer_target( "not-a-udp-target",
                                           buffer,
                                           100,
                                           0,
                                           STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_set_udp_max_message_size( target, 1500 );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_INCOMPATIBLE );
    }

    stumpless_close_buffer_target( target );
  }

  TEST( NetworkTargetSetUdpMaxMessage, NullTarget ) {
    struct stumpless_target *result;
    struct stumpless_error *error;

    result = stumpless_set_udp_max_message_size( NULL, 1500 );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "target" ) );
    }
  }
}
