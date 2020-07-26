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
#include "test/helper/assert.hpp"
#include "test/helper/memory_allocation.hpp"

using::testing::HasSubstr;

namespace {

  class ElementTest : public::testing::Test {
    protected:
      struct stumpless_element *basic_element;
      const char *basic_name = "basic-element";
      struct stumpless_element *element_with_params;
      const char *param_1_name = "param-1";
      const char *param_1_value = "value-1";
      struct stumpless_param *param_1;
      const char *param_2_name = "param-2";
      const char *param_2_value = "value-2";
      struct stumpless_param *param_2;

      virtual void
      SetUp( void ) {
        basic_element = stumpless_new_element( basic_name );

        element_with_params = stumpless_new_element( "element-with-params" );

        param_1 = stumpless_new_param( param_1_name, param_1_value );
        param_2 = stumpless_new_param( param_2_name, param_2_value );

        stumpless_add_param( element_with_params, param_1 );
        stumpless_add_param( element_with_params, param_2 );
      }

      virtual void
      TearDown( void ) {
        stumpless_destroy_element_and_contents( basic_element );
        stumpless_destroy_element_and_contents( element_with_params );
      }
  };

  TEST_F( ElementTest, AddNewParam ) {
    size_t original_param_count;
    const char *new_name = "new-param-name";
    const char *new_value = "new-param-value";
    const struct stumpless_element *result;
    const struct stumpless_param *param;

    original_param_count = stumpless_get_param_count( basic_element );

    result = stumpless_add_new_param( basic_element, new_name, new_value );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_element );

    EXPECT_EQ( stumpless_get_param_count( basic_element ),
               original_param_count + 1 );

    param = stumpless_get_param_by_index( basic_element, original_param_count );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( param != NULL );

