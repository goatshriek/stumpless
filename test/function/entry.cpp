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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/memory_allocation.hpp"

using::testing::HasSubstr;

namespace {

  class EntryTest : public::testing::Test {
    protected:
      const char *basic_app_name = "basic-app-name";
      const char *basic_msgid = "basic-msgid";
      const char *basic_message = "basic message";
      struct stumpless_entry *basic_entry;
      const char *element_1_name = "basic-element";
      struct stumpless_element *element_1;

      virtual void
      SetUp( void ) {
        basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                           STUMPLESS_SEVERITY_INFO,
                                           basic_app_name,
                                           basic_msgid,
                                           basic_message );

        element_1 = stumpless_new_element( element_1_name );
        stumpless_add_element( basic_entry, element_1 );

        // cause a failure so that memory allocation tests will still have an
        // error that they can return
        stumpless_new_element( NULL );
      }

      virtual void
      TearDown( void ){
        stumpless_destroy_entry_and_contents( basic_entry );
      }
  };

  TEST_F( EntryTest, AddElement ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element;

    element = stumpless_new_element( "test-new-element" );
    ASSERT_TRUE( element != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    entry = stumpless_add_element( basic_entry, element );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    ASSERT_TRUE( entry != NULL );
    EXPECT_EQ( basic_entry, entry );
  }

  TEST_F( EntryTest, AddDuplicateElement ) {
    struct stumpless_element *duplicate_element;
    size_t original_element_count;
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    original_element_count = basic_entry->element_count;

    duplicate_element = stumpless_new_element( element_1_name );
    EXPECT_NO_ERROR;
    ASSERT_TRUE( duplicate_element != NULL );

    result = stumpless_add_element( basic_entry, duplicate_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_DUPLICATE_ELEMENT );
    EXPECT_TRUE( result == NULL );
    EXPECT_EQ( basic_entry->element_count, original_element_count );

    stumpless_destroy_element_only( duplicate_element );
  }

  TEST_F( EntryTest, AddElementMemoryFailure ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    const struct stumpless_error *error;
    void * (*set_realloc_result)(void *, size_t);

    element = stumpless_new_element( "test-memory-failure" );
    ASSERT_TRUE( element != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_TRUE( set_realloc_result != NULL );

    entry = stumpless_add_element( basic_entry, element );
    EXPECT_EQ( NULL, entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_realloc_result = stumpless_set_realloc( realloc );
    EXPECT_TRUE( set_realloc_result == realloc );
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
    const struct stumpless_error *error;

    result = stumpless_add_new_element( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST_F( EntryTest, AddNullElement ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_add_element( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    ASSERT_TRUE( result == NULL );
  }

  TEST_F( EntryTest, AddTwoElements ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element1;
    struct stumpless_element *element2;

    element1 = stumpless_new_element( "test-new-element-1" );
    ASSERT_TRUE( element1 != NULL );
    EXPECT_NO_ERROR;

    entry = stumpless_add_element( basic_entry, element1 );
    EXPECT_NO_ERROR;
    ASSERT_TRUE( entry != NULL );
    EXPECT_EQ( basic_entry, entry );

    element2 = stumpless_new_element( "test-new-element-2" );
    ASSERT_TRUE( element2 != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    entry = stumpless_add_element( basic_entry, element2 );
    EXPECT_NO_ERROR;
    ASSERT_TRUE( entry != NULL );
    EXPECT_EQ( basic_entry, entry );
  }

  TEST_F( EntryTest, Copy ) {
    const struct stumpless_entry *result;

    result = stumpless_copy_entry( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_NE( result, basic_entry );
  }

  TEST_F( EntryTest, CopyMallocFailure ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    // create the internal error struct
    stumpless_get_element_name( NULL );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_TRUE( set_malloc_result != NULL );

    result = stumpless_copy_entry( basic_entry );
    EXPECT_TRUE( result == NULL );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( EntryTest, CopyReallocFailure ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;
    void * (*set_realloc_result)(void *, size_t);

    // create the internal error struct
    stumpless_get_element_name( NULL );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_TRUE( set_realloc_result != NULL );

    result = stumpless_copy_entry( basic_entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_TRUE( result == NULL );

    stumpless_set_realloc( realloc );
  }

  TEST_F( EntryTest, GetAppName ) {
    const char *result;

    result = stumpless_get_entry_app_name( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, basic_app_name );
    EXPECT_NE( result, basic_app_name );
  }

  TEST_F( EntryTest, GetElementByIndex ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_index( basic_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element_1 );
  }

  TEST_F( EntryTest, GetElementByIndexOutOfBounds ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_get_element_by_index( basic_entry, 534 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, 534 );
    EXPECT_TRUE( result == NULL );
  }

  TEST_F( EntryTest, GetElementByName ) {
    const struct stumpless_element *result;

    result = stumpless_get_element_by_name( basic_entry, element_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, element_1 );
  }

  TEST_F( EntryTest, GetElementByNameNotFound ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_get_element_by_name( basic_entry, "not-found" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ELEMENT_NOT_FOUND );
    EXPECT_TRUE( result == NULL );
  }

  TEST_F( EntryTest, GetElementByNameNullName ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_get_element_by_name( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST_F( EntryTest, GetElementIndex ) {
    size_t result;

    result = stumpless_get_element_index( basic_entry, element_1_name );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, 0 );
  }

  TEST_F( EntryTest, GetElementIndexNotFound ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_element_index( basic_entry, "not-found" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ELEMENT_NOT_FOUND );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( EntryTest, GetElementIndexNullName ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_element_index( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( EntryTest, GetMsgid ) {
    const char *result;

    result = stumpless_get_entry_msgid( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_STREQ( result, basic_msgid );
    EXPECT_NE( result, basic_msgid );
  }

  TEST_F( EntryTest, HasElement ) {
    bool result;

    result = stumpless_entry_has_element( basic_entry, element_1_name );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result );

    result = stumpless_entry_has_element( basic_entry, "not-found" );
    EXPECT_NO_ERROR;
    EXPECT_FALSE( result );
  }

  TEST_F( EntryTest, HasElementNullName ) {
    bool result;
    const struct stumpless_error *error;

    result = stumpless_entry_has_element( basic_entry, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_FALSE( result );
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
    const struct stumpless_error *error;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_TRUE( set_malloc_result != NULL );

    result = stumpless_set_entry_app_name( basic_entry, "gonna-fail" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_TRUE( result == NULL );

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
    EXPECT_NE( basic_entry->app_name, previous_app_name );

    EXPECT_EQ( basic_entry->app_name_length, 1 );
    EXPECT_EQ( 0, strcmp( basic_entry->app_name, "-" ) );
  }

  TEST_F( EntryTest, SetElement ) {
    struct stumpless_element *new_element;
    const struct stumpless_element *previous_element;
    const struct stumpless_entry *result;

    new_element = stumpless_new_element( "new-element" );
    ASSERT_TRUE( new_element != NULL );

    previous_element = stumpless_get_element_by_index( basic_entry, 0 );

    result = stumpless_set_element( basic_entry, 0, new_element );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, basic_entry );
    EXPECT_NE( stumpless_get_element_by_index( basic_entry, 0 ),
               previous_element );

    stumpless_destroy_element( previous_element );
  }

  TEST_F( EntryTest, SetElementDuplicateName ) {
    struct stumpless_element *new_element;
    const struct stumpless_element *previous_element;
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    new_element = stumpless_new_element( element_1_name );
    ASSERT_TRUE( new_element != NULL );

    previous_element = stumpless_get_element_by_index( basic_entry, 0 );

    result = stumpless_set_element( basic_entry, 0, new_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_DUPLICATE_ELEMENT );
    EXPECT_TRUE( result == NULL );
    EXPECT_EQ( stumpless_get_element_by_index( basic_entry, 0 ),
               previous_element );

    stumpless_destroy_element( new_element );
  }

  TEST_F( EntryTest, SetElementIndexOutOfBounds ) {
    struct stumpless_element *new_element;
    const struct stumpless_element *previous_element;
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    new_element = stumpless_new_element( "new-element" );
    ASSERT_TRUE( new_element != NULL );

    previous_element = stumpless_get_element_by_index( basic_entry, 0 );

    result = stumpless_set_element( basic_entry, 200, new_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, 200 );
    EXPECT_TRUE( result == NULL );
    EXPECT_EQ( stumpless_get_element_by_index( basic_entry, 0 ),
               previous_element );

    stumpless_destroy_element( new_element );
  }

  TEST_F( EntryTest, SetElementNullElement ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_element( basic_entry, 0, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
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
    const struct stumpless_error *error;

    previous_facility = stumpless_get_entry_facility( basic_entry );

    result = stumpless_set_entry_facility( basic_entry,
                                           -66 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );
    EXPECT_EQ( error->code, -66 );
    EXPECT_TRUE( result == NULL );
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
    const struct stumpless_error *error;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_TRUE( set_malloc_result != NULL );

    result = stumpless_set_entry_msgid( basic_entry, "gonna-fail" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_TRUE( result == NULL );

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
    EXPECT_NE( basic_entry->msgid, previous_msgid );

    EXPECT_EQ( basic_entry->msgid_length, 1 );
    EXPECT_EQ( 0, strcmp( basic_entry->msgid, "-" ) );
  }

  TEST_F( EntryTest, SetPriorityInvalidFacility ) {
    int previous_prival;
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    previous_prival = stumpless_get_entry_prival( basic_entry );

    result = stumpless_set_entry_priority( basic_entry,
                                           -66,
                                           STUMPLESS_SEVERITY_EMERG );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_FACILITY );
    EXPECT_EQ( error->code, -66 );
    EXPECT_TRUE( result == NULL );
    EXPECT_EQ( stumpless_get_entry_prival( basic_entry ), previous_prival );
  }

  TEST_F( EntryTest, SetPriorityInvalidSeverity ) {
    int previous_prival;
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    previous_prival = stumpless_get_entry_prival( basic_entry );

    result = stumpless_set_entry_priority( basic_entry,
                                           STUMPLESS_FACILITY_LOCAL5,
                                           -66 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
    EXPECT_EQ( error->code, -66 );
    EXPECT_TRUE( result == NULL );
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
    const struct stumpless_error *error;

    previous_severity = stumpless_get_entry_severity( basic_entry );

    result = stumpless_set_entry_severity( basic_entry,
                                           -66 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );
    EXPECT_EQ( error->code, -66 );
    EXPECT_TRUE( result == NULL );
    EXPECT_EQ( stumpless_get_entry_severity( basic_entry ), previous_severity );
  }

  /* non-fixture tests */

  TEST( AddElementTest, NullEntry ){
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    const struct stumpless_error *error;

    element = stumpless_new_element( "test-new-element" );
    ASSERT_TRUE( element != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    entry = stumpless_add_element( NULL, element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    ASSERT_TRUE( entry == NULL );

    stumpless_destroy_element( element );
  }

  TEST( CopyEntry, NullEntry ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_copy_entry( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( DestroyEntryOnlyTest, NullEntry ) {
    stumpless_destroy_entry_only( NULL );
  }

  TEST( DestroyEntryOnlyTest, OneElement ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    const char *element_name = "test-element-name";

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "test-app-name",
                                 "test-msgid",
                                 "test message" );
    ASSERT_TRUE( entry != NULL );

    element = stumpless_new_element( element_name );
    EXPECT_NO_ERROR;
    ASSERT_TRUE( element != NULL );

    stumpless_destroy_entry_only( entry );

    ASSERT_TRUE( memcmp( element->name,
                         element_name,
                         element->name_length ) == 0 );

    stumpless_destroy_element_and_contents( element );
  }

  TEST( DestroyEntryTest, NullEntry ) {
    stumpless_destroy_entry( NULL );
  }

  TEST( GetElementByIndexTest, NullEntry ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_get_element_by_index( NULL, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( GetElementByNameTest, NullEntry ) {
    const struct stumpless_element *result;
    const struct stumpless_error *error;

    result = stumpless_get_element_by_name( NULL, "irrelevant" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( GetElementIndex, NullEntry ) {
    size_t result;
    const struct stumpless_error *error;

    result = stumpless_get_element_index( NULL, "irrelevant" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, 0 );
  }

  TEST( GetAppName, NullEntry ) {
    const char *result;
    const struct stumpless_error *error;

    result = stumpless_get_entry_app_name( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( GetFacilityTest, NullEntry ) {
    int result;
    const struct stumpless_error *error;

    result = stumpless_get_entry_facility( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, -1 );
  }

  TEST( GetMsgid, NullEntry ) {
    const char *result;
    const struct stumpless_error *error;

    result = stumpless_get_entry_msgid( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( GetPrivalTest, NullEntry ) {
    int result;
    const struct stumpless_error *error;

    result = stumpless_get_entry_prival( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, -1 );
  }

  TEST( GetSeverityTest, NullEntry ) {
    int result;
    const struct stumpless_error *error;

    result = stumpless_get_entry_severity( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_EQ( result, -1 );
  }

  TEST( HasElementTest, NullEntry ) {
    bool result;
    const struct stumpless_error *error;

    result = stumpless_entry_has_element( NULL, "irrelevant" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_FALSE( result );
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
    EXPECT_TRUE( entry != NULL );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );
    EXPECT_TRUE( entry->message != NULL );

    expected_message_length = strlen( expected_message );
    EXPECT_EQ( entry->message_length, expected_message_length );
    EXPECT_EQ( 0, memcmp( entry->message, expected_message, entry->message_length ) );

    stumpless_destroy_entry( entry );
  }

  TEST( NewEntryTest, MallocFailureOnMsgid ) {
    void *(*set_malloc_result)(size_t);
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid-of-unique-length";
    const char *message = "test-message";
    struct stumpless_entry *result;
    const struct stumpless_error *error;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL_ON_SIZE( 28 ) );
    ASSERT_TRUE( set_malloc_result != NULL );

    result = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                  STUMPLESS_SEVERITY_INFO,
                                  app_name,
                                  msgid,
                                  message );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_TRUE( result == NULL );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST( NewEntryTest, MallocFailureOnSecond ) {
    struct stumpless_entry *first_entry;
    struct stumpless_entry *second_entry;
    const struct stumpless_error *error;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";
    void *(*set_malloc_result)(size_t);

    // create at least one entry to allow the cache to initialize
    first_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       msgid,
                                       message );
    ASSERT_TRUE( first_entry != NULL );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_TRUE( set_malloc_result != NULL );

    second_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                        STUMPLESS_SEVERITY_INFO,
                                        app_name,
                                        msgid,
                                        message );

    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_TRUE( second_entry == NULL );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry( second_entry );
    stumpless_destroy_entry( first_entry );
  }

  TEST( NewEntryTest, MoreThan500Entries ) {
    struct stumpless_entry *entry[500];
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    size_t app_name_length = strlen( app_name );
    size_t msgid_length = strlen( msgid );
    size_t message_length = strlen( message );
    size_t i;

    for( i = 0; i < 500; i++ ) {
      entry[i] = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                      STUMPLESS_SEVERITY_INFO,
                                      app_name,
                                      msgid,
                                      message );

      EXPECT_NO_ERROR;

      EXPECT_TRUE( entry[i] != NULL );
    }

    for( i = 0; i < 500; i++ ) {
      stumpless_destroy_entry( entry[i] );
    }

  }

  TEST( NewEntryTest, New ){
    struct stumpless_entry *entry;
    const char *app_name = "test-app-name";
    const char *msgid = "test-msgid";
    const char *message = "test-message";

    size_t app_name_length = strlen( app_name );
    size_t msgid_length = strlen( msgid );
    size_t message_length = strlen( message );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 app_name,
                                 msgid,
                                 message );

    EXPECT_NO_ERROR;

    ASSERT_TRUE( entry != NULL );
    EXPECT_EQ( STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO, entry->prival );
    EXPECT_EQ( NULL, entry->elements );
    EXPECT_EQ( 0, entry->element_count );

    ASSERT_EQ( app_name_length, entry->app_name_length );
    ASSERT_TRUE( entry->app_name != NULL );
    ASSERT_EQ( 0, memcmp( entry->app_name, app_name, app_name_length ) );

    ASSERT_EQ( msgid_length, entry->msgid_length );
    ASSERT_TRUE( entry->msgid != NULL );
    ASSERT_EQ( 0, memcmp( entry->msgid, msgid, msgid_length ) );

    ASSERT_EQ( message_length, entry->message_length );
    ASSERT_TRUE( entry->message != NULL );
    ASSERT_EQ( 0, memcmp( entry->message, message, message_length ) );

    stumpless_destroy_entry( entry );
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
    EXPECT_TRUE( entry != NULL );

    if( entry ) {
      EXPECT_EQ( entry->app_name[0], '-' );
      EXPECT_EQ( entry->app_name_length, 1 );
    }

    stumpless_destroy_entry( entry );
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
    EXPECT_TRUE( entry != NULL );

    if( entry ) {
      EXPECT_EQ( entry->message_length, 0 );
    }

    stumpless_destroy_entry( entry );
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
    EXPECT_TRUE( entry != NULL );

    if( entry ) {
      EXPECT_EQ( entry->msgid[0], '-' );
      EXPECT_EQ( entry->msgid_length, 1 );
    }

    stumpless_destroy_entry( entry );
  }

  TEST( NewEntryTest, ReallocFailureOnSecond ) {
    struct stumpless_entry *entries[2000];
    const struct stumpless_error *error;
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
    ASSERT_TRUE( entries[0] != NULL );

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_TRUE( set_realloc_result != NULL );

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
    while( i > 0 ) {
      stumpless_destroy_entry( entries[i] );
      i--;
    }
  }

  TEST( SetAppNameTest, NullEntry ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_entry_app_name( NULL, "new-app-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( SetElementTest, NullEntry ) {
    struct stumpless_element *new_element;
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    new_element = stumpless_new_element( "new-element" );
    ASSERT_TRUE( new_element != NULL );

    result = stumpless_set_element( NULL, 0, new_element );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );

    stumpless_destroy_element( new_element );
  }

  TEST( SetFacilityTest, NullEntry ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_entry_facility( NULL, STUMPLESS_FACILITY_USER );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( SetMsgidTest, NullEntry ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_entry_msgid( NULL, "new-app-name" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( SetMessageTest, NullEntry ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_entry_message( NULL, "test-message" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( SetMessageTest, NullMessage ) {
    struct stumpless_entry *entry;
    const struct stumpless_entry *result;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "test-app-name",
                                 "test-msgid",
                                 "test-message" );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( entry != NULL );

    result = stumpless_set_entry_message( entry, NULL );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry, result );

    EXPECT_TRUE( entry->message == NULL );
    EXPECT_EQ( 0, entry->message_length );

    stumpless_destroy_entry( entry );
  }

  TEST( SetPrivalTest, NullEntry ) {
    int prival = STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO;
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_entry_prival( NULL, prival );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }

  TEST( SetSeverityTest, NullEntry ) {
    const struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_entry_severity( NULL, STUMPLESS_SEVERITY_INFO );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_TRUE( result == NULL );
  }
}
