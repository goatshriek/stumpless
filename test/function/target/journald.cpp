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

    seed = std::chrono::system_clock::now(  ).time_since_epoch(  ).count(  );
    std::default_random_engine gen( seed );
    std::uniform_int_distribution<int> dist;
    std::ostringstream message_stream;
    message_stream << "test-stumpless-journald-message-" << dist( gen );
    std::string message = message_stream.str(  );

    result = stumpless_add_message( target, message.c_str(  ) );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    std::ostringstream match_stream;
    match_stream << "MESSAGE=" << message;
    std::string message_match = match_stream.str(  );

    for( int i = 0; i < 64 && !msg_found; i++ ) {
      sd_journal_open( &jrnl, 0 );
      sd_journal_add_match( jrnl, message_match.c_str(  ), 0 );
      SD_JOURNAL_FOREACH( jrnl ) {
        msg_found = true;
      }
      sd_journal_close( jrnl );
    }

    EXPECT_TRUE( msg_found );
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
