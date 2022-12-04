// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2021 Joel E. Anderson
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

#include <cstdio>
#include <fstream>
#include <string>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stumpless.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/rfc5424.hpp"
// #include "private/target/stream.h"

namespace {
  int
  basic_log_function( const struct stumpless_target *target,
                      const struct stumpless_entry *entry ) {
    EXPECT_NOT_NULL( target );
    EXPECT_NOT_NULL( entry );
    return 0;
  }

  class StreamTargetTest : public::testing::Test {
    protected:
      const char *filename = "testfile.log";
      FILE *stream;
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      struct stumpless_element *element;
      struct stumpless_param *param;

      stream = fopen( filename, "w+" );

      target = stumpless_open_stream_target( filename, stream );

      stumpless_set_target_default_app_name( target, "buffer-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                         STUMPLESS_SEVERITY_INFO,
                                        "stumpless-unit-test",
                                        "basic-entry",
                                        "basic test message" );

      element = stumpless_new_element( "basic-element" );
      stumpless_add_element( basic_entry, element );

      param = stumpless_new_param( "basic-param-name", "basic-param-value" );
      stumpless_add_param( element, param );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_close_stream_target( target );

      fclose( stream );
      remove( filename );
    }
  };

  TEST_F( StreamTargetTest, AddEntry ) {
    int result;

    SCOPED_TRACE( "EntryTargetTest.AddEntry" );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;
  }

  /* non-fixture tests */

  TEST( StreamTargetCloseTest, Generic ) {
    const char *filename = "genericclosetest.log";
    FILE *stream;
    struct stumpless_target *target;

    stream = fopen( filename, "w+" );
    ASSERT_NOT_NULL( stream );

    target = stumpless_open_stream_target( filename, stream );
    EXPECT_NO_ERROR;
    EXPECT_NOT_NULL( target );
    EXPECT_EQ( stumpless_get_current_target(  ), target );

    stumpless_close_target( target );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(  ),
               stumpless_get_default_target(  ) );
    EXPECT_STRNE( stumpless_get_current_target(  )->name,
                  filename );

    stumpless_free_all(  );
  }

  TEST( StreamTargetCloseTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_stream_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( StreamTargetCloseTest, WrongTargetType ) {
    const struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_function_target( "not-a-stream-target",
                                             basic_log_function );
    ASSERT_NOT_NULL( target );

    stumpless_close_stream_target( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );

    stumpless_close_function_target( target );
  }

  TEST( StreamTargetFormat, NewlineSeparator ) {
    struct stumpless_target *target;
    struct stumpless_entry *entry;
    struct stumpless_element *element;
    struct stumpless_param *param;
    const char *filename = "filetargetformattest.log";
    FILE *stream;
    size_t line_count = 3;
    size_t i;

    stream = fopen( filename, "w+" );
    ASSERT_TRUE( stream != NULL );

    target = stumpless_open_stream_target( filename, stream );
    ASSERT_TRUE( target != NULL );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                "stumpless-unit-test",
                                "basic-entry",
                                "basic test message" );
    ASSERT_TRUE( entry != NULL );

    element = stumpless_new_element( "basic-element" );
    ASSERT_TRUE( element != NULL );
    stumpless_add_element( entry, element );

    param = stumpless_new_param( "basic-param-name", "basic-param-value" );
    ASSERT_TRUE( param != NULL );
    stumpless_add_param( element, param );

    for( i = 0; i < line_count; i++ ) {
      stumpless_add_entry( target, entry );
    }

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_stream_target( target );
    fclose( stream );

    std::ifstream infile( filename );
    std::string line;
    i = 0;
    while( std::getline( infile, line ) ) {
      TestRFC5424Compliance( line.c_str() );
      i++;
    }

    EXPECT_EQ( i, line_count );

    remove( filename );
  }

  TEST( StreamTargetOpenTest, MallocFailure ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;
    const char *filename = "open-malloc-fail.log";
    FILE *stream;
    void *(*set_malloc_result)(size_t);

    set_malloc_result = stumpless_set_malloc( [](size_t size)->void *{ return NULL; } );
    ASSERT_TRUE( set_malloc_result != NULL );

    stream = fopen( filename, "w+" );
    EXPECT_NOT_NULL( stream );

    target = stumpless_open_stream_target( filename, stream );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    fclose( stream );
    remove( filename );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
  }

  TEST( StreamTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;
    const char *filename = "null-name.log";
    FILE *stream;

    stream = fopen( filename, "w+" );
    ASSERT_NOT_NULL( stream );

    target = stumpless_open_stream_target( NULL, stream );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );

    fclose( stream );
    remove( filename );
  }

  TEST( StreamTargetOpenTest, NullStream ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stream_target( "no-stream-provided", NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( StreamTargetStderrTest, NullName ) {
    const struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stderr_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( StreamTargetStdoutTest, NullName ) {
    const struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( StreamTargetWriteTest, ReadOnlyStream ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;
    struct stumpless_entry *basic_entry;
    const char *filename = "null-name.log";
    FILE *stream;
    int result;

    basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                       STUMPLESS_SEVERITY_INFO,
                                      "stumpless-unit-test",
                                      "basic-entry",
                                      "basic test message" );
    ASSERT_TRUE( basic_entry != NULL );

    stream = fopen( filename, "w+" );
    fclose( stream );

    stream = fopen( filename, "r" );
    ASSERT_TRUE( stream != NULL );

    target = stumpless_open_stream_target( filename, stream );
    ASSERT_TRUE( target != NULL );

    result = stumpless_add_entry( target, basic_entry );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_STREAM_WRITE_FAILURE );

    stumpless_destroy_entry_and_contents( basic_entry );
    fclose( stream );
    stumpless_close_stream_target( target );

    remove( filename );
  }

  TEST( SetSeverityColor, CorrectEscapeCodeOut ){
    
    std::FILE* ofs = tmpfile();
    struct stumpless_target *target;
    char color_code[] = "\033[31m";

    struct stumpless_entry *basic_entry;
    struct stumpless_entry *result;
    int log_result;

  
    target = stumpless_open_stream_target( "stdout-test", ofs );

    stumpless_set_severity_color( target, STUMPLESS_SEVERITY_EMERG, color_code );
    
    basic_entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                     STUMPLESS_SEVERITY_EMERG,
                                     "stumpless-unit-test",
                                     "basic-entry",
                                     "basic test message" );
    log_result = stumpless_add_entry( target, basic_entry );
    
    char *written_msg = NULL;
    char *reset_code = NULL;
    size_t line1,line2;
    
    fseek(ofs, 0, SEEK_SET);
    
    getline( &written_msg, &line1, ofs);    
    getline( &reset_code, &line2, ofs);
    
    written_msg[5] = '\0';

    EXPECT_STREQ( written_msg, color_code );
    EXPECT_STREQ( reset_code, "\033[0m" );
  }

  TEST( SetSeverityColor, StdoutNullTarget ){
    const struct stumpless_target *target;
    const struct stumpless_error *error;
    enum stumpless_severity severity = STUMPLESS_SEVERITY_CRIT;
    char color_code[] = "\033[31m";

    target = NULL;

    stumpless_set_severity_color( target, severity, color_code);
    
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );    
  }

  TEST( SetSeverityColor, StdoutInvalidSeverity ){
    const struct stumpless_target *target;
    const struct stumpless_error *error;
    // enum stumpless_severity severity = 10;
    char color_code[] = "\033[31m";

    target = stumpless_open_stdout_target( "stdout-test" );

    stumpless_set_severity_color( target, (enum stumpless_severity)10, color_code);
    
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );    
  }

  TEST( SetSeverityColor, StdoutNullEscapeCode ){
    const struct stumpless_target *target;
    const struct stumpless_error *error;
    enum stumpless_severity severity = STUMPLESS_SEVERITY_CRIT;
    char *color_code = NULL;

    target = stumpless_open_stdout_target( "stdout-test" );

    stumpless_set_severity_color( target, severity, color_code);
    
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );    
  }

  TEST( SetSeverityColor, StdErrNullTarget ){
    const struct stumpless_target *target;
    const struct stumpless_error *error;
    enum stumpless_severity severity = STUMPLESS_SEVERITY_CRIT;
    char color_code[] = "\033[31m";

    target = NULL;

    stumpless_set_severity_color( target, severity, color_code);
    
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );    
  }

  TEST( SetSeverityColor, StdErrInvalidSeverity ){
    const struct stumpless_target *target;
    const struct stumpless_error *error;
    // enum stumpless_severity severity = 10;
    char color_code[] = "\033[31m";

    target = stumpless_open_stderr_target( "stderr-test" );

    stumpless_set_severity_color( target, (enum stumpless_severity)10, color_code);
    
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_SEVERITY );    
  }

  TEST( SetSeverityColor, StdErrNullEscapeCode ){
    const struct stumpless_target *target;
    const struct stumpless_error *error;
    enum stumpless_severity severity = STUMPLESS_SEVERITY_CRIT;
    char *color_code = NULL;

    target = stumpless_open_stderr_target( "stderr-test" );

    stumpless_set_severity_color( target, severity, color_code);
    
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );    
  }

}
