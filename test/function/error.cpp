// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2019 Joel E. Anderson
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
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stumpless.h>

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
    }

  };

  TEST_F( PerrorTest, ErrorCodeAndPrefix ) {
    char buffer[10];
    const char *prefix = "with a prefix";
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_entry *entry;

    target = stumpless_open_buffer_target( "small-buffer-target",
                                           buffer,
                                           10,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );


    stumpless_add_entry( target, entry ); // argument is too big

    stumpless_perror( prefix );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    stumpless_destroy_entry( entry );
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
    struct stumpless_error *error;
    struct stumpless_target *target;
    struct stumpless_entry *entry;

    target = stumpless_open_buffer_target( "small-buffer-target",
                                           buffer,
                                           10,
                                           STUMPLESS_OPTION_NONE,
                                           STUMPLESS_FACILITY_USER );

    entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                                 STUMPLESS_SEVERITY_INFO,
                                 "stumpless-unit-test",
                                 "basic-entry",
                                 "basic test message" );


    stumpless_add_entry( target, entry ); // argument is too big

    stumpless_perror( NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    stumpless_destroy_entry( entry );
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

  TEST_F( PerrorTest, NoError ) {
    stumpless_perror( "this shouldn't show up" );

    std::ifstream infile( filename );
    EXPECT_EQ(infile.peek(), std::ifstream::traits_type::eof() );
  }

  TEST_F( PerrorTest, NoErrorCodeAndPrefix ) {
    const char *prefix = "with a prefix";
    struct stumpless_error *error;

    stumpless_new_param( NULL, NULL ); // will cause an empty argument error

    stumpless_perror( prefix );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

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
    struct stumpless_error *error;

    stumpless_new_param( NULL, NULL ); // will cause an empty argument error

    stumpless_perror( NULL );

    error = stumpless_get_error(  );
    EXPECT_TRUE( error != NULL );

    stumpless_set_error_stream( stderr );
    fflush( error_file );

    std::ifstream infile( filename );
    std::string line;
    std::getline( infile, line );

    EXPECT_THAT( line, HasSubstr( stumpless_get_error_id_string(error->id) ) );
    EXPECT_THAT( line, HasSubstr( ": " ) );
    EXPECT_THAT( line, HasSubstr( error->message ) );
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
    #define STUMPLESS_GENERATE_STRING( STRING, ENUM ) #STRING,
    static const char *stumpless_error_enum_to_string[] = {
      STUMPLESS_FOREACH_ERROR(STUMPLESS_GENERATE_STRING)
    };

    int wrong_id_int = 
	    sizeof( stumpless_error_enum_to_string ) / sizeof( char * ) + 1;
    stumpless_error_id wrong_id = 
	    static_cast<stumpless_error_id>(wrong_id_int);
    
    std::string result( stumpless_get_error_id_string( wrong_id ) );
    
    EXPECT_TRUE( result == "NO_SUCH_ERROR_ID" );
  }


}
