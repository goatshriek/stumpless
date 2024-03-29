// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019-2024 Joel E. Anderson
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
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"

using::testing::HasSubstr;

namespace {

  class PerrorTest : public::testing::Test {

    protected:
      FILE *error_file;
      const char *filename = "testfile.log";

    virtual void
    SetUp( void ) {
      error_file = fopen( filename, "w+" );

      stumpless_set_error_stream( error_file );
    }

    virtual void
    TearDown( void ) {
      stumpless_set_error_stream( stderr );
      fclose( error_file );
      stumpless_free_all(  );
    }

  };

  TEST_F( PerrorTest, ErrorCodeAndPrefix ) {
    char buffer[10];
    const char *prefix = "with a prefix";
    const struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_entry *entry;

    target = stumpless_open_buffer_target( "small-buffer-target",
                                           buffer,
                                           sizeof( buffer ) );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );


    stumpless_add_entry( target, entry ); // argument is too big

    stumpless_perror( prefix );

    error = stumpless_get_error(  );
    EXPECT_NOT_NULL( error );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_buffer_target( target );
    fflush( error_file );

    std::ifstream infile( filename );
    std::string line;
    std::getline( infile, line );

    EXPECT_THAT( line, HasSubstr( prefix ) );
    EXPECT_THAT( line, HasSubstr( ": " ) );
    EXPECT_THAT( line, HasSubstr( stumpless_get_error_id_string(error->id) ) );
    EXPECT_THAT( line, HasSubstr( ": " ) );
    EXPECT_THAT( line, HasSubstr( error->message ) );
    EXPECT_THAT( line, HasSubstr( std::to_string( error->code ) ) );
    EXPECT_THAT( line, HasSubstr( error->code_type ) );
  }

  TEST_F( PerrorTest, ErrorCodeNoPrefix ) {
    char buffer[10];
    const struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_entry *entry;

    target = stumpless_open_buffer_target( "small-buffer-target",
                                           buffer,
                                           sizeof( buffer ) ) ;

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );


    stumpless_add_entry( target, entry ); // argument is too big

    stumpless_perror( NULL );

    error = stumpless_get_error(  );
    EXPECT_NOT_NULL( error );

    stumpless_destroy_entry_and_contents( entry );
    stumpless_close_buffer_target( target );
    fflush( error_file );

    std::ifstream infile( filename );
    std::string line;
    std::getline( infile, line );

    EXPECT_THAT( line, HasSubstr( stumpless_get_error_id_string(error->id) ) );
    EXPECT_THAT( line, HasSubstr( ": " ) );
    EXPECT_THAT( line, HasSubstr( error->message ) );
    EXPECT_THAT( line, HasSubstr( std::to_string( error->code ) ) );
    EXPECT_THAT( line, HasSubstr( error->code_type ) );
  }

  TEST_F( PerrorTest, FileOpenFailure ) {
    struct stumpless_target *target;

    target = stumpless_open_file_target( "/" );
    EXPECT_NULL( target );

    stumpless_perror( "expected file open failure" );
  }

  TEST_F( PerrorTest, InvalidId ) {
    char buffer[10];
    struct stumpless_target *id_target;
    stumpless_id_t actual_id;
    struct stumpless_entry *entry;

    id_target = stumpless_open_buffer_target( "test-target",
                                              buffer,
                                              sizeof( buffer ) ) ;
    actual_id = id_target->id;
    id_target->id = NULL;

    entry = create_entry(  );
    stumpless_add_entry( id_target, entry );
    stumpless_perror( "expected invalid id" );

    id_target->id = actual_id;
    stumpless_close_target( id_target );
    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( PerrorTest, MemoryAllocationFailure ) {
    void * (*set_malloc_result)(size_t);
    const struct stumpless_param *new_param;

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    new_param = stumpless_new_param( "name", "value" );
    EXPECT_NULL( new_param );

    stumpless_perror( "expected memory failure" );

    set_malloc_result = stumpless_set_malloc( malloc );
    EXPECT_TRUE( set_malloc_result == malloc );
  }

  TEST_F( PerrorTest, NoError ) {
    stumpless_perror( "this shouldn't show up" );

    std::ifstream infile( filename );
    EXPECT_EQ(infile.peek(), std::ifstream::traits_type::eof() );
  }

  TEST_F( PerrorTest, NoErrorCodeAndPrefix ) {
    const char *prefix = "with a prefix";
    const struct stumpless_error *error;

    stumpless_new_param( NULL, NULL ); // will cause an empty argument error

    stumpless_perror( prefix );

    error = stumpless_get_error(  );
    EXPECT_NOT_NULL( error );

    stumpless_set_error_stream( stderr );
    fflush( error_file );

    std::ifstream infile( filename );
    std::string line;
    std::getline( infile, line );

    EXPECT_THAT( line, HasSubstr( prefix ) );
    EXPECT_THAT( line, HasSubstr( stumpless_get_error_id_string(error->id) ) );
    EXPECT_THAT( line, HasSubstr( ": " ) );
    EXPECT_THAT( line, HasSubstr( error->message ) );
  }

  TEST_F( PerrorTest, NoErrorCodeOrPrefix ) {
    const struct stumpless_error *error;

    stumpless_new_param( NULL, NULL ); // will cause an empty argument error

    stumpless_perror( NULL );

    error = stumpless_get_error(  );
    EXPECT_NOT_NULL( error );

    stumpless_set_error_stream( stderr );
    fflush( error_file );

    std::ifstream infile( filename );
    std::string line;
    std::getline( infile, line );

    EXPECT_THAT( line, HasSubstr( stumpless_get_error_id_string(error->id) ) );
    EXPECT_THAT( line, HasSubstr( ": " ) );
    EXPECT_THAT( line, HasSubstr( error->message ) );
  }

  TEST_F( PerrorTest, StreamWriteFailure ) {
    struct stumpless_target *target;
    const char *filename = "stream-write-failure.log";
    FILE *stream;
    int result;

    stream = fopen( filename, "w+" );
    fclose( stream );

    stream = fopen( filename, "r" );
    ASSERT_NOT_NULL( stream );

    target = stumpless_open_stream_target( filename, stream );
    ASSERT_NOT_NULL( target );

    result = stumpless_add_message( target, "can i write?" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_STREAM_WRITE_FAILURE );

    stumpless_perror( "expected stream write failure" );

    stumpless_close_stream_target( target );
    fclose( stream );
    remove( filename );
  }

  /* non-fixture tests */

  TEST( GetErrorId, Basic ) {
    struct stumpless_error test_error;
    enum stumpless_error_id result;

    test_error.id = STUMPLESS_FILE_OPEN_FAILURE;

    result = stumpless_get_error_id( &test_error );

    EXPECT_EQ( result, test_error.id );
  }

  TEST( SetPerrorTest, NullStream ) {
    stumpless_set_error_stream( NULL );

    EXPECT_TRUE( stumpless_get_error_stream(  ) == NULL );

    stumpless_perror( "won't be hit, make sure no segfault" );
  }

  TEST( GetErrorId, NoSuchErrorId ) {
    int error_count = 0;
    const char *result;

    #define COUNT_ERRORS( STRING, ENUM ) error_count++;
    STUMPLESS_FOREACH_ERROR( COUNT_ERRORS )

    stumpless_error_id wrong_id = 
	    static_cast<stumpless_error_id>(error_count + 1);
    
    result = stumpless_get_error_id_string( wrong_id );
    EXPECT_STREQ( result, "NO_SUCH_ERROR_ID" );
  }

}
