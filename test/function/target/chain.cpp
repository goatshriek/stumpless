// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2024 Joel E. Anderson
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <stumpless.h>
#include "test/helper/assert.hpp"
#include "test/helper/fixture.hpp"
#include "test/helper/memory_allocation.hpp"
#include "test/helper/rfc5424.hpp"

using::testing::HasSubstr;

namespace {
  class ChainTargetTest : public::testing::Test {
    protected:
      struct stumpless_target *chain = NULL;
      char buffer[8192];
      struct stumpless_target *target_1 = NULL;
      struct stumpless_target *full_chain = NULL;

      void
      SetUp( void ) override {
        size_t i;
        chain = stumpless_new_chain( "test-fixture" );
        target_1 = stumpless_open_buffer_target( "chain-element-1",
                                                 buffer,
                                                 sizeof( buffer ) );
        stumpless_add_target_to_chain( chain, target_1 );

        full_chain = stumpless_new_chain( "test-fixture-full-chain" );
        for( i = 0; i < STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH + 1; i++ ){
          stumpless_add_target_to_chain( full_chain, target_1 );
        }
      }

      void
      TearDown( void ) override {
        stumpless_close_chain_only( chain );
        stumpless_close_chain_only( full_chain );
        stumpless_close_buffer_target( target_1 );
        stumpless_free_all();
      }
  };

  TEST_F( ChainTargetTest, AddTarget ){
    size_t starting_length;
    char target_buffer[1024];
    struct stumpless_target *target;
    struct stumpless_target *add_target_result;
    size_t new_length;
    const char *test_message = "added-target-test";
    int add_message_result;
    char read_buffer[1024];
    size_t read_size;

    starting_length = stumpless_get_chain_length( chain );
    EXPECT_NO_ERROR;

    target = stumpless_open_buffer_target( "chain-add-new",
                                           target_buffer,
                                           sizeof( target_buffer ) );
    ASSERT_NOT_NULL( target );

    add_target_result = stumpless_add_target_to_chain( chain, target );
    EXPECT_NO_ERROR;
    EXPECT_EQ( add_target_result, chain );

    new_length = stumpless_get_chain_length( chain );
    EXPECT_NO_ERROR;
    ASSERT_EQ( new_length, starting_length + 1 );

    add_message_result = stumpless_add_message_str( chain, test_message );
    EXPECT_NO_ERROR;
    EXPECT_GE( add_message_result, 0 );

    read_size = stumpless_read_buffer( target,
                                       read_buffer,
                                       sizeof( read_buffer ) );
    EXPECT_NO_ERROR;
    EXPECT_GT( read_size, 0 );

    std::string read_message( read_buffer, read_size );
    EXPECT_THAT( read_message, HasSubstr( test_message ) );

    stumpless_close_buffer_target( target );
  }

  TEST_F( ChainTargetTest, AddTargetToFullChain ){
    size_t starting_length;
    char target_buffer[1024];
    struct stumpless_target *target;
    struct stumpless_target *add_target_result;
    size_t new_length;
    const char *test_message = "added-target-test";
    int add_message_result;
    char read_buffer[1024];
    size_t read_size;

    starting_length = stumpless_get_chain_length( full_chain );
    EXPECT_NO_ERROR;

    target = stumpless_open_buffer_target( "chain-add-new",
                                           target_buffer,
                                           sizeof( target_buffer ) );
    ASSERT_NOT_NULL( target );

    add_target_result = stumpless_add_target_to_chain( full_chain, target );
    EXPECT_NO_ERROR;
    EXPECT_EQ( add_target_result, full_chain );

    new_length = stumpless_get_chain_length( full_chain );
    EXPECT_NO_ERROR;
    ASSERT_EQ( new_length, starting_length + 1 );

    add_message_result = stumpless_add_message_str( full_chain, test_message );
    EXPECT_NO_ERROR;
    EXPECT_GE( add_message_result, 0 );

    read_size = stumpless_read_buffer( target,
                                       read_buffer,
                                       sizeof( read_buffer ) );
    EXPECT_NO_ERROR;
    EXPECT_GT( read_size, 0 );

    std::string read_message( read_buffer, read_size );
    EXPECT_THAT( read_message, HasSubstr( test_message ) );

    stumpless_close_buffer_target( target );
  }

  TEST_F( ChainTargetTest, AddTargetToFullChainMemoryFailure ){
    size_t starting_length;
    char target_buffer[1024];
    struct stumpless_target *target;
    struct stumpless_target *add_target_result;
    size_t new_length;

    starting_length = stumpless_get_chain_length( full_chain );
    EXPECT_NO_ERROR;

    target = stumpless_open_buffer_target( "chain-add-new",
                                           target_buffer,
                                           sizeof( target_buffer ) );
    ASSERT_NOT_NULL( target );

    stumpless_set_realloc( REALLOC_FAIL );
    EXPECT_NO_ERROR;

    add_target_result = stumpless_add_target_to_chain( full_chain, target );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( add_target_result );

    new_length = stumpless_get_chain_length( full_chain );
    EXPECT_NO_ERROR;
    EXPECT_EQ( new_length, starting_length );

    stumpless_set_realloc( realloc );
    EXPECT_NO_ERROR;

    stumpless_close_buffer_target( target );
  }

