/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2023 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_TARGET_CHAIN_H
#define __STUMPLESS_PRIVATE_TARGET_CHAIN_H

#include <stddef.h>
#include <stumpless/config.h>
#include <stumpless/target.h>
#include "private/config/wrapper/thread_safety.h"

#define CHAIN_TARGET_ARRAY_SIZE 4

/**
 * Internal representation of a chain target.
 */
struct chain_target {
/** A static array of targets this chain contains.*/
  struct stumpless_target *targets[CHAIN_TARGET_ARRAY_SIZE];
/**
 * A dynamic array of targets this chain contains, if the static array is not
 * large enough. This will be NULL if it is not needed.
 */
  struct stumpless_target **overflow_targets;
/** The number of targets in this chain. */
  size_t target_count;
#ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * Protects the chain of targets. This mutex must be locked by a thread before
 * the chain can be modified or written to.
 */
  config_mutex_t chain_mutex;
#endif
};

void
destroy_chain_target( const struct chain_target *target );

struct chain_target *
new_chain_target( void );

/**
 * **Thread Safety: MT-Safe**
 * This function is thread safe. The chain_mutex is used to coordinate updates
 * to the chain.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate writes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 */
int
sendto_chain( struct chain_target *target,
              struct stumpless_entry *entry );

#endif /* __STUMPLESS_PRIVATE_TARGET_CHAIN_H */
