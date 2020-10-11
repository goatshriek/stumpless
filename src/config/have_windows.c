// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2020 Joel E. Anderson
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

#include <stdbool.h>
#include <stddef.h>
#include <windows.h>
#include "private/config/have_windows.h"
#include "private/config/wrapper/thread_safety.h"

bool
windows_compare_exchange_bool( config_atomic_bool_t *b,
                               bool expected,
                               bool replacement ) {
  return false;
}

bool
windows_compare_exchange_ptr( config_atomic_ptr_t *p,
                              const void *expected,
                              void *replacement ) {
  return false;
}

void
windows_destroy_mutex( const config_mutex_t *mutex ){
  return;
}

size_t
windows_getpagesize( void ) {
  SYSTEM_INFO info;

  GetSystemInfo( &info );

  return ( size_t ) info.dwPageSize;
}

int
windows_getpid( void ) {
  return ( int ) ( GetCurrentProcessId(  ) );
}

void
windows_init_mutex( config_mutex_t *mutex ) {
  return;
}

void
windows_lock_mutex( const config_mutex_t *mutex ) {
  return;
}

void
windows_unlock_mutex( const config_mutex_t *mutex ) {
  return;
}
