/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2024 Joel E. Anderson
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
#include <stumpless/entry.h>
#include <stumpless/target.h>
#include "private/config/wrapper/thread_safety.h"

/**
 * The length of the array in the chain target structure. Chains where all
 * targets fit into this array will require less dynamic memory and fewer
 * dereferences, speeding up their performance.
 *
 * @since release v2.2.0
 */
#define CHAIN_TARGET_ARRAY_LENGTH 4

/**
 * Internal representation of a chain target.
 *
 * @since release v2.2.0
 */
struct chain_target {
/** A static array of targets this chain contains.*/
  struct stumpless_target *targets[STUMPLESS_CHAIN_TARGET_ARRAY_LENGTH];
/**
 * A dynamic array of targets this chain contains, if the static array is not
 * large enough. This will be NULL if it is not needed.
 */
  struct stumpless_target **overflow_targets;
/** The total number of targets in this chain. */
  size_t target_count;
#ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * Protects the chain of targets. This mutex must be locked by a thread before
 * the chain can be modified or written to.
 */
  config_mutex_t chain_mutex;
#endif
};

/**
 * Destroys a chain target, but does not modify the targets it holds.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this target.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @param chain The chain target to destroy.
 */
void
destroy_chain_target( const struct chain_target *chain );

/**
 * Acquires the lock for the provided chain target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a non-reentrant lock.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, , due to the use of a lock that could be left locked.
 *
 * @since release v2.2.0
 *
 * @param chain The chain target to lock. Must not be NULL.
 */
void
lock_chain_target( struct chain_target *chain );

/**
 * Creates a new empty chain target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @return The new chain target if no errors are encountered. In the event of
 * an error, NULL is returned and an error code is set appropriately.
 */
struct chain_target *
new_chain_target( void );

/**
 * Sends an entry to every target in the chain.
 *
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
 *
 * @since release v2.2.0
 *
 * @param chain The chain target to send the entry to.
 *
 * @param entry The entry to send to all targets in this chain.
 *
 * @return The result of the send for the final target in the chain. If any send
 * fails, the rest of the targets do not receive the entry and the return value
 * of the failing target is returned.
 */
int
send_entry_to_chain_target( struct chain_target *chain,
                            const struct stumpless_entry *entry );

/**
 * Releases the lock for the provided chain target.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a non-reentrant lock.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, , due to the use of a lock that could be left locked.
 *
 * @since release v2.2.0
 *
 * @param chain The chain target to unlock. Must not be NULL.
 */
void
unlock_chain_target( struct chain_target *chain );

#endif /* __STUMPLESS_PRIVATE_TARGET_CHAIN_H */
