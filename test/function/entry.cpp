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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"

using::testing::HasSubstr;

static
void
confirm_entry_contents( const struct stumpless_entry *entry,
                        const char *app_name,
                        const char *msgid,
                        const char *message ) {
    size_t app_name_length = strlen( app_name );
    size_t msgid_length = strlen( msgid );
    size_t message_length = strlen( message );

    EXPECT_EQ( app_name_length, entry->app_name_length );
    EXPECT_EQ( 0, memcmp( entry->app_name, app_name, app_name_length ) );

    EXPECT_EQ( msgid_length, entry->msgid_length );
    EXPECT_EQ( 0, memcmp( entry->msgid, msgid, msgid_length ) );

    EXPECT_EQ( message_length, entry->message_length );
    EXPECT_NOT_NULL( entry->message );
    EXPECT_EQ( 0, memcmp( entry->message, message, message_length ) );
}

namespace {

  class EntryTest : public::testing::Test {
    protected:
      const char *basic_app_name = "basic-app-name";
      const char *basic_msgid = "basic-msgid";
      const char *basic_message = "basic message";
      struct stumpless_entry *basic_entry = NULL;
      const char *element_1_name = "basic-element";
      struct stumpless_element *element_1 = NULL;
      const char *element_2_name = "basic-element-2";
      struct stumpless_element *element_2 = NULL;
      const char *param_1_1_name = "basic-param";
      const char *param_1_1_value = "basic-value";
      struct stumpless_param *param_1_1 = NULL;
      struct stumpless_entry *nil_entry = NULL;

      virtual void
      SetUp( void ) {
        basic_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                               STUMPLESS_SEVERITY_INFO,
                                               basic_app_name,
                                               basic_msgid,
                                               basic_message );

        element_1 = stumpless_new_element( element_1_name );
        stumpless_add_element( basic_entry, element_1 );

        param_1_1 = stumpless_new_param( param_1_1_name, param_1_1_value );
        stumpless_add_param( element_1, param_1_1 );

        element_2 = stumpless_new_element( element_2_name );
        stumpless_add_element( basic_entry, element_2 );

        nil_entry = create_nil_entry();

        
      }

