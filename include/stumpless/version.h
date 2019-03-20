/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2019 Joel E. Anderson
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
 * Runtime information about the library.
 */

#ifndef __STUMPLESS_VERSION_H
#  define __STUMPLESS_VERSION_H

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * A description of a library version. This project follows semantic versioning.
 */
struct stumpless_version {
  int major; /**< The major version. */
  int minor; /**< The minor version. */
  int patch; /**< The patch version. */
};

/**
 * Gets the version of code the library was built with.
 *
 * @return The version of code used by the library build.
 */
struct stumpless_version *
stumpless_get_version( void );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_VERSION_H */
