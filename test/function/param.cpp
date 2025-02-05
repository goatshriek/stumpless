// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2024 Joel E. Anderson
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

#include <string>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"

namespace {

  class ParamTest : public::testing::Test {
    protected:
      struct stumpless_param basic_param;
      const char *basic_name = "basic-name";
      const char *basic_value = "basic-value";

      virtual void
      SetUp( void ) {
        stumpless_load_param( &basic_param, basic_name, basic_value );
      }

      virtual void
      TearDown( void ) {
        stumpless_unload_param( &basic_param );

        stumpless_free_all(  );
      }
  };

  TEST_F( ParamTest, Copy ) {
    const struct stumpless_param *result;
    const char *original_name;
    const char *result_name;
    const char *original_value;
    const char *result_value;

    result = stumpless_copy_param( &basic_param );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result != &basic_param );

    original_name = stumpless_get_param_name( &basic_param );
    result_name = stumpless_get_param_name( result );
    EXPECT_STREQ( result_name, original_name );
    EXPECT_TRUE( result_name != original_name );

    free( ( void * ) original_name );
    free( ( void * ) result_name );

    original_value = stumpless_get_param_value( &basic_param );
    result_value = stumpless_get_param_value( result );
    EXPECT_STREQ( result_value, original_value );
    EXPECT_TRUE( result_value != original_value );

    free( ( void * ) original_value );
    free( ( void * ) result_value );

