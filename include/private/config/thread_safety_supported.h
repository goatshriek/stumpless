/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_THREAD_SAFETY_SUPPORTED_H
#  define __STUMPLESS_PRIVATE_CONFIG_THREAD_SAFETY_SUPPORTED_H

#  include "private/config/wrapper/thread_safety.h"

/**
 * Destroys the mutex and releases its memory.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to use the mutex.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed.
 *
 * @param mutex The mutex to destroy.
 */
void
thread_safety_destroy_mutex( config_mutex_t *mutex );

/**
 * Frees all memory used for thread safety support.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * might be using.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of the
 * memory deallocation function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory deallocation function may not be AC-Safe itself.
 */
void
thread_safety_free_all( void );

/**
 * Creates a new mutex and initializes it for usage.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the possible
 * use of memory management functions to create the new mutex.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the possible use of memory management functions.
 *
 * @return The created and initialized mutex, or NULL if an error was
 * encountered.
 */
config_mutex_t *
thread_safety_new_mutex( void );

#endif /* __STUMPLESS_PRIVATE_CONFIG_THREAD_SAFETY_SUPPORTED_H */
