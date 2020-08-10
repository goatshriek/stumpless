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

#ifndef __STUMPLESS_PRIVATE_WFP_H
#  define __STUMPLESS_PRIVATE_WFP_H

/** @file
 * Wait-Free Pointer functions.
 */

#  include <stdatomic.h>
#  include <stddef.h>

#  define MAX_THREADS 16

struct wf_reference {
  void *pointer;
  unsigned alloc_era;
  unsigned retire_era;
};

struct wf_thread_state {
  // result is an unsigned int split into two parts:
  // A -> pointer index and B -> tag
  atomic_uint result;
  int era;
  size_t reference;
};

struct wfp {
  atomic_uint id;
  struct  wf_reference ref_cache[MAX_THREADS*MAX_THREADS];
  // reservations are an unsigned int split into two parts:
  // A -> era and B -> tag
  atomic_uint reservations[MAX_THREADS];
  // these fill the role of the extra two reservations
  atomic_uint extra_reservation_1[MAX_THREADS];
  atomic_uint extra_reservation_2[MAX_THREADS];
  struct wf_thread_state states[MAX_THREADS];
  atomic_uint counter_start;
  atomic_uint counter_end;
};

void
wfp_set( struct wfp *pointer, void *new_pointer );

void
wfp_destroy( const struct wfp *pointer );

void *
wfp_get( struct wfp *pointer );

struct wfp *
wfp_new( void *initial_pointer );

#endif /* __STUMPLESS_PRIVATE_WFP_H */
