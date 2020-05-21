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
 * Facility codes for classifying log entries. See RFC 5424 section 6.2.1 for
 * details on these values. Facilities are defined to be compatible with the
 * syslog.h header if it is found on the system. Otherwise, they are defined as
 * closely as possible to the RFC 5425 specification. Some facilities do not
 * exist in the syslog.h header and as such are defined here in either case.
 */

#ifndef __STUMPLESS_FACILITY_H
#  define __STUMPLESS_FACILITY_H

#  include <stumpless/config.h>

/* facility codes as set by syslog.h */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE

#    include <syslog.h>

/** Kernel messages. */
#    define STUMPLESS_FACILITY_KERN   LOG_KERN

/** User-level messages. */
#    define STUMPLESS_FACILITY_USER   LOG_USER

/** Mail system. */
#    define STUMPLESS_FACILITY_MAIL   LOG_MAIL

/** Network news subsystem. */
#    define STUMPLESS_FACILITY_NEWS   LOG_NEWS

/** UUCP subsystem. */
#    define STUMPLESS_FACILITY_UUCP   LOG_UUCP

/** System daemons. */
#    define STUMPLESS_FACILITY_DAEMON LOG_DAEMON

/** Security/authorization messages. */
#    define STUMPLESS_FACILITY_AUTH   LOG_AUTH

/** Clock daemon. */
#    define STUMPLESS_FACILITY_CRON   LOG_CRON

/** Line printer subsystem. */
#    define STUMPLESS_FACILITY_LPR    LOG_LPR

/** Local use 0. */
#    define STUMPLESS_FACILITY_LOCAL0 LOG_LOCAL0

/** Local use 1. */
#    define STUMPLESS_FACILITY_LOCAL1 LOG_LOCAL1

/** Local use 2. */
#    define STUMPLESS_FACILITY_LOCAL2 LOG_LOCAL2

/** Local use 3. */
#    define STUMPLESS_FACILITY_LOCAL3 LOG_LOCAL3

/** Local use 4. */
#    define STUMPLESS_FACILITY_LOCAL4 LOG_LOCAL4

/** Local use 5. */
#    define STUMPLESS_FACILITY_LOCAL5 LOG_LOCAL5

/** Local use 6. */
#    define STUMPLESS_FACILITY_LOCAL6 LOG_LOCAL6

/** Local use 7. */
#    define STUMPLESS_FACILITY_LOCAL7 LOG_LOCAL7

/* facility codes as specified in RFC 5424*/
#  else

#    define STUMPLESS_FACILITY_KERN   0
#    define STUMPLESS_FACILITY_USER   (1<<3)
#    define STUMPLESS_FACILITY_MAIL   (2<<3)
#    define STUMPLESS_FACILITY_DAEMON (3<<3)
#    define STUMPLESS_FACILITY_AUTH   (4<<3)
#    define STUMPLESS_FACILITY_LPR    (6<<3)
#    define STUMPLESS_FACILITY_NEWS   (7<<3)
#    define STUMPLESS_FACILITY_UUCP   (8<<3)
#    define STUMPLESS_FACILITY_CRON   (9<<3)
#    define STUMPLESS_FACILITY_LOCAL0 (16<<3)
#    define STUMPLESS_FACILITY_LOCAL1 (17<<3)
#    define STUMPLESS_FACILITY_LOCAL2 (18<<3)
#    define STUMPLESS_FACILITY_LOCAL3 (19<<3)
#    define STUMPLESS_FACILITY_LOCAL4 (20<<3)
#    define STUMPLESS_FACILITY_LOCAL5 (21<<3)
#    define STUMPLESS_FACILITY_LOCAL6 (22<<3)
#    define STUMPLESS_FACILITY_LOCAL7 (23<<3)

#  endif

/* remaining facility codes specified in RFC 5424 */

/** Messages generated internally by logging daemon. */
#  define STUMPLESS_FACILITY_SYSLOG (5<<3)

/** Security/authorization messages. */
#  define STUMPLESS_FACILITY_AUTH2  (10<<3)

/** FTP daemon. */
#  define STUMPLESS_FACILITY_FTP    (11<<3)

/** NTP subsystem. */
#  define STUMPLESS_FACILITY_NTP    (12<<3)

/** Log audit. */
#  define STUMPLESS_FACILITY_AUDIT  (13<<3)

/** Log alert. */
#  define STUMPLESS_FACILITY_ALERT  (14<<3)

/** Clock daemon. */
#  define STUMPLESS_FACILITY_CRON2  (15<<3)

#endif /* __STUMPLESS_FACILITY_H */
