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

#include <gtest/gtest.h>
#include <stddef.h>
#include <stumpless.h>
#include "test/function/windows/events.h"

namespace {
  class WelSupportedTest : public::testing::Test {
    protected:
      struct stumpless_entry *simple_entry;
      struct stumpless_entry *one_insertion_entry;
      struct stumpless_entry *two_insertion_entry;

    virtual void
    SetUp( void ) {
      simple_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                          STUMPLESS_SEVERITY_INFO,
                                          "stumpless-wel-unit-test",
                                          "simple-entry",
                                          "simple test message" );

      stumpless_set_wel_category( simple_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( simple_entry, MSG_SIMPLE );
      stumpless_set_wel_type( simple_entry, EVENTLOG_SUCCESS );

      one_insertion_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                                 STUMPLESS_SEVERITY_INFO,
                                                 "stumpless-wel-unit-test",
                                                 "single-insertion-entry",
                                                 "message with one insertion string" );

      stumpless_set_wel_category( one_insertion_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( one_insertion_entry, MSG_ONE_INSERTION );
      stumpless_set_wel_type( one_insertion_entry, EVENTLOG_SUCCESS );
      stumpless_add_wel_insertion_string( one_insertion_entry, "insertion-string-1" );

      two_insertion_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                                 STUMPLESS_SEVERITY_INFO,
                                                 "stumpless-wel-unit-test",
                                                 "two-insertion-entry",
                                                 "message with two insertion strings" );

      stumpless_set_wel_category( two_insertion_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( two_insertion_entry, MSG_ONE_INSERTION );
      stumpless_set_wel_type( two_insertion_entry, EVENTLOG_SUCCESS );
      stumpless_add_wel_insertion_string( two_insertion_entry, "insertion-string-1" );
      stumpless_add_wel_insertion_string( two_insertion_entry, "insertion-string-2" );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry( simple_entry );
      stumpless_destroy_entry( one_insertion_entry );
      stumpless_destroy_entry( two_insertion_entry );
    }
  };

  TEST_F( WelSupportedTest, AddNullInsertionString ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry_result;
 
    entry_result = stumpless_add_wel_insertion_string( simple_entry, NULL );
    EXPECT_TRUE( entry_result == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  /* non-fixture tests */

  TEST( WelEntryCategory, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_set_wel_category( NULL, CATEGORY_TEST );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryEventId, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_set_wel_event_id( NULL, MSG_SIMPLE );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryInsertionString, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_add_wel_insertion_string( NULL, "test-string" );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryType, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_set_wel_type( NULL, EVENTLOG_SUCCESS );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }
}
