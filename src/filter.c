// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2022 Joel E. Anderson
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

#include <stdbool.h>
#include <stumpless/entry.h>
#include <stumpless/filter.h>
#include <stumpless/target.h>

bool
stumpless_mask_filter( const struct stumpless_target *target,
                       const struct stumpless_entry *entry ) {
  return STUMPLESS_SEVERITY_MASK( stumpless_get_entry_severity( entry ) )
           & stumpless_get_target_mask( target );
}
