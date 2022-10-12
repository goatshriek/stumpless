// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stumpless.h>
#include <wchar.h>
#include <windows.h>
#include "test/function/windows/events.h"
#include "test/helper/assert.hpp"

using::testing::HasSubstr;

namespace {
  class WelTargetTest : public::testing::Test {
    protected:
      struct stumpless_target *target = NULL;
      struct stumpless_entry *simple_entry = NULL;
      LPCWSTR simple_entry_message_w = L"This is a simple log message.";
      struct stumpless_entry *one_insertion_entry = NULL;
      struct stumpless_entry *two_insertion_entry = NULL;
      struct stumpless_entry *one_insertion_param_entry = NULL;
      struct stumpless_param *insertion_param = NULL;
      const char *insertion_string_1 = "insertion-string-1";
      const char *insertion_string_2 = "insertion-string-2";

    virtual void
    SetUp( void ) {
      target = stumpless_open_local_wel_target( "wel-target-test" );

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

      one_insertion_param_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                                       STUMPLESS_SEVERITY_INFO,
                                                       "stumpless-wel-unit-test",
                                                       "one-insertion-param-entry",
                                                       "message with one insertion param" );

      stumpless_set_wel_category( one_insertion_param_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( one_insertion_param_entry, MSG_ONE_INSERTION );
      stumpless_set_wel_type( one_insertion_param_entry, EVENTLOG_SUCCESS );

      insertion_param = stumpless_new_param( "index-0", insertion_string_1 );
      stumpless_set_wel_insertion_param( one_insertion_param_entry,
                                         0,
                                         insertion_param );
    }

    virtual void
    TearDown( void ) {
      stumpless_close_wel_target( target );
      stumpless_destroy_entry_and_contents( simple_entry );
      stumpless_destroy_entry_and_contents( one_insertion_entry );
      stumpless_destroy_entry_and_contents( two_insertion_entry );
      stumpless_destroy_entry_and_contents( one_insertion_param_entry );
      stumpless_destroy_param( insertion_param );
    }
  };

