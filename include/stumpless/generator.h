/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2024 Joel E. Anderson
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
 * Generic functionality to be used with STUMPLESS_FOREACH macros to allow for
 * more generic definition of enumerations and to string functions.
 */

#ifndef __STUMPLESS_GENERATOR_H
#define __STUMPLESS_GENERATOR_H

/**
 * Returns a definition of a symbol with the given name and value fit for use in
 * an enum definition. Compatible with \c STUMPLESS_FOREACH_ macro functions
 * such as STUMPLESS_FOREACH_FACILITY().
 *
 * @since release v2.0.0.
 */
#define STUMPLESS_GENERATE_ENUM( NAME, VALUE ) NAME = ( VALUE ),

#endif /* __STUMPLESS_GENERATOR_H */
