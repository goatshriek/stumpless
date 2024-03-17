/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_TEST_HELPER_USAGE_HPP
#  define __STUMPLESS_TEST_HELPER_USAGE_HPP

#  include <cstddef>
#  include <stumpless.h>

void
add_messages( struct stumpless_target *target, size_t message_count );

void
repeat_add_entry( struct stumpless_target *target,
                  const struct stumpless_entry *entry,
                  size_t _count );

#endif /* __STUMPLESS_TEST_HELPER_USAGE_HPP */
