/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2022 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_ELEMENT_H
#  define __STUMPLESS_PRIVATE_ELEMENT_H

#  include <stddef.h>
#  include <string.h>
#  include <stumpless/element.h>
#  include <stumpless/param.h>
#  include "private/param.h"

/**
 * Iterates the parameters of an element and executes the following block only
 * for parameters whose name matches the provided name.
 *
 * **Thread Safety: MT-Safe req:element-stable**
 * This macro locks each parameter during the name comparison but does not guard
 * against concurrent structural changes to the element's parameter array. No
 * other thread should modify the element's parameter list during iteration.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This macro is not safe to use from signal handlers due to locking.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This macro is not safe for threads that may be asynchronously cancelled
 * during the locking operations performed inside the macro.
 */
#define FOR_EACH_PARAM_WITH_NAME( ELEMENT, NAME ) \
for( i = 0; i < ( ELEMENT )->param_count; i++ ) {   \
  param = element->params[i];                       \
                                                    \
  lock_param( param );                              \
  cmp_result = strcmp( param->name, ( NAME ) );     \
  unlock_param( param );                            \
                                                    \
  if( cmp_result != 0 ) {                           \
    continue;                                       \
  }

/**
 * Locks the provided element.
 *
 * **Thread Safety: MT-Safe**
 * This function acquires the element's internal lock. Only one thread may hold
 * the same element's lock at a time.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * mutex routine.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled during the lock operation.
 *
 * @param element The element to lock. Must not be NULL.
 * 
 */
void
lock_element( const struct stumpless_element *element );

/**
 * Gets a parameter by index from a locked element, without performing additional locking.
 *
 * **Thread Safety: MT-Safe req:element-locked**
 * This function is safe when the caller already holds the element's lock. It
 * must not be called without the element being locked by the caller.
 *
 * **Async Signal Safety: AS-Unsafe**
 * This function is not intended for use in signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function does not allocate memory or perform blocking operations, but
 * safety depends on the caller maintaining the required lock.
 *
 * @param element The locked element to read from. Must not be NULL.
 *
 * @param index The zero-based index of the parameter to retrieve. Must be less
 * than the element's param_count.
 *
 * @return A pointer to the parameter at the requested index on success, or NULL
 * if the index is out of range.
 */
struct stumpless_param *
locked_get_param_by_index( const struct stumpless_element *element,
                           size_t index );

/**
 * Destroys the provided element, without performing a NULL check.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
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
 * @param element The element to destroy. Must not be NULL.
 */
void
unchecked_destroy_element( const struct stumpless_element *element );

/**
 * Does the same as stumpless_load_element, but without performing any
 * validation or NULL checks.
 *
 * **Thread Safety: MT-Safe race:element race:name**
 * This function is thread safe, assuming that the element and name are
 * not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a mutex initialization routine.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a mutex initialization routine.
 *
 * @param element The struct to load.
 *
 * @param name The name of the element.
 *
 * @param name_length The length of the name in bytes, not including the NULL
 * terminator.
 *
 * @return A pointer to the loaded element, if no error is encountered. If an
 * error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
struct stumpless_element *
unchecked_load_element( struct stumpless_element *element,
                        const char *name,
                        size_t name_length );

/**
 * Unloads the provided element, without performing a NULL check.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
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
 * @param element The element to unload. Must not be NULL.
 */
void
unchecked_unload_element( const struct stumpless_element *element );

/**
 * Unlocks the provided element.
 *
 * **Thread Safety: MT-Safe**
 * This function releases the element's internal lock. It must only be called
 * by the thread that currently holds the lock.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * mutex routine.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled during the unlock operation.
 *
 * @param element The element to unlock. Must not be NULL.
 */
void
unlock_element( const struct stumpless_element *element );

#endif /* __STUMPLESS_PRIVATE_ELEMENT_H */
