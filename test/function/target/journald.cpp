// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2021 Joel E. Anderson
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

#include <chrono>
#include <cstring>
#include <random>
#include <sstream>
#include <stddef.h>
#include <stdlib.h>
#include <stumpless.h>
#include <systemd/sd-journal.h>
#include <gtest/gtest.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"

#define FOR_JOURNALD_MATCH_BEGIN( MATCH )                   \
for( int i = 0; i < 64 && !msg_found && !abort; i++ ) {     \
  result = sd_journal_open( &jrnl, SD_JOURNAL_LOCAL_ONLY ); \
  if( result < 0 ) {                                        \
    SUCCEED(  ) << "could not open the journal to verify "  \
                   "the write, failed with error code "     \
                << result;                                  \
    abort = true;                                           \
  }                                                         \
                                                            \
  sd_journal_add_match( jrnl, ( MATCH ), 0 );               \
  SD_JOURNAL_FOREACH( jrnl ) {

#define FOR_JOURNALD_MATCH_END \
  }                            \
  sd_journal_close( jrnl );    \
}


using namespace std;

void TestData( sd_journal *jrnl, const char *name, const string &value ) {
  const void *data;
  size_t data_len;
  int result = sd_journal_get_data( jrnl, name, &data, &data_len );
  EXPECT_GE( result, 0 );

  ostringstream data_stream;
  data_stream << name << '=' << value;
  EXPECT_EQ( data_len, strlen( name ) + 1 + value.length(  ) );
  EXPECT_EQ( 0, memcmp( data, data_stream.str(  ).c_str(  ), data_len ) );
}

void TestDataExists( sd_journal *jrnl, const char *name ) {
  const void *data;
  size_t data_len;
  int result = sd_journal_get_data( jrnl, name, &data, &data_len );
  EXPECT_GE( result, 0 );
}

namespace {

  class JournaldTargetTest : public::testing::Test {
    protected:
      const char *target_name = "test-journald-target";
      struct stumpless_target *target;
      struct stumpless_entry *basic_entry;

    virtual void
    SetUp( void ) {
      target = stumpless_open_journald_target( target_name );

      stumpless_set_target_default_app_name( target, "journald-target-test" );
      stumpless_set_target_default_msgid( target, "default-message" );

      basic_entry = create_entry(  );
    }

    virtual void
    TearDown( void ) {
      stumpless_destroy_entry_and_contents( basic_entry );
      stumpless_close_journald_target( target );
      stumpless_free_all( );
    }
  };

