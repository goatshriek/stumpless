/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020 Joel E. Anderson
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

#ifndef __STUMPLESS_TEST_HELPER_MEMORY_ALLOCATION_HPP
#  define __STUMPLESS_TEST_HELPER_MEMORY_ALLOCATION_HPP

#  include <cstddef>
#  include <cstdlib>

#  define MALLOC_FAIL         \
[]( size_t size ) -> void * { \
  return NULL;                \
}

#  define MALLOC_FAIL_ON_SIZE( fail_size ) \
[]( size_t size ) -> void * {              \
  if( size == ( fail_size ) ) {            \
    return NULL;                           \
  } else {                                 \
    return malloc( size );                 \
  }                                        \
}

#  define REALLOC_FAIL           \
[]( void *, size_t ) -> void * { \
  return NULL;                   \
}

#endif /* __STUMPLESS_TEST_HELPER_MEMORY_ALLOCATION_HPP */
