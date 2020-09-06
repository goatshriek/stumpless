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

#include <cstddef>
#include <stumpless.h>
#include "test/helper/usage.hpp"

void
add_messages( struct stumpless_target *target, size_t message_count ) {
  for( size_t i = 0; i < message_count; i++ ) {
    stumpless_add_message( target,
                           "message number #%zd from thread #%d",
                           i,
                           pthread_self(  ) );
  }

  stumpless_free_thread(  );
}
