
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

#ifndef __STUMPLESS_TARGET_BUFFER_H
#  define __STUMPLESS_TARGET_BUFFER_H

#  include <stddef.h>
#  include <stumpless/target.h>

#  ifdef __cplusplus
extern "C" {
#  endif

  void stumpless_close_buffer_target( struct stumpless_target *target );
  struct stumpless_target *stumpless_open_buffer_target( const char *name,
                                                         char *buffer,
                                                         size_t size,
                                                         int options,
                                                         int facility );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif                          /* __STUMPLESS_TARGET_BUFFER_H */
