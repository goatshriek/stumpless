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

/** @dir level
 * Header files for working with specific logging levels.
 */

/** @file
 * Masks that provide shorthand for enabling or disabling logging levels at
 * compile time.
 *
 * While this files does not contain any definitions itself, it provides the
 * logic that makes it possible to set a certain level of compile-time logging
 * using some shorthand definitions.
 *
 * Stumpless does not support mixing any of these masks with the
 * `STUMPLESS_DISABLE_<LEVEL_NAME>_LEVEL` definitions that remove specific
 * levels during compilation. If you need to disable a non-contiguous series
 * of levels, then you will need to explicitly disable each one, rather than
 * using a mask and disabling the remaining ones.
 *
 * The first mask definition is `STUMPLESS_ENABLE_UPTO_<LEVEL>`, which enables
 * all levels up to and including the named one, and disables all of those below
 * it. For example, defining `STUMPLESS_ENABLE_UPTO_WARNING` will enable
 * `EMERG`, `ALERT`, `CRIT`, `ERR`, and `WARNING` level calls and will
 * disable `NOTICE`, `INFO`, `DEBUG`, and `TRACE` level calls. Note that the
 * semantics of this mask closely resemble the `LOG_UPTO` macro provided in
 * `syslog.h` for runtime level filtering.
 *
 * By this logic, defining `STUMPLESS_ENABLE_UPTO_TRACE` enables all log levels.
 * Since this is the default for stumpless, this definition is effectively
 * ignored.
 *
 * As the corollary to the UPTO mask, the `STUMPLESS_DISABLE_DOWNTO_<LEVEL>`
 * definition will perform the opposite, disabling all levels down to and
 * including the named one and enabling all of those above it. For example,
 * defining `STUMPLESS_DISABLE_DOWNTO_WARNING` will enable `EMERG`, `ALERT`,
 * `CRIT`, and `ERR` level calls and will disable `WARNING`, `NOTICE`, `INFO`,
 * `DEBUG`, and `TRACE` level calls.
 *
 * This means that defining `STUMPLESS_DISABLE_DOWNTO_EMERG` disables all
 * logging calls that can be removed during compile time. There is also a
 * synonym for this which is more descriptive of the intent:
 * `STUMPLESS_DISABLE_ALL_LEVELS`.
 *
 * Note that for all of the above cases, the symbol must be defined _before_ the
 * inclusion of this header (or before inclusion of stumpless.h). The best way
 * to ensure that this happens is to pass it in as a definition during the build
 * process. If this is not possible, be sure that it is defined first in any
 * sources depending on this behavior.
 * 
 */

#ifndef __STUMPLESS_LEVEL_MASK_H
#  define __STUMPLESS_LEVEL_MASK_H

#  if defined( STUMPLESS_ENABLE_UPTO_DEBUG ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_TRACE )
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_ENABLE_UPTO_INFO ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_DEBUG )
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_ENABLE_UPTO_NOTICE ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_INFO )
#    define STUMPLESS_DISABLE_INFO_LEVEL 1
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_ENABLE_UPTO_WARNING ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_NOTICE )
#    define STUMPLESS_DISABLE_NOTICE_LEVEL 1
#    define STUMPLESS_DISABLE_INFO_LEVEL 1
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_ENABLE_UPTO_ERR ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_WARNING )
#    define STUMPLESS_DISABLE_WARNING_LEVEL 1
#    define STUMPLESS_DISABLE_NOTICE_LEVEL 1
#    define STUMPLESS_DISABLE_INFO_LEVEL 1
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_ENABLE_UPTO_CRIT ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_ERR )
#    define STUMPLESS_DISABLE_ERR_LEVEL 1
#    define STUMPLESS_DISABLE_WARNING_LEVEL 1
#    define STUMPLESS_DISABLE_NOTICE_LEVEL 1
#    define STUMPLESS_DISABLE_INFO_LEVEL 1
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_ENABLE_UPTO_ALERT ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_CRIT )
#    define STUMPLESS_DISABLE_CRIT_LEVEL 1
#    define STUMPLESS_DISABLE_ERR_LEVEL 1
#    define STUMPLESS_DISABLE_WARNING_LEVEL 1
#    define STUMPLESS_DISABLE_NOTICE_LEVEL 1
#    define STUMPLESS_DISABLE_INFO_LEVEL 1
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_ENABLE_UPTO_EMERG ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_ALERT )
#    define STUMPLESS_DISABLE_ALERT_LEVEL 1
#    define STUMPLESS_DISABLE_CRIT_LEVEL 1
#    define STUMPLESS_DISABLE_ERR_LEVEL 1
#    define STUMPLESS_DISABLE_WARNING_LEVEL 1
#    define STUMPLESS_DISABLE_NOTICE_LEVEL 1
#    define STUMPLESS_DISABLE_INFO_LEVEL 1
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#  if defined( STUMPLESS_DISABLE_ALL_LEVELS ) || \
      defined( STUMPLESS_DISABLE_DOWNTO_EMERG )
#    define STUMPLESS_DISABLE_EMERG_LEVEL 1
#    define STUMPLESS_DISABLE_ALERT_LEVEL 1
#    define STUMPLESS_DISABLE_CRIT_LEVEL 1
#    define STUMPLESS_DISABLE_ERR_LEVEL 1
#    define STUMPLESS_DISABLE_WARNING_LEVEL 1
#    define STUMPLESS_DISABLE_NOTICE_LEVEL 1
#    define STUMPLESS_DISABLE_INFO_LEVEL 1
#    define STUMPLESS_DISABLE_DEBUG_LEVEL 1
#    define STUMPLESS_DISABLE_TRACE_LEVEL 1
#  endif

#endif /* __STUMPLESS_LEVEL_MASK_H */
