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

namespace {

  TEST( NetworkTargetTest, Add ) {
    struct stumpless_target target;
    struct stumpless_entry *entry;
    struct stumpless_error *error;
    int result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );

    target.type = STUMPLESS_NETWORK_TARGET;
    target.id = &target;

    result = stumpless_add_entry( &target, entry );
    EXPECT_LT( result, 0 );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_UNSUPPORTED );
    }

    stumpless_destroy_entry( entry );
  }

  TEST( NetworkTargetTest, GenericClose ) {
    struct stumpless_target target;
    struct stumpless_error *error;

    target.type = STUMPLESS_NETWORK_TARGET;

    stumpless_close_target( &target );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_UNSUPPORTED );
    }
  }

  TEST( NetworkTargetTest, IsOpen ) {
    struct stumpless_target target;
    const struct stumpless_target *result;
    struct stumpless_error *error;

    target.type = STUMPLESS_NETWORK_TARGET;
    target.id = &target;

    result = stumpless_target_is_open( &target );

    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_TARGET_UNSUPPORTED );
    }
  }
}
