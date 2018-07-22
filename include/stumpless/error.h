/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018 Joel E. Anderson
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

#ifndef __STUMPLESS_ERROR_H
#  define __STUMPLESS_ERROR_H

#  ifdef __cplusplus
extern "C" {
#  endif

  enum stumpless_error_id {
    STUMPLESS_ARGUMENT_EMPTY,
    STUMPLESS_ARGUMENT_TOO_BIG,
    STUMPLESS_INVALID_ID,
    STUMPLESS_MEMORY_ALLOCATION_FAILURE,
    STUMPLESS_SOCKET_BIND_FAILURE,
    STUMPLESS_TARGET_UNSUPPORTED
  };

  struct stumpless_error {
    enum stumpless_error_id id;
  };

  struct stumpless_error *stumpless_get_error( void );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_ERROR_H */
