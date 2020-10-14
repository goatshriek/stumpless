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
#include "private/config/have_windows.h"
#include "private/windows_wrapper.h"

bool
windows_compare_exchange_bool( LONG volatile *b,
                               LONG expected,
                               LONG replacement ) {
  LONG initial;

  initial = InterlockedCompareExchange( b, replacement, expected );
  return initial == expected;
}

bool
windows_compare_exchange_ptr( PVOID volatile *p,
                              const void *expected,
                              PVOID replacement ) {
  PVOID initial;
  
  initial = InterlockedCompareExchangePointer( p,
                                               replacement,
                                               ( PVOID ) expected );
  return initial == expected;
}

void
windows_destroy_mutex( const CRITICAL_SECTION *mutex ){
  DeleteCriticalSection( ( LPCRITICAL_SECTION ) mutex );
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
windows_init_mutex( LPCRITICAL_SECTION mutex ) {
  InitializeCriticalSection(mutex);
}

void
windows_lock_mutex( const CRITICAL_SECTION *mutex ) {
  EnterCriticalSection( ( LPCRITICAL_SECTION ) mutex );
}

void
windows_unlock_mutex( const CRITICAL_SECTION *mutex ) {
  LeaveCriticalSection( ( LPCRITICAL_SECTION ) mutex );
}