  TEST_F( WelTargetTest, AddEntryWithOneInsertionParam ) {
    int result;
    HANDLE event_log_handle;
    BOOL success;
    BYTE record_buffer[1000];
    DWORD format_result;
    DWORD bytes_read = 0;
    DWORD minimum_bytes_to_read = 0;
    HMODULE resource_dll;
    PEVENTLOGRECORD record;
    LPCWSTR insertion_strings[2];
    size_t string_1_length;
    WCHAR message_buffer[1000];

    result = stumpless_add_entry( target, one_insertion_param_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    // read from the event log and find the entry
    event_log_handle = OpenEventLog( NULL, "wel-target-test" );
    ASSERT_NOT_NULL( event_log_handle );

    success = ReadEventLogW( event_log_handle,
                             EVENTLOG_SEQUENTIAL_READ |
                               EVENTLOG_BACKWARDS_READ,
                             0,
                             record_buffer,
                             1000,
                             &bytes_read,
                             &minimum_bytes_to_read );
    EXPECT_TRUE( success );

    record = ( PEVENTLOGRECORD ) record_buffer;
    EXPECT_EQ( record->EventID, MSG_ONE_INSERTION );
    EXPECT_EQ( record->EventCategory, CATEGORY_TEST );
    EXPECT_EQ( record->EventType, EVENTLOG_SUCCESS );
    EXPECT_EQ( record->NumStrings, 1 );

    resource_dll = LoadLibraryEx( WEL_EVENTS_LIBRARY_NAME,
                                  NULL,
                                  LOAD_LIBRARY_AS_IMAGE_RESOURCE |
                                    LOAD_LIBRARY_AS_DATAFILE );
    EXPECT_NOT_NULL( resource_dll );

    insertion_strings[0] = ( LPCWSTR ) ( record_buffer + record->StringOffset );
    string_1_length = wcslen( insertion_strings[0] );
    EXPECT_EQ( string_1_length, strlen( insertion_string_1 ) );

    format_result = FormatMessageW( FORMAT_MESSAGE_FROM_HMODULE |
                                      FORMAT_MESSAGE_ARGUMENT_ARRAY,
                                    resource_dll,
                                    record->EventID,
                                    0,
                                    message_buffer,
                                    1000,
                                    ( va_list * )( insertion_strings ) );
    EXPECT_NE( format_result, 0 );

    EXPECT_NOT_NULL( wcsstr( message_buffer, insertion_strings[0] ) );

    CloseEventLog( event_log_handle );
  }

  TEST_F( WelTargetTest, AddEntryWithOneInsertionString ) {
    int result;

    result = stumpless_add_entry( target, one_insertion_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;
  }

  TEST_F( WelTargetTest, AddEntryWithTwoInsertionStrings ) {
    int result;
    HANDLE event_log_handle;
    BOOL success;
    BYTE record_buffer[1000];
    DWORD format_result;
    DWORD bytes_read = 0;
    DWORD minimum_bytes_to_read = 0;
    HMODULE resource_dll;
    PEVENTLOGRECORD record;
    LPCWSTR insertion_strings[2];
    size_t string_1_length;
    WCHAR message_buffer[1000];

    result = stumpless_add_entry( target, two_insertion_entry );
    EXPECT_GE( result, 0 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    // read from the event log and find the entry
    event_log_handle = OpenEventLog( NULL, "wel-target-test" );
    ASSERT_NOT_NULL( event_log_handle );

    success = ReadEventLogW( event_log_handle,
                             EVENTLOG_SEQUENTIAL_READ |
                               EVENTLOG_BACKWARDS_READ,
                             0,
                             record_buffer,
                             1000,
                             &bytes_read,
                             &minimum_bytes_to_read );
    EXPECT_TRUE( success );

    record = ( PEVENTLOGRECORD ) record_buffer;
    EXPECT_EQ( record->EventID, MSG_TWO_INSERTIONS );
    EXPECT_EQ( record->EventCategory, CATEGORY_TEST );
    EXPECT_EQ( record->EventType, EVENTLOG_SUCCESS );
    EXPECT_EQ( record->NumStrings, 2 );

    resource_dll = LoadLibraryEx( WEL_EVENTS_LIBRARY_NAME,
                                  NULL,
                                  LOAD_LIBRARY_AS_IMAGE_RESOURCE |
                                    LOAD_LIBRARY_AS_DATAFILE );
    EXPECT_NOT_NULL( resource_dll );

    insertion_strings[0] = ( LPCWSTR ) ( record_buffer + record->StringOffset );
    string_1_length = wcslen( insertion_strings[0] );
    EXPECT_EQ( string_1_length, strlen( insertion_string_1 ) );

    insertion_strings[1] = ( LPCWSTR ) ( insertion_strings[0] + string_1_length + 1 );
    EXPECT_EQ( wcslen( insertion_strings[1] ), strlen( insertion_string_2 ) );

    format_result = FormatMessageW( FORMAT_MESSAGE_FROM_HMODULE |
                                      FORMAT_MESSAGE_ARGUMENT_ARRAY,
                                    resource_dll,
                                    record->EventID,
                                    0,
                                    message_buffer,
                                    1000,
                                    ( va_list * )( insertion_strings ) );
    EXPECT_NE( format_result, 0 );

    EXPECT_NOT_NULL( wcsstr( message_buffer, insertion_strings[0] ) );
    EXPECT_NOT_NULL( wcsstr( message_buffer, insertion_strings[1] ) );

    CloseEventLog( event_log_handle );
  }

  TEST_F( WelTargetTest, AddSimpleEntry ) {
    int result;
    HANDLE event_log_handle;
    BOOL success;
    BYTE record_buffer[1000];
    DWORD format_result;
    DWORD bytes_read = 0;
    DWORD minimum_bytes_to_read = 0;
    HMODULE resource_dll;
    PEVENTLOGRECORD record;
    WCHAR message_buffer[1000];

    result = stumpless_add_entry( target, simple_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    // read from the event log and find the entry
    event_log_handle = OpenEventLog( NULL, "wel-target-test" );
    ASSERT_NOT_NULL( event_log_handle );

    success = ReadEventLogW( event_log_handle,
                             EVENTLOG_SEQUENTIAL_READ | EVENTLOG_BACKWARDS_READ,
                             0,
                             record_buffer,
                             1000,
                             &bytes_read,
                             &minimum_bytes_to_read );
    EXPECT_TRUE( success );

    record = ( PEVENTLOGRECORD ) record_buffer;
    EXPECT_EQ( record->EventID, MSG_SIMPLE );
    EXPECT_EQ( record->EventCategory, CATEGORY_TEST );
    EXPECT_EQ( record->EventType, EVENTLOG_SUCCESS );

    resource_dll = LoadLibraryEx( WEL_EVENTS_LIBRARY_NAME,
                                  NULL,
                                  LOAD_LIBRARY_AS_IMAGE_RESOURCE |
                                    LOAD_LIBRARY_AS_DATAFILE );
    EXPECT_NOT_NULL( resource_dll );

    format_result = FormatMessageW( FORMAT_MESSAGE_FROM_HMODULE,
                                    resource_dll,
                                    record->EventID,
                                    0,
                                    message_buffer,
                                    1000,
                                    NULL );
    EXPECT_NE( format_result, 0 );

    EXPECT_NOT_NULL( wcsstr( message_buffer, simple_entry_message_w ) );

    CloseEventLog( event_log_handle );
  }

  /* non-fixture tests */

  TEST( WelTargetCloseTest, Generic ) {
    const char *target_name = "wel-target-test";
    struct stumpless_target *target;

    target = stumpless_open_local_wel_target( target_name );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_EQ( stumpless_get_current_target(  ), target );

    stumpless_close_target( target );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(  ),
               stumpless_get_default_target(  ) );
    EXPECT_STRNE( stumpless_get_current_target(  )->name,
                  target_name );
  }

  TEST( WelTargetCloseTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_wel_target( NULL );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelTargetCloseTest, WrongTargetType ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-wel-target" );
    ASSERT_NOT_NULL( target );

    stumpless_close_wel_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_stream_target( target );
  }

  TEST( WelTargetOpenRemoteTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_remote_wel_target( "remote-server", NULL );
    ASSERT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }
}
