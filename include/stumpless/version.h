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

/**
 * Creates a string representation of the given version.
 *
 * This string will be NULL-terminated, and will appear in the standard
 * semantic versioning format of 'major.minor.patch'.
 *
 * @param version The version to convert to a string.
 *
 * @return A string representation of the provided version. This should be
 * destroyed via the memory deallocation function currently configured via
 * stumpless_set_free(). If an error is encountered, then NULL is returned
 * and an error code is set appropriately.
 */
char *
stumpless_version_to_string( const struct stumpless_version *version );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_VERSION_H */
