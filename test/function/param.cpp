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
#include <stumpless.h>

namespace {

  class ParamTest : public::testing::Test {
    protected:
      struct stumpless_param *basic_param;
      const char *basic_name = "basic-name";
      const char *basic_value = "basic-value";

      virtual void
      SetUp( void ) {
        basic_param = stumpless_new_param( basic_name, basic_value );
      }

      virtual void
      TearDown( void ) {
        stumpless_destroy_param( basic_param );
      }
  };

  TEST_F( ParamTest, GetName ) {
    EXPECT_STREQ( stumpless_get_param_name( basic_param ), basic_name );
  }

  TEST_F( ParamTest, GetValue ) {
    EXPECT_STREQ( stumpless_get_param_value( basic_param ), basic_value );
  }

  /* non-fixture tests */

  TEST( DestroyParamTest, NullParam ) {
    stumpless_destroy_param( NULL );
  }

  TEST( SetName, Basic ) {
    struct stumpless_param *param;

    param = stumpless_new_param( "my_name", "my_value" );

    stumpless_destroy_param( param );
  }

}
