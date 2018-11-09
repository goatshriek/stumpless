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

#ifndef __STUMPLESS_TARGET_FILE_H
#  define __STUMPLESS_TARGET_FILE_H

#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

  void
  stumpless_close_file_target( struct stumpless_target *target );

  struct stumpless_target *
  stumpless_open_file_target( const char *name,
                              int options,
                              int default_facility );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_FILE_H */
