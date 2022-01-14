// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2021 Joel E. Anderson
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

#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( set_port )
NEW_MEMORY_COUNTER( unsupported_transport )

namespace {

  TEST( NetworkTargetLeakTest, SetPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;

    INIT_MEMORY_COUNTER( set_port );

    target = stumpless_open_udp4_target( "set-port-leak",
                                         "127.0.0.1" );
    ASSERT_NOT_NULL( target );

    result = stumpless_set_transport_port( target, "6514" );
    ASSERT_NOT_NULL( result );

    stumpless_close_network_target( target );
    stumpless_free_all(  );

    ASSERT_NO_LEAK( set_port );
  }

  TEST( NetworkTargetLeakTest, UnsupportedTransportProtocol ) {
    struct stumpless_target *target;

    INIT_MEMORY_COUNTER( unsupported_transport );

    target = stumpless_new_network_target( "bad-ipv4-transport",
                                           STUMPLESS_IPV4_NETWORK_PROTOCOL,
                                           // assuming this isn't a valid protocol
                                           ( enum stumpless_transport_protocol ) -1 );
    ASSERT_NULL( target );

    stumpless_free_all(  );

    ASSERT_NO_LEAK( unsupported_transport );
  }

}
