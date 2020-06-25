/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020 Joel E. Anderson
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

#ifndef __STUMPLESS_TEST_HELPER_ASSERT_HPP
#  define __STUMPLESS_TEST_HELPER_ASSERT_HPP

#  include <cstddef>
#  include <gtest/gtest.h>
#  include <stumpless.h>

#  define EXPECT_ERROR_ID_EQ( code ) \
error = stumpless_get_error(  );     \
EXPECT_TRUE( error != NULL );        \
if( error ) {                        \
  EXPECT_EQ( error->id, (code) );    \
}

#  define EXPECT_NO_ERROR EXPECT_FALSE( stumpless_has_error(  ) )

#endif /* __STUMPLESS_TEST_HELPER_ASSERT_HPP */
