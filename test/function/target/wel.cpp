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
  class WelTargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target;
      struct stumpless_entry *simple_entry;
      struct stumpless_entry *one_insertion_entry;
      struct stumpless_entry *two_insertion_entry;

    virtual void
    SetUp( void ) {
      target = stumpless_open_local_wel_target( "wel-target-test", 0, 0 );

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
      stumpless_close_wel_target( target );
      stumpless_destroy_entry( simple_entry );
      stumpless_destroy_entry( one_insertion_entry );
      stumpless_destroy_entry( two_insertion_entry );
    }
  };

  TEST_F( WelTargetTest, AddEntryWithOneInsertionString ) {
    int result;

    result = stumpless_add_entry( target, one_insertion_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
  }

  TEST_F( WelTargetTest, AddEntryWithTwoInsertionStrings ) {
    int result;

    result = stumpless_add_entry( target, two_insertion_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
  }

  TEST_F( WelTargetTest, AddSimpleEntry ) {
    int result;
    HANDLE event_log_handle;
    BOOL success;
    BYTE buffer[1000];
    DWORD dwBytesRead = 0;
    DWORD dwMinimumBytesToRead = 0;
    PEVENTLOGRECORD record;
    LPWSTR retrieved_message;

    result = stumpless_add_entry( target, simple_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    // read from the event log and find the entry
    event_log_handle = OpenEventLog( NULL, "wel-target-test" );
    ASSERT_TRUE( event_log_handle != NULL );

    success = ReadEventLog(
      event_log_handle,
      EVENTLOG_SEQUENTIAL_READ | EVENTLOG_BACKWARDS_READ,
      0,
      buffer,
      1000,
      &dwBytesRead,
      &dwMinimumBytesToRead
    );
    EXPECT_TRUE( success );

    record = (PEVENTLOGRECORD)buffer;

    retrieved_message = (LPWSTR)(record + record->StringOffset);
    EXPECT_TRUE( retrieved_message != NULL );

    CloseEventLog( event_log_handle );
  }

  /* non-fixture tests */

  TEST( WelTargetCloseTest, NullTarget ) {
    struct stumpless_error *error;

    stumpless_close_wel_target( NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    ASSERT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }
}
