// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2020-2021 Joel E. Anderson
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

#include <gmock/gmock.h>
#include "test/helper/fixture.hpp"
#include "test/helper/level_enabled.hpp"

using::testing::HasSubstr;

namespace {

  BUFFER_TARGET_FIXTURE_CLASS( LevelEnabledTest );

  TEST_LEVEL_ENABLED( EMERG, em );
  TEST_LEVEL_ENABLED( ALERT, a );
  TEST_LEVEL_ENABLED( CRIT, c );
  TEST_LEVEL_ENABLED( ERR, er );
  TEST_LEVEL_ENABLED( WARNING, w );
  TEST_LEVEL_ENABLED( NOTICE, n );
  TEST_LEVEL_ENABLED( INFO, i );
  TEST_LEVEL_ENABLED( DEBUG, d );
  TEST_LEVEL_ENABLED( TRACE, t );

}
