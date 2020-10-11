// SPDX-License-Identifier: Apache-2.0

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

#include <pthread.h>
#include <stddef.h>
#include "private/config/have_pthread.h"

void
pthread_destroy_mutex( const pthread_mutex_t *mutex ) {
  pthread_mutex_destroy( ( pthread_mutex_t * ) mutex );
}

void
pthread_init_mutex( pthread_mutex_t *mutex ) {
  pthread_mutex_init( mutex, NULL );
}

void
pthread_lock_mutex( const pthread_mutex_t *mutex ) {
  pthread_mutex_lock( ( pthread_mutex_t * ) mutex );
}

void
pthread_unlock_mutex( const pthread_mutex_t *mutex ) {
  pthread_mutex_unlock( ( pthread_mutex_t * ) mutex );
}
