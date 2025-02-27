/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2021 Joel E. Anderson
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
typedef bool config_atomic_bool_t;
typedef int config_atomic_int_t;
typedef void * config_atomic_ptr_t;
#    define CONFIG_THREAD_LOCAL_STORAGE
#    include "private/config/thread_safety_unsupported.h"
#    define config_assign_cached_mutex( MUTEX ) ( ( void ) 0 )
#    define config_atomic_bool_false false
#    define config_atomic_bool_true true
#    define config_atomic_ptr_initializer NULL
#    define config_check_mutex_valid( MUTEX ) ( true )
#    define config_compare_exchange_bool no_thread_safety_compare_exchange_bool
#    define config_compare_exchange_ptr no_thread_safety_compare_exchange_ptr
#    define config_destroy_mutex( MUTEX ) ( ( void ) 0 )
#    define config_destroy_cached_mutex( MUTEX ) ( ( void ) 0 )
#    define config_init_mutex( MUTEX ) ( ( void ) 0 )
#    define config_lock_mutex( MUTEX ) ( ( void ) 0 )
#    define CONFIG_MUTEX_T_SIZE 0
#    define config_read_bool( B ) *( B )
#    define config_read_int( I ) *( I )
#    define config_read_ptr( P ) *( P )
#    define config_thread_safety_free_all(  ) ( ( void ) 0 )
#    define config_unlock_mutex( MUTEX ) ( ( void ) 0 )
#    define config_write_bool( B, REPLACEMENT ) *( B ) = ( REPLACEMENT )
#    define config_write_int( I, REPLACEMENT ) *( I ) = ( REPLACEMENT )
#    define config_write_ptr( P, REPLACEMENT ) *( P ) = ( REPLACEMENT )
#  elif defined HAVE_PTHREAD_H && defined HAVE_STDATOMIC_H
#    include <pthread.h>
#    include <stdatomic.h>
#    include <stdint.h>
typedef atomic_bool config_atomic_bool_t;
typedef atomic_int config_atomic_int_t;
typedef atomic_uintptr_t config_atomic_ptr_t;
typedef pthread_mutex_t config_mutex_t;
#    define CONFIG_THREAD_LOCAL_STORAGE __thread
#    include "private/config/have_pthread.h"
#    include "private/config/have_stdatomic.h"
#    include "private/config/thread_safety_supported.h"
#    define config_assign_cached_mutex( MUTEX ) \
( MUTEX = thread_safety_new_mutex(  ) )
#    define config_atomic_bool_false false
#    define config_atomic_bool_true true
#    define config_atomic_ptr_initializer ( uintptr_t ) NULL
#    define config_check_mutex_valid( MUTEX ) ( MUTEX != NULL )
#    define config_compare_exchange_bool stdatomic_compare_exchange_bool
#    define config_compare_exchange_ptr stdatomic_compare_exchange_ptr
#    define config_destroy_cached_mutex( MUTEX ) \
( thread_safety_destroy_mutex( MUTEX ) )
#    define config_destroy_mutex pthread_destroy_mutex
#    define config_init_mutex pthread_init_mutex
#    define config_lock_mutex pthread_lock_mutex
#    define CONFIG_MUTEX_T_SIZE sizeof( config_mutex_t )
#    define config_read_bool stdatomic_read_bool
#    define config_read_int stdatomic_read_int
#    define config_read_ptr stdatomic_read_ptr
#    define config_thread_safety_free_all thread_safety_free_all
#    define config_unlock_mutex pthread_unlock_mutex
#    define config_write_bool stdatomic_write_bool
#    define config_write_int stdatomic_write_int
#    define config_write_ptr stdatomic_write_ptr
#  elif defined HAVE_WINDOWS_H
#    include "private/config/have_windows.h"
#    include "private/windows_wrapper.h"
typedef LONG volatile config_atomic_bool_t;
typedef INT volatile config_atomic_int_t;
typedef PVOID volatile config_atomic_ptr_t;
typedef CRITICAL_SECTION config_mutex_t;
#    include "private/config/thread_safety_supported.h"
#    define CONFIG_THREAD_LOCAL_STORAGE __declspec( thread )
#    define config_assign_cached_mutex( MUTEX ) \
( MUTEX = thread_safety_new_mutex(  ) )
#    define config_atomic_bool_false false
#    define config_atomic_bool_true true
#    define config_atomic_ptr_initializer NULL
#    define config_check_mutex_valid( MUTEX ) ( MUTEX != NULL )
#    define config_compare_exchange_bool windows_compare_exchange_bool
#    define config_compare_exchange_ptr windows_compare_exchange_ptr
#    define config_destroy_cached_mutex( MUTEX ) \
( thread_safety_destroy_mutex( MUTEX ) )
#    define config_destroy_mutex windows_destroy_mutex
#    define config_init_mutex windows_init_mutex
#    define config_lock_mutex windows_lock_mutex
#    define CONFIG_MUTEX_T_SIZE sizeof( config_mutex_t )
#    define config_read_bool( B ) *( B )
#    define config_read_int( I ) *( I )
#    define config_read_ptr( P ) *( P )
#    define config_thread_safety_free_all thread_safety_free_all
#    define config_unlock_mutex windows_unlock_mutex
#    define config_write_bool( B, REPLACEMENT ) *( B ) = ( REPLACEMENT )
#    define config_write_int( I, REPLACEMENT ) *( I ) = ( REPLACEMENT )
#    define config_write_ptr( P, REPLACEMENT ) *( P ) = ( REPLACEMENT )
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_THREAD_SAFETY_H */
