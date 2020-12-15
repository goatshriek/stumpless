// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020 Joel E. Anderson
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

#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.hpp>

using namespace stumpless;

namespace {

  class CppEntryTest : public::testing::Test {
  protected:
    Entry *basic_entry;
    const char *basic_app_name = "stumpless-cpp-testing";
    const char *basic_message = "This is a basic entry.";

    virtual void
    SetUp( void ) {
      basic_entry = new Entry( Facility::USER,
                               Severity::INFO,
                               basic_app_name,
                               "basic-msg",
                               "This is a basic entry." );
    }

    virtual void
    TearDown( void ) {
      delete basic_entry;
    }

  };

  TEST_F( CppEntryTest, GetAppName ) {
    const char *result;

    result = basic_entry->GetAppName(  );
    EXPECT_STREQ( result, basic_app_name );

    free( ( void * ) result );
  }

  TEST_F( CppEntryTest, GetMessage ) {
    const char *result;

    result = basic_entry->GetMessage(  );
    EXPECT_STREQ( result, basic_message );

    free( ( void * ) result );
  }

  /* non-fixture tests */

  TEST( BuildEntry, WithElement ) {
    Entry my_entry( Facility::USER,
                    Severity::INFO,
                    "my-app-name",
                    "my-msgid",
                    "my message" );

    Element my_element( "my-element" );
    my_entry.AddElement( my_element );
  }

  TEST( BuildEntry, WithElementAndParams ) {
    Entry my_entry( Facility::USER,
                    Severity::INFO,
                    "my-app-name",
                    "my-msgid",
                    "my message" );

    Element my_element( "my-element" );
    my_entry.AddElement( my_element );

    Param param_1( "param-1", "value-1" );
    Param param_2( "param-2", "value-2" );
    my_element.AddParam(param_1).AddParam(param_2);
  }

  TEST( Constructor, BasicEntry ) {
    Entry my_entry( Facility::USER,
                    Severity::INFO,
                    "my-app-name",
                    "my-msgid",
                    "my message" );
  }
}
