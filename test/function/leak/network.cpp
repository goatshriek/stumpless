// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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
#include <stddef.h>
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( set_port )

namespace {

  TEST( NetworkTargetLeakTest, SetPort ) {
    struct stumpless_target *target;
    struct stumpless_target *result;

    INIT_MEMORY_COUNTER( set_port );
    stumpless_set_malloc( set_port_memory_counter_malloc );
    stumpless_set_realloc( set_port_memory_counter_realloc );
    stumpless_set_free( set_port_memory_counter_free );

    target = stumpless_open_udp4_target( "set-port-leak",
                                         "127.0.0.1",
                                         0,
                                         STUMPLESS_FACILITY_USER );
    ASSERT_TRUE( target != NULL );

    result = stumpless_set_transport_port( target, "6514" );
    ASSERT_TRUE( result != NULL );

    stumpless_close_network_target( target );

    stumpless_free_all(  );

    EXPECT_EQ( set_port_memory_counter.alloc_total,
               set_port_memory_counter.free_total );

  }

}
