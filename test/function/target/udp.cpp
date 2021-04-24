// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/function/target/udp.hpp"

void TestTruncatedMessage( struct stumpless_target *target ) {
  size_t max_msg_size;
  size_t my_msg_size;
  char *message;
  int result;
  const struct stumpless_error *error;

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