  TEST_F( ChainTargetTest, AddEntry ){
    struct stumpless_entry *entry;
    int result;

    entry = create_entry();

    result = stumpless_add_entry( chain, entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( ChainTargetTest, AddEntryToFullChain ){
    struct stumpless_entry *entry;
    int result;

    entry = create_entry();

    result = stumpless_add_entry( full_chain, entry );
    EXPECT_GE( result, 0 );
    EXPECT_NO_ERROR;

    TestRFC5424Compliance( buffer );

    stumpless_destroy_entry_and_contents( entry );
  }

  TEST_F( ChainTargetTest, AddNullTargetToChain ){
    struct stumpless_target *result;

    result = stumpless_add_target_to_chain( chain, NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ChainTargetTest, AddTargetToNonChain ){
    struct stumpless_target *result;

    result = stumpless_add_target_to_chain( target_1, target_1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );
    EXPECT_NULL( result );
  }

  TEST_F( ChainTargetTest, AddTargetToNullChain ){
    struct stumpless_target *result;

    result = stumpless_add_target_to_chain( NULL, target_1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
    EXPECT_NULL( result );
  }

  TEST_F( ChainTargetTest, CloseIncompatibleTargetAndContents ){
    stumpless_close_chain_and_contents( target_1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );
  }

  TEST_F( ChainTargetTest, CloseIncompatibleTargetOnly ){
    stumpless_close_chain_only( target_1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );
  }

  TEST_F( ChainTargetTest, GetLengthFromIncompatibleTarget ){
    size_t result;

    result = stumpless_get_chain_length( target_1 );
    EXPECT_ERROR_ID_EQ( STUMPLESS_TARGET_INCOMPATIBLE );
    EXPECT_EQ( result, 0 );
  }

  TEST_F( ChainTargetTest, GetLengthFromInvalidTarget ){
    void *id;
    size_t result;

    id = chain->id;
    chain->id = NULL;

    result = stumpless_get_chain_length( chain );
    EXPECT_ERROR_ID_EQ( STUMPLESS_INVALID_ID );
    EXPECT_EQ( result, 0 );

    chain->id = id;
  }

  /* non-fixture tests */

  TEST( CloseTargetTest, ChainTarget ){
    struct stumpless_target *chain;

    chain = stumpless_new_chain( "generic-close-test" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( chain );

    EXPECT_EQ( stumpless_get_current_target(), chain );

    stumpless_close_target( chain );
    EXPECT_NO_ERROR;

    EXPECT_EQ( stumpless_get_current_target(),
               stumpless_get_default_target() );

    stumpless_free_all();
  }

  TEST( ChainTargetLengthTest, EmptyChain ){
    struct stumpless_target *chain;
    size_t length;

    chain = stumpless_new_chain( "empty" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( chain );

    length = stumpless_get_chain_length( chain );
    EXPECT_NO_ERROR;
    EXPECT_EQ( length, 0 );

    stumpless_close_chain_only( chain );
    stumpless_free_all();
  }

  TEST( CloseChainAndContentsTest, FullChain ){
    struct stumpless_target *chain;
    struct stumpless_target *sub_target;
    char buffer[1024];
    size_t i;

    chain = stumpless_new_chain( "full-chain-to-close" );
    EXPECT_NO_ERROR;
    ASSERT_NOT_NULL( chain );

    for( i = 0; i < STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH + 1; i++ ){
      sub_target = stumpless_open_buffer_target( "sub-target",
                                                 buffer,
                                                 sizeof( buffer ) );
      EXPECT_NO_ERROR;

      stumpless_add_target_to_chain( chain, sub_target );
      EXPECT_NO_ERROR;
    }

    stumpless_close_chain_and_contents( chain );
    EXPECT_NO_ERROR;
  }

  TEST( CloseChainAndContentsTest, NullTarget ){
    stumpless_close_chain_and_contents( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( CloseChainOnlyTest, NullTarget ){
    stumpless_close_chain_only( NULL );
    EXPECT_ERROR_ID_EQ( STUMPLESS_ARGUMENT_EMPTY );
  }

  TEST( NewChainTargetTest, MemoryFailure ){
    const struct stumpless_target *result;

    stumpless_set_malloc( MALLOC_FAIL );
    EXPECT_NO_ERROR;

    result = stumpless_new_chain( "memory-failure" );
    EXPECT_ERROR_ID_EQ( STUMPLESS_MEMORY_ALLOCATION_FAILURE );
    EXPECT_NULL( result );

    stumpless_set_malloc( malloc );
    EXPECT_NO_ERROR;

    stumpless_free_all();
  }
}
