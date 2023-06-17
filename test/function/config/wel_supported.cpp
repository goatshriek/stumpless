// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2022 Joel E. Anderson
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
#include <gtest/gtest.h>
#include <stumpless.h>
#include <wchar.h>
#include <windows.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/function/windows/events.h"

#define BASE_KEY L"SYSTEM\\CurrentControlSet\\Services\\EventLog"

// this is required to allow UTF-8 strings to naturally exist in the tests
#pragma execution_character_set("utf-8")

static
std::vector<std::wstring> *
multi_sz_to_vector( LPCWSTR multi_sz ) {
  std::vector<std::wstring> *vec;
  LPCWSTR current = multi_sz;

  vec = new std::vector<std::wstring>();
  while( *current != L'\0' ) {
    vec->push_back( std::wstring( current ) );

    current += wcslen( current );
    current++;
  }

  return vec;
}

static
bool
registry_key_exists( LPCWSTR key ) {
  LSTATUS query_result;
  HKEY key_handle;
  bool result;

  query_result = RegOpenKeyExW( HKEY_LOCAL_MACHINE,
                                key,
                                0,
                                READ_CONTROL,
                                &key_handle );
  result = query_result != ERROR_FILE_NOT_FOUND;
  CloseHandle( key_handle );

  return result;
}

namespace {
  class WelSupportedTest : public::testing::Test {
    protected:
      struct stumpless_entry *simple_entry = NULL;
      struct stumpless_entry *insertion_entry = NULL;
      struct stumpless_entry *one_insertion_param_entry = NULL;
      struct stumpless_param *insertion_param = NULL;
      LPCSTR first_insertion = "message #1";
      LPCSTR second_insertion = "message #2";
      LPCWSTR first_insertion_w = L"message #1";
      LPCWSTR second_insertion_w = L"message #2";

    virtual void
    SetUp( void ) {
      simple_entry = create_entry(  );

      stumpless_set_wel_category( simple_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( simple_entry, MSG_SIMPLE );
      stumpless_set_wel_type( simple_entry, EVENTLOG_SUCCESS );

      insertion_entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                                 STUMPLESS_SEVERITY_INFO,
                                                 "stumpless-wel-unit-test",
                                                 "insertion-entry",
                                                 "string 1: %1\r\nstring 2: %2" );

      stumpless_set_wel_category( insertion_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( insertion_entry, MSG_TWO_INSERTIONS );
      stumpless_set_wel_type( insertion_entry, EVENTLOG_SUCCESS );

      stumpless_set_wel_insertion_strings( insertion_entry,
                                           2,
                                           first_insertion,
                                           second_insertion );

      one_insertion_param_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                                       STUMPLESS_SEVERITY_INFO,
                                                       "stumpless-wel-unit-test",
                                                       "one-insertion-param-entry",
                                                       "message with one insertion param" );

      stumpless_set_wel_category( one_insertion_param_entry, CATEGORY_TEST );
      stumpless_set_wel_event_id( one_insertion_param_entry, MSG_ONE_INSERTION );
      stumpless_set_wel_type( one_insertion_param_entry, EVENTLOG_SUCCESS );

      insertion_param = stumpless_new_param( "index-0", first_insertion );
      stumpless_set_wel_insertion_param( one_insertion_param_entry,
                                         0,
                                         insertion_param );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_only( simple_entry );
      stumpless_destroy_entry_only( insertion_entry );
      stumpless_destroy_entry_and_contents( one_insertion_param_entry );
      stumpless_destroy_param( insertion_param );
    }
  };

  TEST_F( WelSupportedTest, CopyEntry ) {
    const struct stumpless_entry *copy;

    copy = stumpless_copy_entry( simple_entry );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( copy );

    EXPECT_EQ( stumpless_get_wel_category( copy ),
               stumpless_get_wel_category( simple_entry ) );

    EXPECT_EQ( stumpless_get_wel_event_id( copy ),
               stumpless_get_wel_event_id( simple_entry ) );

    EXPECT_EQ( stumpless_get_wel_type( copy ),
               stumpless_get_wel_type( simple_entry ) );

    stumpless_destroy_entry_only( copy );
  }

