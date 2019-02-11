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

#include <fstream>
#include <stdio.h>
#include <gtest/gtest.h>
#include <stumpless.h>

namespace {

  class PerrorTest : public::testing::Test {

    protected:
      FILE *error_file;
      const char *filename = "testfile.log";

    virtual void
    SetUp( void ) {
      error_file = fopen( filename, "w+" );

      stumpless_set_error_stream( error_file );
    }

    virtual void
    TearDown( void ) {
      fclose( error_file );
    }

  };

  TEST_F( PerrorTest, NoError ) {
    stumpless_perror( "this shouldn't show up" );

    std::ifstream infile( filename );
    EXPECT_EQ(infile.peek(), std::ifstream::traits_type::eof() );
  }

}
