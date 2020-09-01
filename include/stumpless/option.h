/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2020 Joel E. Anderson
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
 * Options that can be used to modify the behavior of Stumpless components.
 */

#ifndef __STUMPLESS_OPTION_H
#  define __STUMPLESS_OPTION_H

#  include <stumpless/config.h>

/* options defined in syslog.h */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    include <syslog.h>
#  endif

/** Option to include the PID in stumpless messages. */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_PID    LOG_PID
#  else
#    define STUMPLESS_OPTION_PID    1
#  endif

/** Not currently supported. */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_CONS   LOG_CONS
#  else
#    define STUMPLESS_OPTION_CONS   (1<<1)
#  endif

/** Not currently supported. */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_NDELAY LOG_NDELAY
#  else
#    define STUMPLESS_OPTION_NDELAY (1<<2)
#  endif

/** Not currently supported. */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_ODELAY LOG_ODELAY
#  else
#    define STUMPLESS_OPTION_ODELAY (1<<3)
#  endif

/** Not currently supported. */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_NOWAIT LOG_NOWAIT
#  else
#    define STUMPLESS_OPTION_NOWAIT (1<<4)
#  endif

/** Empty option mask for explicit 'no option' use. */
#  define STUMPLESS_OPTION_NONE 0

#endif /* __STUMPLESS_OPTION_H */
