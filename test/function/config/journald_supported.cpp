// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"

namespace {

  TEST( GetElementNamer, Default ) {
    const struct stumpless_element *element = stumpless_new_element( "test" );
    stumpless_element_namer_func_t namer;
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    namer = stumpless_get_element_journald_namer( element );
    EXPECT_TRUE( namer == stumpless_flatten_element_name );
    EXPECT_NO_ERROR;

    stumpless_destroy_element_and_contents( element );
    stumpless_free_all(  );
  }

  TEST( GetElementNamer, NullElement ) {
    stumpless_element_namer_func_t result;
    const struct stumpless_error *error;

    result = stumpless_get_element_journald_namer( NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( GetParamNamer, Default ) {
    const struct stumpless_param *param = stumpless_new_param( "test", "val" );
    stumpless_param_namer_func_t namer;
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    namer = stumpless_get_param_journald_namer( param );
    EXPECT_TRUE( namer == stumpless_flatten_param_name );
    EXPECT_NO_ERROR;

    stumpless_destroy_param( param );
    stumpless_free_all(  );
  }

  TEST( GetParamNamer, NullParam ) {
    stumpless_param_namer_func_t result;
    const struct stumpless_error *error;

    result = stumpless_get_param_journald_namer( NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( SetElementNamer, Basic ) {
    struct stumpless_element *element = stumpless_new_element( "test" );
    stumpless_element_namer_func_t namer;
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    namer = stumpless_flatten_element_name;
    result = stumpless_set_element_journald_namer( element, namer );
    EXPECT_TRUE( result == element );
    EXPECT_NO_ERROR;

    stumpless_destroy_element_and_contents( element );
    stumpless_free_all(  );
  }

  TEST( SetElementNamer, NullElement ) {
    stumpless_element_namer_func_t namer;
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    namer = stumpless_flatten_element_name;

    result = stumpless_set_element_journald_namer( NULL, namer );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( SetElementNamer, NullNamer ) {
    struct stumpless_element *element = stumpless_new_element( "test" );
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_set_element_journald_namer( element, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_element_and_contents( element );
    stumpless_free_all(  );
  }

  TEST( SetParamNamer, Basic ) {
    struct stumpless_param *param = stumpless_new_param( "test", "val" );
    stumpless_param_namer_func_t namer;
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    namer = stumpless_flatten_param_name;
    result = stumpless_set_param_journald_namer( param, namer );
    EXPECT_TRUE( result == param );
    EXPECT_NO_ERROR;

    stumpless_destroy_param( param );
    stumpless_free_all(  );
  }

  TEST( SetParamNamer, NullParam ) {
    stumpless_param_namer_func_t namer;
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    namer = stumpless_flatten_param_name;

    result = stumpless_set_param_journald_namer( NULL, namer );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( SetParamNamer, NullNamer ) {
    struct stumpless_param *param = stumpless_new_param( "test", "val" );
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    result = stumpless_set_param_journald_namer( param, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_param( param );
    stumpless_free_all(  );
  }

}