  TEST_F( WelSupportedTest, GetCategory ) {
    WORD result;

    result = stumpless_get_wel_category( simple_entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, CATEGORY_TEST );
  }

  TEST_F( WelSupportedTest, GetEventId ) {
    DWORD result;

    result = stumpless_get_wel_event_id( simple_entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, MSG_SIMPLE );
  }

  TEST_F( WelSupportedTest, GetInsertionParam ) {
    const struct stumpless_param *result;

    result = stumpless_get_wel_insertion_param( one_insertion_param_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result == insertion_param );
  }

  TEST_F( WelSupportedTest, GetInsertionParamIndexTooHigh ) {
    const struct stumpless_param *result;
    WORD index = 4;
    const struct stumpless_error *error;

    result = stumpless_get_wel_insertion_param( one_insertion_param_entry, index );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, index );
  }

  TEST_F( WelSupportedTest, GetInsertionParamStringSetInstead ) {
    const struct stumpless_param *result;

    result = stumpless_get_wel_insertion_param( insertion_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_NULL( result );
  }

  TEST_F( WelSupportedTest, GetInsertionStringIndexTooHigh ) {
    LPCSTR result;
    WORD index = 4;
    const struct stumpless_error *error;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string( insertion_entry, index );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, index );
  }

  TEST_F( WelSupportedTest, GetInsertionStringWIndexTooHigh ) {
    LPCWSTR result;
    WORD index = 4;
    const struct stumpless_error *error;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string_w( insertion_entry, index );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, index );
  }

  TEST_F( WelSupportedTest, GetInsertionStringFirstString ) {
    LPCSTR result;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string( insertion_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    EXPECT_TRUE( result != first_insertion );
    EXPECT_STREQ( result, first_insertion );
  }

  TEST_F( WelSupportedTest, GetInsertionStringLastString ) {
    LPCSTR result;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string( insertion_entry, 1 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    EXPECT_TRUE( result != second_insertion );
    EXPECT_STREQ( result, second_insertion );
  }

  TEST_F( WelSupportedTest, GetInsertionStringWFirstString ) {
    LPCWSTR result;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string_w( insertion_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    EXPECT_TRUE( ( void * ) result != ( void * ) first_insertion );
    EXPECT_STREQ( result, first_insertion_w );
  }

  TEST_F( WelSupportedTest, GetInsertionStringWLastString ) {
    LPCWSTR result;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string_w( insertion_entry, 1 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( result );

    EXPECT_TRUE( ( void * ) result != ( void * ) second_insertion );
    EXPECT_STREQ( result, second_insertion_w );
  }

  TEST_F( WelSupportedTest, GetInsertionStringNullEntry ) {
    LPCSTR result;
    const struct stumpless_error *error;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string( NULL, 1 );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( WelSupportedTest, GetInsertionStringWNullEntry ) {
    LPCWSTR result;
    const struct stumpless_error* error;

    ASSERT_NOT_NULL( insertion_entry );

    result = stumpless_get_wel_insertion_string_w( NULL, 1 );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( WelSupportedTest, GetType ) {
    WORD result;

    result = stumpless_get_wel_type( simple_entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( result, EVENTLOG_SUCCESS );
  }

  TEST_F( WelSupportedTest, SetNullInsertionParam ) {
    const struct stumpless_entry *entry_result;
    const struct stumpless_param *param_result;
    LPCSTR str_result;

    entry_result = stumpless_set_wel_insertion_param( simple_entry, 0, NULL );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( entry_result == simple_entry );

    param_result = stumpless_get_wel_insertion_param( simple_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_NULL( param_result );

    str_result = stumpless_get_wel_insertion_string( simple_entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_NULL( str_result );
  }

  TEST_F( WelSupportedTest, SetNullInsertionString ) {
    const struct stumpless_error *error;
    const struct stumpless_entry *entry_result;

    entry_result = stumpless_set_wel_insertion_string( simple_entry, 0, NULL );
    EXPECT_NULL( entry_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( WelSupportedTest, SetWNullInsertionString ) {
    const struct stumpless_error *error;
    const struct stumpless_entry *entry_result;

    entry_result = stumpless_set_wel_insertion_string_w( simple_entry, 0, NULL );
    EXPECT_NULL( entry_result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST_F( WelSupportedTest, InvalidUtf8InsertionString ) {
    const struct stumpless_error *error;
    const struct stumpless_entry *entry_result;
    LPCSTR invalid_utf8_string = "\xc3\x28 invalid";

    entry_result = stumpless_set_wel_insertion_string( insertion_entry, 
                                                        0, 
                                                        invalid_utf8_string );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    EXPECT_NULL( entry_result );
  }

  TEST_F( WelSupportedTest, InsertionStringNotModifiedWhenInvalidUtf8StringProvided ) {
    const struct stumpless_error *error;
    const struct stumpless_entry *entry_result;
    LPCSTR valid_string = "valid string";
    LPCSTR invalid_utf8_string = "\xc3\x28 invalid";

    stumpless_set_wel_insertion_string( insertion_entry, 0, valid_string );
    EXPECT_NO_ERROR;

    entry_result = stumpless_set_wel_insertion_string( insertion_entry, 
                                                        0, 
                                                        invalid_utf8_string );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ENCODING );
    EXPECT_NULL( entry_result );

    LPCSTR actual_string = stumpless_get_wel_insertion_string( insertion_entry, 0 );
    
    ASSERT_STREQ( actual_string, valid_string );
  }

  /* 
    Add the test case for invalid utf8 insertion string when insertion string is out of range
  */

  TEST_F ( WelSupportedTest, InsertionIndexNotModifiedWhenInRangeButNotAssigned ) {
    LPCSTR invalid_utf8_string = "\xc3\x28 invalid";
    LPCSTR valid_string = "valid string";

    stumpless_set_wel_insertion_strings( insertion_entry, 2, invalid_utf8_string, NULL );

    stumpless_set_wel_insertion_string( insertion_entry, 1, valid_string );
    EXPECT_NO_ERROR;
    
    LPCSTR insertion_string = stumpless_get_wel_insertion_string( insertion_entry, 1 );

    ASSERT_STREQ( insertion_string, valid_string );
  }

  /* non-fixture tests */

  TEST( GetDefaultTarget, WelSupported ) {
    struct stumpless_target *target;

    target = stumpless_get_default_target(  );
    ASSERT_NOT_NULL( target );

    EXPECT_EQ( target->type, STUMPLESS_WINDOWS_EVENT_LOG_TARGET );
    EXPECT_STREQ( target->name, "Stumpless" );

    stumpless_free_all(  );
  }

  TEST( WelDefaultEvents, Message ) {
    stump_str( "Default message for Stumpless" );
  }

  TEST( WelEntryCategoryTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_category( NULL, CATEGORY_TEST );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryEventIdTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_event_id( NULL, MSG_SIMPLE );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEntryTypeTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_type( NULL, EVENTLOG_SUCCESS );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelEventSource, AddAndRemove ) {
    LPCSTR subkey_name = "StumplessTestSubkey";
    LPCWSTR subkey_name_w = L"StumplessTestSubkey";
    LPCSTR source_name = "StumplessTestSource";
    std::wstring source_name_w( L"StumplessTestSource" );
    DWORD category_count = 5;
    LPCSTR category_file = "%APPDATA%\\è\\category.dll";
    LPCWSTR category_file_w = L"%APPDATA%\\è\\category.dll";
    LPCSTR parameter_file = "%APPDATA%\\è\\parameter.dll";
    LPCWSTR parameter_file_w = L"%APPDATA%\\è\\parameter.dll";
    DWORD types_supported = EVENTLOG_ERROR_TYPE | 
                              EVENTLOG_INFORMATION_TYPE |
                              EVENTLOG_WARNING_TYPE;
    const struct stumpless_error *error;
    LPCWSTR full_key = BASE_KEY L"\\StumplessTestSubkey\\StumplessTestSource";
    LPCWSTR subkey = BASE_KEY L"\\StumplessTestSubkey";
    LPCWSTR event_subkey = BASE_KEY L"\\StumplessTestSubkey"\
                            L"\\StumplessTestSource\\EventMessageFile";
    WCHAR lpcwstr_result[1024]{};
    LSTATUS reg_result;
    std::vector<std::wstring> *sources_vec;
    size_t source_name_count;
    DWORD dword_result;
    DWORD result_size;

    dword_result = stumpless_add_wel_event_source( subkey_name,
                                                   source_name,
                                                   category_count,
                                                   category_file,
                                                   NULL,
                                                   parameter_file,
                                                   types_supported );
    error = stumpless_get_error(  );
    if( error && error->code == ERROR_ACCESS_DENIED ) {
      SUCCEED(  ) << "not enough permissions to install, skipping test";
    } else {
      EXPECT_NO_ERROR;
      EXPECT_EQ( dword_result, ERROR_SUCCESS );
      EXPECT_TRUE( registry_key_exists( full_key ) );

      result_size = sizeof( lpcwstr_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 subkey,
                                 L"Sources",
                                 RRF_RT_REG_MULTI_SZ,
                                 NULL,
                                 lpcwstr_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );

      sources_vec = multi_sz_to_vector( lpcwstr_result );

      // std::count would be cleaner, but may not be available
      source_name_count = 0;
      for( std::wstring str : *sources_vec ) {
        if( str.compare( source_name_w ) == 0 ) {
          source_name_count++;
        }
      }

      EXPECT_EQ( source_name_count, 1 );
      delete sources_vec;
      ASSERT_EQ( source_name_count, 1 );

      result_size = sizeof( dword_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"CategoryCount",
                                 RRF_RT_REG_DWORD,
                                 NULL,
                                 &dword_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size, sizeof( DWORD ) );
      EXPECT_EQ( dword_result, category_count );

      result_size = sizeof( lpcwstr_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"CategoryMessageFile",
                                 RRF_RT_REG_SZ |
                                   RRF_RT_REG_EXPAND_SZ |
                                   RRF_NOEXPAND,
                                 NULL,
                                 lpcwstr_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size,
                 ( wcslen( category_file_w ) + 1 ) * sizeof( WCHAR ) );
      EXPECT_STREQ( lpcwstr_result, category_file_w );

      EXPECT_FALSE( registry_key_exists( event_subkey ) );

      result_size = sizeof( lpcwstr_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"ParameterMessageFile",
                                 RRF_RT_REG_SZ |
                                   RRF_RT_REG_EXPAND_SZ |
                                   RRF_NOEXPAND,
                                 NULL,
                                 lpcwstr_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size,
                 ( wcslen( parameter_file_w ) + 1 ) * sizeof( WCHAR ) );
      EXPECT_STREQ( lpcwstr_result, parameter_file_w );

      result_size = sizeof( dword_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"TypesSupported",
                                 RRF_RT_REG_DWORD,
                                 NULL,
                                 &dword_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size, sizeof( DWORD ) );
      EXPECT_EQ( dword_result, types_supported );

      dword_result = stumpless_remove_wel_event_source( subkey_name,
                                                        source_name );
      EXPECT_NO_ERROR;
      EXPECT_EQ( dword_result, ERROR_SUCCESS );
      EXPECT_FALSE( registry_key_exists( full_key ) );
    }
  }

  TEST( WelEventSourceW, AddAndRemove ) {
    LPCWSTR subkey_name = L"StumplessTestSubkeyW";
    std::wstring source_name( L"StumplessTestSourceW" );
    DWORD category_count = 5;
    LPCWSTR category_file = L"%APPDATA%\\è\\category.dll";
    LPCWSTR parameter_file = L"%APPDATA%\\è\\parameter.dll";
    DWORD types_supported = EVENTLOG_ERROR_TYPE |
                              EVENTLOG_INFORMATION_TYPE |
                              EVENTLOG_WARNING_TYPE;
    const struct stumpless_error *error;
    LPCWSTR full_key = BASE_KEY L"\\StumplessTestSubkeyW\\StumplessTestSourceW";
    LPCWSTR subkey = BASE_KEY L"\\StumplessTestSubkeyW";
    LPCWSTR event_subkey = BASE_KEY L"\\StumplessTestSubkeyW"\
                            L"\\StumplessTestSourceWs\\EventMessageFile";
    WCHAR lpcwstr_result[1024]{};
    LSTATUS reg_result;
    std::vector<std::wstring> *sources_vec;
    size_t source_name_count;
    DWORD dw_result;
    DWORD result_size;

    dw_result = stumpless_add_wel_event_source_w( subkey_name,
                                                  source_name.c_str(  ),
                                                  category_count,
                                                  category_file,
                                                  NULL,
                                                  parameter_file,
                                                  types_supported );
    error = stumpless_get_error(  );
    if( error && error->code == ERROR_ACCESS_DENIED ) {
      SUCCEED(  ) << "not enough permissions to install, skipping test";
    } else {
      EXPECT_NO_ERROR;
      EXPECT_EQ( dw_result, ERROR_SUCCESS );
      EXPECT_TRUE( registry_key_exists( full_key ) );

      result_size = sizeof( lpcwstr_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 subkey,
                                 L"Sources",
                                 RRF_RT_REG_MULTI_SZ,
                                 NULL,
                                 lpcwstr_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );

      sources_vec = multi_sz_to_vector( lpcwstr_result );

      // std::count would be cleaner, but may not be available
      source_name_count = 0;
      for( std::wstring str : *sources_vec ) {
        if( str.compare( source_name ) == 0 ) {
          source_name_count++;
        }
      }

      EXPECT_EQ( source_name_count, 1 );
      delete sources_vec;

      result_size = sizeof( dw_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"CategoryCount",
                                 RRF_RT_REG_DWORD,
                                 NULL,
                                 &dw_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size, sizeof( DWORD ) );
      EXPECT_EQ( dw_result, category_count );

      result_size = sizeof( lpcwstr_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"CategoryMessageFile",
                                 RRF_RT_REG_SZ |
                                   RRF_RT_REG_EXPAND_SZ |
                                   RRF_NOEXPAND,
                                 NULL,
                                 lpcwstr_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size,
                 ( wcslen( category_file ) + 1 ) * sizeof( WCHAR ) );
      EXPECT_STREQ( lpcwstr_result, category_file );

      EXPECT_FALSE( registry_key_exists( event_subkey ) );

      result_size = sizeof( lpcwstr_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"ParameterMessageFile",
                                 RRF_RT_REG_SZ |
                                   RRF_RT_REG_EXPAND_SZ |
                                   RRF_NOEXPAND,
                                 NULL,
                                 lpcwstr_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size,
                 ( wcslen( parameter_file ) + 1 ) * sizeof( WCHAR ) );
      EXPECT_STREQ( lpcwstr_result, parameter_file );

      result_size = sizeof( dw_result );
      reg_result = RegGetValueW( HKEY_LOCAL_MACHINE,
                                 full_key,
                                 L"TypesSupported",
                                 RRF_RT_REG_DWORD,
                                 NULL,
                                 &dw_result,
                                 &result_size );
      EXPECT_EQ( reg_result, ERROR_SUCCESS );
      EXPECT_EQ( result_size, sizeof( DWORD ) );
      EXPECT_EQ( dw_result, types_supported );

      dw_result = stumpless_remove_wel_event_source_w( subkey_name,
                                                       source_name.c_str(  ) );
      EXPECT_NO_ERROR;
      EXPECT_EQ( dw_result, ERROR_SUCCESS );
      EXPECT_FALSE( registry_key_exists( full_key ) );
    }
  }

  TEST( WelEventSource, AddAndRemoveDefault ) {
    DWORD result;
    const struct stumpless_error *error;

    result = stumpless_add_default_wel_event_source(  );
    error = stumpless_get_error(  );
    if( error != NULL && error->code == ERROR_ACCESS_DENIED ) {
      SUCCEED(  ) << "not enough permissions to install, skipping test";
    } else {
      EXPECT_NO_ERROR;
      EXPECT_EQ( result, ERROR_SUCCESS );
      EXPECT_TRUE( registry_key_exists( BASE_KEY L"\\Stumpless\\Stumpless" ) );

      result = stumpless_remove_default_wel_event_source(  );
      EXPECT_NO_ERROR;
      EXPECT_EQ( result, ERROR_SUCCESS );
      EXPECT_FALSE( registry_key_exists( BASE_KEY L"\\Stumpless\\Stumpless" ) );
    }
  }

  TEST( WelGetEntryCategoryTest, DefaultAlertUserCategory ) {
    const struct stumpless_entry *entry;
    WORD result;

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_ALERT,
                                     "wel-supported-test-suite",
                                     "default-category-alert-test",
                                     "testing the default category" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_get_wel_category( entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( STUMPLESS_WEL_EVENT_ALERT, result );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST( WelGetEntryCategoryTest, DefaultInfoUserCategory ) {
    const struct stumpless_entry *entry;
    WORD result;

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "wel-supported-test-suite",
                                     "default-category-info-test",
                                     "testing the default category" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_get_wel_category( entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( STUMPLESS_WEL_EVENT_INFO, result );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST( WelGetEntryCategoryTest, NullEntry ) {
    WORD result;
    const struct stumpless_error *error;

    result = stumpless_get_wel_category( NULL );
    EXPECT_EQ( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelGetEntryEventIdTest, DefaultAlertUserEventId ) {
    const struct stumpless_entry *entry;
    DWORD result;

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_ALERT,
                                     "wel-supported-test-suite",
                                     "default-event-id-alert-test",
                                     "testing the default event id" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_get_wel_event_id( entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( STUMPLESS_WEL_MSG_ERR_USER, result );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST( WelGetEntryEventIdTest, DefaultInfoUserEventId ) {
    const struct stumpless_entry *entry;
    DWORD result;

    entry = stumpless_new_entry_str( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_INFO,
                                     "wel-supported-test-suite",
                                     "default-event-id-info-test",
                                     "testing the default event id" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_get_wel_event_id( entry );
    EXPECT_NO_ERROR;
    EXPECT_EQ( STUMPLESS_WEL_MSG_INFO_USER, result );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST( WelGetEntryEventIdTest, NullEntry ) {
    DWORD result;
    const struct stumpless_error *error;

    result = stumpless_get_wel_event_id( NULL );
    EXPECT_EQ( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelGetEntryInsertionParamTest, NullEntry ) {
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    result = stumpless_get_wel_insertion_param( NULL, 0 );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelGetEntryInsertionParamTest, EmptyEntry ) {
    const struct stumpless_entry *entry;
    WORD index = 0;
    const struct stumpless_param *result;
    const struct stumpless_error *error;

    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    result = stumpless_get_wel_insertion_param( entry, 0 );
    EXPECT_NULL( result );

    EXPECT_ERROR_ID_EQ( STUMPLESS_INDEX_OUT_OF_BOUNDS );
    EXPECT_EQ( error->code, index );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelGetEntryInsertionStringTest, AfterParamSetAndUnset ) {
    struct stumpless_entry *entry;
    const char *str_value = "str value";
    LPCSTR str_result;
    const char *param_value = "param value";
    struct stumpless_param *param;
    const struct stumpless_entry *set_result;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    set_result =  stumpless_set_wel_insertion_string( entry, 1, str_value );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( set_result == entry );

    str_result = stumpless_get_wel_insertion_string( entry, 1 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( str_result );
    EXPECT_STREQ( str_result, str_value );
    free( ( void * ) str_result );

    param = stumpless_new_param( "insertion-string", param_value );
    ASSERT_NOT_NULL( param );

    set_result = stumpless_set_wel_insertion_param( entry, 1, param );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( set_result == entry );

    str_result = stumpless_get_wel_insertion_string( entry, 1 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( str_result );
    EXPECT_STREQ( str_result, param_value );
    free( ( void * ) str_result );

    set_result = stumpless_set_wel_insertion_param( entry, 1, NULL );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( set_result == entry );

    str_result = stumpless_get_wel_insertion_string( entry, 1 );
    EXPECT_NO_ERROR;
    EXPECT_NULL( str_result );

    stumpless_destroy_param( param );
    stumpless_destroy_entry_only( entry );
  }

  TEST( WelGetEntryInsertionStringTest, AfterParamSetAndLogAndUnset ) {
    struct stumpless_entry *entry;
    const char *str_value = "str value";
    LPCSTR str_result;
    const char *param_value = "param value";
    struct stumpless_param *param;
    const struct stumpless_entry *set_result;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    stumpless_set_wel_category( entry, CATEGORY_TEST );
    stumpless_set_wel_event_id( entry, MSG_SIMPLE );
    stumpless_set_wel_type( entry, EVENTLOG_SUCCESS );

    set_result =  stumpless_set_wel_insertion_string( entry, 2, str_value );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( set_result == entry );

    str_result = stumpless_get_wel_insertion_string( entry, 2 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( str_result );
    EXPECT_STREQ( str_result, str_value );
    free( ( void * ) str_result );

    param = stumpless_new_param( "insertion-string", param_value );
    ASSERT_NOT_NULL( param );

    set_result = stumpless_set_wel_insertion_param( entry, 2, param );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( set_result == entry );

    str_result = stumpless_get_wel_insertion_string( entry, 2 );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( str_result );
    EXPECT_STREQ( str_result, param_value );
    free( ( void * ) str_result );

    stumpless_add_entry( stumpless_get_current_target(  ), entry );
    EXPECT_NO_ERROR;

    set_result = stumpless_set_wel_insertion_param( entry, 2, NULL );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( set_result == entry );

    str_result = stumpless_get_wel_insertion_string( entry, 2 );
    EXPECT_NO_ERROR;
    EXPECT_NULL( str_result );

    stumpless_destroy_param( param );
    stumpless_destroy_entry_only( entry );
  }

  TEST( WelGetEntryInsertionStringTest, NotYetAssigned ) {
    struct stumpless_entry *entry;
    LPCSTR result;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    stumpless_set_wel_insertion_string( entry, 1, "index 1 string" );
    EXPECT_NO_ERROR;

    result = stumpless_get_wel_insertion_string( entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_NULL( result );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelGetEntryInsertionStringWTest, NotYetAssigned ) {
    struct stumpless_entry *entry;
    LPCWSTR result;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    stumpless_set_wel_insertion_string_w( entry, 1, L"index 1 string" );
    EXPECT_NO_ERROR;

    result = stumpless_get_wel_insertion_string_w( entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_NULL( result );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelGetEntryTypeTest, NullEntry ) {
    DWORD result;
    const struct stumpless_error *error;

    result = stumpless_get_wel_type( NULL );
    EXPECT_EQ( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetEntryInsertionParamTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;
    struct stumpless_param *param;

    param = stumpless_new_param( "param-name", "param-value" );
    ASSERT_NOT_NULL( param );

    entry = stumpless_set_wel_insertion_param( NULL, 0, param );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_param( param );
  }

  TEST( WelSetInsertionParamTest, SetSingleParam ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;
    struct stumpless_param *param;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    param = stumpless_new_param( "param-name", "param-value" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( param );

    entry_result = stumpless_set_wel_insertion_param( entry, 0, param );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    stumpless_destroy_entry_only( entry );
    stumpless_destroy_param( param );
  }

  TEST( WelSetInsertionParamTest, SetTwoParamsInOrder ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;
    struct stumpless_param *param_1;
    struct stumpless_param *param_2;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    param_1 = stumpless_new_param( "param-1-name", "param-1-value" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( param_1 );

    param_2 = stumpless_new_param( "param-2-name", "param-2-value" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( param_2 );

    entry_result = stumpless_set_wel_insertion_param( entry, 0, param_1 );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    entry_result = stumpless_set_wel_insertion_param( entry, 1, param_2 );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    stumpless_destroy_entry_only( entry );
    stumpless_destroy_param( param_1 );
    stumpless_destroy_param( param_2 );
  }

  TEST( WelSetInsertionParamTest, SetTwoParamsOutOfOrder ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;
    struct stumpless_param *param_1;
    struct stumpless_param *param_2;

    entry = create_empty_entry();
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    param_1 = stumpless_new_param("param-1-name", "param-1-value");
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL(param_1);

    param_2 = stumpless_new_param("param-2-name", "param-2-value");
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL(param_2);

    entry_result = stumpless_set_wel_insertion_string( entry, 1, "second string" );
    EXPECT_NO_ERROR;
    EXPECT_EQ(entry_result, entry);

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "first string" );
    EXPECT_NO_ERROR;
    EXPECT_EQ(entry_result, entry);

    stumpless_destroy_entry_only( entry );
    stumpless_destroy_param( param_1 );
    stumpless_destroy_param( param_2 );
  }

  TEST( WelSetEntryInsertionStringTest, NullEntry ) {
    const struct stumpless_error *error;
    struct stumpless_entry *entry;

    entry = stumpless_set_wel_insertion_string( NULL, 0, "test-string" );
    EXPECT_NULL( entry );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetInsertionStringTest, SetSingleString ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;
    entry = create_empty_entry(  );
    ASSERT_NOT_NULL( entry );

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "testing" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelSetInsertionStringTest, SetTwoStrings ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;

    entry = create_empty_entry(  );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "first string" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    entry_result = stumpless_set_wel_insertion_string( entry, 1, "second string" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelSetInsertionStringTest, SetTwoStringsOutOfOrder ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *entry_result;

    entry = create_empty_entry();
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    entry_result = stumpless_set_wel_insertion_string( entry, 1, "second string" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    entry_result = stumpless_set_wel_insertion_string( entry, 0, "first string" );
    EXPECT_NO_ERROR;
    EXPECT_EQ( entry_result, entry );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelSetInsertionStringsTest, NullEntry ) {
    struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_wel_insertion_strings( NULL, 1, "add me!" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetInsertionStringsTest, NullString ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const struct stumpless_error *error;

    entry = create_empty_entry();
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_wel_insertion_strings( entry, 1, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelSetInsertionStringsTest, TwoStrings ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    LPCSTR first = "tik";
    LPCSTR second = "tok";
    LPCSTR insertion;

    entry = create_empty_entry();
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_wel_insertion_strings( entry, 2, first, second );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result == entry );

    insertion = stumpless_get_wel_insertion_string( entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( insertion != first );
    EXPECT_STREQ( insertion, first );

    insertion = stumpless_get_wel_insertion_string( entry, 1 );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( insertion != second );
    EXPECT_STREQ( insertion, second );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelSetInsertionStringsWTest, NullEntry ) {
    struct stumpless_entry *result;
    const struct stumpless_error *error;

    result = stumpless_set_wel_insertion_strings_w( NULL, 1, L"add me!" );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( WelSetInsertionStringsWTest, NullString ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    const struct stumpless_error *error;

    entry = create_empty_entry();
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_wel_insertion_strings_w( entry, 1, NULL );
    EXPECT_NULL( result );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    stumpless_destroy_entry_only( entry );
  }

  TEST( WelSetInsertionStringsWTest, TwoStrings ) {
    struct stumpless_entry *entry;
    struct stumpless_entry *result;
    LPCWSTR first = L"tik";
    LPCWSTR second = L"tok";
    LPCWSTR insertion;

    entry = create_empty_entry();
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( entry );

    result = stumpless_set_wel_insertion_strings_w( entry, 2, first, second );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( result == entry );

    insertion = stumpless_get_wel_insertion_string_w( entry, 0 );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( insertion != first );
    EXPECT_EQ( wcscmp( insertion, first ), 0 );

    insertion = stumpless_get_wel_insertion_string_w( entry, 1 );
    EXPECT_NO_ERROR;
    EXPECT_TRUE( insertion != second );
    EXPECT_EQ( wcscmp( insertion, second ), 0 );

    stumpless_destroy_entry_only( entry );
  }
}
