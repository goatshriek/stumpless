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

#ifndef __STUMPLESS_VERSION_H
#define __STUMPLESS_VERSION_H

#define STUMPLESS_MAJOR_VERSION 0
#define STUMPLESS_MINOR_VERSION 0
#define STUMPLESS_PATCH_VERSION 1

#ifdef __cplusplus
extern "C" {
#endif

struct stumpless_version {
  int major;
  int minor;
  int patch;
};

struct stumpless_version *get_stumpless_version();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_VERSION_H */
