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

#  include <stumpless/config.h>
#  include "private/config.h"

#  ifndef STUMPLESS_THREAD_SAFETY_SUPPORTED
#    define config_destroy_mutex( MUTEX ) ( ( void ) 0 )
#    define config_init_mutex( MUTEX ) ( ( void ) 0 )
#    define config_lock_mutex( MUTEX ) ( ( void ) 0 )
#    define config_unlock_mutex( MUTEX ) ( ( void ) 0 )
#  elif defined HAVE_PTHREAD_H
#    include <pthread.h>
typedef pthread_mutex_t config_mutex_t;
#    include "private/config/have_pthread.h"
#    define config_destroy_mutex pthread_destroy_mutex
#    define config_init_mutex pthread_init_mutex
#    define config_lock_mutex pthread_lock_mutex
#    define config_unlock_mutex pthread_unlock_mutex
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_THREAD_SAFETY_H */
