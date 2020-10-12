/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2020 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_TARGET_H
#  define __STUMPLESS_PRIVATE_TARGET_H

#include <stddef.h>
#include <stumpless/entry.h>
#include <stumpless/target.h>

void
destroy_target( const struct stumpless_target *target );

void
lock_target( const struct stumpless_target *target );

struct stumpless_target *
new_target( enum stumpless_target_type type,
            const char *name,
            int options,
            int default_facility );

struct stumpless_target *
open_unsupported_target( struct stumpless_target *target );

int
send_entry_to_unsupported_target( const struct stumpless_target *target,
                                  const struct stumpless_entry *entry );

int
sendto_unsupported_target( const struct stumpless_target *target,
                           const char *msg,
                           size_t msg_length );

void
target_free_global( void );

void
target_free_thread( void );

void
unlock_target( const struct stumpless_target *target );

int
unsupported_target_is_open( const struct stumpless_target *target );

#endif /* __STUMPLESS_PRIVATE_TARGET_H */
