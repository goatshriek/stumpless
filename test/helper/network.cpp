// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021-2024 Joel E. Anderson
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

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/network.hpp"
#include "test/helper/rfc5424.hpp"

void
TestSetDestinationOnOpenTarget( struct stumpless_target *target,
                                const char *original_destination,
                                const char *new_destination,
                                socket_handle_t new_dest_server ) {
  const char *destination_result;
  const struct stumpless_target *target_result;
  const struct stumpless_entry *entry;
  char buffer[2048];
  int add_result;

  destination_result = stumpless_get_destination( target );
  EXPECT_NOT_NULL( destination_result );
  EXPECT_STREQ( destination_result, original_destination );
  free( ( void * ) destination_result );

  EXPECT_TRUE( stumpless_target_is_open( target ) );
  target_result = stumpless_set_destination( target, new_destination );
  EXPECT_NO_ERROR;
  EXPECT_NOT_NULL( target_result );

  EXPECT_TRUE( stumpless_target_is_open( target ) );

  destination_result = stumpless_get_destination( target );
  EXPECT_NOT_NULL( destination_result );
  EXPECT_STREQ( destination_result, new_destination );
  free( ( void * ) destination_result );

  if( new_dest_server != BAD_HANDLE ) {
    entry = create_entry(  );
    EXPECT_NOT_NULL( entry );

    add_result = stumpless_add_entry( target, entry );
    EXPECT_GE( add_result, 0 );

    recv_from_handle( new_dest_server, buffer, 1024 );
    EXPECT_TRUE( buffer[0] != '\0' );
    TestRFC5424Compliance( buffer );

    stumpless_destroy_entry_and_contents( entry );
  }
}

void
TestSetDestinationOnPausedTarget( struct stumpless_target *target,
                                  const char *new_destination,
                                  socket_handle_t new_dest_server ) {
  const char *destination_result;
  const struct stumpless_target *target_result;
  const struct stumpless_entry *entry;
  char buffer[2048];
  int add_result;

  destination_result = stumpless_get_destination( target );
  EXPECT_NULL( destination_result );

  EXPECT_FALSE( stumpless_target_is_open( target ) );
  target_result = stumpless_set_destination( target, new_destination );
  EXPECT_NOT_NULL( target_result );
  EXPECT_NO_ERROR;

  EXPECT_FALSE( stumpless_target_is_open( target ) );

  destination_result = stumpless_get_destination( target );
  EXPECT_NOT_NULL( destination_result );
  EXPECT_STREQ( destination_result, new_destination );
  free( ( void * ) destination_result );

  target_result = stumpless_open_target( target );
  ASSERT_NOT_NULL( target_result );
  EXPECT_TRUE( target_result == target );
  EXPECT_NO_ERROR;

  EXPECT_TRUE( stumpless_target_is_open( target ) );

  if( new_dest_server != BAD_HANDLE ) {
    entry = create_entry(  );
    EXPECT_NOT_NULL( entry );

    add_result = stumpless_add_entry( target, entry );
    EXPECT_GE( add_result, 0 );

    recv_from_handle( new_dest_server, buffer, 1024 );
    EXPECT_TRUE( buffer[0] != '\0' );
    TestRFC5424Compliance( buffer );

    stumpless_destroy_entry_and_contents( entry );
  }
}

void
TestSetTransportPortOnOpenTarget( struct stumpless_target *target,
                                  const char *new_port,
                                  socket_handle_t new_port_server ) {
    const char *default_port;
    const char *current_port;
    const struct stumpless_target *target_result;
    const struct stumpless_entry *entry;
    char buffer[2048];
    int add_result;

    default_port = stumpless_get_transport_port( target );
    EXPECT_NOT_NULL( default_port );
    ASSERT_STRNE( default_port, new_port );
    free( ( void * ) default_port );

    EXPECT_TRUE( stumpless_target_is_open( target ) );
    target_result = stumpless_set_transport_port( target, new_port );
    EXPECT_NOT_NULL( target_result );
    EXPECT_NO_ERROR;

    EXPECT_TRUE( stumpless_target_is_open( target ) );

    current_port = stumpless_get_transport_port( target );
    EXPECT_NOT_NULL( current_port );
    EXPECT_TRUE( current_port != new_port );
    EXPECT_STREQ( new_port, current_port );
    EXPECT_NO_ERROR;
    free( ( void * ) current_port );

    if( new_port_server != BAD_HANDLE ) {
      entry = create_entry(  );
      add_result = stumpless_add_entry( target, entry );
      EXPECT_GT( add_result, 0 );

      recv_from_handle( new_port_server, buffer, 1024 );
      EXPECT_TRUE( buffer[0] != '\0' );
      TestRFC5424Compliance( buffer );

      stumpless_destroy_entry_and_contents( entry );
    }
}

void
TestSetTransportPortOnPausedTarget( struct stumpless_target *target,
                                    const char *destination,
                                    const char *new_port,
                                    socket_handle_t new_port_server ) {
  const char *default_port;
  const char *current_port;
  struct stumpless_target *target_result;
  const struct stumpless_entry *entry;
  char buffer[2048];
  int add_result;

  default_port = stumpless_get_transport_port( target );
  EXPECT_NOT_NULL( default_port );
  ASSERT_STRNE( default_port, new_port );
  free( ( void * ) default_port );

  EXPECT_FALSE( stumpless_target_is_open( target ) );
  target_result = stumpless_set_transport_port( target, new_port );
  EXPECT_NOT_NULL( target_result );
  EXPECT_NO_ERROR;

  EXPECT_FALSE( stumpless_target_is_open( target ) );

  current_port = stumpless_get_transport_port( target );
  EXPECT_NOT_NULL( current_port );
  EXPECT_TRUE( current_port != new_port );
  EXPECT_STREQ( new_port, current_port );
  EXPECT_NO_ERROR;
  free( ( void * ) current_port );

  target_result = stumpless_set_destination( target, destination );
  EXPECT_NOT_NULL( target_result );

  target_result = stumpless_open_target( target );
  ASSERT_NOT_NULL( target_result );
  EXPECT_TRUE( target_result == target );
  EXPECT_NO_ERROR;

  EXPECT_TRUE( stumpless_target_is_open( target ) );

  if( new_port_server != BAD_HANDLE ) {
    entry = create_entry(  );
    add_result = stumpless_add_entry( target, entry );
    EXPECT_GT( add_result, 0 );
    EXPECT_NO_ERROR;

    recv_from_handle( new_port_server, buffer, 1024 );
    EXPECT_TRUE( buffer[0] != '\0' );
    TestRFC5424Compliance( buffer );

    stumpless_destroy_entry_and_contents( entry );
  }
}

void TestTruncatedMessage( struct stumpless_target *target ) {
  size_t max_msg_size;
  size_t my_msg_size;
  char *message;
  int result;

  ASSERT_NOT_NULL( target );
  ASSERT_TRUE( stumpless_target_is_open( target ) );

  max_msg_size = stumpless_get_udp_max_message_size( target );
  ASSERT_NE( max_msg_size, 0 );

  my_msg_size = max_msg_size + 10;
  message = ( char * ) malloc( my_msg_size );
  ASSERT_NOT_NULL( message );
  memset( message, 'a', max_msg_size );
  memcpy( message, "begin", 5 );
  memcpy( message + max_msg_size, "truncated", 9 );
  message[my_msg_size-1] = '\0';

  result = stumpless_add_message( target, message );
  EXPECT_GE( result, 0 );
  EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );

  free( message );
}
