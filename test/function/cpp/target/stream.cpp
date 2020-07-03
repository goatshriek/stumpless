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

#include <cstdio>
#include <gtest/gtest.h>
#include <stumpless.hpp>
#include <stumpless/option.h>

using namespace stumplesscpp;

namespace {

  class CppStreamTargetTest : public::testing::Test {
    protected:
      const char *filename = "cpptestfile.log";
      FILE *stream;

    virtual void
    SetUp( void ) {
      stream = fopen( filename, "w+" );
    }

    virtual void
    TearDown( void ) {
      fclose( stream );
      remove( filename );
    }
  };

  TEST_F( CppStreamTargetTest, AddMessage ) {
    StreamTarget target( "test-stream",
                         stream,
                         STUMPLESS_OPTION_NONE,
                         Facility::USER );

    target.Log( "this is a basic test of the stream target" );
  }
}
