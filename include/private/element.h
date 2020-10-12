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

#ifndef __STUMPLESS_PRIVATE_ELEMENT_H
#  define __STUMPLESS_PRIVATE_ELEMENT_H

#  include <stddef.h>
#  include <stumpless/element.h>
#  include <stumpless/param.h>

void
lock_element( const struct stumpless_element *element );

struct stumpless_param *
locked_get_param_by_index( const struct stumpless_element *element,
                           size_t index );

void
unchecked_destroy_element( const struct stumpless_element *element );

void
unlock_element( const struct stumpless_element *element );

#endif /* __STUMPLESS_PRIVATE_ELEMENT_H */
