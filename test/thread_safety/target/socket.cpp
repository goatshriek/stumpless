// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020 Joel E. Anderson
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

#include <atomic>
#include <cstddef>
#include <gtest/gtest.h>
#include <string.h>
#include <stumpless.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <thread>
#include <unistd.h>
#include "test/function/rfc5424.hpp"
#include "test/helper/assert.hpp"
#include "test/helper/usage.hpp"

namespace {
  const int THREAD_COUNT = 4;
  const int MESSAGE_COUNT = 100;
  std::atomic_int received_count;

  void
  listen_and_validate( int socket ){
    size_t i;
    char buffer[1024];
    ssize_t msg_len;
    struct sockaddr_un from_addr;
    socklen_t size = 100;

    while( true ) {
      msg_len = recvfrom( socket, buffer, 1024, 0, ( struct sockaddr *) &from_addr, &size );
      if( msg_len < 0 ) {
        break;
      } else {
        buffer[msg_len] = '\0';
      }

      TestRFC5424Compliance( buffer );
      received_count++;
    }
  }

  TEST( WriteConsistency, SimultaneousWrites ) {
    struct sockaddr_un test_socket_addr;
    int test_socket;
    const char *socket_name = "sockettargettest";
    struct stumpless_target *target;
    size_t i;
    std::thread *threads[THREAD_COUNT];
    std::thread *listener_threads[THREAD_COUNT*2];
    struct timeval read_timeout;
    int buffer_size;

    // setting up the listening socket
    test_socket_addr.sun_family = AF_UNIX;
    memcpy(&test_socket_addr.sun_path, socket_name, strlen(socket_name)+1);

    test_socket = socket(test_socket_addr.sun_family, SOCK_DGRAM, 0);

    read_timeout.tv_sec = 2;
    read_timeout.tv_usec = 0;
    setsockopt( test_socket,
                SOL_SOCKET,
                SO_RCVTIMEO,
                &read_timeout,
                sizeof( read_timeout ) );

    buffer_size = 8192 * THREAD_COUNT;
    setsockopt( test_socket,
                SOL_SOCKET,
                SO_SNDBUF,
                &buffer_size,
                sizeof( buffer_size ) );
    setsockopt( test_socket,
                SOL_SOCKET,
                SO_RCVBUF,
                &buffer_size,
                sizeof( buffer_size ) );

    bind(test_socket,
         (struct sockaddr *) &test_socket_addr,
         sizeof(test_socket_addr));

    received_count = 0;
    for( i = 0; i < THREAD_COUNT*2; i++ ) {
      listener_threads[i] = new std::thread( listen_and_validate, test_socket );
    }

    // set up the target to log to
    target = stumpless_open_socket_target( socket_name,
                                           "thread-safety-test-target-socket",
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( target );

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i] = new std::thread( add_messages, target, MESSAGE_COUNT );
    }

    for( i = 0; i < THREAD_COUNT; i++ ) {
      threads[i]->join(  );
      delete threads[i];
    }

    for( i = 0; i < THREAD_COUNT*2; i++ ) {
      listener_threads[i]->join(  );
      delete listener_threads[i];
    }

    // cleanup after the test
    stumpless_close_socket_target( target );
    EXPECT_NO_ERROR;

    close( test_socket );
    unlink( socket_name );

    stumpless_free_all(  );

    // final checks
    EXPECT_EQ( THREAD_COUNT * MESSAGE_COUNT, received_count );
  }
}
