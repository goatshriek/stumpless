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

#ifndef __STUMPLESS_SEVERITY_H
#  define __STUMPLESS_SEVERITY_H

#  include <stumpless/config.h>

/* severity codes as set by syslog.h */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE

#    include <syslog.h>

/** Emergency: system is unusable. */
#    define STUMPLESS_SEVERITY_EMERG    LOG_EMERG

/** Alert: action must be taken immediately. */
#    define STUMPLESS_SEVERITY_ALERT    LOG_ALERT

/** Critical: critical conditions. */
#    define STUMPLESS_SEVERITY_CRIT     LOG_CRIT

/** Error: error conditions. */
#    define STUMPLESS_SEVERITY_ERR      LOG_ERR

/** Warning: warning conditions. Included for compatibility with 1.x
 * releases.
 */
#    define STUMPLESS_SEVERITY_WARN     LOG_WARNING

/** Warning: warning conditions. */
#    define STUMPLESS_SEVERITY_WARNING  LOG_WARNING

/** Notice: normal but significant condition. */
#    define STUMPLESS_SEVERITY_NOTICE   LOG_NOTICE

/** Informational: informational messages. */
#    define STUMPLESS_SEVERITY_INFO     LOG_INFO

/** Debug: debug-level messages. */
#    define STUMPLESS_SEVERITY_DEBUG    LOG_DEBUG

/** Creates a severity mask for the provided severity. */
#    define STUMPLESS_SEVERITY_MASK(severity) (LOG_MASK(severity))

/** Creates a severity mask from EMERG up to the provided severity. */
#    define STUMPLESS_SEVERITY_MASK_UPTO(severity) (LOG_UPTO(severity))

/* severity codes as specified in RFC 5424 */
#  else

#    define STUMPLESS_SEVERITY_EMERG   0
#    define STUMPLESS_SEVERITY_ALERT   1
#    define STUMPLESS_SEVERITY_CRIT    2
#    define STUMPLESS_SEVERITY_ERR     3
#    define STUMPLESS_SEVERITY_WARN    4
#    define STUMPLESS_SEVERITY_WARNING 4
#    define STUMPLESS_SEVERITY_NOTICE  5
#    define STUMPLESS_SEVERITY_INFO    6
#    define STUMPLESS_SEVERITY_DEBUG   7

#    define STUMPLESS_SEVERITY_MASK(severity) (1<<(severity))
#    define STUMPLESS_SEVERITY_MASK_UPTO(severity) ((1<<((severity)+1))-1)

#  endif

#endif /* __STUMPLESS_SEVERITY_H */
