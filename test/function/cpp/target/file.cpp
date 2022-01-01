// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2021 Joel E. Anderson
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

#include <cstddef>
#include <fstream>
#include <gtest/gtest.h>
#include <stumpless.h>
#include <stumpless.hpp>
#include "test/helper/rfc5424.hpp"

using namespace stumpless;

namespace {

  class CppFileTargetTest : public::testing::Test {
  protected:
    Entry *basic_entry;

    virtual void
    SetUp( void ) {
      basic_entry = new Entry( Facility::USER,
                               Severity::INFO,
                               "stumpless-cpp-testing",
                               "basic-msg",
                               "This is a basic entry." );
    }
  };

  TEST_F( CppFileTargetTest, BasicLog ) {
    const char *filename = "cppbasictest.log";
    int i;

    remove( filename );
    FileTarget test( filename );

    test.Log( *basic_entry );

    std::ifstream infile( filename );
    std::string line;
    i = 0;
    while( std::getline( infile, line ) ) {
      TestRFC5424Compliance( line.c_str() );
      i++;
    }

    remove( filename );
  }

  /* non-fixture tests */

  TEST( Constructor, NullName ) {
    const char *filename = NULL;

    EXPECT_THROW( FileTarget test( filename ), StumplessException * );
  }

  TEST( DefaultFileConstant, EqualToOriginal ) {
    EXPECT_STREQ( FileTarget::DEFAULT_FILE, STUMPLESS_DEFAULT_FILE );
  }

  TEST( SetDefaultAppName, NullName ) {
    const char *filename = "cppbasictest.log";

    remove( filename );

    FileTarget test( filename );

    EXPECT_THROW( test.SetDefaultAppName( NULL ), StumplessException * );

    try {
      test.SetDefaultAppName( NULL );
    } catch( StumplessException *e ) {
      EXPECT_EQ( e->GetErrorId(), ErrorId::ARGUMENT_EMPTY );
    }

    remove( filename );
  }
}
