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

#include <stdbool.h>
#include "private/wfi.h"

bool
wfi_compare_and_exchange( struct wfi *wait_free_id, int old_id, int new_id ){
  return false;
}

void
wfi_destroy( const struct wfi *wait_free_id ){
  return;
}

struct wfi *
wfi_new( int initial_id, void ( *retire_id )( int ) ){
  return NULL;
}

int
wfi_read( struct wfi *wait_free_id ){
  return 0;
}

/* pseudocode from wfe paper */

/*
int counter_start = 0;
int counter_end = 0;
int_pair // Each pair is { .A,.B }
 reservations[max_threads][max_hes+2] = { ∞,0 };

struct state_s {
int_pair result; // Initially: { nullptr,∞ }
int era; // Initially: ∞
void* pointer; // Initially: nullptr
};
state_s state[max_threads][max_hes];

// Read a block pointer
block* get_protected(block** ptr,
                     int index,
                     block* parent) {
  int prevEra = reservations[tid][index].A;
  int attempts = max_attempts;
  while (--attempts ≠ 0) { // Fast path
    block* ret = *ptr;
    int newEra = global_era;
    if (prevEra == newEra) return ret;
    reservations[tid][index].A = newEra;
    prevEra = newEra;
  }

  // Fetch parent’s era for [ptr] protection
  if (parent == nullptr) alloc_era = ∞;
  else alloc_era = parent->alloc_era;
  // Slow path, request helping
  F&A(&counter_start, 1);
  state[tid][index].pointer = ptr;
  state[tid][index].era = alloc_era;
  int tag = reservations[tid][index].B;
  state[tid][index].result = {invptr,tag};
  do { // Bounded by # of in-flight threads
  block* ret = *ptr;
  int newEra = global_era;
  if (prevEra == newEra &&
  WCAS(&state[tid][index].result,
   {invptr,tag}, {nullptr,∞}) {
  reservations[tid][index].B = tag + 1;
  F&A(counter_end, 1);
  return ret;
  }
  // Ignore failures, the loop will exit
  WCAS(&reservations[tid][index],
   {prevEra,tag}, {newEra,tag});
  prevEra = newEra;
  res_ptr = state[tid][index].result.A;
  } while (res_ptr == invptr);
  int res_era = state[tid][index].result.B;
  reservations[tid][index].A = res_era;
  reservations[tid][index].B = tag + 1;
  F&A(&counter_end, 1);
  return res_ptr;
}

void cleanup() { // A new cleanup() procedure
foreach blk in retire_list {
int ce = counter_end;
if (!can_delete(blk, 0, max_hes) ||
 !can_delete(blk, max_hes, max_hes+1))
continue;
if (ce == counter_start ||
(can_delete(blk, max_hes+1, max_hes+2)
&& can_delete(blk, 0, max_hes))
free(blk);
} }
// Allocate a memory block
block* alloc_block(int size) {
if (alloc_counter++ % era_freq == 0)
increment_era(tid);
block* ptr = new block(size);
ptr->alloc_era = global_era;
return ptr;
}

// Retire a memory block
void retire(block* ptr) {
ptr->retire_era = global_era;
retire_list.append(ptr);
if (retire_counter++ % cleanup_freq == 0) {
if (ptr->retire_era == global_era)
increment_era(tid);
cleanup();
}
}

// Help others before incrementing an era
void increment_era(int tid) {
int ce = counter_end;
int cs = counter_start;
if (cs – ce ≠ 0) {
for (int i = 0; i < max_threads; i++) {
for (int j = 0; j < max_hes; j++) {
void* ptr = state[i][j].result.A;
if (ptr == invptr)
help_thread(i, j, tid);
} } }
F&A(&global_era, 1);
}

// An internal function to help other threads
void help_thread(int i, int j, int tid) {
int_pair res = state[i][j].result;
if (res.A ≠ invptr) return;
int era = state[i][j].era;
reservations[tid][max_hes].A = era;
block** ptr = state[i][j].pointer;
int tag = reservations[i][j].B;
if (tag ≠ res.B) goto exit;
// All state data were read consistently
int prevEra = global_era;
do { // Bounded by # of in-flight threads
reservations[tid][max_hes+1] = prevEra;
block* ret_ptr = *ptr;
int newEra = global_era;
if (prevEra == newEra) {
if (WCAS(&state[i][j].result,
res, {ret_ptr,newEra}) {
do { // At most 2 iterations
old = reservations[i][j];
if (old.B ≠ tag) break;
ok = WCAS(&reservations[i][j],
old, {newEra,tag+1});
} while (!ok);
}
break;
}
prevEra = newEra;
} while (state[i][j].result == res);
reservations[tid][max_hes+1] = ∞;
exit:
reservations[tid][max_hes].A = ∞;
}
*/
