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

#ifndef __STUMPLESS_PRIVATE_CONFIG_JOURNALD_SUPPORTED_H
#  define __STUMPLESS_PRIVATE_CONFIG_JOURNALD_SUPPORTED_H

#  include <stumpless/element.h>
#  include <stumpless/param.h>

/**
 * Initializes an element's journald fields.
 *
 * **Thread Safety: MT-Unsafe*
 * This function is not thread safe; it should only be used on elements that
 * are already locked by the caller.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param element The element to initialize.
 */
void
journald_init_journald_element( struct stumpless_element *element );

/**
 * Initializes a param's journald fields.
 *
 * **Thread Safety: MT-Unsafe*
 * This function is not thread safe; it should only be used on params that
 * are already locked by the caller.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param param The param to initialize.
 */
void
journald_init_journald_param( struct stumpless_param *param );

#endif /* __STUMPLESS_PRIVATE_CONFIG_JOURNALD_SUPPORTED_H */
