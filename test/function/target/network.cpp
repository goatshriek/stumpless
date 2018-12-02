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

#define BINDING_DISABLED_WARNING "some network tests will not run without"     \
                                 " permissions to bind to a local socket to"   \
                                 " to receive messages."

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
#ifdef _WIN32
      SOCKET handle;
      SOCKET accepted = INVALID_SOCKET;
#else
      int handle;
      int accepted = -1;
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
      getaddrinfo( "127.0.0.1", port, NULL, &addr_result );
      bind(handle, addr_result->ai_addr, ( int ) addr_result->ai_addrlen );
      listen( handle, 1 );
      freeaddrinfo( addr_result );
#else
      struct addrinfo *addr_result;
      handle = socket( AF_INET, SOCK_STREAM, 0 );
      getaddrinfo( "127.0.0.1", port, NULL, &addr_result );
      if( bind(handle, addr_result->ai_addr, addr_result->ai_addrlen ) == -1 ){
        if( errno == EACCES ) {
          printf( "WARNING: " BINDING_DISABLED_WARNING "\n" );
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
      closesocket( accepted );
      closesocket( handle );
#else
      close( accepted );
      close( handle );
#endif
    }

    void
    GetNextMessage( void ) {
#ifdef _WIN32
      int msg_len;
      struct sockaddr_storage fromaddr;
      int fromaddr_len = sizeof( sockaddr_storage );

      if( accepted == INVALID_SOCKET ) {
      accepted = accept( handle, ( struct sockaddr * ) &fromaddr, &fromaddr_len );
        if( accepted == INVALID_SOCKET ) {
          printf( "could not accept connection: %d\n", WSAGetLastError(  ) );
        }
      }

      msg_len = recv( accepted, buffer, 1024, 0 );
      if( msg_len == SOCKET_ERROR ) {
        buffer[0] = '\0';
        printf( "could not receive message: %d\n", WSAGetLastError(  ) );
      } else {
        buffer[msg_len] = '\0';
      }
#else
      ssize_t msg_len;
      struct sockaddr_storage fromaddr;
      socklen_t fromaddr_len = sizeof( struct sockaddr_storage );

      if( accepted == -1 ) {
        accepted = accept( handle, ( struct sockaddr * ) &fromaddr, &fromaddr_len );
      }

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
    int octet_count;
    struct stumpless_error *error;
    char *syslog_msg;
    std::cmatch matches;
    std::regex octet_count_regex( "^(\\d+) (.*)$" );

    if( !tcp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

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
      handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
      getaddrinfo( "127.0.0.1", port, NULL, &addr_result );
      bind(handle, addr_result->ai_addr, ( int ) addr_result->ai_addrlen );
      listen( handle, 1 );
      freeaddrinfo( addr_result );
#else
      struct addrinfo *addr_result;
      handle = socket( AF_INET, SOCK_DGRAM, 0 );
      getaddrinfo( "127.0.0.1", port, NULL, &addr_result );
      if( bind(handle, addr_result->ai_addr, addr_result->ai_addrlen ) == -1 ){
        if( errno == EACCES ) {
          printf( "WARNING: " BINDING_DISABLED_WARNING "\n" );
          udp_fixtures_enabled = false;
        }
      }
      listen( handle, 1 );
      freeaddrinfo( addr_result );
#endif

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

#ifdef _WIN32
      closesocket( handle );
#else
      close( handle );
#endif
    }

    void
    GetNextMessage( void ) {
#ifdef _WIN32
      int msg_len;

      msg_len = recv( handle, buffer, 1024, 0 );
      if( msg_len == SOCKET_ERROR ) {
        buffer[0] = '\0';
        printf( "could not receive message: %d\n", WSAGetLastError(  ) );
      } else {
        buffer[msg_len] = '\0';
      }
#else
      ssize_t msg_len;

      msg_len = recv( handle, buffer, 1024, 0 );
      if( msg_len < 0 ) {
        buffer[0] = '\0';
      } else {
        buffer[msg_len] = '\0';
      }
#endif
    }
  };

  TEST_F( Udp4TargetTest, AddEntry ) {
    int result;
    struct stumpless_error *error;

    if( !udp_fixtures_enabled ) {
      SUCCEED(  ) << BINDING_DISABLED_WARNING;

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

    ASSERT_TRUE( target != NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error == NULL );

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, AfterTargetOpen ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    const char *new_port = "515";
    const char *default_port;
    const char *current_port;
    bool could_bind = true;
    char buffer[2048];

      // setting up to receive the sent messages
#ifdef _WIN32
    SOCKET handle;
    SOCKET accepted = INVALID_SOCKET;
    PADDRINFOA addr_result;
    WSADATA wsa_data;
    int msg_len;
    WSAStartup( MAKEWORD( 2, 2 ), &wsa_data );
    handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
    getaddrinfo( "127.0.0.1", new_port, NULL, &addr_result );
    bind(handle, addr_result->ai_addr, ( int ) addr_result->ai_addrlen );
    listen( handle, 1 );
    freeaddrinfo( addr_result );
#else
    int handle;
    int accepted = -1;
    struct addrinfo *addr_result;
    ssize_t msg_len;
    handle = socket( AF_INET, SOCK_DGRAM, 0 );
    getaddrinfo( "127.0.0.1", new_port, NULL, &addr_result );
    if( bind(handle, addr_result->ai_addr, addr_result->ai_addrlen ) == -1 ){
      if( errno == EACCES ) {
        could_bind = false;
      }
    }
    listen( handle, 1 );
    freeaddrinfo( addr_result );
#endif

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

    if( could_bind ) {
      entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   "stumpless-unit-test",
                                   "basic-entry",
                                   "basic test message" );
      stumpless_add_entry( target, entry );
      EXPECT_TRUE( result != NULL );

#ifdef _WIN32
      msg_len = recv( handle, buffer, 1024, 0 );
      if( msg_len == SOCKET_ERROR ) {
        buffer[0] = '\0';
        printf( "could not receive message: %d\n", WSAGetLastError(  ) );
      } else {
        buffer[msg_len] = '\0';
      }
#else
      msg_len = recv( handle, buffer, 1024, 0 );
      if( msg_len < 0 ) {
        buffer[0] = '\0';
      } else {
        buffer[msg_len] = '\0';
      }
#endif

      EXPECT_TRUE( buffer[0] != '\0' );
    }

    stumpless_close_network_target( target );
  }

  TEST( NetworkTargetSetTransportPort, BadPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    struct stumpless_entry *entry;
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

  TEST( NetworkTargetSetTransportPort, NullTarget ) {
    struct stumpless_error *error;
    struct stumpless_target *result;
    char buffer[100];

    result = stumpless_set_transport_port( NULL, "5514" );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
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
