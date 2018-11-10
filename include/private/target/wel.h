/* SPDX-License-Identifier: Apache-2.0 */

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

#ifndef __STUMPLESS_PRIVATE_TARGET_WEL_H
#  define __STUMPLESS_PRIVATE_TARGET_WEL_H

#include <windows.h>
#include <stumpless/entry.h>

struct wel_target {
  HANDLE handle;
};

void
destroy_wel_target( struct wel_target *target );

struct wel_target *
new_wel_target( LPCSTR server_name, LPCSTR source_name );

int
send_entry_to_wel_target( const struct wel_target *target,
                          const struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_TARGET_WEL_H */
