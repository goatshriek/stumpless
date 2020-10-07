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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_THREAD_SAFETY_H
#  define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_THREAD_SAFETY_H

#  include <stdbool.h>
#  include <stddef.h>
#  include <stumpless/config.h>
#  include "private/config.h"

#  ifndef STUMPLESS_THREAD_SAFETY_SUPPORTED
#    define config_destroy_mutex( MUTEX ) ( ( void ) 0 )
#    define config_init_mutex( MUTEX ) ( ( void ) 0 )
#    define config_lock_mutex( MUTEX ) ( ( void ) 0 )
#    define config_unlock_mutex( MUTEX ) ( ( void ) 0 )
#  elif defined HAVE_PTHREAD_H && defined HAVE_STDATOMIC_H
#    include <pthread.h>
#    include <stdatomic.h>
#    include <stdint.h>
typedef atomic_bool config_atomic_bool_t;
typedef atomic_uintptr_t config_atomic_ptr_t;
typedef pthread_mutex_t config_mutex_t;
#    include "private/config/have_pthread.h"
#    include "private/config/have_stdatomic.h"
#    define config_atomic_bool_false false
#    define config_atomic_bool_true true
#    define config_atomic_ptr_initializer ( uintptr_t ) NULL
#    define config_compare_exchange_bool stdatomic_compare_exchange_bool
#    define config_compare_exchange_ptr stdatomic_compare_exchange_ptr
#    define config_destroy_mutex pthread_destroy_mutex
#    define config_init_mutex pthread_init_mutex
#    define config_lock_mutex pthread_lock_mutex
#    define config_read_bool stdatomic_read_bool
#    define config_read_ptr stdatomic_read_ptr
#    define config_unlock_mutex pthread_unlock_mutex
#    define config_write_bool stdatomic_write_bool
#    define config_write_ptr stdatomic_write_ptr
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_THREAD_SAFETY_H */
