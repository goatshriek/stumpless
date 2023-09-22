/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021-2023 Joel E. Anderson
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

/**
 * @file
 * Functions that help when using journald targets.
 */

#ifndef __STUMPLESS_CONFIG_JOURNALD_SUPPORTED_H
#  define __STUMPLESS_CONFIG_JOURNALD_SUPPORTED_H

#  include <stumpless/config.h>
#  include <stumpless/element.h>
#  include <stumpless/param.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Gets the function used to derive the name of the field for this element
 * when logging to journald targets.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate with other
 * accesses to the element.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock which could be left locked.
 *
 * @since release v2.1.0
 *
 * @param element The element to get the function of.
 *
 * @return The namer function of the element if no error is encountered. If an
 * error is encountered, NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
stumpless_element_namer_func_t
stumpless_get_element_journald_namer( const struct stumpless_element *element );

/**
 * Gets the function used to derive the name of the field for this param
 * when logging to journald targets.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate with other
 * accesses to the param.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock which could be left locked.
 *
 * @since release v2.1.0
 *
 * @param param The param to get the function of.
 *
 * @return The namer function of the param if no error is encountered. If an
 * error is encountered, NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
stumpless_param_namer_func_t
stumpless_get_param_journald_namer( const struct stumpless_param *param );

/**
 * Sets the function used to derive the name of the field for this element
 * when logging to journald targets.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate with other
 * accesses to the element.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock which could be left locked.
 *
 * @since release v2.1.0
 *
 * @param element The element to set the function of.
 *
 * @param namer The naming function to use for the element.
 *
 * @return The modified element if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_set_element_journald_namer( struct stumpless_element *element,
                                      stumpless_element_namer_func_t namer );

/**
 * Sets the function used to derive the name of the field for this param
 * when logging to journald targets.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate with other
 * accesses to the param.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock which could be left locked.
 *
 * @since release v2.1.0
 *
 * @param param The param to set the function of.
 *
 * @param namer The naming function to use for the param.
 *
 * @return The modified param if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_set_param_journald_namer( struct stumpless_param *param,
                                    stumpless_param_namer_func_t namer );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_CONFIG_JOURNALD_SUPPORTED_H */
