/*
 * Copyright 2018, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <string.h>
#include <gtest/gtest.h>
#include <stumpless/target.h>
#include <stumpless/target/buffer.h>
#include <stumpless/target/socket.h>
#include <stumpless/error.h>
#include "test/function/rfc5424.hpp"

#define TEST_BUFFER_LENGTH 1024

namespace {

  class BufferTargetTest : public ::testing::Test {
    protected:
      char buffer[TEST_BUFFER_LENGTH];
      struct stumpless_target *target;

      virtual void SetUp(){
        buffer[0] = '\0';
        target = stumpless_open_buffer_target("buffer target testing", buffer, TEST_BUFFER_LENGTH, 0, 0);
      }

      virtual void TearDown(){
        stumpless_close_buffer_target(target);
      }
  };

  TEST_F(BufferTargetTest, Basic){
    SCOPED_TRACE("BufferTargetTest.Basic");

    ASSERT_TRUE(stumpless_get_current_target() != NULL);

    EXPECT_EQ(0, stumpless("\xef\xbb\xbftesting 1 \xfc\x88\x81\x8f\x8f\x8f"));
    EXPECT_EQ(NULL, stumpless_get_error());

    TestRFC5424Compliance(buffer);
  }

  TEST_F(BufferTargetTest, Overflow){
    const char *test_string = "smash the stack for fun and profit`";
    size_t test_string_len = strlen(test_string);

    ASSERT_TRUE(stumpless_get_current_target() != NULL);

    for(size_t bytes_written=0; bytes_written <= TEST_BUFFER_LENGTH; bytes_written += test_string_len ){
      ASSERT_EQ(0, stumpless(test_string));
      ASSERT_EQ(NULL, stumpless_get_error());
    }

    EXPECT_EQ(NULL, stumpless_get_error());
  }

  class BufferTargetOpenTest : public ::testing::Test {

  };

  TEST(BufferTargetOpenTest, NormalOpenTarget){
    struct stumpless_target *target;
    char buffer[100];

    target = stumpless_open_buffer_target("normal target", buffer, 100, 0, 0);
    ASSERT_TRUE(target != NULL);

    EXPECT_EQ(target, stumpless_get_current_target());

    stumpless_close_buffer_target(target);
  }
  
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
