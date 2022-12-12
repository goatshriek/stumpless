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

#  define FOR_EACH_PARAM_WITH_NAME( ELEMENT, NAME ) \
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

void
lock_element( const struct stumpless_element *element );

struct stumpless_param *
locked_get_param_by_index( const struct stumpless_element *element,
                           size_t index );

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

void
unlock_element( const struct stumpless_element *element );

#endif /* __STUMPLESS_PRIVATE_ELEMENT_H */
