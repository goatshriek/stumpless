// SPDX-License-Identifier: Apache-2.0

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
#include <gtest/gtest.h>
#include <stumpless.h>

namespace {

  class VersionTest : public ::testing::Test {};

  TEST(GetVersionTest, Function){
    struct stumpless_version *version;
  
    version = stumpless_get_version();
  
    ASSERT_TRUE(version != NULL);
    ASSERT_TRUE(version->major >= 0);
    ASSERT_TRUE(version->minor >= 0);
    ASSERT_TRUE(version->patch >= 0);
  }
  
  TEST(GetVersionTest, Defines){
    #ifndef STUMPLESS_MAJOR_VERSION
      FAIL();
    #endif
  
    #ifndef STUMPLESS_MINOR_VERSION
      FAIL();
    #endif
  
    #ifndef STUMPLESS_PATCH_VERSION
      FAIL();
    #endif
  }

}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
