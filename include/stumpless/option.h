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
 * Severity codes for classifying log entries. See RFC 5424 section 6.2.1 for
 * details on these values. Severities are defined to be compatible with the
 * syslog.h header if it is found on the system. Otherwise, they are defined as
 * closely as possible to the RFC 5424 specification.
 */

#ifndef __STUMPLESS_OPTION_H
#  define __STUMPLESS_OPTION_H

#  include <stumpless/config.h>

/* options defined in syslog.h */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE

#    include <syslog.h>

/* these don't have doxygen documentation as they are currently not supported
 * by the implementation */
#    define STUMPLESS_OPTION_PID    LOG_PID
#    define STUMPLESS_OPTION_CONS   LOG_CONS
#    define STUMPLESS_OPTION_NDELAY LOG_NDELAY
#    define STUMPLESS_OPTION_ODELAY LOG_ODELAY
#    define STUMPLESS_OPTION_NOWAIT LOG_NOWAIT

/* options normally defined in syslog.h */
#  else

#    define STUMPLESS_OPTION_PID    1
#    define STUMPLESS_OPTION_CONS   (1<<1)
#    define STUMPLESS_OPTION_NDELAY (1<<2)
#    define STUMPLESS_OPTION_ODELAY (1<<3)
#    define STUMPLESS_OPTION_NOWAIT (1<<4)

#  endif

/** Empty option mask for explicit 'no option' use. */
#  define STUMPLESS_OPTION_NONE 0

#endif /* __STUMPLESS_OPTION_H */
