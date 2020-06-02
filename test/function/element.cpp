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

#include <cstddef>
#include <cstdlib>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>

using::testing::HasSubstr;

namespace {

  class ElementTest : public::testing::Test {
    protected:
      struct stumpless_element *basic_element;
      const char *basic_name = "basic-element";
      struct stumpless_element *element_with_params;

      virtual void
      SetUp( void ) {
        basic_element = stumpless_new_element( basic_name );

        element_with_params = stumpless_new_element( "element-with-params" );
        stumpless_add_new_param( element_with_params, "param-1", "value-1" );
        stumpless_add_new_param( element_with_params, "param-2", "value-2" );
      }

      virtual void
      TearDown( void ) {
        stumpless_destroy_element_and_contents( basic_element );
        stumpless_destroy_element_and_contents( element_with_params );
      }
  };

  TEST_F( ElementTest, AddNewParamNullName ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_add_new_param( basic_element, NULL, "param-value" );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }

    // todo test to make sure that param count has not changed
  }

  TEST_F( ElementTest, AddNullParam ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_add_param( basic_element, NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }

    // todo test to make sure that param count has not changed
  }

  TEST_F( ElementTest, AddParam ) {
    struct stumpless_param *param;
    const struct stumpless_element *result;

    param = stumpless_new_param( "test-param-name", "test-param-value" );
    ASSERT_TRUE( param != NULL );

    result = stumpless_add_param( basic_element, param );
    EXPECT_EQ( basic_element, result );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
   
    // todo test that param count has increased 
    // todo test to make sure that new param actually exists
  }

  TEST_F( ElementTest, AddParamMemoryFailure ) {
    struct stumpless_element *result;
    struct stumpless_param *param;
    struct stumpless_error *error;
    void * (*set_realloc_result)(void *, size_t);

    param = stumpless_new_param( "test-param-name", "test-param-value" );
    ASSERT_TRUE( param != NULL );
   
    set_realloc_result = stumpless_set_realloc( [](void *, size_t)->void *{ return NULL; } );
    ASSERT_TRUE( set_realloc_result != NULL );

    result = stumpless_add_param( basic_element, param );
    EXPECT_EQ( NULL, result );
    
    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }
   
    stumpless_set_realloc( realloc );
  }

  TEST_F( ElementTest, AddTwoParams ) {
    struct stumpless_element *result;
    struct stumpless_param *param1, *param2;

    param1 = stumpless_new_param( "test-param-name-1", "test-param-value-1" );
    ASSERT_TRUE( param1 != NULL );

    result = stumpless_add_param( basic_element, param1 );
    EXPECT_EQ( basic_element, result );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    
    param2 = stumpless_new_param( "test-param-name-2", "test-param-value-2" );
    ASSERT_TRUE( param2 != NULL );

    result = stumpless_add_param( basic_element, param2 );
    EXPECT_EQ( basic_element, result );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
   
    // todo test that param count has increased 
    // todo test to make sure that new param actually exists
  }

  TEST_F( ElementTest, GetName ) {
    EXPECT_STREQ( stumpless_get_element_name( basic_element ), basic_name );
  }

  TEST_F( ElementTest, SetNameMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *new_name = "this-wont-work";
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    // create the internal error struct
    stumpless_get_element_name( NULL );

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    result = stumpless_set_element_name( basic_element, new_name );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    EXPECT_STRNE( stumpless_get_element_name( basic_element ), new_name );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ElementTest, SetNameToNull ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_element_name( basic_element, NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }
  }

  /* non-fixture tests */

  TEST( AddParamTest, NullElement ) {
    struct stumpless_param *param;
    struct stumpless_element *result;
    struct stumpless_error *error;

    param = stumpless_new_param( "test-name", "test-value" );
    ASSERT_TRUE( param != NULL );

    result = stumpless_add_param( NULL, param );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "element" ) );
      EXPECT_THAT( error->message, HasSubstr( "NULL" ) );
    }

    stumpless_destroy_param( param );
  }

  TEST( DestroyElementOnlyTest, NullElement ) {
    stumpless_destroy_element_only( NULL );
  }

  TEST( DestroyElementOnlyTest, OneParam ) {
    struct stumpless_element *element;
    struct stumpless_param *param;
    const char *param_name = "test-param-name";

    element = stumpless_new_element( "test-element" );
    ASSERT_TRUE( element != NULL );

    param = stumpless_new_param( param_name, "test-param-value" );
    ASSERT_TRUE( param != NULL );

    EXPECT_TRUE( stumpless_add_param( element, param ) == element );

    stumpless_destroy_element_only( element );

    EXPECT_TRUE( memcmp( param->name, param_name, param->name_length ) == 0 );
    stumpless_destroy_param( param );
  }

  TEST( DestroyElementTest, NullElement ) {
    stumpless_destroy_element( NULL );
  }

  TEST( GetElementNameTest, NullElement ) {
    const char *result;
    const struct stumpless_error *error;

    result = stumpless_get_element_name( NULL );
    EXPECT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
    }
  }

  TEST( NewElementTest, MemoryFailure ) {
    struct stumpless_element *element;
    struct stumpless_error *error;
    void *(*result)(size_t);
   
    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( result != NULL );

    element = stumpless_new_element( "memory-failure" );
    EXPECT_EQ( NULL, element );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    stumpless_set_malloc( malloc );
  }

  TEST( NewElementTest, NullName ) {
    struct stumpless_element *element;
    struct stumpless_error *error;

    element = stumpless_new_element( NULL );    
    EXPECT_TRUE( element == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

}