    stumpless_destroy_param( result );
  }

  TEST_F( ParamTest, GetName ) {
    const char *name = stumpless_get_param_name( &basic_param );

    EXPECT_STREQ( name, basic_name );
    EXPECT_NO_ERROR;

    free( ( void * ) name );
  }

  TEST_F( ParamTest, GetNameMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *name;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    name = stumpless_get_param_name( &basic_param );
    EXPECT_NULL( name );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ParamTest, GetValue ) {
    const char *value;

    value = stumpless_get_param_value( &basic_param );

    EXPECT_STREQ( value, basic_value );
    EXPECT_NO_ERROR;

    free( ( void * ) value );
  }

  TEST_F( ParamTest, GetValueMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *value;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    value = stumpless_get_param_value( &basic_param );
    EXPECT_NULL( value );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ParamTest, SetNameToNull ) {
    const struct stumpless_param *result;

    result = stumpless_set_param_name( &basic_param, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( ParamTest, SetValueMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *new_value = "this-wont-work";
    const struct stumpless_param *result;
    const char *after_value;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_param_value( &basic_param, new_value );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    after_value = stumpless_get_param_value( &basic_param );
    EXPECT_STRNE( stumpless_get_param_value( &basic_param ), new_value );
    free( ( void * ) after_value );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ParamTest, SetValueToNull ) {
    const struct stumpless_param *result;

    result = stumpless_set_param_value( &basic_param, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }


  TEST_F( ParamTest, GetParamToString) {
      const char *format;
    
      format = stumpless_param_to_string( &basic_param );
      ASSERT_NOT_NULL( format );

      EXPECT_STREQ( format, "basic-name=\"basic-value\"" );
      EXPECT_NO_ERROR;

      free( ( void * ) format );
  }

  TEST_F( ParamTest, ParamToStringMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *result;
    
    
    // create the internal error struct
    stumpless_get_param_name( NULL );

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_param_to_string( &basic_param );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( ParamTest, GetParamIntoString) {
    const size_t max_size = 100;
    size_t param_size;
    char *buffer = (char*)malloc(max_size);

    param_size = stumpless_param_into_string( &basic_param, buffer, max_size );
    ASSERT_EQ( param_size, (&basic_param)->name_length + (&basic_param)->value_length + 4 );
    EXPECT_STREQ( buffer, "basic-name=\"basic-value\"" );
    EXPECT_NO_ERROR;
    
    free( buffer );
  }

  TEST_F( ParamTest, ParamIntoStringNullBuffer) {
    const size_t max_size = 100;
    size_t param_size;

    param_size = stumpless_param_into_string( &basic_param, NULL, max_size );
    ASSERT_EQ( param_size, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( ParamTest, ParamIntoStringInsufficientBuffer) {
    const size_t max_size = 10;
    size_t param_size;
    char *buffer = (char*)malloc(max_size);

    param_size = stumpless_param_into_string( &basic_param, buffer, max_size );
    ASSERT_EQ( param_size, (&basic_param)->name_length + (&basic_param)->value_length + 4 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_SMALL );

    free( buffer );
  }

  /* non-fixture tests */

  TEST( CopyParamTest, NullParam ) {
    const struct stumpless_param *result;

    result = stumpless_copy_param( NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( DestroyParamTest, NullParam ) {
    stumpless_destroy_param( NULL );

    stumpless_free_all(  );
  }

  TEST( GetParamNameTest, NullParam ) {
    const char *result;

    result = stumpless_get_param_name( NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( GetParamValueTest, NullParam ) {
    const char *result;

    result = stumpless_get_param_value( NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( LoadParamTest, InvalidName ) {
    struct stumpless_param param;
    const struct stumpless_param *result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_load_param( &param, invalid_name.c_str(), "test-value" );
      EXPECT_NULL( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
    stumpless_free_all(  );
  }

  TEST( LoadParamTest, LoadAndUnload ) {
    struct stumpless_param param;
    struct stumpless_param *result;

    result = stumpless_load_param( &param, "name", "value" );
    EXPECT_NOT_NULL( result );

    stumpless_unload_param( &param );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, MemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_param *param;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    param = stumpless_new_param( "name", "value" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, MemoryFailureOnValue ) {
    void * (*set_malloc_result)(size_t);
    const char *param_value = "this-value-is-awesome";
    const struct stumpless_param *param;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 22 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    param = stumpless_new_param( "name", param_value );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, New ){
    struct stumpless_param *param;
    const char *name = "test-param-name";
    const char *value = "test-param-value";

    size_t name_length = strlen( name );
    size_t value_length = strlen( value );

    param = stumpless_new_param( name, value );
    ASSERT_NOT_NULL( param );
    EXPECT_NO_ERROR;

    ASSERT_EQ( name_length, param->name_length );
    ASSERT_NOT_NULL( param->name );
    ASSERT_EQ( 0, memcmp( param->name, name, name_length ) );

    ASSERT_EQ( value_length, param->value_length );
    ASSERT_NOT_NULL( param->value );
    ASSERT_EQ( 0, memcmp( param->value, value, value_length ) );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, NullName ) {
    struct stumpless_param *param;

    param = stumpless_new_param( NULL, "test-value" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, InvalidName ) {
    struct stumpless_param *param;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      param = stumpless_new_param( invalid_name.c_str(), "test-value" );
      EXPECT_NULL( param );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
    stumpless_free_all(  );
  }

  TEST( NewParamTest, InvalidNameLength ) {
    struct stumpless_param *param;

    param = stumpless_new_param( "very-long-name-abcdefghijklmnopqrstuvwxyz", "test-value" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, NullValue ) {
    struct stumpless_param *param;

    param = stumpless_new_param( "test-name", NULL );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, ValidUTF8 ) {
    const struct stumpless_param *param;
    const char *name = "test-param-name";
    // U+2162 U+2264 U+0035(<Roman Numeral Three><Less-Than or Equal To>5)
    const char *value = "\xe2\x85\xa2\xe2\x89\xa4\x35";
    const size_t name_length = strlen( name );
    const size_t value_length = strlen( value );

    param = stumpless_new_param( name, value );
    ASSERT_NOT_NULL( param );
    EXPECT_NO_ERROR;

    ASSERT_EQ( name_length, param->name_length );
    ASSERT_NOT_NULL( param->name );
    ASSERT_EQ( 0, memcmp( param->name, name, name_length ) );

    ASSERT_EQ( value_length, param->value_length );
    ASSERT_NOT_NULL( param->value );
    ASSERT_EQ( 0, memcmp( param->value, value, value_length ) );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( NewParamTest, InvalidUTF8 ) {
    struct stumpless_param *param;
    const char *name = "test-param-name";

    // invalid lead byte
    param = stumpless_new_param( name, "\x80" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    // continuation byte should start with 0b10
    param = stumpless_new_param( name, "\xc0\xc0" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    // U+0000 should be encoded into \x00, not \xc0\x80
    param = stumpless_new_param( name, "\xc0\x80" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( SetName, Basic ) {
    struct stumpless_param *param;
    const char *original_name = "first-name";
    const char *retrieved_name;
    const char *new_name = "second-name";
    struct stumpless_param *result;

    param = stumpless_new_param( original_name, "my-value" );
    ASSERT_NOT_NULL( param );
    retrieved_name = stumpless_get_param_name( param );
    EXPECT_STREQ( retrieved_name, original_name );
    free( ( void * ) retrieved_name );

    result = stumpless_set_param_name( param, new_name );
    EXPECT_TRUE( result == param );
    EXPECT_NO_ERROR;

    retrieved_name = stumpless_get_param_name( param );
    EXPECT_STREQ( retrieved_name, new_name );
    free( ( void * ) retrieved_name );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( SetName, NullParam ) {
    const struct stumpless_param *result;

    result = stumpless_set_param_name( NULL, "new-name" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( SetName, InvalidName) {
    struct stumpless_param *param;
    struct stumpless_param *result;

    param = stumpless_new_param( "param", "my-value" );
    ASSERT_NOT_NULL( param );

    result = stumpless_set_param_name( param, "par=am");
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    result = stumpless_set_param_name( param, "par]m");
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    result = stumpless_set_param_name( param, "param\"");
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    
    stumpless_destroy_param( param );
    stumpless_free_all(  );
  }

  TEST( SetName, InvalidNameLength ) {
    struct stumpless_param *param;
    struct stumpless_param *result;

    param = stumpless_new_param( "param", "test-value" );

    result = stumpless_set_param_name( param, "very-long-name-abcdefghijklmnopqrstuvwxyz" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );

    stumpless_destroy_param( param );
    stumpless_free_all(  );
  }

  TEST( SetValue, Basic ) {
    struct stumpless_param *param;
    const char *original_value = "first-value";
    const char *retrieved_value;
    const char *new_value = "second-value";
    struct stumpless_param *result;

    param = stumpless_new_param( "my-name", original_value );
    ASSERT_NOT_NULL( param );

    retrieved_value = stumpless_get_param_value( param );
    EXPECT_STREQ( retrieved_value, original_value );
    free( ( void * ) retrieved_value );

    result = stumpless_set_param_value( param, new_value );
    EXPECT_TRUE( result == param );
    EXPECT_NO_ERROR;

    retrieved_value = stumpless_get_param_value( param );
    EXPECT_STREQ( retrieved_value, new_value );
    free( ( void * ) retrieved_value );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( SetValue, NullParam ) {
    const struct stumpless_param *result;

    result = stumpless_set_param_value( NULL, "new-value" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all(  );
  }

  TEST( SetValue, ValidUTF8 ) {
    struct stumpless_param *param;
    // U+2162 U+2264 U+0035(<Roman Numeral Three><Less-Than or Equal To>5)
    const char *original_value = "\xe2\x85\xa2\xe2\x89\xa4\x35";
    const char *retrieved_value;
    // BOM U+0041 U+0391 U+1d2c U+10ffff(<BOM>A<Alpha><Modifier Letter A><noncharacter>)
    const char *new_value = "\xef\xbb\xbf\x41\xce\x91\xe1\xb4\xac\xf4\x8f\xbf\xbf";
    const struct stumpless_param *result;

    param = stumpless_new_param( "my-name", original_value );
    ASSERT_NOT_NULL( param );

    retrieved_value = stumpless_get_param_value( param );
    EXPECT_STREQ( retrieved_value, original_value );
    free( ( void * ) retrieved_value );

    result = stumpless_set_param_value( param, new_value );
    EXPECT_TRUE( result == param );
    EXPECT_NO_ERROR;

    retrieved_value = stumpless_get_param_value( param );
    EXPECT_STREQ( retrieved_value, new_value );
    free( ( void * ) retrieved_value );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( SetValue, InvalidUTF8 ) {
    struct stumpless_param *param;
    const char *original_value = "first-value";
    const char *retrieved_value;
    struct stumpless_param *result;

    param = stumpless_new_param( "my-name", original_value );
    ASSERT_NOT_NULL( param );

    retrieved_value = stumpless_get_param_value( param );
    EXPECT_STREQ( retrieved_value, original_value );
    free( ( void * ) retrieved_value );

    // invalid lead byte
    result = stumpless_set_param_value( param, "\x80" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    // continuation byte should start with 0b10
    result = stumpless_set_param_value( param, "\xc0\xc0" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    // U+0000 should be encoded into \x00, not \xc0\x80
    result = stumpless_set_param_value( param, "\xc0\x80" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( ParamToStringTest, NullParam) {
    const char *result;

    result = stumpless_param_to_string( NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( ParamIntoStringTest, NullParam) {
    const size_t max_size = 100;
    size_t param_size;
    char *buffer = (char*)malloc(max_size);

    param_size = stumpless_param_into_string( NULL, buffer, max_size );
    ASSERT_EQ( param_size, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    free( buffer );
  }

  TEST( UnloadParamTest, NullParam ) {
    stumpless_unload_param( NULL );

    stumpless_free_all(  );
  }

  TEST( ParamFromStringTest, MallocFail ) {
    void * ( *set_malloc_result )( size_t );
    const struct stumpless_param *param;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    param = stumpless_new_param_from_string( "param-name=\"param-value\"" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST( ParamFromStringTest, MallocFailOnValue ) {
    void * ( *set_malloc_result )( size_t );
    const struct stumpless_param *param;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 12 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    param = stumpless_new_param_from_string( "param-name=\"param-value\"" );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST( ParamFromStringTest, New ) {
    struct stumpless_param *param;
    const char *param_string = "test-param-name=\"test-param-value\"";

    size_t name_length = strlen("test-param-name");
    size_t value_length = strlen("test-param-value");

    param = stumpless_new_param_from_string( param_string );
    ASSERT_NOT_NULL( param );
    EXPECT_NO_ERROR;

    ASSERT_EQ( name_length, param->name_length );
    ASSERT_NOT_NULL( param->name );
    ASSERT_EQ( 0, memcmp( param->name, "test-param-name", name_length ) );

    ASSERT_EQ( value_length, param->value_length );
    ASSERT_NOT_NULL( param->value );
    ASSERT_EQ( 0, memcmp( param->value, "test-param-value", value_length ) );

    stumpless_destroy_param( param );

    stumpless_free_all();
  }

  TEST( ParamFromStringTest, NullName ) {
    struct stumpless_param *param;
    
    param = stumpless_new_param_from_string( NULL );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_free_all();
  }

  TEST( ParamFromStringTest, InvalidFormat ) {
    std::vector<const char *> invalid_names = {
      "param-na=me=\"param-value\"",
      "param-name\"param-value\"",
      "param]-name=\"param-value\"",
      "p\"aram-name=\"param-value\"",
      "param-name==\"param-value\"",
      "param-name=\"param-value",
      "param-name=\""
    };
    struct stumpless_param *param;

    for( auto it = begin( invalid_names ); it != end( invalid_names ); ++it ){
      param = stumpless_new_param_from_string( *it );
      EXPECT_NULL( param );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_PARAM_STRING );
    }

    stumpless_free_all();
  }

  TEST( ParamFromStringTest, NameTooLong ) {
    const char *str = "param-name-that-is-entirely-too-long=\"param-value\"";
    struct stumpless_param *param;

    param = stumpless_new_param_from_string( str );
    EXPECT_NULL( param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );

    stumpless_free_all();
  }
}