      virtual void
      TearDown( void ){
        stumpless_destroy_entry_and_contents( basic_entry );
        stumpless_destroy_entry_only( nil_entry );
        stumpless_free_all(  );
      }
  };

  TEST_F( EntryTest, EntryToStringMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_entry_to_string(basic_entry);
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F(EntryTest, OutputFormatCheck) {
    char *result = stumpless_entry_to_string(basic_entry);
    ASSERT_NE(result, nullptr);

    const char *expected_output =
      "prival=\"14\",app_name=\"basic-app-name\",hostname=\"\","
      "message_id=\"basic-msgid\",process_id=\"\","
      "message=\"basic message\","
      "basic-element=[basic-param=\"basic-value\"],"
      "basic-element-2";
    EXPECT_STREQ(result, expected_output);
    size_t len = strlen(result);
    EXPECT_NE(result[len - 1], ',');
    free(result);
  }

  TEST_F(EntryTest, LastCommaCheck) {
    char *result = stumpless_entry_to_string(basic_entry);
    ASSERT_NE(result, nullptr);

    size_t len = strlen(result);
    EXPECT_NE(result[len - 1], ',');

    free(result);
  }

  TEST_F(EntryTest, NullEntry) {
    char *result = stumpless_entry_to_string(NULL);
    EXPECT_EQ(result, nullptr);
    free(result);
  }

  TEST_F(EntryTest, EmptyHostnameAndProcid) {
    char *result = stumpless_entry_to_string(basic_entry);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(strstr(result, "hostname=\"\"") != nullptr);
    EXPECT_TRUE(strstr(result, "process_id=\"\"") != nullptr);
    EXPECT_TRUE(strstr(result, "message_id=\"basic-msgid\"") != nullptr);
    free(result);
  }

  TEST_F(EntryTest, NoneOfElementCheck) {
    struct stumpless_entry *test_entry = create_empty_entry();
    char *result = stumpless_entry_to_string(test_entry);
    ASSERT_NE(result, nullptr);

    const char *expected_output =
      "prival=\"14\",app_name=\"fixture-app-name\",hostname=\"\""
      ",message_id=\"fixture-msgid\",process_id=\"\",message=\"fixture message\"";

    EXPECT_STREQ(result, expected_output);

    stumpless_destroy_entry_and_contents(test_entry);
    free(result);
  }

  TEST_F( EntryTest, AddElement ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element;

    element = stumpless_new_element( "test-new-element" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element );

    entry = stumpless_add_element( basic_entry, element );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    EXPECT_EQ( basic_entry, entry );
  }

  TEST_F( EntryTest, AddDuplicateElement ) {
    struct stumpless_element *duplicate_element;
    size_t original_element_count;
    const struct stumpless_entry *result;

    original_element_count = basic_entry->element_count;

    duplicate_element = stumpless_new_element( element_1_name );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( duplicate_element );

    result = stumpless_add_element( basic_entry, duplicate_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_DUPLICATE_ELEMENT );
    EXPECT_NULL( result );
    EXPECT_EQ( basic_entry->element_count, original_element_count );

    stumpless_destroy_element_only( duplicate_element );
  }

  TEST_F( EntryTest, AddElementMemoryFailure ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    void * (*set_realloc_result)(void *, size_t);

    element = stumpless_new_element( "test-memory-failure" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_NOT_NULL( set_realloc_result );

    entry = stumpless_add_element( basic_entry, element );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_realloc_result = stumpless_set_realloc( realloc );
    EXPECT_TRUE( set_realloc_result == realloc );

    stumpless_destroy_element_and_contents( element );
  }

  TEST_F( EntryTest, AddNewElement ) {
    size_t original_element_count;
    const struct stumpless_entry *result;

    original_element_count = basic_entry->element_count;

    result = stumpless_add_new_element( basic_entry, "new-name" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    EXPECT_EQ( basic_entry->element_count, original_element_count + 1 );
  }

  TEST_F( EntryTest, AddNewElementNullName ) {
    const struct stumpless_entry *result;

    result = stumpless_add_new_element( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, InvalidNameLength ) {
    const struct stumpless_entry *result;

    result = stumpless_add_new_param_to_entry( basic_entry,
                                               "checking-valid-elemant-name-length",
                                               "new-param-name",
                                               "new-param-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, AddNewParam ) {
    const struct stumpless_entry *result;
    const struct stumpless_param *new_param;

    result = stumpless_add_new_param_to_entry( basic_entry,
                                               element_1_name,
                                               "new-param-name",
                                               "new-param-value" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    new_param = stumpless_get_param_by_name( element_1, "new-param-name" );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( new_param );
  }

  TEST_F( EntryTest, AddNewParamAndNewElement ) {
    const struct stumpless_entry *result;
    struct stumpless_element *new_element;
    const struct stumpless_param *new_param;

    result = stumpless_add_new_param_to_entry( basic_entry,
                                               "new-element-name",
                                               "new-param-name",
                                               "new-param-value" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    new_element = stumpless_get_element_by_name( basic_entry, "new-element-name" );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( new_element );
    EXPECT_EQ( stumpless_get_param_count( new_element ), 1 );

    new_param = stumpless_get_param_by_name( new_element, "new-param-name" );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( new_param );
  }

  TEST_F( EntryTest, AddNewParamAndNewElementMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_add_new_param_to_entry( basic_entry,
                                               "new-element-name",
                                               "new-param-name",
                                               "new-param-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, AddNewParamMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_add_new_param_to_entry( basic_entry,
                                               element_1_name,
                                               "new-param-name",
                                               "new-param-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, AddNewParamNullElementName ) {
    const struct stumpless_entry *result;

    result = stumpless_add_new_param_to_entry( basic_entry,
                                               NULL,
                                               "new-param-name",
                                               "new-param-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, AddNullElement ) {
    const struct stumpless_entry *result;

    result = stumpless_add_element( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    ASSERT_NULL( result );
  }

  TEST_F( EntryTest, AddTwoElements ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element1;
    struct stumpless_element *element2;

    element1 = stumpless_new_element( "test-new-element-1" );
    ASSERT_NOT_NULL( element1 );
    EXPECT_NO_ERROR;

    entry = stumpless_add_element( basic_entry, element1 );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );
    EXPECT_EQ( basic_entry, entry );

    element2 = stumpless_new_element( "test-new-element-2" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element2 );

    entry = stumpless_add_element( basic_entry, element2 );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );
    EXPECT_EQ( basic_entry, entry );
  }

  TEST_F( EntryTest, Copy ) {
    const struct stumpless_entry *result;

    result = stumpless_copy_entry( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_NE( result, basic_entry );

    stumpless_destroy_entry_and_contents( result );
  }

  TEST_F( EntryTest, CopyMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_copy_entry( basic_entry );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, CopyMallocFailureOnElementArray ) {
    void * ( *fail )( size_t );
    void * ( *set_malloc_result )( size_t );
    const struct stumpless_entry *result;

    fail = MALLOC_FAIL_ON_SIZE( sizeof( struct stumpless_element * ) * 2 );
    set_malloc_result = stumpless_set_malloc( fail );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_copy_entry( basic_entry );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, CopyMallocFailureOnElementName ) {
    void * ( *fail )( size_t );
    void * ( *set_malloc_result )( size_t );
    const struct stumpless_entry *result;

    fail = MALLOC_FAIL_ON_SIZE( 12 );
    set_malloc_result = stumpless_set_malloc( fail );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_copy_entry( basic_entry );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }


  TEST_F( EntryTest, CopyReallocFailure ) {
    const struct stumpless_entry *result;
    void * (*set_realloc_result)(void *, size_t);

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_NOT_NULL( set_realloc_result );

    result = stumpless_copy_entry( basic_entry );

    if( !result ) {
      EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    } else {
      EXPECT_NO_ERROR;
      EXPECT_NE( result, basic_entry );
      stumpless_destroy_entry_and_contents( result );
    }

    stumpless_set_realloc( realloc );

  }

  TEST_F( EntryTest, GetAppName ) {
    const char *result;

    result = stumpless_get_entry_app_name( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, basic_app_name );
    EXPECT_NE( result, basic_app_name );

    free( ( void * ) result );
  }

  TEST_F( EntryTest, GetAppNameMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_get_entry_app_name( basic_entry );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, GetElementByIndex ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_index( basic_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element_1 );
  }

  TEST_F( EntryTest, GetElementByIndexOutOfBounds ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_index( basic_entry, 534 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 534 );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetElementByName ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_name( basic_entry, element_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element_1 );
  }

  TEST_F( EntryTest, GetElementByNameNotFound ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_name( basic_entry, "not-found" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ELEMENT_NOT_FOUND );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetElementByNameNullName ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_name( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetElementCount ) {
    size_t result;

    result = stumpless_get_element_count( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 2 );
  }

  TEST_F( EntryTest, GetElementIndex ) {
    size_t result;

    result = stumpless_get_element_index( basic_entry, element_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 0 );
  }

  TEST_F( EntryTest, GetElementIndexNotFound ) {
    size_t result;

    result = stumpless_get_element_index( basic_entry, "not-found" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ELEMENT_NOT_FOUND );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( EntryTest, GetElementIndexNullName ) {
    size_t result;

    result = stumpless_get_element_index( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( EntryTest, GetMessage ) {
    const char *result;

    result = stumpless_get_entry_message( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, basic_message );

    free( ( void * ) result );
  }

  TEST_F( EntryTest, GetMessageMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_get_entry_message( basic_entry );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, GetMsgid ) {
    const char *result;

    result = stumpless_get_entry_msgid( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, basic_msgid );
    EXPECT_NE( result, basic_msgid );

    free( ( void * ) result );
  }

  TEST_F( EntryTest, GetMsgidMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_get_entry_msgid( basic_entry );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, GetNullMessage ) {
    const char *message;

    message = stumpless_get_entry_message( nil_entry );
    EXPECT_NULL( message );
    EXPECT_NO_ERROR;
  }

  TEST_F( EntryTest, GetParamByIndex ) {
    const struct stumpless_param *result;

    result = stumpless_get_entry_param_by_index( basic_entry, 0, 0 );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, param_1_1 );
  }

  TEST_F( EntryTest, GetParamByIndexElementIndexOutOfBounds ) {
    const struct stumpless_param *result;

    result = stumpless_get_entry_param_by_index( basic_entry, 766, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 766 );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamByName ) {
    const struct stumpless_param *result;

    result = stumpless_get_entry_param_by_name( basic_entry,
                                                element_1_name,
                                                param_1_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, param_1_1 );
  }

  TEST_F( EntryTest, GetParamByNameNotFound ) {
    const struct stumpless_param *result;

    result = stumpless_get_entry_param_by_name( basic_entry,
                                                "not-present",
                                                param_1_1_name );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ELEMENT_NOT_FOUND );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamByNameNullElementName ) {
    struct stumpless_param *result;

    result = stumpless_get_entry_param_by_name( basic_entry, NULL, "p-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamByNameNullParamName ) {
    struct stumpless_param *result;

    result = stumpless_get_entry_param_by_name( basic_entry, "e-name", NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamByNameInvalidParamName ) {
    const struct stumpless_param *result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_get_entry_param_by_name( basic_entry, "e-name", invalid_name.c_str() );
      EXPECT_NULL( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
  }

  TEST_F( EntryTest, GetParamByNameInvalidElementName ) {
    const struct stumpless_param *result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_get_entry_param_by_name( basic_entry, invalid_name.c_str(), "param" );
      EXPECT_NULL( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
  }

  TEST_F( EntryTest, GetParamValueByIndex ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_index( basic_entry, 0, 0 );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, param_1_1_value );

    free( ( void * ) result );
  }

  TEST_F( EntryTest, GetParamValueByIndexElementIndexOutOfBounds ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_index( basic_entry, 455, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 455 );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamValueByName ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_name( basic_entry,
                                                      element_1_name,
                                                      param_1_1_name );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, param_1_1_value );

    free( ( void * ) result );
  }

  TEST_F( EntryTest, GetParamValueByNameNotFound ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_name( basic_entry,
                                                      "not-present",
                                                      param_1_1_name );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ELEMENT_NOT_FOUND );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamValueByNameNullElementName ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_name( basic_entry,
                                                      NULL,
                                                      "p-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamValueByNameNullParamName ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_name( basic_entry,
                                                      "e-name",
                                                      NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, GetParamValueByNameInvalidParamName ) {
    const char *result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_get_entry_param_value_by_name( basic_entry, "e-name", invalid_name.c_str() );
      EXPECT_NULL( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
  }

  TEST_F( EntryTest, GetParamValueByNameInvalidElementName ) {
    const char *result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_get_entry_param_value_by_name( basic_entry, invalid_name.c_str(), "param" );
      EXPECT_NULL( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
  }

  TEST_F( EntryTest, HasElement ) {
    bool result;

    result = stumpless_entry_has_element( basic_entry, element_1_name );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result );

    result = stumpless_entry_has_element( basic_entry, element_2_name );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result );

    result = stumpless_entry_has_element( basic_entry, "not-found" );
    EXPECT_NO_ERROR;
    EXPECT_FALSE( result );
  }

  TEST_F( EntryTest, HasElementNullName ) {
    bool result;

    result = stumpless_entry_has_element( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_FALSE( result );
  }

  TEST_F( EntryTest, HasElementInvalidName ) {
    bool result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_entry_has_element( basic_entry, invalid_name.c_str() );
      EXPECT_FALSE( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
  }

  TEST_F( EntryTest, GetElementInvalidName ) {
    bool result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_get_element_by_name( basic_entry, invalid_name.c_str() );
      EXPECT_FALSE( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
  }

  TEST_F( EntryTest, GetElementIdxInvalidName ) {
    bool result;
    std::vector<std::string> invalid_names = load_corpus_folder("invalid_param_name");

    for(const auto& invalid_name : invalid_names) {
      result = stumpless_get_element_index( basic_entry, invalid_name.c_str() );
      EXPECT_FALSE( result );
      EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    }
  }

  TEST_F( EntryTest, SetAppName ) {
    struct stumpless_entry *entry;
    const char *previous_app_name;
    const char *new_app_name = "new-app-name";

    size_t new_app_name_length = strlen( new_app_name );

    previous_app_name = basic_entry->app_name;

    entry = stumpless_set_entry_app_name( basic_entry, new_app_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, basic_entry );

    ASSERT_EQ( new_app_name_length, basic_entry->app_name_length );
    ASSERT_EQ( 0, memcmp( basic_entry->app_name, new_app_name, new_app_name_length ) );
  }

  TEST_F( EntryTest, SetAppNameMemoryFailure ) {
    void *(*set_malloc_result)(size_t);
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_entry_app_name( basic_entry, "no-memory-required" );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, SetAppNameNullAppName ) {
    struct stumpless_entry *entry;
    const char *previous_app_name;

    previous_app_name = basic_entry->app_name;

    entry = stumpless_set_entry_app_name( basic_entry, NULL );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, basic_entry );

    EXPECT_EQ( basic_entry->app_name_length, 1 );
    EXPECT_EQ( 0, strcmp( basic_entry->app_name, "-" ) );
  }

  TEST_F( EntryTest, SetElement ) {
    struct stumpless_element *new_element;
    const struct stumpless_element *previous_element;
    const struct stumpless_entry *result;

    new_element = stumpless_new_element( "new-element" );
    ASSERT_NOT_NULL( new_element );

    previous_element = stumpless_get_element_by_index( basic_entry, 0 );

    result = stumpless_set_element( basic_entry, 0, new_element );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );
    EXPECT_NE( stumpless_get_element_by_index( basic_entry, 0 ),
               previous_element );

    stumpless_destroy_element_and_contents( previous_element );
  }

  TEST_F( EntryTest, SetElementDuplicateName ) {
    struct stumpless_element *new_element;
    const struct stumpless_element *previous_element;
    const struct stumpless_entry *result;

    new_element = stumpless_new_element( element_1_name );
    ASSERT_NOT_NULL( new_element );

    previous_element = stumpless_get_element_by_index( basic_entry, 0 );

    result = stumpless_set_element( basic_entry, 0, new_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_DUPLICATE_ELEMENT );
    EXPECT_NULL( result );
    EXPECT_EQ( stumpless_get_element_by_index( basic_entry, 0 ),
               previous_element );

    stumpless_destroy_element_and_contents( new_element );
  }

  TEST_F( EntryTest, SetElementIndexOutOfBounds ) {
    struct stumpless_element *new_element;
    const struct stumpless_element *previous_element;
    const struct stumpless_entry *result;

    new_element = stumpless_new_element( "new-element" );
    ASSERT_NOT_NULL( new_element );

    previous_element = stumpless_get_element_by_index( basic_entry, 0 );

    result = stumpless_set_element( basic_entry, 200, new_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 200 );
    EXPECT_NULL( result );
    EXPECT_EQ( stumpless_get_element_by_index( basic_entry, 0 ),
               previous_element );

    stumpless_destroy_element_and_contents( new_element );
  }

  TEST_F( EntryTest, SetElementNullElement ) {
    const struct stumpless_entry *result;

    result = stumpless_set_element( basic_entry, 0, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, SetFacility ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_facility( basic_entry,
                                           STUMPLESS_FACILITY_LOCAL5 );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    EXPECT_EQ( stumpless_get_entry_facility( basic_entry ),
               STUMPLESS_FACILITY_LOCAL5 );
  }

  TEST_F( EntryTest, SetFacilityInvalidFacility ) {
    int previous_facility;
    const struct stumpless_entry *result;

    previous_facility = stumpless_get_entry_facility( basic_entry );

    result = stumpless_set_entry_facility( basic_entry,
                                           ( enum stumpless_facility ) -66 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );
    EXPECT_EQ( stumpless_get_error()->code, -66 );
    EXPECT_NULL( result );
    EXPECT_EQ( stumpless_get_entry_facility( basic_entry ), previous_facility );
  }

  TEST_F( EntryTest, SetMsgid ) {
    struct stumpless_entry *entry;
    const char *previous_msgid;
    const char *new_msgid = "new-msgid";

    size_t new_msgid_length = strlen( new_msgid );

    previous_msgid = basic_entry->msgid;

    entry = stumpless_set_entry_msgid( basic_entry, new_msgid );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, basic_entry );

    ASSERT_EQ( new_msgid_length, basic_entry->msgid_length );
    ASSERT_EQ( 0, memcmp( basic_entry->msgid, new_msgid, new_msgid_length ) );
  }

  TEST_F( EntryTest, SetMsgidMemoryFailure ) {
    void *(*set_malloc_result)(size_t);
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_entry_msgid( basic_entry, "no-memory-required" );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, SetMsgidNullMsgid ) {
    struct stumpless_entry *entry;
    const char *previous_msgid;

    previous_msgid = basic_entry->msgid;

    entry = stumpless_set_entry_msgid( basic_entry, NULL );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, basic_entry );

    EXPECT_EQ( basic_entry->msgid_length, 1 );
    EXPECT_EQ( 0, strcmp( basic_entry->msgid, "-" ) );
  }

  TEST_F( EntryTest, MsgidRejected ) {
    struct stumpless_entry* entry;

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "test-app-name",
                                     "test-msgid-too-long-to-be-accepted-and-must-be-rejected",
                                     "test message" );


    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
  }

  TEST_F( EntryTest, MsgidFormatRejected ) {
    struct stumpless_entry* entry;

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "test-app-name",
                                     "test-msgid-wro\ng-format",
                                     "test message" );


    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
  }

  TEST_F( EntryTest, SetMsgidRejected ) {
    const struct stumpless_entry* result;

    result = stumpless_set_entry_msgid( basic_entry, "gonna-fail-because-length-exceeded-max-allowed" );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
  }

  TEST_F( EntryTest, SetMsgidFormatRejected ) {
    const struct stumpless_entry* result;

    result = stumpless_set_entry_msgid( basic_entry, "test-msgid-wro\ng-format" );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
  }

  TEST_F( EntryTest, SetAppNameRejectedLen ) {
     const struct stumpless_entry* result;

    result = stumpless_set_entry_app_name( basic_entry, "it-is-gonna-fail-because-length-exceeded-max-allowed" );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
  }

  TEST_F( EntryTest, SetAppNameRejectedFormat ) {
     const struct stumpless_entry* result;

    result = stumpless_set_entry_app_name( basic_entry, "test-appname-wro\ng-format" );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
  }

  TEST_F( EntryTest, AppNameRejected ) {
      struct stumpless_entry* entry;

      entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       "test-app-name-too-long-to-be-accepted-and-must-be-rejected",
                                       "test-msgid",
                                       "test message" );


      EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
  }


  TEST_F( EntryTest, SetParam ) {
    struct stumpless_param *new_param;
    const struct stumpless_param *previous_param;
    const struct stumpless_entry *result;

    new_param = stumpless_new_param( "new-param", "new-value" );
    ASSERT_NOT_NULL( new_param );

    previous_param = stumpless_get_entry_param_by_index( basic_entry, 0, 0 );
    ASSERT_NOT_NULL( previous_param );

    result = stumpless_set_entry_param_by_index( basic_entry, 0, 0, new_param );
    EXPECT_NO_ERROR;
    ASSERT_EQ( result, basic_entry );

    stumpless_destroy_param( previous_param );
  }

  TEST_F( EntryTest, SetParamElementIndexOutOfBounds ) {
    struct stumpless_param *new_param;
    const struct stumpless_entry *result;

    new_param = stumpless_new_param( "new-param", "new-value" );
    ASSERT_NOT_NULL( new_param );

    result = stumpless_set_entry_param_by_index( basic_entry,
                                                 455,
                                                 0,
                                                 new_param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 455 );
    EXPECT_NULL( result );

    stumpless_destroy_param( new_param );
  }

  TEST_F( EntryTest, SetParamParamIndexOutOfBounds ) {
    struct stumpless_param *new_param;
    const struct stumpless_entry *result;

    new_param = stumpless_new_param( "new-param", "new-value" );
    ASSERT_NOT_NULL( new_param );

    result = stumpless_set_entry_param_by_index( basic_entry,
                                                 0,
                                                 566,
                                                 new_param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 566 );
    EXPECT_NULL( result );

    stumpless_destroy_param( new_param );
  }

  TEST_F( EntryTest, SetParamValueByIndex ) {
    const struct stumpless_entry *result;
    const char *param_value;

    result = stumpless_set_entry_param_value_by_index( basic_entry,
                                                       0,
                                                       0,
                                                       "new-value" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    param_value = stumpless_get_param_value( param_1_1 );
    EXPECT_STREQ( param_value, "new-value" );
    free( ( void * ) param_value );
  }

  TEST_F( EntryTest, SetParamValueByIndexElementIndexOutOfBounds ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_param_value_by_index( basic_entry,
                                                       5666,
                                                       0,
                                                       "new-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 5666 );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, SetParamValueByIndexParamIndexOutOfBounds ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_param_value_by_index( basic_entry,
                                                       0,
                                                       666,
                                                       "new-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( stumpless_get_error()->code, 666 );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, SetParamValueByName ) {
    const struct stumpless_entry *result;
    const char *param_value;

    result = stumpless_set_entry_param_value_by_name( basic_entry,
                                                      element_1_name,
                                                      param_1_1_name,
                                                      "new-value" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    param_value = stumpless_get_param_value( param_1_1 );
    EXPECT_STREQ( param_value, "new-value" );
    free( ( void * ) param_value );
  }

  TEST_F( EntryTest, SetParamValueByNameNullElementName ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_param_value_by_name( basic_entry,
                                                      NULL,
                                                      param_1_1_name,
                                                      "new-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( EntryTest, SetParamValueByNameElementNameNotFound ) {
    const struct stumpless_entry *result;
    struct stumpless_element *new_element;
    const char *param_value;

    result = stumpless_set_entry_param_value_by_name( basic_entry,
                                                      "doesnt-exist",
                                                      "new-name",
                                                      "new-value" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );
    EXPECT_TRUE( stumpless_entry_has_element( basic_entry, "doesnt-exist" ) );

    new_element = stumpless_get_element_by_name( basic_entry, "doesnt-exist" );
    EXPECT_NOT_NULL( new_element );
    EXPECT_TRUE( stumpless_element_has_param( new_element, "new-name" ) );

    param_value = stumpless_get_param_value_by_name( new_element, "new-name" );
    EXPECT_STREQ( param_value, "new-value" );
    free( ( void * ) param_value );
  }

  TEST_F( EntryTest, SetParamValueByNameElementNameNotFoundMallocFailure ) {
    void *(*set_malloc_result)(size_t);
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_entry_param_value_by_name( basic_entry,
                                                      "doesnt-exist",
                                                      "new-name",
                                                      "new-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, SetParamValueByNameElementNameNotFoundMallocFailureOnParamValue ) {
    void *(*set_malloc_result)(size_t);
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 17 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_entry_param_value_by_name( basic_entry,
                                                      "doesnt-exist",
                                                      "new-name",
                                                      "new-doomed-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, SetParamValueByNameElementNameNotFoundReallocFailure ) {
    void * (*set_realloc_result)(void *, size_t);
    const struct stumpless_entry *result;

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_NOT_NULL( set_realloc_result );

    result = stumpless_set_entry_param_value_by_name( basic_entry,
                                                      "doesnt-exist",
                                                      "new-name",
                                                      "new-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_realloc_result = stumpless_set_realloc( realloc );
    ASSERT_TRUE( set_realloc_result == realloc );
  }

  TEST_F( EntryTest, SetParamValueByNameParamNameNotFound ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_param_value_by_name( basic_entry,
                                                      element_1_name,
                                                      "doesnt-exist",
                                                      "new-value" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );
    EXPECT_TRUE( stumpless_element_has_param( element_1, "doesnt-exist" ) );
  }

  TEST_F( EntryTest, SetPriorityInvalidFacility ) {
    int previous_prival;
    const struct stumpless_entry *result;

    previous_prival = stumpless_get_entry_prival( basic_entry );

    result = stumpless_set_entry_priority( basic_entry,
                                           ( enum stumpless_facility ) -66,
                                           STUMPLESS_SEVERITY_EMERG );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );
    EXPECT_EQ( stumpless_get_error()->code, -66 );
    EXPECT_NULL( result );
    EXPECT_EQ( stumpless_get_entry_prival( basic_entry ), previous_prival );
  }

  TEST_F( EntryTest, SetPriorityInvalidSeverity ) {
    int previous_prival;
    const struct stumpless_entry *result;

    previous_prival = stumpless_get_entry_prival( basic_entry );

    result = stumpless_set_entry_priority( basic_entry,
                                           STUMPLESS_FACILITY_LOCAL5,
                                           ( enum stumpless_severity ) -66 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
    EXPECT_EQ( stumpless_get_error()->code, -66 );
    EXPECT_NULL( result );
    EXPECT_EQ( stumpless_get_entry_prival( basic_entry ), previous_prival );
  }

  TEST_F( EntryTest, SetPrival ) {
    int new_prival = STUMPLESS_FACILITY_LOCAL5 | STUMPLESS_SEVERITY_EMERG;
    const struct stumpless_entry *result;

    result = stumpless_set_entry_prival( basic_entry, new_prival );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    EXPECT_EQ( stumpless_get_entry_prival( basic_entry ), new_prival );
  }

  TEST_F( EntryTest, SetSeverity ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_severity( basic_entry,
                                           STUMPLESS_SEVERITY_EMERG );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );

    EXPECT_EQ( stumpless_get_entry_severity( basic_entry ),
               STUMPLESS_SEVERITY_EMERG );
  }

  TEST_F( EntryTest, SetSeverityInvalidSeverity ) {
    int previous_severity;
    const struct stumpless_entry *result;

    previous_severity = stumpless_get_entry_severity( basic_entry );

    result = stumpless_set_entry_severity( basic_entry,
                                           ( enum stumpless_severity ) -66 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
    EXPECT_EQ( stumpless_get_error()->code, -66 );
    EXPECT_NULL( result );
    EXPECT_EQ( stumpless_get_entry_severity( basic_entry ), previous_severity );
  }

    TEST_F( EntryTest, AppNameFormatRejected ) {
    struct stumpless_entry *bad_stump;

    bad_stump = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
                                         "bad\nappname",
                                         basic_msgid,
                                         basic_message );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );

    EXPECT_NULL( bad_stump );
  }

  /* non-fixture tests */

  TEST( AddElementTest, NullEntry ){
    struct stumpless_entry *entry;
    struct stumpless_element *element;

    element = stumpless_new_element( "test-new-element" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element );

    entry = stumpless_add_element( NULL, element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    ASSERT_NULL( entry );

    stumpless_destroy_element_and_contents( element );

    stumpless_free_all(  );
  }

  TEST( AddNewParam, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_add_new_param_to_entry( NULL,
                                               "new-element-name",
                                               "new-param-name",
                                               "new-param-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( CopyEntry, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_copy_entry( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( DestroyEntryOnlyTest, NullEntry ) {
    stumpless_destroy_entry_only( NULL );
  }

  TEST( DestroyEntryOnlyTest, OneElement ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    const char *element_name = "test-element-name";

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "test-app-name",
                                     "test-msgid",
                                     "test message" );
    ASSERT_NOT_NULL( entry );

    element = stumpless_new_element( element_name );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( element );

    stumpless_destroy_entry_only( entry );

    ASSERT_TRUE( memcmp( element->name,
                         element_name,
                         element->name_length ) == 0 );

    stumpless_destroy_element_and_contents( element );

    stumpless_free_all(  );
  }

  TEST( DestroyEntryTest, NullEntry ) {
    stumpless_destroy_entry_and_contents( NULL );
  }

  TEST( GetElementByIndexTest, NullEntry ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_index( NULL, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetElementByNameTest, NullEntry ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_name( NULL, "irrelevant" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetElementCount, NullEntry ) {
    size_t result;

    result = stumpless_get_element_count( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );

    stumpless_free_all(  );
  }

  TEST( GetElementIndex, NullEntry ) {
    size_t result;

    result = stumpless_get_element_index( NULL, "irrelevant" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );

    stumpless_free_all(  );
  }

  TEST( GetAppName, NullEntry ) {
    const char *result;

    result = stumpless_get_entry_app_name( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetFacilityTest, NullEntry ) {
    int result;

    result = stumpless_get_entry_facility( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, -1 );

    stumpless_free_all(  );
  }

  TEST( GetMessage, NullEntry ) {
    const char *result;

    result = stumpless_get_entry_message( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetMsgid, NullEntry ) {
    const char *result;

    result = stumpless_get_entry_msgid( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetParamByIndexTest, NullEntry ) {
    struct stumpless_param *result;

    result = stumpless_get_entry_param_by_index( NULL, 0, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetParamByNameTest, NullEntry ) {
    struct stumpless_param *result;

    result = stumpless_get_entry_param_by_name( NULL, "e-name", "p-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetParamValueByIndexTest, NullEntry ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_index( NULL, 0, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetParamValueByNameTest, NullEntry ) {
    const char *result;

    result = stumpless_get_entry_param_value_by_name( NULL,
                                                      "e-name",
                                                      "p-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( GetPrivalTest, NullEntry ) {
    int result;

    result = stumpless_get_entry_prival( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, -1 );

    stumpless_free_all(  );
  }

  TEST( GetSeverityTest, NullEntry ) {
    int result;

    result = stumpless_get_entry_severity( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, -1 );

    stumpless_free_all(  );
  }

  TEST( HasElementTest, NullEntry ) {
    bool result;

    result = stumpless_entry_has_element( NULL, "irrelevant" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_FALSE( result );

    stumpless_free_all(  );
  }

  TEST( LoadEntryTest, FormatSpecifiers ) {
    struct stumpless_entry entry;
    const struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *format = "string: %s\nint: %d";
    const char *string_sub = "added to the string";
    int int_sub = 2234;
    const char *expected_message = "string: added to the string\nint: 2234";
    size_t expected_message_length;

    result = stumpless_load_entry( &entry,
                                   STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   app_name,
                                   msgid,
                                   format,
                                   string_sub,
                                   int_sub );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );
    EXPECT_NOT_NULL( entry.message );

    expected_message_length = strlen( expected_message );
    EXPECT_EQ( entry.message_length, expected_message_length );
    EXPECT_EQ( 0, memcmp( entry.message, expected_message, entry.message_length ) );

    stumpless_unload_entry_only( &entry );

    stumpless_free_all(  );
  }

  TEST( LoadEntryTest, InvalidAppName ) {
    struct stumpless_entry entry;
    const char *app_name = "test-app-name-错误";
    const char *msgid = "test-msgid";
    const struct stumpless_entry *result;

    result = stumpless_load_entry( &entry,
                                   STUMPLESS_FACILITY_USER,
                                   STUMPLESS_SEVERITY_INFO,
                                   app_name,
                                   msgid,
                                   NULL );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( LoadEntryStrTest, InvalidAppName ) {
    struct stumpless_entry entry;
    const char *app_name = "test-app-name-错误";
    const char *msgid = "test-msgid";
    const struct stumpless_entry *result;

    result = stumpless_load_entry_str( &entry,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       msgid,
                                       NULL );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( LoadEntryStrTest, MallocFailureOnMessage ) {
    void * (*set_malloc_result)(size_t);
    struct stumpless_entry entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "nice and long to make sure it beats the first";
    const struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 46 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_load_entry_str( &entry,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       msgid,
                                       message );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_free_all(  );
  }

  TEST( LoadEntryStrTest, NullMesssage ) {
    struct stumpless_entry entry;
    const struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";

    result = stumpless_load_entry_str( &entry,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       msgid,
                                       NULL );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    if( result ) {
      EXPECT_EQ( entry.message_length, 0 );
    }

    stumpless_unload_entry_only( &entry );

    stumpless_free_all(  );
  }

  TEST( LoadEntryStrTest, NullMessageId ) {
    struct stumpless_entry entry;
    const struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *message = "test-message";

    result = stumpless_load_entry_str( &entry,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       NULL,
                                       message );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    if( result ) {
      EXPECT_EQ( entry.msgid[0], '-' );
      EXPECT_EQ( entry.msgid_length, 1 );
    }

    stumpless_unload_entry_only( &entry );

    stumpless_free_all(  );
  }

  TEST( LoadEntryStrTest, Success ) {
    struct stumpless_entry entry;
    const struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    result = stumpless_load_entry_str( &entry,
                                       STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       msgid,
                                       message );
    EXPECT_NO_ERROR;
    ASSERT_TRUE( result == &entry );

    EXPECT_EQ( STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO, entry.prival );
    EXPECT_NULL( entry.elements );
    EXPECT_EQ( 0, entry.element_count );

    confirm_entry_contents( &entry, app_name, msgid, message );

    stumpless_unload_entry_only( &entry );
    stumpless_free_all(  );
  }

  TEST( NewEntryStrTest, New ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     app_name,
                                     msgid,
                                     message );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    EXPECT_EQ( STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO, entry->prival );
    EXPECT_NULL( entry->elements );
    EXPECT_EQ( 0, entry->element_count );

    confirm_entry_contents( entry, app_name, msgid, message );

    stumpless_destroy_entry_only( entry );
    stumpless_free_all(  );
  }

  TEST( NewEntryStrTest, NullAppName ) {
    struct stumpless_entry *entry;
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     NULL,
                                     msgid,
                                     message );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    if( entry ) {
      EXPECT_EQ( entry->app_name[0], '-' );
      EXPECT_EQ( entry->app_name_length, 1 );
    }

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( NewEntryStrTest, NullMesssage ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     app_name,
                                     msgid,
                                     NULL );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    if( entry ) {
      EXPECT_EQ( entry->message_length, 0 );
    }

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( NewEntryStrTest, NullMessageId ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *message = "test-message";

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     app_name,
                                     NULL,
                                     message );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    if( entry ) {
      EXPECT_EQ( entry->msgid[0], '-' );
      EXPECT_EQ( entry->msgid_length, 1 );
    }

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( NewEntryTest, FormatSpecifiers ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *format = "string: %s\nint: %d";
    const char *string_sub = "added to the string";
    int int_sub = 2234;
    const char *expected_message = "string: added to the string\nint: 2234";
    size_t expected_message_length;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 format,
                                 string_sub,
                                 int_sub );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );
    EXPECT_NOT_NULL( entry->message );

    expected_message_length = strlen( expected_message );
    EXPECT_EQ( entry->message_length, expected_message_length );
    EXPECT_EQ( 0, memcmp( entry->message, expected_message, entry->message_length ) );

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST(NewEntryTest, MallocFailureAfterCacheFill) {
    struct stumpless_entry *entries[2000];
    size_t i,j;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    void *(*set_malloc_result)(size_t);

    // create an entry to initialize the cache
    entries[0] = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                      STUMPLESS_SEVERITY_INFO,
                                      app_name,
                                      msgid,
                                      NULL );
    EXPECT_NOT_NULL(entries[0]);

    set_malloc_result = stumpless_set_malloc(MALLOC_FAIL);
    ASSERT_NOT_NULL(set_malloc_result);

    for (i = 1; i < 2000; i++) {
      entries[i] = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                        STUMPLESS_SEVERITY_INFO,
                                        app_name,
                                        msgid,
                                        NULL );

      if (!entries[i]) {
        EXPECT_ERROR_ID_EQ(STUMPLESS_MEMORY_ALLOCATION_FAILURE);
        break;
      }
    }

    EXPECT_NE(i, 2000);

    set_malloc_result = stumpless_set_malloc(malloc);
    EXPECT_TRUE(set_malloc_result == malloc);

    for (j = 0; j < i; j++) {
        stumpless_destroy_entry_and_contents(entries[j]);
    }
    stumpless_free_all();
  }

  TEST( NewEntryTest, MallocFailureOnMsgid ) {
    void *(*set_malloc_result)(size_t);
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid-of-unique-length";
    const char *message = "test-message";
    struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 28 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                      STUMPLESS_SEVERITY_INFO,
                                      app_name,
                                      msgid,
                                      message );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( result );
    stumpless_free_all(  );
  }

  TEST( NewEntryTest, MallocFailureOnAppName ) {
    void *(*set_malloc_result)(size_t);
    const char *app_name = "test-app-name-of-unique-length";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    struct stumpless_entry *result;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 31 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                      STUMPLESS_SEVERITY_INFO,
                                      app_name,
                                      msgid,
                                      message );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( result );
    stumpless_free_all(  );
  }

  TEST( NewEntryTest, MallocFailureOnSecond ) {
    struct stumpless_entry *first_entry;
    struct stumpless_entry *second_entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    void *(*set_malloc_result)(size_t);

    // create at least one entry to allow the cache to initialize
    first_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                           STUMPLESS_SEVERITY_INFO,
                                           app_name,
                                           msgid,
                                           message );
    ASSERT_NOT_NULL( first_entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    second_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                            STUMPLESS_SEVERITY_INFO,
                                            app_name,
                                            msgid,
                                            message );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( second_entry );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( second_entry );
    stumpless_destroy_entry_and_contents( first_entry );

    stumpless_free_all(  );
  }

  TEST( NewEntryTest, MoreThan500Entries ) {
    struct stumpless_entry *entry[500];
    size_t i;

    for( i = 0; i < 500; i++ ) {
      entry[i] = create_empty_entry(  );
      EXPECT_NO_ERROR;
      EXPECT_NOT_NULL( entry[i] );
    }

    for( i = 0; i < 500; i++ ) {
      stumpless_destroy_entry_and_contents( entry[i] );
    }

    stumpless_free_all(  );
  }

  TEST( NewEntryTest, NoFormat ){
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_ALERT,
                                 STUMPLESS_SEVERITY_ALERT,
                                 app_name,
                                 msgid,
                                 message );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    EXPECT_EQ( STUMPLESS_FACILITY_ALERT | STUMPLESS_SEVERITY_ALERT, entry->prival );
    EXPECT_NULL( entry->elements );
    EXPECT_EQ( 0, entry->element_count );

    confirm_entry_contents( entry, app_name, msgid, message );

    stumpless_destroy_entry_only( entry );
    stumpless_free_all(  );
  }

  TEST( NewEntryTest, NullAppName ) {
    struct stumpless_entry *entry;
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 NULL,
                                 msgid,
                                 message );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    if( entry ) {
      EXPECT_EQ( entry->app_name[0], '-' );
      EXPECT_EQ( entry->app_name_length, 1 );
    }

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( NewEntryTest, NullMesssage ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 NULL );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    if( entry ) {
      EXPECT_EQ( entry->message_length, 0 );
    }

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( NewEntryTest, NullMessageId ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *message = "test-message";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 NULL,
                                 message );

    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    if( entry ) {
      EXPECT_EQ( entry->msgid[0], '-' );
      EXPECT_EQ( entry->msgid_length, 1 );
    }

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( NewEntryTest, ReallocFailureOnSecond ) {
    struct stumpless_entry *entries[2000];
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    void * (*set_realloc_result)(void *, size_t);
    int i;

    // create at least one entry to allow the cache to initialize
    entries[0] = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                      STUMPLESS_SEVERITY_INFO,
                                      app_name,
                                      msgid,
                                      message );
    ASSERT_NOT_NULL( entries[0] );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_NOT_NULL( set_realloc_result );

    for( i = 1; i < 2000; i++ ) {
     entries[i] = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       msgid,
                                       message );

      if( !entries[i] ) {
        EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
        break;
      }
    }

    EXPECT_NE( i, 2000 );

    set_realloc_result = stumpless_set_realloc( realloc );
    ASSERT_TRUE( set_realloc_result == realloc );

    i--;
    while( i >= 0 ) {
      stumpless_destroy_entry_and_contents( entries[i] );
      i--;
    }

    stumpless_free_all(  );
  }

  TEST( SetAppNameTest, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_app_name( NULL, "new-app-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetElementTest, NullEntry ) {
    struct stumpless_element *new_element;
    const struct stumpless_entry *result;

    new_element = stumpless_new_element( "new-element" );
    ASSERT_NOT_NULL( new_element );

    result = stumpless_set_element( NULL, 0, new_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_destroy_element_and_contents( new_element );

    stumpless_free_all(  );
  }

  TEST( SetFacilityTest, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_facility( NULL, STUMPLESS_FACILITY_USER );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetMsgidTest, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_msgid( NULL, "new-app-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetMessageTest, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_message( NULL, "test-message" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetMessageTest, NullMessage ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    result = stumpless_set_entry_message( entry, NULL );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, result );

    EXPECT_NULL( entry->message );
    EXPECT_EQ( 0, entry->message_length );

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( SetMessageStrTest, AsciiMessage ) {
    struct stumpless_entry *entry;
    const char *ascii_message;
    const struct stumpless_entry *result;
    const char *new_message;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    ascii_message = load_corpus( "cstring/ascii" );
    ASSERT_NOT_NULL( ascii_message );

    result = stumpless_set_entry_message_str( entry, ascii_message );
    EXPECT_EQ( entry, result );
    EXPECT_NO_ERROR;

    new_message = stumpless_get_entry_message( entry );
    EXPECT_NOT_NULL( new_message );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( ascii_message, new_message );

    delete[] ascii_message;
    free( ( void * ) new_message );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetMessageStrTest, LongAsciiMessage ) {
    struct stumpless_entry *entry;
    const char *long_message;
    const struct stumpless_entry *result;
    const char *new_message;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    long_message = load_corpus( "cstring/lorem" );
    ASSERT_NOT_NULL( long_message );

    result = stumpless_set_entry_message_str( entry, long_message );
    EXPECT_EQ( entry, result );
    EXPECT_NO_ERROR;

    new_message = stumpless_get_entry_message( entry );
    EXPECT_NOT_NULL( new_message );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( long_message, new_message );

    delete[] long_message;
    free( ( void * ) new_message );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetMessageStrTest, MallocFailureOnMessage ) {
    void * (*set_malloc_result)(size_t);
    struct stumpless_entry *entry;
    const char *new_message = "nice and long to make sure it beats the first";
    const struct stumpless_entry *result;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 46 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_entry_message_str( entry, new_message );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetMessageStrTest, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_message_str( NULL, "test-message" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetMessageStrTest, NullMessage ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    result = stumpless_set_entry_message_str( entry, NULL );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, result );

    EXPECT_NULL( entry->message );
    EXPECT_EQ( 0, entry->message_length );

    stumpless_destroy_entry_and_contents( entry );

    stumpless_free_all(  );
  }

  TEST( SetMessageStrTest, Utf8Message ) {
    struct stumpless_entry *entry;
    const char *utf8_message;
    const struct stumpless_entry *result;
    const char *new_message;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    utf8_message = load_corpus( "cstring/zh-cn" );
    ASSERT_NOT_NULL( utf8_message );

    result = stumpless_set_entry_message_str( entry, utf8_message );
    EXPECT_EQ( entry, result );
    EXPECT_NO_ERROR;

    new_message = stumpless_get_entry_message( entry );
    EXPECT_NOT_NULL( new_message );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( utf8_message, new_message );

    delete[] utf8_message;
    free( ( void * ) new_message );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

    TEST( SetMessageWideStrTest, AsciiMessage ) {
    struct stumpless_entry *entry;
    const wchar_t *wide_ascii_message = L"ASCII Message";
    const char *ascii_message = "ASCII Message";
    const struct stumpless_entry *result;
    const char *new_message;

    entry = create_empty_entry();
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_message_str_w( entry, wide_ascii_message );
    EXPECT_EQ( entry, result );
    EXPECT_NO_ERROR;

    new_message = stumpless_get_entry_message( entry );
    EXPECT_NOT_NULL( new_message );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( ascii_message, new_message );

    free( ( void * ) new_message );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all();
  }

  TEST( SetMessageWideStrTest, LongAsciiMessage ) {
    struct stumpless_entry *entry;
    const char *long_message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.Proin porta, sem quis imperdiet aliquam, lectus odio consequat elit, at ullamcorper felis urna vel leo. Ut vitae risus cursus, tempor risus sed, elementum risus. Vestibulum porta egestas libero et lacinia.";
    const wchar_t *wide_long_message = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit.Proin porta, sem quis imperdiet aliquam, lectus odio consequat elit, at ullamcorper felis urna vel leo. Ut vitae risus cursus, tempor risus sed, elementum risus. Vestibulum porta egestas libero et lacinia.";
    const struct stumpless_entry *result;
    const char *new_message;

    entry = create_empty_entry();
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_message_str_w( entry, wide_long_message );
    EXPECT_EQ( entry, result );
    EXPECT_NO_ERROR;

    new_message = stumpless_get_entry_message( entry );
    EXPECT_NOT_NULL( new_message );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( long_message, new_message );
    free( ( void * ) new_message );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all();
  }

  TEST( SetMessageWideStrTest, MallocFailureOnMessage ) {
    void * (*set_malloc_result)(size_t);
    struct stumpless_entry *entry;
    const wchar_t *new_message = L"nice and long to make sure it beats the first";
    const struct stumpless_entry *result;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 46 ) );
    ASSERT_NOT_NULL( set_malloc_result );

    result = stumpless_set_entry_message_str_w( entry, new_message );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all();
  }

  TEST( SetMessageWideStrTest, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_message_str_w( NULL, L"test-message" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all();
  }

  TEST( SetMessageWideStrTest, NullMessage ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    entry = create_empty_entry();
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry );

    result = stumpless_set_entry_message_str_w( entry, NULL );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, result );

    EXPECT_NULL( entry->message );
    EXPECT_EQ( 0, entry->message_length );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all();
  }

  TEST( SetMessageWideStrTest, WideMessage ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;
    const wchar_t *wide_message= L"message";
    const char *utf8_message = "message";
    const char *new_message;

    entry = create_empty_entry();
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_message_str_w( entry, wide_message );
    EXPECT_EQ( entry, result );
    EXPECT_NO_ERROR;

    new_message = stumpless_get_entry_message( entry );
    EXPECT_NOT_NULL( new_message );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( new_message, utf8_message );

    free( ( void * ) new_message );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all();
  }

  TEST( SetParam, NullEntry ) {
    struct stumpless_param *param;
    const struct stumpless_entry *result;

    param = stumpless_new_param( "param-name", "param-value" );
    ASSERT_NOT_NULL( param );

    result = stumpless_set_entry_param_by_index( NULL, 0, 0, param );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_destroy_param( param );

    stumpless_free_all(  );
  }

  TEST( SetParamValueByIndex, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_param_value_by_index( NULL,
                                                       0,
                                                       0,
                                                       "new-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetParamValueByName, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_param_value_by_name( NULL,
                                                      "element-name",
                                                      "param-name",
                                                      "new-value" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetPrivalTest, NullEntry ) {
    int prival = STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO;
    const struct stumpless_entry *result;

    result = stumpless_set_entry_prival( NULL, prival );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetSeverityTest, NullEntry ) {
    const struct stumpless_entry *result;

    result = stumpless_set_entry_severity( NULL, STUMPLESS_SEVERITY_INFO );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( AddParamTest, ParamNameTooLong ){
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    const char *param_name = "very-long-name-abcdefghijklmnopqrstuvwxyz";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 message );

    result = stumpless_add_new_param_to_entry( entry,
                                               "new-element-name",
                                               param_name,
                                               "test-value" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( GetProcid, ProcidNotSet ) {
    struct stumpless_entry *entry;
    const char *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_get_entry_procid( entry );

    EXPECT_NOT_NULL( result );
    EXPECT_NO_ERROR;

    free( (void *) result );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( GetProcid, ProcidSet ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *entry_result;
    const char *str_result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    const char *procid = "test-procid";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    entry_result = stumpless_set_entry_procid( entry, procid );
    EXPECT_NOT_NULL( entry_result );
    EXPECT_NO_ERROR;

    str_result = stumpless_get_entry_procid( entry );
    EXPECT_NOT_NULL( str_result );
    EXPECT_NO_ERROR;

    EXPECT_GT( entry->procid_length, 0 );
    EXPECT_STREQ( str_result, procid );

    free( (void *) str_result );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( GetProcid, NullEntry ) {
    const char *procid;

    procid = stumpless_get_entry_procid( NULL );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL ( procid );

    stumpless_free_all(  );
  }

  TEST( SetProcid, SetValue ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    const char *procid = "test-procid";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_procid( entry, procid );
    EXPECT_EQ( result, entry );
    EXPECT_NO_ERROR;

    EXPECT_GE( entry->procid_length, 0 );
    EXPECT_STREQ( entry->procid, procid );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetProcid, ResetValue ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_procid( entry, NULL );

    EXPECT_NOT_NULL( result );
    EXPECT_NO_ERROR;

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetProcid, NullEntry ) {
    struct stumpless_entry *result;

    result = stumpless_set_entry_procid( NULL, NULL );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL ( result );

    stumpless_free_all(  );
  }

  TEST( SetProcid, ProcidTooLong ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;
    const char *procid = "test-procid-"
                         "abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmn";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_procid( entry, procid );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
    EXPECT_NULL( result );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetProcid, ProcidNotPrintable ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    const char *procid = "\n";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 message );

    result = stumpless_set_entry_procid( entry, procid );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    EXPECT_NULL( result );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetProcid, SetValueBufferValue ) {
    struct stumpless_entry *entry;
    struct stumpless_target *target;
    const char *buffer_name = "output-buffer";
    char buffer[8096];
    const char *procid = "test-procid";

    target = stumpless_open_buffer_target("output buffer", buffer, 8096);
    stumpless_set_option( target, STUMPLESS_OPTION_PID);
    ASSERT_NOT_NULL( target );

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    stumpless_set_entry_procid( entry, procid );
    stumpless_add_entry( target, entry );
    EXPECT_THAT( buffer, HasSubstr( "test-procid" ) );

    stumpless_close_buffer_target( target );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( GetHostName, HostNameSet ) {
    struct stumpless_entry *entry;
    const char *hostname = "test-hostname";
    const struct stumpless_entry *set_result;
    const char *str_result;

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    set_result = stumpless_set_entry_hostname( entry, hostname );
    EXPECT_NO_ERROR;
    EXPECT_EQ( set_result, entry );

    str_result = stumpless_get_entry_hostname( entry );
    EXPECT_NO_ERROR;
    EXPECT_THAT( str_result, HasSubstr( hostname ) );

    free( ( void * ) str_result );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( GetHostName, HostNameNotSet ) {
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    const char *hostname;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 message );
    ASSERT_NOT_NULL( entry );

    hostname = stumpless_get_entry_hostname( entry );
    EXPECT_NOT_NULL( hostname );

    free( (void *) hostname );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( GetHostName, NullEntry ) {
    const char *hostname;

    hostname = stumpless_get_entry_hostname( NULL );

    EXPECT_NULL( hostname );
  }

  TEST( SetHostName, SetValue ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    const char *hostname = "test-hostname";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 message );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_hostname( entry, hostname );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );
    EXPECT_EQ( result, entry );
    const char *result_hostname = stumpless_get_entry_hostname( entry );
    EXPECT_THAT( result_hostname, HasSubstr( hostname ) );

    free( (void *) result_hostname );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetHostName, ResetValue ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_hostname( entry, NULL );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetHostName, NullEntry ) {
    struct stumpless_entry *result;

    result = stumpless_set_entry_hostname( NULL, NULL );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );

    stumpless_free_all(  );
  }

  TEST( SetHostName, HostNameTooLong ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *hostname = "test-hostname"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy"
                         "-abcdefghijklmnopqrstuvwxy";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_hostname( entry, hostname );

    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_TOO_BIG );
    EXPECT_NULL( result );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetHostName, HostNameNotPrintable ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const char *hostname = "test-procid-\x01";

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_entry_hostname( entry, hostname );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    EXPECT_NULL( result );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( SetHostname, SetValueBufferValue ) {
    struct stumpless_entry *entry;
    struct stumpless_target *target;
    const char *buffer_name = "output-buffer";
    char buffer[8096];
    const char *hostname = "test-hostname";

    target = stumpless_open_buffer_target("output buffer", buffer, 8096);
    ASSERT_NOT_NULL( target );

    entry = create_entry(  );
    ASSERT_NOT_NULL( entry );

    stumpless_set_entry_hostname( entry, hostname );
    stumpless_add_entry( target, entry );
    EXPECT_THAT( buffer, HasSubstr( "test-hostname" ) );

    stumpless_close_buffer_target( target );
    stumpless_destroy_entry_and_contents( entry );
    stumpless_free_all(  );
  }

  TEST( UnloadEntryAndContents, NullEntry ) {
    stumpless_unload_entry_and_contents( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( UnloadEntryOnly, NullEntry ) {
    stumpless_unload_entry_only( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( CopyEntry, MallocFailureOnSizeOverflow ) {
    const struct stumpless_entry *result;
    struct stumpless_entry *large_entry = NULL;
	size_t large_entry_ec;

    large_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
			STUMPLESS_SEVERITY_INFO,
			"large-app-name",
			"large-msgid",
			"large message" );
	large_entry_ec = large_entry->element_count;
	large_entry->element_count = SIZE_MAX;

	result = stumpless_copy_entry( large_entry );
	EXPECT_NULL( result );
	EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    large_entry->element_count = large_entry_ec;
    stumpless_destroy_entry_and_contents(large_entry);
  }

}
