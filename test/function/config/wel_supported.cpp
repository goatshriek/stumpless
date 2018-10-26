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
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry( simple_entry );
    }
  };

  TEST_F( WelSupportedTest, SetNullInsertionParam ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry_result;
 
    entry_result = stumpless_set_wel_insertion_param( simple_entry, 0, NULL );
    EXPECT_TRUE( entry_result == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( WelSupportedTest, SetNullInsertionString ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry_result;
 
    entry_result = stumpless_set_wel_insertion_string( simple_entry, 0, NULL );
    EXPECT_TRUE( entry_result == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  /* non-fixture tests */

  TEST( WelEntryCategoryTest, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_set_wel_category( NULL, CATEGORY_TEST );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryEventIdTest, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_set_wel_event_id( NULL, MSG_SIMPLE );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryTypeTest, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_set_wel_type( NULL, EVENTLOG_SUCCESS );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetEntryInsertionParamTest, NullEntry ) {
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    struct stumpless_param *param;

    param = stumpless_new_param( "param-name", "param-value" );
    ASSERT_TRUE( param != NULL );
    
    entry = stumpless_set_wel_insertion_param( NULL, 0, param );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );

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
    struct stumpless_error *error;
    struct stumpless_entry *entry;
    
    entry = stumpless_set_wel_insertion_string( NULL, 0, "test-string" );
    EXPECT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
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
}
