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

#include <stddef.h>
//#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>

namespace {

  class EntryTest : public::testing::Test {
    protected:
      struct stumpless_entry *basic_entry;

      virtual void
      SetUp( void ) {
        basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                           STUMPLESS_SEVERITY_INFO,
                                           "basic-app-name",
                                           "basic-msgid",
                                           "basic message" );
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
  
  TEST_F( EntryTest, AddNullElement ) {
    struct stumpless_entry *entry;
    struct stumpless_error *error;

    entry = stumpless_add_element( basic_entry, NULL );
    ASSERT_TRUE( entry == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
  }

  /* non-fixture tests */

  TEST( NewElementTest, NullName ) {
    struct stumpless_element *element;
    struct stumpless_error *error;

    element = stumpless_new_element( NULL );    
    EXPECT_TRUE( element == NULL );

    error = stumpless_get_error(  );
    ASSERT_TRUE( error != NULL );
    EXPECT_EQ( error->id, STUMPLESS_ARGUMENT_EMPTY );
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

    ASSERT_EQ( strlen( msgid ), entry->msgid_length );
    ASSERT_TRUE( entry->msgid != NULL );
    ASSERT_EQ( 0, memcmp( entry->msgid, msgid, msgid_length ) );

    ASSERT_EQ( strlen( message ), entry->message_length );
    ASSERT_TRUE( entry->message != NULL );
    ASSERT_EQ( 0, memcmp( entry->message, message, message_length ) );

    stumpless_destroy_entry( entry );
  }

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
  
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
