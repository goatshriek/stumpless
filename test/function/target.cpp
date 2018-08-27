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

#include <stddef.h>
#include <gtest/gtest.h>
#include <stumpless.h>

namespace {

  TEST( AddEntryTest, NullEntry ) {
    int result;
    struct stumpless_target *target;
    struct stumpless_error *error;
    char buffer[10];

    target = stumpless_open_buffer_target( "null entry testing",
                                           buffer,
                                           10,
                                           0,
                                           0 );

    result = stumpless_add_entry( target, NULL );
    EXPECT_LT( result, 0 );
    
    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );

    stumpless_close_buffer_target( target );
  }

  TEST( AddEntryTest, NullTarget ) {
    int result;
    struct stumpless_entry *entry;
    struct stumpless_error *error;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );

    result = stumpless_add_entry( NULL, entry );
    EXPECT_LT( result, 0 );
    
    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry( entry );
  }

  TEST( SetDefaultAppName, MemoryFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target", buffer, 100, 0, 0 );
    ASSERT_TRUE( target != NULL );
   
    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    target_result = stumpless_set_target_default_app_name( target, "app-name" );
    EXPECT_EQ( NULL, target_result );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
  }

  TEST( SetDefaultMsgId, MemoryFailure ) {
    char buffer[100];
    struct stumpless_target *target;
    struct stumpless_target *target_result;
    struct stumpless_error *error;
    void *(*set_malloc_result)(size_t);

    target = stumpless_open_buffer_target( "test target", buffer, 100, 0, 0 );
    ASSERT_TRUE( target != NULL );
   
    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    target_result = stumpless_set_target_default_msgid( target, "msgid" );
    EXPECT_EQ( NULL, target_result );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    stumpless_set_malloc( malloc );
    stumpless_close_buffer_target( target );
  }
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
