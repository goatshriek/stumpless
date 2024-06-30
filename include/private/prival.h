/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_PRIVAL_H
#define __STUMPLESS_PRIVATE_PRIVAL_H

#include <stumpless/facility.h>
#include <stumpless/severity.h>

/**
 * Gets the priority value from facility and severity parameters.
 *
 * Priority value is calculated by left shifting the facility value by 3
 * and adding it to the severity value which is according to the
 * RFC 5424 Section 6.2.1. The shift operation is done prior to get_prival()
 * function with macros in "facility.h"
 *
 * Moved from "private/entry.h" to "private/prival.h" in release v3.0.0.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe **
 * This function must be safe to call from signal handlers
 *
 * **Async Cancel Safety: AC-Safe**
 * This function must be safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @param facility Facility value. This should be a \c STUMPLESS_FACILITY value.
 *
 * @param severity Severity value. This should be a \c STUMPLESS_SEVERITY value
 *
 * @return Priority value
 */
int
get_prival( enum stumpless_facility facility,
            enum stumpless_severity severity );

#endif /* __STUMPLESS_PRIVATE_PRIVAL_H */
