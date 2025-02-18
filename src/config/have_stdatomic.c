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

#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include "private/config/have_stdatomic.h"

bool
stdatomic_compare_exchange_bool( atomic_bool *b,
                                 bool expected,
                                 bool replacement ) {
  return atomic_compare_exchange_strong( b, &expected, replacement );
}

bool
stdatomic_compare_exchange_ptr( atomic_uintptr_t *p,
                                const void *expected,
                                const void *replacement ) {
  uintptr_t expected_uint = ( uintptr_t ) expected;

  return atomic_compare_exchange_strong( p,
                                         &expected_uint,
                                         ( uintptr_t ) replacement );
}

bool
stdatomic_read_bool( atomic_bool *b ) {
  return ( bool ) atomic_load( b );
}

int
stdatomic_read_int( atomic_int *i ) {
  return ( int ) atomic_load( i );
}

void *
stdatomic_read_ptr( atomic_uintptr_t *p ) {
  return ( void * ) atomic_load( p );
}

void
stdatomic_write_bool( atomic_bool *b, bool replacement ) {
  atomic_store( b, replacement );
}

void
stdatomic_write_int( atomic_int *i, int replacement ) {
  atomic_store( i, replacement );
}

void
stdatomic_write_ptr( atomic_uintptr_t *p, void *replacement ) {
  atomic_store( p, ( uintptr_t ) replacement );
}
