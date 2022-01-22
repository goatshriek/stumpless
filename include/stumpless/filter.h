/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2022 Joel E. Anderson
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

/** @file
 * Filters that can be used to control which entries are sent to targets at
 * runtime.
 *
 * @since release v2.1.0
 */

#ifndef __STUMPLESS_FILTER_H
#  define __STUMPLESS_FILTER_H

#  include <stdbool.h>
#  include <stumpless/entry.h>
#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * Compares the severity of the entry to the current mask of the target, and
 * only passes the entry if the mask bit corresponding to the severity is set.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * target while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the target.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked..
 *
 * @since release v2.1.0
 *
 * @param target The target that the entry will be sent to if it passes.
 *
 * @param entry The entry that is being submitted to the target.
 *
 * @return true if the severity of the entry is set in the target's mask,
 * false otherwise.
 */
bool
stumpless_mask_filter( const struct stumpless_target *target,
                       const struct stumpless_entry *entry );

#  ifdef __cplusplus
} /* extern "C" */
#  endif

#endif /* __STUMPLESS_FILTER_H */