    EXPECT_STREQ( stumpless_get_param_name( param ), new_name );
    EXPECT_STREQ( stumpless_get_param_value( param ), new_value );
  }

  TEST_F( ElementTest, AddNewParamNullName ) {
    size_t original_param_count;
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    original_param_count = stumpless_get_param_count( basic_element );

    result = stumpless_add_new_param( basic_element, NULL, "param-value" );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    EXPECT_EQ( stumpless_get_param_count( basic_element ),
               original_param_count );
  }

  TEST_F( ElementTest, AddNullParam ) {
    size_t original_param_count;
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    original_param_count = stumpless_get_param_count( basic_element );

    result = stumpless_add_param( basic_element, NULL );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    EXPECT_EQ( stumpless_get_param_count( basic_element ),
               original_param_count );
  }

  TEST_F( ElementTest, AddParam ) {
    size_t original_param_count;
    struct stumpless_param *param;
    const struct stumpless_element *result;
    const struct stumpless_param *last_param;

    original_param_count = stumpless_get_param_count( basic_element );

    param = stumpless_new_param( "test-param-name", "test-param-value" );
    ASSERT_NOT_NULL( param );

    result = stumpless_add_param( basic_element, param );
    EXPECT_EQ( basic_element, result );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    EXPECT_EQ( stumpless_get_param_count( basic_element ),
               original_param_count + 1 );

    last_param = stumpless_get_param_by_index( basic_element,
                                               original_param_count );
    EXPECT_EQ( last_param, param );
  }

  TEST_F( ElementTest, AddParamMemoryFailure ) {
    struct stumpless_element *result;
    struct stumpless_param *param;
    struct stumpless_error *error;
    void * (*set_realloc_result)(void *, size_t);

    // create the internal error struct
    stumpless_get_element_name( NULL );

    param = stumpless_new_param( "test-param-name", "test-param-value" );
    ASSERT_NOT_NULL( param );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_NOT_NULL( set_realloc_result );

    result = stumpless_add_param( basic_element, param );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_realloc( realloc );
  }

  TEST_F( ElementTest, AddTwoParams ) {
    size_t original_param_count;
    const struct stumpless_element *result;
    const char *param1_name = "test-param-name-1";
    const char *param2_name = "test-param-name-2";
    struct stumpless_param *param1, *param2;
    const struct stumpless_param *found;

    original_param_count = stumpless_get_param_count( basic_element );

    param1 = stumpless_new_param( param1_name, "test-param-value-1" );
    ASSERT_NOT_NULL( param1 );

    result = stumpless_add_param( basic_element, param1 );
    EXPECT_EQ( basic_element, result );
    EXPECT_NO_ERROR;

    param2 = stumpless_new_param( param2_name, "test-param-value-2" );
    ASSERT_NOT_NULL( param2 );

    result = stumpless_add_param( basic_element, param2 );
    EXPECT_EQ( result, basic_element );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_param_count( basic_element ),
               original_param_count + 2 );

    found = stumpless_get_param_by_name( basic_element, param1_name );
    EXPECT_TRUE( found != NULL );

    found = stumpless_get_param_by_name( basic_element, param2_name );
    EXPECT_TRUE( found != NULL );
  }

  TEST_F( ElementTest, CopyMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    // create the internal error struct
    stumpless_get_element_name( NULL );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_copy_element( basic_element );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ElementTest, CopyMallocFailureOnParamName ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    // create the internal error struct
    stumpless_get_element_name( NULL );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 8 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_copy_element( element_with_params );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ElementTest, CopyReallocFailure ) {
    struct stumpless_element *result;
    struct stumpless_error *error;
    void * (*set_realloc_result)(void *, size_t);

    // create the internal error struct
    stumpless_get_element_name( NULL );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_NOT_NULL( set_realloc_result );

    result = stumpless_copy_element( element_with_params );
    EXPECT_NO_ERROR;
    EXPECT_NE( result, element_with_params );

    stumpless_set_realloc( realloc );

    stumpless_destroy_element_and_contents( result );
  }

  TEST_F( ElementTest, CopyWithoutParams ) {
    const struct stumpless_element *result;

    result = stumpless_copy_element( element_with_params );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result != element_with_params );
    EXPECT_STREQ( stumpless_get_element_name( result ),
                  stumpless_get_element_name( element_with_params ) );
    EXPECT_EQ( stumpless_get_param_count( result ),
               stumpless_get_param_count( element_with_params ) );

    stumpless_destroy_element_and_contents( result );
  }

  TEST_F( ElementTest, CopyWithParams ) {
    const struct stumpless_element *result;

    result = stumpless_copy_element( basic_element );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result != basic_element );
    EXPECT_STREQ( stumpless_get_element_name( result ), basic_name );
    EXPECT_EQ( stumpless_get_param_count( result ), 0 );

    stumpless_destroy_element_and_contents( result );
  }

  TEST_F( ElementTest, GetName ) {
    EXPECT_STREQ( stumpless_get_element_name( basic_element ), basic_name );
    EXPECT_NO_ERROR;
  }

  TEST_F( ElementTest, GetParamByNameAndModify ) {
    struct stumpless_param *param;
    struct stumpless_param *set_result;

    param = stumpless_get_param_by_name( element_with_params, param_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( param, param_1 );

    set_result = stumpless_set_param_name( param, "my-special-new-name" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( set_result, param );
    EXPECT_STREQ( stumpless_get_param_name( param ), "my-special-new-name" );
  }

  TEST_F( ElementTest, GetParamByNameNotFound ) {
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    result = stumpless_get_param_by_name( element_with_params, "ugly-puppy" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_PARAM_NOT_FOUND );
  }

  TEST_F( ElementTest, GetParamCount ) {
    EXPECT_EQ( stumpless_get_param_count( basic_element ), 0 );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_param_count( element_with_params ), 2 );
    EXPECT_NO_ERROR;
  }

  TEST_F( ElementTest, GetParamByIndexOutOfBounds ) {
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    result = stumpless_get_param_by_index( element_with_params, 455 );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, 455 );
  }

  TEST_F( ElementTest, GetParamIndex ) {
    size_t result;

    result = stumpless_get_param_index( element_with_params, param_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 0 );

    result = stumpless_get_param_index( element_with_params, param_2_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 1 );
  }

  TEST_F( ElementTest, GetParamIndexNotFound ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_param_index( element_with_params, "not-there" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_PARAM_NOT_FOUND );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( ElementTest, GetParamIndexNullName ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_param_index( element_with_params, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( ElementTest, GetParamNameCount ) {
    size_t result;

    result = stumpless_get_param_name_count( basic_element, param_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 0 );

    result = stumpless_get_param_name_count( element_with_params,
                                             param_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 1 );

    stumpless_add_new_param( element_with_params, param_1_name, "new-val" );
    EXPECT_NO_ERROR;

    result = stumpless_get_param_name_count( element_with_params,
                                             param_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 2 );
  }

  TEST_F( ElementTest, GetParamNameCountNullName ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_param_name_count( basic_element, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( ElementTest, GetParamNameByIndex ) {
    const char *name;

    name = stumpless_get_param_name_by_index( element_with_params, 0 );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( name, param_1_name );

    name = stumpless_get_param_name_by_index( element_with_params, 1 );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( name, param_2_name );
  }

  TEST_F( ElementTest, GetParamNameByIndexOutOfBounds ) {
    const char *name;
    const struct stumpless_error *error;

    name = stumpless_get_param_name_by_index( element_with_params, 9001 );
    EXPECT_NULL( name );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, 9001 );
  }

  TEST_F( ElementTest, GetParamValueByIndex ) {
    const char *value;

    value = stumpless_get_param_value_by_index( element_with_params, 0 );
    EXPECT_STREQ( value, param_1_value );

    value = stumpless_get_param_value_by_index( element_with_params, 1 );
    EXPECT_STREQ( value, param_2_value );
  }

  TEST_F( ElementTest, GetParamValueByIndexNullElement ) {
    const char *value;
    const struct stumpless_error *error;

    value = stumpless_get_param_value_by_index( NULL, 0 );
    EXPECT_NULL( value );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    value = stumpless_get_param_value_by_index( NULL, 1 );
    EXPECT_NULL( value );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( ElementTest, GetParamValueByName ) {
    const char *value;

    value = stumpless_get_param_value_by_name( element_with_params,
                                               param_1_name );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( value, param_1_value );

    value = stumpless_get_param_value_by_name( element_with_params,
                                               param_2_name );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( value, param_2_value );
  }

  TEST_F( ElementTest, GetParamValueByNameNullElement ) {
    const char *value;
    const struct stumpless_error *error;

    value = stumpless_get_param_value_by_name( NULL, param_1_name );
    EXPECT_NULL( value );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    value = stumpless_get_param_value_by_name( NULL, param_2_name );
    EXPECT_NULL( value );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( ElementTest, GetParamValueByNameNullName ) {
    const char *value;
    const struct stumpless_error *error;

    value = stumpless_get_param_value_by_name( element_with_params, NULL );
    EXPECT_NULL( value );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( ElementTest, HasParam ) {
    bool result;

    result = stumpless_element_has_param( element_with_params, param_1_name );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result );

    result = stumpless_element_has_param( element_with_params, "not-there" );
    EXPECT_NO_ERROR;
    EXPECT_FALSE( result );
  }

  TEST_F( ElementTest, HasParamNullName ) {
    bool result;
    const struct stumpless_error *error;

    result = stumpless_element_has_param( element_with_params, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_FALSE( result );
  }

  TEST_F( ElementTest, SetNameMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *new_name = "this-wont-work";
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    // create the internal error struct
    stumpless_get_element_name( NULL );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_element_name( basic_element, new_name );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_STRNE( stumpless_get_element_name( basic_element ), new_name );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ElementTest, SetName ) {
    const char *new_name = "awesome-new-name";
    const struct stumpless_element *result;

    result = stumpless_set_element_name( basic_element, new_name );
    EXPECT_EQ( result, basic_element );

    EXPECT_STRNE( stumpless_get_element_name( basic_element ), basic_name );
    EXPECT_STREQ( stumpless_get_element_name( basic_element ), new_name );
  }

  TEST_F( ElementTest, SetNameToNull ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_element_name( basic_element, NULL );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( ElementTest, SetParam ) {
    struct stumpless_param *new_param;
    const struct stumpless_element *result;

    new_param = stumpless_new_param( "new-param", "new-value" );
    ASSERT_NOT_NULL( new_param );

    result = stumpless_set_param( element_with_params, 1, new_param );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element_with_params );

    EXPECT_EQ( stumpless_get_param_by_index( element_with_params, 1 ),
               new_param );
  }

  TEST_F( ElementTest, SetParamNullElement ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param( NULL, 1, param_1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamNullParam ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param( element_with_params, 1, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamOutOfBounds ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param( element_with_params, 455, param_2 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, 455 );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamValueByIndex ) {
    const char *new_value = "my-new-value-by-index";
    const struct stumpless_element *result;

    result = stumpless_set_param_value_by_index( element_with_params, 1, new_value );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element_with_params );

    EXPECT_STREQ( stumpless_get_param_value_by_index( element_with_params, 1 ),
                  new_value );
    EXPECT_STREQ( stumpless_get_param_value( param_2 ), new_value );
  }

  TEST_F( ElementTest, SetParamValueByIndexNullElement ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param_value_by_index( NULL, 1, "val" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamValueByIndexNullValue ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param_value_by_index( element_with_params, 1, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamValueByIndexOutOfBounds ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param_value_by_index( element_with_params,
                                                 455,
                                                 "new-value" );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, 455 );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamValueByName ) {
    const char *new_value = "my-new-value-by-name";
    const struct stumpless_element *result;

    result = stumpless_set_param_value_by_name( element_with_params,
                                                param_1_name,
                                                new_value );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element_with_params );

    EXPECT_STREQ( stumpless_get_param_value_by_index( element_with_params, 0 ),
                  new_value );
    EXPECT_STREQ( stumpless_get_param_value( param_1 ), new_value );
  }

  TEST_F( ElementTest, SetParamValueByNameNullElement ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param_value_by_name( NULL, param_1_name, "val" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamValueByNameNullName ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param_value_by_name( element_with_params,
                                                NULL,
                                                "val" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ElementTest, SetParamValueByNameNullValue ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_param_value_by_name( element_with_params,
                                                param_1_name,
                                                NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  /* non-fixture tests */

  TEST( AddParamTest, NullElement ) {
    struct stumpless_param *param;
    struct stumpless_element *result;
    struct stumpless_error *error;

    param = stumpless_new_param( "test-name", "test-value" );
    ASSERT_NOT_NULL( param );

    result = stumpless_add_param( NULL, param );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

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
    ASSERT_NOT_NULL( element );

    param = stumpless_new_param( param_name, "test-param-value" );
    ASSERT_NOT_NULL( param );

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
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( GetParamByIndex, NullElement ) {
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    result = stumpless_get_param_by_index( NULL, 2 );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( GetParamCount, NullElement ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_param_count( NULL );
    EXPECT_EQ( result, 0 );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( GetParamIndex, NullElement ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_param_index( NULL, "irrelevant-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
  }

  TEST( GetParamNameCount, NullElement ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_param_name_count( NULL, "param-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
  }

  TEST( HasParam, NullElement ) {
    bool result;
    const struct stumpless_error *error;

    result = stumpless_element_has_param( NULL, "irrelevant" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_FALSE( result );
  }

  TEST( NewElementTest, MemoryFailure ) {
    struct stumpless_element *element;
    struct stumpless_error *error;
    void *(*result)(size_t);

    // create the internal error struct
    stumpless_get_element_name( NULL );

    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_NOT_NULL( result );

    element = stumpless_new_element( "memory-failure" );
    EXPECT_EQ( NULL, element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
  }

  TEST( NewElementTest, MemoryFailureOnName ) {
    const char *element_name = "this-name-is-awesome";
    struct stumpless_element *element;
    struct stumpless_error *error;
    void *(*result)(size_t);

    // create the internal error struct
    stumpless_get_element_name( NULL );

    result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 21 ) );
    ASSERT_NOT_NULL( result );

    element = stumpless_new_element( element_name );
    EXPECT_EQ( NULL, element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    stumpless_set_malloc( malloc );
  }

  TEST( NewElementTest, NullName ) {
    struct stumpless_element *element;
    struct stumpless_error *error;

    element = stumpless_new_element( NULL );
    EXPECT_NULL( element );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SetElementNameTest, NullElement ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_element_name( NULL, "awesome-new-name" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

}