  TEST_F( JournaldTargetTest, AddEntry ) {
    unsigned seed;
    int result;
    sd_journal *jrnl;
    bool msg_found = false;
    bool abort = false;
    struct stumpless_entry *entry;

    entry = create_entry(  );

    seed = chrono::system_clock::now(  ).time_since_epoch(  ).count(  );
    default_random_engine gen( seed );
    uniform_int_distribution<int> dist;
    ostringstream message_stream;
    message_stream << "test-stumpless-journald-entry-" << dist( gen );
    string message = message_stream.str(  );
    stumpless_set_entry_message( entry, message.c_str(  ) );

    ostringstream match_stream;
    match_stream << "MESSAGE=" << message;
    string message_match = match_stream.str(  );

    result = stumpless_add_entry( target, entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    int severity_value = stumpless_get_entry_severity( entry );
    string expected_priority = to_string( severity_value );

    int facility_value = stumpless_get_entry_facility( entry ) >> 3;
    string expected_facility = to_string( facility_value );

    const char *app_name = stumpless_get_entry_app_name( entry );
    string expected_app_name = string( app_name );

    const char *element_name = "FIXTURE_ELEMENT";
    const char *param_1_name = "FIXTURE_ELEMENT_FIXTURE_PARAM_1";
    const char *expected_param_1 = "fixture-value-1";
    const char *param_2_name = "FIXTURE_ELEMENT_FIXTURE_PARAM_2";
    const char *expected_param_2 = "fixture-value-2";

    FOR_JOURNALD_MATCH_BEGIN( message_match.c_str(  ) )
      msg_found = true;

      TestData( jrnl, "PRIORITY", expected_priority );
      TestData( jrnl, "SYSLOG_FACILITY", expected_facility );
      TestData( jrnl, "SYSLOG_IDENTIFIER", expected_app_name );
      TestDataExists( jrnl, "SYSLOG_TIMESTAMP" );
      TestDataExists( jrnl, "SYSLOG_PID" );

      TestData( jrnl, element_name, string(  ) );
      TestData( jrnl, param_1_name, string( expected_param_1 ) );
      TestData( jrnl, param_2_name, string( expected_param_2 ) );
    FOR_JOURNALD_MATCH_END

    if( !abort ) {
      EXPECT_TRUE( msg_found );
    }

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( JournaldTargetTest, AddMessage ) {
    unsigned seed;
    int result;
    sd_journal *jrnl;
    bool msg_found = false;
    bool abort = false;

    seed = chrono::system_clock::now(  ).time_since_epoch(  ).count(  );
    default_random_engine gen( seed );
    uniform_int_distribution<int> dist;
    ostringstream message_stream;
    message_stream << "test-stumpless-journald-message-" << dist( gen );
    string message = message_stream.str(  );

    ostringstream match_stream;
    match_stream << "MESSAGE=" << message;
    string message_match = match_stream.str(  );

    result = stumpless_add_message( target, message.c_str(  ) );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    int severity_value = STUMPLESS_DEFAULT_SEVERITY;
    string expected_priority = to_string( severity_value );

    int facility_value = stumpless_get_default_facility( target ) >> 3;
    string expected_facility = to_string( facility_value );

    const char *app_name = stumpless_get_target_default_app_name( target );
    string expected_app_name = string( app_name );

    FOR_JOURNALD_MATCH_BEGIN( message_match.c_str(  ) )
      msg_found = true;

      TestData( jrnl, "PRIORITY", expected_priority );
      TestData( jrnl, "SYSLOG_FACILITY", expected_facility );
      TestData( jrnl, "SYSLOG_IDENTIFIER", expected_app_name );
      TestDataExists( jrnl, "SYSLOG_TIMESTAMP" );
      TestDataExists( jrnl, "SYSLOG_PID" );
    FOR_JOURNALD_MATCH_END

    if( !abort ) {
      EXPECT_TRUE( msg_found );
    }
  }

  TEST_F( JournaldTargetTest, AddEntryReallocFailure ) {
    void * (*set_realloc_result)(void *, size_t);
    int result;
    const struct stumpless_error *error;

    set_realloc_result = stumpless_set_realloc( REALLOC_FAIL );
    ASSERT_NOT_NULL( set_realloc_result );

    result = stumpless_add_message( target, "expected realloc failure" );
    EXPECT_LT( result, 0 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_realloc_result = stumpless_set_realloc( realloc );
    EXPECT_TRUE( set_realloc_result == realloc );
  }

  /* non-fixture tests */

  TEST( JournaldTargetCloseTest, GenericCloseFunction ) {
    struct stumpless_target *target;

    target = stumpless_open_journald_target( "basic-target" );
    stumpless_close_target( target );
    EXPECT_NO_ERROR;
    stumpless_free_all(  );
  }

  TEST( JournaldTargetCloseTest, NullTarget ) {
    const struct stumpless_error *error;

    stumpless_close_function_target( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all(  );
  }

  TEST( JournaldTargetCloseTest, WrongTargetType ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_stdout_target( "not-a-journald-target" );
    stumpless_close_journald_target( target );

    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );
    stumpless_close_target( target );
    stumpless_free_all(  );
  }

  TEST( JournaldTargetOpenTest, MallocFailure ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;
    void * ( *set_malloc_result )( size_t );

    set_malloc_result = stumpless_set_malloc( MALLOC_FAIL );
    ASSERT_NOT_NULL( set_malloc_result );

    target = stumpless_open_journald_target( "function-target-malloc-failure" );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );

    set_malloc_result = stumpless_set_malloc( malloc );
    ASSERT_TRUE( set_malloc_result == malloc );
    stumpless_free_all( );
  }

  TEST( JournaldTargetOpenTest, NullName ) {
    struct stumpless_target *target;
    const struct stumpless_error *error;

    target = stumpless_open_journald_target( NULL );
    EXPECT_NULL( target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    stumpless_free_all( );
  }
}
