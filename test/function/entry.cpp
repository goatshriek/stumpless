// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018 Joel E. Anderson
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

using::testing::HasSubstr;

namespace {

  class EntryTest : public::testing::Test {
    protected:
      struct stumpless_entry *basic_entry;

      virtual void
      SetUp( void ) {
        struct stumpless_element *element;

        basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                           STUMPLESS_SEVERITY_INFO,
                                           "basic-app-name",
                                           "basic-msgid",
                                           "basic message" );

        element = stumpless_new_element( "basic-element" );
        stumpless_add_element( basic_entry, element );

        // cause a failure so that memory allocation tests will still have an
        // error that they can return
        stumpless_new_element( NULL );
      }

      virtual void
      TearDown( void ){
        stumpless_destroy_entry( basic_entry );
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

  TEST_F( EntryTest, AddElementMemoryFailure ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    struct stumpless_error *error;
    void * (*set_realloc_result)(void *, size_t);

    element = stumpless_new_element( "test-memory-failure" );
    ASSERT_TRUE( element != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
   
    set_realloc_result = stumpless_set_realloc( [](void *, size_t)->void *{ return NULL; } );
    ASSERT_TRUE( set_realloc_result != NULL );
 
    entry = stumpless_add_element( basic_entry, element );
    EXPECT_EQ( NULL, entry );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    set_realloc_result = stumpless_set_realloc( realloc );
    EXPECT_TRUE( set_realloc_result == realloc );
  }
  
  TEST_F( EntryTest, AddNullElement ) {
    struct stumpless_entry *entry;
    struct stumpless_error *error;

    entry = stumpless_add_element( basic_entry, NULL );
    ASSERT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( EntryTest, AddNullParam ) {
    struct stumpless_element *element, *result;
    struct stumpless_error *error;

    element = basic_entry->elements[0];
    ASSERT_TRUE( element != NULL );

    result = stumpless_add_param( element, NULL );
    ASSERT_TRUE( result == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );

    // todo test to make sure that param count has not changed
  }

  TEST_F( EntryTest, AddParam ) {
    struct stumpless_element *element, *result;
    struct stumpless_param *param;

    element = basic_entry->elements[0];
    ASSERT_TRUE( element != NULL );
    
    param = stumpless_new_param( "test-param-name", "test-param-value" );
    ASSERT_TRUE( param != NULL );

    result = stumpless_add_param( element, param );
    EXPECT_EQ( element, result );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
   
    // todo test that param count has increased 
    // todo test to make sure that new param actually exists
  }

  TEST_F( EntryTest, AddParamMemoryFailure ) {
    struct stumpless_element *element, *result;
    struct stumpless_param *param;
    struct stumpless_error *error;
    void * (*set_realloc_result)(void *, size_t);

    element = basic_entry->elements[0];
    ASSERT_TRUE( element != NULL );
    
    param = stumpless_new_param( "test-param-name", "test-param-value" );
    ASSERT_TRUE( param != NULL );
   
    set_realloc_result = stumpless_set_realloc( [](void *, size_t)->void *{ return NULL; } );
    ASSERT_TRUE( set_realloc_result != NULL );

    result = stumpless_add_param( element, param );
    EXPECT_EQ( NULL, result );
    
    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }
   
    stumpless_set_realloc( realloc );
  }
  
  TEST_F( EntryTest, AddTwoElements ) {
    struct stumpless_entry *entry;
    struct stumpless_element *element1, *element2;

    element1 = stumpless_new_element( "test-new-element-1" );
    ASSERT_TRUE( element1 != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    
    entry = stumpless_add_element( basic_entry, element1 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    ASSERT_TRUE( entry != NULL );
    EXPECT_EQ( basic_entry, entry );

    element2 = stumpless_new_element( "test-new-element-2" );
    ASSERT_TRUE( element2 != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    
    entry = stumpless_add_element( basic_entry, element2 );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    ASSERT_TRUE( entry != NULL );
    EXPECT_EQ( basic_entry, entry );
  }

  TEST_F( EntryTest, AddTwoParams ) {
    struct stumpless_element *element, *result;
    struct stumpless_param *param1, *param2;

    element = basic_entry->elements[0];
    ASSERT_TRUE( element != NULL );
    
    param1 = stumpless_new_param( "test-param-name-1", "test-param-value-1" );
    ASSERT_TRUE( param1 != NULL );

    result = stumpless_add_param( element, param1 );
    EXPECT_EQ( element, result );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
    
    param2 = stumpless_new_param( "test-param-name-2", "test-param-value-2" );
    ASSERT_TRUE( param2 != NULL );

    result = stumpless_add_param( element, param2 );
    EXPECT_EQ( element, result );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
   
    // todo test that param count has increased 
    // todo test to make sure that new param actually exists
  }

  TEST_F( EntryTest, SetAppName ) {
    struct stumpless_entry *entry;
    const char *previous_app_name;
    const char *new_app_name = "new-app-name";

    size_t new_app_name_length = strlen( new_app_name );

    previous_app_name = basic_entry->app_name;

    entry = stumpless_set_entry_app_name( basic_entry, new_app_name );
    EXPECT_EQ( entry, basic_entry );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    ASSERT_EQ( new_app_name_length, basic_entry->app_name_length );
    ASSERT_EQ( 0, memcmp( basic_entry->app_name, new_app_name, new_app_name_length ) );
  }

  /* non-fixture tests */

  TEST( AddElementTest, NullEntry ){
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    struct stumpless_error *error;

    element = stumpless_new_element( "test-new-element" );
    ASSERT_TRUE( element != NULL );
    EXPECT_EQ( NULL, stumpless_get_error(  ) );

    entry = stumpless_add_element( NULL, element );
    ASSERT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_element( element );
  }

  TEST( AddParamTest, NullElement ) {
    struct stumpless_param *param;
    struct stumpless_element *element;
    struct stumpless_error *error;

    param = stumpless_new_param( "test-name", "test-value" );
    ASSERT_TRUE( param != NULL );

    element = stumpless_add_param( NULL, param );
    EXPECT_TRUE( element == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );
    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
      EXPECT_THAT( error->message, HasSubstr( "element" ) );
      EXPECT_THAT( error->message, HasSubstr( "NULL" ) );
    }

    stumpless_destroy_param( param );
  }

  TEST( DestroyElementTest, NullElement ) {
    stumpless_destroy_element( NULL );
  }

  TEST( DestroyEntryTest, NullEntry ) {
    stumpless_destroy_entry( NULL );
  }

  TEST( DestroyParamTest, NullParam ) {
    stumpless_destroy_param( NULL );
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

  TEST( NewEntryTest, MallocFailureOnSecond ) {
    struct stumpless_entry *first_entry;
    struct stumpless_entry *second_entry;
    struct stumpless_error *error;
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
   
    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    second_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                        STUMPLESS_SEVERITY_INFO,
                                        app_name,
                                        msgid,
                                        message );

    EXPECT_TRUE( second_entry == NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );

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
      
      EXPECT_EQ( NULL, stumpless_get_error(  ) );
 
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
    
    EXPECT_EQ( NULL, stumpless_get_error(  ) );
 
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

    EXPECT_TRUE( entry != NULL );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    if( entry ) {
      EXPECT_EQ( entry->app_name[0], '-' );
      EXPECT_EQ( entry->app_name_length, 1 );
    }
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

    EXPECT_TRUE( entry != NULL );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    if( entry ) {
      EXPECT_EQ( entry->message_length, 0 );
    }
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

    EXPECT_TRUE( entry != NULL );
    EXPECT_TRUE( stumpless_get_error(  ) == NULL );

    if( entry ) {
      EXPECT_EQ( entry->msgid[0], '-' );
      EXPECT_EQ( entry->msgid_length, 1 );
    }
  }

  TEST( NewEntryTest, ReallocFailureOnSecond ) {
    struct stumpless_entry *entries[2000];
    struct stumpless_error *error;
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
   
    set_realloc_result = stumpless_set_realloc( [](void *, size_t)->void *{ return NULL; } );
    ASSERT_TRUE( set_realloc_result != NULL );

    for( i = 1; i < 2000; i++ ) {
     entries[i] = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                       app_name,
                                       msgid,
                                       message ); 

      if( !entries[i] ) {
        error = stumpless_get_error(  );
        EXPECT_TRUE( error != NULL );

        if( error ) {
          EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
        }

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

  TEST( NewParamTest, MemoryFailure ) {
    struct stumpless_param *param;
    struct stumpless_error *error;
    void *(*result)(size_t);
   
    result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( result != NULL );

    param = stumpless_new_param( "memory-failure", "just-happened" );
    EXPECT_EQ( NULL, param );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    if( error ) {
      EXPECT_EQ( error->id, STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    }

    stumpless_set_malloc( malloc );
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
 
  TEST( SetAppNameTest, NullEntry ) {
    struct stumpless_entry *entry;
    struct stumpless_error *error;

    entry = stumpless_set_entry_app_name( NULL, "new-app-name" );
    ASSERT_EQ( NULL, entry );
    
    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( SetMessageTest, NullEntry ) {
    struct stumpless_entry *result;
    struct stumpless_error *error;

    result = stumpless_set_entry_message( NULL, "test-message" );
    ASSERT_EQ( NULL, result );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

}
