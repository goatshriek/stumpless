// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2024 Joel E. Anderson
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

#include <cstdlib>
#include <gtest/gtest.h>
#include <stumpless.hpp>

using namespace stumpless;

namespace {

  class CppElementTest : public ::testing::Test {
    protected:
      Element *element_with_params;
      const char *param_1_name = "param-1-name";
      const char *param_2_name = "param-1-name";

    virtual void
    SetUp( void ) {
      element_with_params = new Element( "basic" );
      element_with_params->AddParam( param_1_name, "param-1-value" );
      element_with_params->AddParam( param_2_name, "param-2-value" );
    }

    virtual void
    TearDown( void ) {
      delete element_with_params;
      MemoryManager::FreeAll(  );
    }
  };

  TEST_F( CppElementTest, GetParamByIndex ) {
     Param param = element_with_params->GetParam( ( size_t ) 0 );
     const char *param_name = param.GetName(  );
     EXPECT_STREQ( param_name, param_1_name );
     free( ( void * ) param_name );
  }
}
