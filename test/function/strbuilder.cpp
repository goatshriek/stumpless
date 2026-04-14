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

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"

namespace {

  class StrbuilderTest : public::testing::Test {
    protected:
      struct stumpless_entry *basic_entry;
      struct stumpless_target *target;
      char buffer[8096];

      virtual void
      SetUp( void ) {
        basic_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                               STUMPLESS_SEVERITY_INFO,
                                               "strbuilder-test-app",
                                               "strbuilder-test-msgid",
                                               "test message for strbuilder" );
        ASSERT_NOT_NULL( basic_entry );

        target = stumpless_open_buffer_target( "strbuilder-buffer-target",
                                               buffer,
                                               sizeof( buffer ) );
        ASSERT_NOT_NULL( target );

        stumpless_set_option( target, STUMPLESS_OPTION_PID );
      }

      virtual void
      TearDown( void ) {
        stumpless_destroy_entry_and_contents( basic_entry );
        stumpless_close_buffer_target( target );
        stumpless_free_all(  );
        memset( buffer, 0, sizeof( buffer ) );
      }
  };

  TEST_F( StrbuilderTest, AppendAppName ) {
    const char *original_app_name;
    const char *new_app_name;

    original_app_name = stumpless_get_entry_app_name( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( original_app_name );
    free( ( void * ) original_app_name );

    stumpless_set_entry_app_name( basic_entry, "new-test-app" );
    EXPECT_NO_ERROR;

    new_app_name = stumpless_get_entry_app_name( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_THAT( new_app_name, testing::HasSubstr( "new-test-app" ) );
    free( ( void * ) new_app_name );
  }

  TEST_F( StrbuilderTest, AppendBufferWithElements ) {
    int result;

    stumpless_add_new_element( basic_entry, "element-one" );
    stumpless_add_new_param_to_entry( basic_entry,
                                      "element-one",
                                      "param-name",
                                      "param-value" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( "strbuilder-test-app" ) );
    EXPECT_THAT( buffer, testing::HasSubstr( "element-one" ) );
    EXPECT_THAT( buffer, testing::HasSubstr( "param-name" ) );
    EXPECT_THAT( buffer, testing::HasSubstr( "param-value" ) );
  }

  TEST_F( StrbuilderTest, AppendCharSpecialCharacters ) {
    const char *hostname;
    const char *procid;

    stumpless_set_entry_hostname( basic_entry, "my-test-host" );
    EXPECT_NO_ERROR;

    stumpless_set_entry_procid( basic_entry, "12345" );
    EXPECT_NO_ERROR;

    hostname = stumpless_get_entry_hostname( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_THAT( hostname, testing::HasSubstr( "my-test-host" ) );
    free( ( void * ) hostname );

    procid = stumpless_get_entry_procid( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_THAT( procid, testing::HasSubstr( "12345" ) );
    free( ( void * ) procid );
  }

  TEST_F( StrbuilderTest, AppendEmptyMessage ) {
    int result;

    stumpless_set_entry_message( basic_entry, NULL );
    EXPECT_NO_ERROR;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;
  }

  TEST_F( StrbuilderTest, AppendHostname ) {
    const char *hostname;
    const char *original_hostname;

    original_hostname = stumpless_get_entry_hostname( basic_entry );
    ASSERT_NOT_NULL( original_hostname );
    free( ( void * ) original_hostname );

    stumpless_set_entry_hostname( basic_entry, "custom-hostname" );
    EXPECT_NO_ERROR;

    hostname = stumpless_get_entry_hostname( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_THAT( hostname, testing::HasSubstr( "custom-hostname" ) );
    free( ( void * ) hostname );
  }

  TEST_F( StrbuilderTest, AppendHostnameMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *hostname;
    struct stumpless_entry *entry;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    hostname = stumpless_get_entry_hostname( entry );
    EXPECT_NULL( hostname );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( StrbuilderTest, AppendMessage ) {
    int result;
    const char *new_message = "modified test message";

    stumpless_set_entry_message( basic_entry, new_message );
    EXPECT_NO_ERROR;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( new_message ) );
  }

  TEST_F( StrbuilderTest, AppendMessageMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *message;
    struct stumpless_entry *entry;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    message = stumpless_get_entry_message( entry );
    EXPECT_NULL( message );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( StrbuilderTest, AppendMsgid ) {
    int result;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( "strbuilder-test-msgid" ) );
  }

  TEST_F( StrbuilderTest, AppendMsgidMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *msgid;
    struct stumpless_entry *entry;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    msgid = stumpless_get_entry_msgid( entry );
    EXPECT_NULL( msgid );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( StrbuilderTest, AppendPositiveInt ) {
    const char *procid;
    int original_prival;
    struct stumpless_entry *entry;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    procid = stumpless_get_entry_procid( entry );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( procid );
    free( ( void * ) procid );

    original_prival = stumpless_get_entry_prival( entry );

    stumpless_set_entry_prival( entry, STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO );
    EXPECT_NO_ERROR;
    EXPECT_EQ( stumpless_get_entry_prival( entry ),
               STUMPLESS_FACILITY_USER | STUMPLESS_SEVERITY_INFO );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( StrbuilderTest, AppendProcid ) {
    const char *procid;

    stumpless_set_entry_procid( basic_entry, "99999" );
    EXPECT_NO_ERROR;

    procid = stumpless_get_entry_procid( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_THAT( procid, testing::HasSubstr( "99999" ) );
    free( ( void * ) procid );
  }

  TEST_F( StrbuilderTest, AppendProcidMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    const char *procid;
    struct stumpless_entry *entry;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    procid = stumpless_get_entry_procid( entry );
    EXPECT_NULL( procid );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( StrbuilderTest, AppendString ) {
    int result;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( "test message for strbuilder" ) );
  }

  TEST_F( StrbuilderTest, AppendStructuredData ) {
    int result;

    stumpless_add_new_element( basic_entry, "test-element" );
    stumpless_add_new_param_to_entry( basic_entry,
                                      "test-element",
                                      "test-param",
                                      "test-value" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( "[test-element test-param=\"test-value\"]" ) );
  }

  TEST_F( StrbuilderTest, AppendStructuredDataEmpty ) {
    int result;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( "- " ) );
  }

  TEST_F( StrbuilderTest, AppendStructuredDataMultipleElements ) {
    int result;

    stumpless_add_new_element( basic_entry, "element-a" );
    stumpless_add_new_param_to_entry( basic_entry,
                                      "element-a",
                                      "param-a",
                                      "value-a" );

    stumpless_add_new_element( basic_entry, "element-b" );
    stumpless_add_new_param_to_entry( basic_entry,
                                      "element-b",
                                      "param-b",
                                      "value-b" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( "[element-a param-a=\"value-a\"]" ) );
    EXPECT_THAT( buffer, testing::HasSubstr( "[element-b param-b=\"value-b\"]" ) );
  }

  TEST_F( StrbuilderTest, GetBuffer ) {
    int result;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;
    EXPECT_GT( strlen( buffer ), 0 );
  }

  TEST_F( StrbuilderTest, GetBufferLength ) {
    int result;
    size_t length_before;
    size_t length_after;
    char read_buffer[1024];
    struct stumpless_entry *second_entry;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    memset( read_buffer, 0, sizeof( read_buffer ) );
    stumpless_read_buffer( target, read_buffer, sizeof( read_buffer ) );
    length_before = strlen( read_buffer );

    second_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                            STUMPLESS_SEVERITY_INFO,
                                            "strbuilder-test-app",
                                            "strbuilder-test-msgid",
                                            "longer message that should increase the buffer size" );
    ASSERT_NOT_NULL( second_entry );

    result = stumpless_add_entry( target, second_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    memset( read_buffer, 0, sizeof( read_buffer ) );
    stumpless_read_buffer( target, read_buffer, sizeof( read_buffer ) );
    length_after = strlen( read_buffer );
    EXPECT_GT( length_after, length_before );

    stumpless_destroy_entry_and_contents( second_entry );
  }

  TEST_F( StrbuilderTest, LongMessage ) {
    int result;
    const char *long_message = "This is a very long message that should thoroughly test the "
                               "strbuilder's ability to handle buffer growth and reallocation. "
                               "It contains multiple words and should trigger the internal "
                               "buffer expansion logic as the strbuilder needs to dynamically "
                               "grow its internal buffer to accommodate all this content.";

    stumpless_set_entry_message( basic_entry, long_message );
    EXPECT_NO_ERROR;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( long_message ) );
  }

  TEST_F( StrbuilderTest, MultiByteCharacters ) {
    int result;
    const char *message_with_multibyte = "Hello 你好 мир";

    stumpless_set_entry_message( basic_entry, message_with_multibyte );
    EXPECT_NO_ERROR;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;
  }

  TEST_F( StrbuilderTest, NullHostname ) {
    const char *hostname;

    stumpless_set_entry_hostname( basic_entry, NULL );
    EXPECT_NO_ERROR;

    hostname = stumpless_get_entry_hostname( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_THAT( hostname, testing::HasSubstr( "-" ) );
    free( ( void * ) hostname );
  }

  TEST_F( StrbuilderTest, NullProcid ) {
    const char *procid;

    stumpless_set_entry_procid( basic_entry, NULL );
    EXPECT_NO_ERROR;

    procid = stumpless_get_entry_procid( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( procid );

    free( ( void * ) procid );
  }

  TEST_F( StrbuilderTest, PrivalFormatting ) {
    int result;

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    EXPECT_THAT( buffer, testing::HasSubstr( "<14>" ) );
  }

  TEST_F( StrbuilderTest, ResetBuilder ) {
    int result1;
    int result2;
    struct stumpless_entry *second_entry;
    const char *first_msg = "test message for strbuilder";
    const char *second_msg = "second message";
    char *current;
    char *end;
    bool found_first = false;
    bool found_second = false;

    result1 = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result1, 0 );
    EXPECT_NO_ERROR;

    second_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                            STUMPLESS_SEVERITY_INFO,
                                            "strbuilder-test-app",
                                            "strbuilder-test-msgid",
                                            "second message" );
    ASSERT_NOT_NULL( second_entry );

    result2 = stumpless_add_entry( target, second_entry );
    EXPECT_GE( result2, 0 );
    EXPECT_NO_ERROR;

    current = buffer;
    end = buffer + sizeof( buffer );
    while ( current < end ) {
      char *segment_end = ( char * ) memchr( current, '\0', end - current );
      if ( !segment_end )
        break;
      size_t seg_len = segment_end - current;
      if ( seg_len > 0 ) {
        if ( strstr( current, first_msg ) )
          found_first = true;
        if ( strstr( current, second_msg ) )
          found_second = true;
      }
      current = segment_end + 1;
    }
    EXPECT_TRUE( found_first );
    EXPECT_TRUE( found_second );

    stumpless_destroy_entry_and_contents( second_entry );
  }

  TEST_F( StrbuilderTest, Rfc5424Format ) {
    int result;
    char read_buffer[2048];
    size_t read_result;
    struct stumpless_entry *formatted_entry;

    formatted_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                              STUMPLESS_SEVERITY_INFO,
                                              "strbuilder-test-app",
                                              "strbuilder-test-msgid",
                                              "test message for strbuilder" );
    ASSERT_NOT_NULL( formatted_entry );

    stumpless_set_entry_hostname( formatted_entry, "test-host" );
    stumpless_set_entry_procid( formatted_entry, "1234" );
    stumpless_add_new_element( formatted_entry, "sd-element" );
    stumpless_add_new_param_to_entry( formatted_entry,
                                      "sd-element",
                                      "key",
                                      "value" );

    result = stumpless_add_entry( target, formatted_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    read_result = stumpless_read_buffer( target, read_buffer, sizeof( read_buffer ) );
    EXPECT_GT( read_result, 0 );

    EXPECT_THAT( read_buffer, testing::HasSubstr( "<14>1 " ) );
    EXPECT_THAT( read_buffer, testing::HasSubstr( "test-host " ) );
    EXPECT_THAT( read_buffer, testing::HasSubstr( "strbuilder-test-app " ) );
    EXPECT_THAT( read_buffer, testing::HasSubstr( "strbuilder-test-msgid " ) );
    EXPECT_THAT( read_buffer, testing::HasSubstr( "[sd-element key=\"value\"]" ) );

    stumpless_destroy_entry_and_contents( formatted_entry );
  }

  TEST_F( StrbuilderTest, ToStringEntry ) {
    char *entry_str;

    entry_str = stumpless_entry_to_string( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry_str );

    EXPECT_THAT( entry_str, testing::HasSubstr( "strbuilder-test-app" ) );
    EXPECT_THAT( entry_str, testing::HasSubstr( "strbuilder-test-msgid" ) );
    EXPECT_THAT( entry_str, testing::HasSubstr( "test message for strbuilder" ) );

    free( entry_str );
  }

  TEST_F( StrbuilderTest, ToStringEntryWithElements ) {
    char *entry_str;

    stumpless_add_new_element( basic_entry, "my-element" );
    stumpless_add_new_param_to_entry( basic_entry,
                                      "my-element",
                                      "my-param",
                                      "my-value" );

    entry_str = stumpless_entry_to_string( basic_entry );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( entry_str );

    EXPECT_THAT( entry_str, testing::HasSubstr( "my-element" ) );
    EXPECT_THAT( entry_str, testing::HasSubstr( "my-param" ) );
    EXPECT_THAT( entry_str, testing::HasSubstr( "my-value" ) );

    free( entry_str );
  }

  TEST_F( StrbuilderTest, ToStringEntryMemoryFailure ) {
    void * (*set_malloc_result)(size_t);
    char *entry_str;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    entry_str = stumpless_entry_to_string( basic_entry );
    EXPECT_NULL( entry_str );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( StrbuilderTest, ToStringEntryNullEntry ) {
    char *entry_str;

    entry_str = stumpless_entry_to_string( NULL );
    EXPECT_NULL( entry_str );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( StrbuilderTest, ZeroLengthElements ) {
    int result;

    stumpless_set_entry_message_str( basic_entry, "" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
  }

  /* non-fixture tests */

  TEST( StrbuilderFreeAllTest, NullOperation ) {
    stumpless_free_all(  );
  }

  TEST( StrbuilderFreeAllTest, AfterMultipleAllocations ) {
    struct stumpless_entry *entries[10];
    size_t i;

    for( i = 0; i < 10; i++ ) {
      entries[i] = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                            STUMPLESS_SEVERITY_INFO,
                                            "test-app",
                                            "test-msgid",
                                            "test message" );
      ASSERT_NOT_NULL( entries[i] );
    }

    for( i = 0; i < 10; i++ ) {
      stumpless_destroy_entry_and_contents( entries[i] );
    }

    stumpless_free_all(  );
  }
}
