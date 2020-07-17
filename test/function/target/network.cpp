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

#ifdef _WIN32
#  include <winsock2.h>
#else
#  include <sys/socket.h>
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stumpless.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/resolve.hpp"
#include "test/helper/server.hpp"

#define BINDING_DISABLED_WARNING "some network tests will not run without the" \
                                 " ability to listen on a local socket to"     \
                                 " receive messages."

using::testing::EndsWith;
using::testing::HasSubstr;
using::testing::Not;

namespace {

  TEST( NetworkTargetCloseTest, Generic ) {
    const char *target_name = "generic-close-test";
    struct stumpless_target *target;

    target = stumpless_open_udp4_target( target_name,
                                         "127.0.0.1",
                                         STUMPLESS_OPTION_NONE,
                                         STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_EQ( stumpless_get_current_target(  ), target );

    stumpless_close_target( target );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(  ),
               stumpless_get_default_target(  ) );
    EXPECT_STRNE( stumpless_get_current_target(  )->name,
                  target_name );
  }

  TEST( NetworkTargetCloseTest, NullTarget ) {
    struct stumpless_error *error;

    stumpless_close_network_target( NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }
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
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
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
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
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
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
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

  TEST( NetworkTargetNewTest, BadIpv4TransportProtocol ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_new_network_target( "bad-ipv4-transport",
                                           STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                           // assuming this isn't a valid protocol
                                           ( enum stumpless_transport_protocol ) -1 );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED );
    }
  }

  TEST( NetworkTargetNewTest, BadIpv6TransportProtocol ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_new_network_target( "bad-ipv6-transport",
                                           STUMPLESS_IPV6_NETWORK_PROTOCOL,
                                           // assuming this isn't a valid protocol
                                           ( enum stumpless_transport_protocol ) -1 );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED );
    }
  }

  TEST( NetworkTargetNewTest, BadNetworkProtocol ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_new_network_target( "bad-network",
                                           // assuming this isn't a valid protocol
                                           ( enum stumpless_network_protocol ) -1,
                                           STUMPLESS_TCP_TRANSPORT_PROTOCOL );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED );
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

  TEST( NetworkTargetNewTest, MallocFailure ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    void * ( *set_malloc_result ) ( size_t );

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    target = stumpless_new_network_target( "malloc-failure-target",
                                           STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                           STUMPLESS_TCP_TRANSPORT_PROTOCOL );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
  }

  TEST( NetworkTargetNewTest, NullName ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_new_network_target( NULL,
                                           STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                           STUMPLESS_UDP_TRANSPORT_PROTOCOL );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "name" ) );
    }
  }

  TEST( NetworkTargetOpenTest, BadHostname ) {
    struct stumpless_target *target;
    struct stumpless_error *error;
    const char *hostname = "this doesn't exist.net";

    if( name_resolves( hostname, AF_INET ) ) {
      printf( "WARNING: the bad hostname resolved, so this test will be skipped\n" );
      SUCCEED(  ) << "the bad hostname resolved, so this test will be skipped";

    } else {
      target = stumpless_open_network_target( "bad-hostname",
                                              hostname,
                                              STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                              STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                              STUMPLESS_OPTION_NONE,
                                              STUMPLESS_FACILITY_USER );

      EXPECT_TRUE(target == NULL);

      error = stumpless_get_error();
      EXPECT_TRUE(error != NULL);

      if (error) {
        EXPECT_EQ(error->id, STUMPLESS_ADDRESS_FAILURE);
      }
    }
  }

  TEST( NetworkTargetOpenTest, BadIpv4TransportProtocol ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "bad-ipv4-transport",
                                            "127.0.0.1",
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            // assuming this isn't a valid protocol
                                            ( enum stumpless_transport_protocol ) -1,
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED );
    }
  }

  TEST( NetworkTargetOpenTest, BadIpv6TransportProtocol ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "bad-ipv6-transport",
                                            "::1",
                                            STUMPLESS_IPV6_NETWORK_PROTOCOL,
                                            // assuming this isn't a valid protocol
                                            ( enum stumpless_transport_protocol ) -1,
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TRANSPORT_PROTOCOL_UNSUPPORTED );
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
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_NETWORK_PROTOCOL_UNSUPPORTED );
    }
  }

  TEST( NetworkTargetOpenTest, FacilityNotDivisibleBy8 ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "non-divisible-facility",
                                            "127.0.0.1",
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                            STUMPLESS_OPTION_NONE,
                                            3 );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_INVALID_FACILITY );
    }
  }

  TEST( NetworkTargetOpenTest, FacilityTooHigh ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "too-high-facility",
                                            "127.0.0.1",
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                            STUMPLESS_OPTION_NONE,
                                            800 );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_INVALID_FACILITY );
    }
  }

  TEST( NetworkTargetOpenTest, FacilityTooLow ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "too-low-facility",
                                            "127.0.0.1",
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                            STUMPLESS_OPTION_NONE,
                                            -800 );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_INVALID_FACILITY );
    }
  }

  TEST( NetworkTargetOpenTest, Hostname ) {
    struct stumpless_target *target;
    const char *hostname = "localhost";
    struct stumpless_error *error;

    if( !name_resolves( hostname, AF_INET ) ) {
      printf( "WARNING: %s did not resolve, so this test will be skipped\n", hostname );
      SUCCEED(  ) <<  "the hostname did not resolve, so this test will be skipped";

    } else {
      target = stumpless_open_network_target( "local-hostname",
                                              hostname,
                                              STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                              STUMPLESS_UDP_TRANSPORT_PROTOCOL,
                                              STUMPLESS_OPTION_NONE,
                                              STUMPLESS_FACILITY_USER );
      EXPECT_TRUE( target != NULL );

      error = stumpless_get_error(  );
      EXPECT_TRUE( error == NULL );

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
                                            STUMPLESS_OPTION_NONE,
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
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }
  }

  TEST( NetworkTargetOpenTest, NullDestination ) {
    struct stumpless_target *target;
    struct stumpless_error *error;

    target = stumpless_open_network_target( "no-name-provided",
                                            NULL,
                                            STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                            STUMPLESS_TCP_TRANSPORT_PROTOCOL,
                                            STUMPLESS_OPTION_NONE,
                                            STUMPLESS_FACILITY_USER );
    EXPECT_TRUE( target == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }
  }

  TEST( NetworkTargetSetDestination, BadTargetType ) {
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_target *result;
    char buffer[100];

    target = stumpless_open_buffer_target( "not-a-udp-target",
                                           buffer,
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
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
                                         STUMPLESS_OPTION_NONE,
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
                                         STUMPLESS_OPTION_NONE,
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

  TEST( NetworkTargetSetTransportPort, BadTcpPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;
    struct stumpless_error *error;
    const char *default_port;
    const char *bad_port = "337zrat";
    socket_handle_t handle;

    handle = open_tcp_server_socket( AF_INET, "127.0.0.1", "514" );
    if( handle != BAD_HANDLE ) {
      target = stumpless_open_tcp4_target( "target-to-self",
                                           "127.0.0.1",
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
      EXPECT_TRUE( target != NULL );
      error = stumpless_get_error(  );

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
                                         STUMPLESS_OPTION_NONE,
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
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
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
                                         STUMPLESS_OPTION_NONE,
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
                                         STUMPLESS_OPTION_NONE,
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
                                           sizeof( buffer ),
                                           STUMPLESS_OPTION_NONE,
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
