/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2022 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_FACILITY_H
#  define __STUMPLESS_PRIVATE_FACILITY_H

/**
 * Gets the value of the facility from the given prival. This will be equivalent
 * to the STUMPLESS_FACILITY_*_VALUE constant for the facility.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param prival The prival to extract the facility from.
 *
 * @return the facility of the prival, as an integer.
 */
int
get_facility( int prival );

/**
 * Returns non-zero if a facility value is invalid.
 *
 * A valid facility value is the syslog-encoded facility (facility_id << 3):
 * a multiple of 8 in the inclusive range [0, 23 << 3]. Valid examples:
 * 0, 8, 16, ..., 184. Any value outside this range or not divisible by 8
 * is considered invalid.
 *
 * @param facility The encoded facility value to validate (facility_id << 3).
 * 
 * @return Non-zero if invalid; 0 if valid.
 *
 * **Thread Safety: MT-Safe**
 * **Async Signal Safety: AS-Safe**
 * **Async Cancel Safety: AC-Safe**
 * 
 */
int
facility_is_invalid( int facility );

#endif /* __STUMPLESS_PRIVATE_FACILITY_H */
