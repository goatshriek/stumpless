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

#ifndef __STUMPLESS_PRIVATE_WFI_H
#  define __STUMPLESS_PRIVATE_WFI_H

#include <stdbool.h>

struct wfi {
  int id;
};

bool
wfi_compare_and_exchange( struct wfi *wait_free_id, int old_id, int new_id );

void
wfi_destroy( const struct wfi *wait_free_id );

struct wfi *
wfi_new( int initial_id, void ( *retire_id )( int ) );

int
wfi_read( struct wfi *wait_free_id );

#endif /* __STUMPLESS_PRIVATE_WFI_H */
