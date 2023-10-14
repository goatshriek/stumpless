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

#ifndef __STUMPLESS_PRIVATE_CONFIG_THREAD_SAFETY_UNSUPPORTED_H
#  define __STUMPLESS_PRIVATE_CONFIG_THREAD_SAFETY_UNSUPPORTED_H

#  include <stdbool.h>
#  include "private/config/wrapper/thread_safety.h"

bool
no_thread_safety_compare_exchange_bool( config_atomic_bool_t *b,
                                        bool expected,
                                        bool replacement );

bool
no_thread_safety_compare_exchange_ptr( config_atomic_ptr_t *p,
                                       const void *expected,
                                       void *replacement );

#endif /* __STUMPLESS_PRIVATE_CONFIG_THREAD_SAFETY_UNSUPPORTED_H */
