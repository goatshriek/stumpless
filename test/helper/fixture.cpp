// SPDX-License-Identifier: Apache-2.0

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

#include <stumpless.h>
#include "test/helper/fixture.hpp"

struct stumpless_entry *
create_entry( void ) {
  struct stumpless_entry *entry;

  entry = stumpless_new_entry( STUMPLESS_FACILITY_USER,
                               STUMPLESS_SEVERITY_INFO,
                               "fixture-app-name",
                               "fixture-msgid",
                               "fixture message" );

  stumpless_add_new_element( entry, "fixture-element" );

  stumpless_add_new_param_to_entry( entry,
                                    "fixture-element",
                                    "fixture-param-1",
                                    "fixture-value-1" );

  stumpless_add_new_param_to_entry( entry,
                                    "fixture-element",
                                    "fixture-param-2",
                                    "fixture-value-2" );

  return entry;
}
