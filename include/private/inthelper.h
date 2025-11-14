/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2019 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_INTHELPER_H
#  define __STUMPLESS_PRIVATE_INTHELPER_H

#  include <stddef.h>

/**
 * The maximum possible size of an integer when it is converted to a string.
 *
 * This may be a little heavy-handed, but there is potential for different
 * systems to support different sizes, and without a more precise way to figure
 * this out we'll stick with this.
 */
#  define MAX_INT_SIZE 50

/**
 * Converts a `size_t` value to an `int`, capping at `INT_MAX` if necessary.
 *
 * This helper prevents integer overflow when a `size_t` value must be used
 * in an interface that accepts only signed integers. If `val` exceeds
 * `INT_MAX`, the function returns `INT_MAX`; otherwise it returns `(int) val`.
 *
 * **Thread Safety: MT-Safe**
 * Performs only arithmetic on the provided argument; uses no shared state.
 *
 * **Async Signal Safety: AS-Safe**
 * Contains only simple arithmetic and comparison; safe for use in signal
 * handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * Contains no cancellation points.
 *
 * @param val The non-negative value to convert.
 * @return `(int) val` when within range, or `INT_MAX` if capped.
 */
int
cap_size_t_to_int( size_t val );


/**
 * Converts a size_t value to int with overflow detection.
 *
 * Returns -1 if @p val is greater than INT_MAX; otherwise returns (int) @p val.
 * Typical use: preparing a size_t index for APIs that take an int error/code,
 * e.g., raise_error(..., size_t_to_int(index), ...).
 *
 * @param val The non-negative value to convert.
 * 
 * @return (int) val when val <= INT_MAX; otherwise -1 to indicate overflow.
 *
 * **Thread Safety: MT-Safe**
 * **Async Signal Safety: AS-Safe**
 * **Async Cancel Safety: AC-Safe**
 * Performs only integer comparison/cast; no locking, allocation, or I/O.
 * 
 */
int
size_t_to_int( size_t val );

#endif /* __STUMPLESS_PRIVATE_INTHELPER_H */
