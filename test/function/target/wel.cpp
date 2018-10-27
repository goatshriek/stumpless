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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stddef.h>
#include <string.h>
#include <stumpless.h>
#include <windows.h>
#include "test/function/windows/events.h"

using::testing::HasSubstr;

namespace {
  class WelTargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target;
      struct stumpless_entry *simple_entry;
      struct stumpless_entry *one_insertion_entry;
      struct stumpless_entry *two_insertion_entry;
      const char *insertion_string_1 = "insertion-string-1";
      const char *insertion_string_2 = "insertion-string-2";

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
      stumpless_set_wel_insertion_string( one_insertion_entry, 0, insertion_string_1 );

      two_insertion_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                                 STUMPLESS_SEVERITY_INFO,
                                                 "stumpless-wel-unit-test",
                                                 "two-insertion-entry",
                                                 "message with two insertion strings" );

      stumpless_set_wel_category( two_insertion_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( two_insertion_entry, MSG_TWO_INSERTIONS );
      stumpless_set_wel_type( two_insertion_entry, EVENTLOG_SUCCESS );
      stumpless_set_wel_insertion_string( two_insertion_entry, 0, insertion_string_1 );
      stumpless_set_wel_insertion_string( two_insertion_entry, 1, insertion_string_2 );
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
    HANDLE event_log_handle;
    BOOL success;
    BYTE buffer[1000];
    DWORD format_result;
    DWORD bytes_read = 0;
    DWORD minimum_bytes_to_read = 0;
    HMODULE resource_dll;
    PEVENTLOGRECORD record;
    LPTSTR insertion_strings[2];
    LPTSTR message_buffer;

    result = stumpless_add_entry( target, two_insertion_entry );
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
      &bytes_read,
      &minimum_bytes_to_read
    );
    EXPECT_TRUE( success );

    record = ( PEVENTLOGRECORD ) buffer;
    EXPECT_EQ( record->EventID, MSG_TWO_INSERTIONS );
    EXPECT_EQ( record->EventCategory, CATEGORY_TEST );
    EXPECT_EQ( record->EventType, EVENTLOG_SUCCESS );

    resource_dll = LoadLibraryEx( "events.dll", NULL, LOAD_LIBRARY_AS_IMAGE_RESOURCE | LOAD_LIBRARY_AS_DATAFILE );
    EXPECT_TRUE( resource_dll != NULL );

    insertion_strings[0] = ( LPTSTR ) ( buffer + record->StringOffset );
    insertion_strings[1] = ( LPTSTR ) ( insertion_strings[0] + strlen( insertion_strings[0] ) + 1 );

    format_result = FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ARGUMENT_ARRAY,
      resource_dll,
      record->EventID,
      0,
      (LPTSTR)&message_buffer,
      1000,
      (va_list*)(insertion_strings)
    );
    EXPECT_NE( format_result, 0 );

    EXPECT_THAT( message_buffer, HasSubstr( insertion_string_1 ) );
    EXPECT_THAT( message_buffer, HasSubstr( insertion_string_2 ) );

    CloseEventLog( event_log_handle );
  }

  TEST_F( WelTargetTest, AddSimpleEntry ) {
    int result;
    HANDLE event_log_handle;
    BOOL success;
    BYTE buffer[1000];
    DWORD format_result;
    DWORD bytes_read = 0;
    DWORD minimum_bytes_to_read = 0;
    HMODULE resource_dll;
    PEVENTLOGRECORD record;
    LPTSTR message_buffer;

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
      &bytes_read,
      &minimum_bytes_to_read
    );
    EXPECT_TRUE( success );

    record = ( PEVENTLOGRECORD )buffer;
    EXPECT_EQ( record->EventID, MSG_SIMPLE );
    EXPECT_EQ( record->EventCategory, CATEGORY_TEST );
    EXPECT_EQ( record->EventType, EVENTLOG_SUCCESS );

    resource_dll = LoadLibraryEx("events.dll", NULL, LOAD_LIBRARY_AS_IMAGE_RESOURCE | LOAD_LIBRARY_AS_DATAFILE);
    EXPECT_TRUE( resource_dll != NULL );

    format_result = FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE,
      resource_dll,
      record->EventID,
      0,
      (LPTSTR)&message_buffer,
      1000,
      NULL
    );
    EXPECT_NE( format_result, 0 );

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
