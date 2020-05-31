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

  TEST( NewParamTest, New ){
    struct stumpless_param *param;
    const char *name = "test-param-name";
    const char *value = "test-param-value";
  
    size_t name_length = strlen( name );
    size_t value_length = strlen( value );
 
    param = stumpless_new_param( name, value );
    ASSERT_TRUE( param != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
   
    ASSERT_EQ( name_length, param->name_length );
    ASSERT_TRUE( param->name != NULL );
    ASSERT_EQ( 0, memcmp( param->name, name, name_length ) );
    
    ASSERT_EQ( value_length, param->value_length );
    ASSERT_TRUE( param->value != NULL );
    ASSERT_EQ( 0, memcmp( param->value, value, value_length ) );

    stumpless_destroy_param( param );
  }

  TEST( NewParamTest, NullName ) {
    struct stumpless_param *param;
    struct stumpless_error *error;

    param = stumpless_new_param( NULL, "test-value" );    
    EXPECT_TRUE( param == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NewParamTest, NullValue ) {
    struct stumpless_param *param;
    struct stumpless_error *error;

    param = stumpless_new_param( "test-name", NULL );    
    EXPECT_TRUE( param == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SetName, Basic ) {
    struct stumpless_param *param;
    const char *original_name = "first_name";
    const char *new_name = "second_name";
    struct stumpless_param *result;

    param = stumpless_new_param( original_name, "my_value" );
    ASSERT_TRUE( param != NULL );
    EXPECT_STREQ( stumpless_get_param_name( param ), original_name );

    result = stumpless_set_param_name( param, new_name );
    EXPECT_TRUE( result == param );
    EXPECT_STREQ( stumpless_get_param_name( param ), new_name );

    stumpless_destroy_param( param );
  }

}
