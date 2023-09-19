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

/** @file
 * Chains allow logs to be sent to a group of targets.
 *
 * @since release v2.2.0
 *
 * **Thread Safety: MT-Safe**
 * Logging to chains is thread safe. A lock is used to prevent changes to the
 * chain during a logging operation. Note that the thread safety of each target
 * in the chain must also be considered when determining the thread safety of
 * an operation on a chain.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * Logging to chains is not signal safe, as a non-reentrant lock is used
 * to coordinate changes to the chain.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * Logging to chains is not safe to call from threads that may be
 * asynchronously cancelled, as the cleanup of the lock may not be completed.
 */

#ifndef __STUMPLESS_TARGET_CHAIN_H
#define __STUMPLESS_TARGET_CHAIN_H

#include <stumpless/config.h>
#include <stumpless/target.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Adds a target to an existing chain target.
 *
 * @since release v2.2.0
 *
 * @param chain The chain target to add the target to.
 *
 * @param target The new target to add to the chain.
 *
 * @return The chain target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
struct stumpless_target *
stumpless_add_target_to_chain( struct stumpless_target *chain,
                               struct stumpless_target *target );

/**
 * Closes a chain of targets.
 *
 * This function closes each target in the chain, and then destroys all memory
 * allocated for the chain itself.
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
 * @param target The chain of targets to close.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_chain_and_contents( struct stumpless_target *target );

/**
 * Closes a chain target.
 *
 * This function destroys all memory allocated for the chain itself. The targets
 * in the chain are not closed or modified.
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
 * @param target The chain to close.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_chain_only( struct stumpless_target *target );

/**
 * Creates a new target chain.
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
 * @param name The name of the logging target, as well as the name of the file
 * to open.
 *
 * @return The new chain if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_new_chain( const char *name );

#ifdef __cplusplus
}                               /* extern "C" */
#endif

#endif                          /* __STUMPLESS_TARGET_CHAIN_H */
