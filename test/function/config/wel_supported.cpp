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

#include <gtest/gtest.h>
#include <stddef.h>
#include <stumpless.h>
#include <windows.h>
#include "test/helper/assert.hpp"
#include "test/function/windows/events.h"

namespace {
  class WelSupportedTest : public::testing::Test {
    protected:
      struct stumpless_entry *simple_entry;
      struct stumpless_entry *insertion_entry;
      LPCSTR first_insertion = "message #1";
      LPCSTR second_insertion = "message #2";

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

      insertion_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                             STUMPLESS_SEVERITY_INFO,
                                             "stumpless-wel-unit-test",
                                             "insertion-entry",
                                             "string 1: %%1\nstring 2: %%2" );

      stumpless_set_wel_category( insertion_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( insertion_entry, MSG_TWO_INSERTIONS );
      stumpless_set_wel_type( insertion_entry, EVENTLOG_SUCCESS );

      stumpless_set_wel_insertion_strings( insertion_entry,
                                           2,
                                           first_insertion,
                                           second_insertion );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry( simple_entry );
      stumpless_destroy_entry( insertion_entry );
    }
  };

  TEST_F( WelSupportedTest, GetInsertionStringIndexTooHigh ) {
    const char *result;
    WORD index = 4;
    const struct stumpless_error *error;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string( insertion_entry, index );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, index );
  }

  TEST_F( WelSupportedTest, GetInsertionStringLastString ) {
    const char *result;

    ASSERT_TRUE( insertion_entry != NULL );

    result = stumpless_get_wel_insertion_string( insertion_entry, 1 );
    EXPECT_TRUE( result != NULL );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    EXPECT_TRUE( result != second_insertion );
    EXPECT_STREQ( result, second_insertion );
  }

  TEST_F( WelSupportedTest, GetInsertionStringNullEntry ) {
    const char *result;
    const struct stumpless_error *error;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string( NULL, 1 );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( WelSupportedTest, SetNullInsertionParam ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry_result;

    entry_result = stumpless_set_wel_insertion_param( simple_entry, 0, NULL );
    EXPECT_NULL( entry_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( WelSupportedTest, SetNullInsertionString ) {
    const struct stumpless_error *error;
    const struct stumpless_entry *entry_result;

    entry_result = stumpless_set_wel_insertion_string( simple_entry, 0, NULL );
    EXPECT_NULL( entry_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  /* non-fixture tests */

  TEST( GetDefaultTarget, WelSupported ) {
    struct stumpless_target *target;

    target = stumpless_get_default_target(  );
    ASSERT_NOT_NULL( target );

    EXPECT_EQ( target->type, STUMPLESS_WINDOWS_EVENT_LOG_TARGET );
    EXPECT_STREQ( target->name, STUMPLESS_DEFAULT_TARGET_NAME );

    stumpless_free_all(  );
  }

  TEST( WelEntryCategoryTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_category( NULL, CATEGORY_TEST );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryEventIdTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_event_id( NULL, MSG_SIMPLE );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryTypeTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_type( NULL, EVENTLOG_SUCCESS );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetEntryInsertionParamTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;
    struct stumpless_param *param;

    param = stumpless_new_param( "param-name", "param-value" );
    ASSERT_NOT_NULL( param );

    entry = stumpless_set_wel_insertion_param( NULL, 0, param );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_param( param );
  }

  TEST( WelSetInsertionParamTest, SetSingleParam ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;
    struct stumpless_param *param;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_TRUE( entry != NULL );

    param = stumpless_new_param( "param-name", "param-value" );
    ASSERT_TRUE( param != NULL );

    entry_result = stumpless_set_wel_insertion_param( entry, 0, param );
    EXPECT_EQ( entry_result, entry );

    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    stumpless_destroy_entry( entry );
    stumpless_destroy_param( param );
  }

  TEST( WelSetInsertionParamTest, SetTwoParams ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;
    struct stumpless_param *param_1;
    struct stumpless_param *param_2;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_TRUE( entry != NULL );

    param_1 = stumpless_new_param( "param-1-name", "param-1-value" );
    ASSERT_TRUE( param_1 != NULL );

    param_2 = stumpless_new_param( "param-2-name", "param-2-value" );
    ASSERT_TRUE( param_2 != NULL );

    entry_result = stumpless_set_wel_insertion_param( entry, 0, param_1 );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    entry_result = stumpless_set_wel_insertion_param( entry, 1, param_2 );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    stumpless_destroy_entry( entry );
    stumpless_destroy_param( param_1 );
    stumpless_destroy_param( param_2 );
  }

  TEST( WelSetInsertionParamTest, SetTwoParamsOutOfOrder ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;
    struct stumpless_param *param_1;
    struct stumpless_param *param_2;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_TRUE( entry != NULL );

    param_1 = stumpless_new_param( "param-1-name", "param-1-value" );
    ASSERT_TRUE( param_1 != NULL );

    param_2 = stumpless_new_param( "param-2-name", "param-2-value" );
    ASSERT_TRUE( param_2 != NULL );

    entry_result = stumpless_set_wel_insertion_string( entry, 1, "second string" );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "first string" );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    stumpless_destroy_entry( entry );
    stumpless_destroy_param( param_1 );
    stumpless_destroy_param( param_2 );
  }

  TEST( WelSetEntryInsertionStringTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_insertion_string( NULL, 0, "test-string" );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetInsertionStringTest, SetSingleString ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_TRUE( entry != NULL );

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "testing" );
    EXPECT_EQ( entry_result, entry );

    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    stumpless_destroy_entry( entry );
  }

  TEST( WelSetInsertionStringTest, SetTwoStrings ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_TRUE( entry != NULL );

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "first string" );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    entry_result = stumpless_set_wel_insertion_string( entry, 1, "second string" );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    stumpless_destroy_entry( entry );
  }

  TEST( WelSetInsertionStringTest, SetTwoStringsOutOfOrder ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_TRUE( entry != NULL );

    entry_result = stumpless_set_wel_insertion_string( entry, 1, "second string" );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "first string" );
    EXPECT_EQ( entry_result, entry );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    stumpless_destroy_entry( entry );
  }

  TEST( WelSetInsertionStringsTest, NullEntry ) {
    struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_wel_insertion_strings( NULL, 1, "add me!" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetInsertionStringsTest, NullString ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const struct stumpless_error *error;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_wel_insertion_strings( entry, 1, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry( entry );
  }

  TEST( WelSetInsertionStringsTest, TwoStrings ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    LPCSTR first = "tik";
    LPCSTR second = "tok";
    LPCSTR insertion;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-wel-unit-test",
                                 "simple-entry",
                                 "simple test message" );
    ASSERT_TRUE( entry != NULL );

    result = stumpless_set_wel_insertion_strings( entry, 2, first, second );
    EXPECT_TRUE( result != NULL );
    EXPECT_TRUE( result == entry );

    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    insertion = stumpless_get_wel_insertion_string( entry, 0 );
    EXPECT_TRUE( insertion != first );
    EXPECT_STREQ( insertion, first );

    insertion = stumpless_get_wel_insertion_string( entry, 1 );
    EXPECT_TRUE( insertion != second );
    EXPECT_STREQ( insertion, second );

    stumpless_destroy_entry( entry );
  }
}
