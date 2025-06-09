/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2024 Joel E. Anderson
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
 * details on these values. The underlying values of facilities are defined to
 * be compatible with the syslog.h header if it is found on the system.
 * Otherwise, they are defined as closely as possible to the RFC 5425
 * specification. Some facilities do not exist in the syslog.h header and as
 * such are always defined according to the RFC.
 */

#ifndef __STUMPLESS_FACILITY_H
#  define __STUMPLESS_FACILITY_H

#  include <stumpless/config.h>
#  include <stumpless/generator.h>
#  include <stddef.h>

#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    include <syslog.h>
#  endif

/**
 * Kernel message facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_KERN_VALUE LOG_KERN
#  else
#    define STUMPLESS_FACILITY_KERN_VALUE 0
#  endif

/**
 * User-level message facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_USER_VALUE LOG_USER
#  else
#    define STUMPLESS_FACILITY_USER_VALUE ( 1 << 3 )
#  endif

/**
 * Mail system facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_MAIL_VALUE LOG_MAIL
#  else
#    define STUMPLESS_FACILITY_MAIL_VALUE ( 2 << 3 )
#  endif

/**
 * System daemons facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_DAEMON_VALUE LOG_DAEMON
#  else
#    define STUMPLESS_FACILITY_DAEMON_VALUE ( 3 << 3 )
#  endif

/**
 *
 * Facility code value for security/authorization messages.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_AUTH_VALUE LOG_AUTH
#  else
#    define STUMPLESS_FACILITY_AUTH_VALUE ( 4 << 3 )
#  endif

/**
 * Facility code value for messages generated internally by the logging daemon
 * as defined by RFC 5424.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FACILITY_SYSLOG_VALUE ( 5 << 3 )

/**
 * Line printer subsystem facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LPR_VALUE LOG_LPR
#  else
#    define STUMPLESS_FACILITY_LPR_VALUE ( 6 << 3 )
#  endif

/**
 * Network news subsystem facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_NEWS_VALUE LOG_NEWS
#  else
#    define STUMPLESS_FACILITY_NEWS_VALUE ( 7 << 3 )
#  endif

/**
 * UUCP subsystem facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_UUCP_VALUE LOG_UUCP
#  else
#    define STUMPLESS_FACILITY_UUCP_VALUE ( 8 << 3 )
#  endif

/**
 * Clock daemon facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_CRON_VALUE LOG_CRON
#  else
#    define STUMPLESS_FACILITY_CRON_VALUE ( 9 << 3 )
#  endif

/**
 * Security/authorization messages facility code value as defined by RFC 5424.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FACILITY_AUTH2_VALUE ( 10 << 3 )

/**
 * FTP daemon facility code value as defined by RFC 5424.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FACILITY_FTP_VALUE ( 11 << 3 )

/**
 * NTP subsystem facility code value as defined by RFC 5424.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FACILITY_NTP_VALUE ( 12 << 3 )

/**
 * Log audit facility code value as defined by RFC 5424.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FACILITY_AUDIT_VALUE ( 13 << 3 )

/**
 * Log alert facility code value as defined by RFC 5424.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FACILITY_ALERT_VALUE ( 14 << 3 )

/**
 * Clock daemon facility code value as defined by RFC 5424.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FACILITY_CRON2_VALUE ( 15 << 3 )

/**
 * Local use 0 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL0_VALUE LOG_LOCAL0
#  else
#    define STUMPLESS_FACILITY_LOCAL0_VALUE ( 16 << 3 )
#  endif

/**
 * Local use 1 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL1_VALUE LOG_LOCAL1
#  else
#    define STUMPLESS_FACILITY_LOCAL1_VALUE ( 17 << 3 )
#  endif

/**
 * Local use 2 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL2_VALUE LOG_LOCAL2
#  else
#    define STUMPLESS_FACILITY_LOCAL2_VALUE ( 18 << 3 )
#  endif

/**
 * Local use 3 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL3_VALUE LOG_LOCAL3
#  else
#    define STUMPLESS_FACILITY_LOCAL3_VALUE ( 19 << 3 )
#  endif

/**
 * Local use 4 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL4_VALUE LOG_LOCAL4
#  else
#    define STUMPLESS_FACILITY_LOCAL4_VALUE ( 20 << 3 )
#  endif

/**
 * Local use 5 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL5_VALUE LOG_LOCAL5
#  else
#    define STUMPLESS_FACILITY_LOCAL5_VALUE ( 21 << 3 )
#  endif

/**
 * Local use 6 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL6_VALUE LOG_LOCAL6
#  else
#    define STUMPLESS_FACILITY_LOCAL6_VALUE ( 22 << 3 )
#  endif

/**
 * Local use 7 facility code value.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_FACILITY_LOCAL7_VALUE LOG_LOCAL7
#  else
#    define STUMPLESS_FACILITY_LOCAL7_VALUE ( 23 << 3 )
#  endif

/**
 * A macro function that runs the provided action once for each facility,
 * providing the symbol and value. The action must take two arguments, the
 * first being the symbol name of the facility, and the second the numeric
 * value of the facility.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FOREACH_FACILITY( ACTION )                       \
/** Kernel messages. */                                              \
ACTION( STUMPLESS_FACILITY_KERN, STUMPLESS_FACILITY_KERN_VALUE )     \
/** User-level messages. */                                          \
ACTION( STUMPLESS_FACILITY_USER, STUMPLESS_FACILITY_USER_VALUE )     \
/** Mail system facility code value as defined by RFC 5424. */       \
ACTION( STUMPLESS_FACILITY_MAIL, STUMPLESS_FACILITY_MAIL_VALUE )     \
/** System daemons. */                                               \
ACTION( STUMPLESS_FACILITY_DAEMON, STUMPLESS_FACILITY_DAEMON_VALUE ) \
/** Security/authorization messages. */                              \
ACTION( STUMPLESS_FACILITY_AUTH, STUMPLESS_FACILITY_AUTH_VALUE )     \
/** Message generated internally by the logging daemon. */           \
ACTION( STUMPLESS_FACILITY_SYSLOG, STUMPLESS_FACILITY_SYSLOG_VALUE ) \
/** Line printer subsystem. */                                       \
ACTION( STUMPLESS_FACILITY_LPR, STUMPLESS_FACILITY_LPR_VALUE )       \
/** Network news. */                                                 \
ACTION( STUMPLESS_FACILITY_NEWS, STUMPLESS_FACILITY_NEWS_VALUE )     \
/** UUCP subsystem. */                                               \
ACTION( STUMPLESS_FACILITY_UUCP, STUMPLESS_FACILITY_UUCP_VALUE )     \
/** Clock daemon. */                                                 \
ACTION( STUMPLESS_FACILITY_CRON, STUMPLESS_FACILITY_CRON_VALUE )     \
/** Security/authorization messages. */                              \
ACTION( STUMPLESS_FACILITY_AUTH2, STUMPLESS_FACILITY_AUTH2_VALUE )   \
/** FTP daemon. */                                                   \
ACTION( STUMPLESS_FACILITY_FTP, STUMPLESS_FACILITY_FTP_VALUE )       \
/** NTP subsystem. */                                                \
ACTION( STUMPLESS_FACILITY_NTP, STUMPLESS_FACILITY_NTP_VALUE )       \
/** Log audit. */                                                    \
ACTION( STUMPLESS_FACILITY_AUDIT, STUMPLESS_FACILITY_AUDIT_VALUE )   \
/** Log alert. */                                                    \
ACTION( STUMPLESS_FACILITY_ALERT, STUMPLESS_FACILITY_ALERT_VALUE )   \
/** Clock daemon. */                                                 \
ACTION( STUMPLESS_FACILITY_CRON2, STUMPLESS_FACILITY_CRON2_VALUE )   \
/** Local use 0. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL0, STUMPLESS_FACILITY_LOCAL0_VALUE ) \
/** Local use 1. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL1, STUMPLESS_FACILITY_LOCAL1_VALUE ) \
/** Local use 2. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL2, STUMPLESS_FACILITY_LOCAL2_VALUE ) \
/** Local use 3. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL3, STUMPLESS_FACILITY_LOCAL3_VALUE ) \
/** Local use 4. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL4, STUMPLESS_FACILITY_LOCAL4_VALUE ) \
/** Local use 5. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL5, STUMPLESS_FACILITY_LOCAL5_VALUE ) \
/** Local use 6. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL6, STUMPLESS_FACILITY_LOCAL6_VALUE ) \
/** Local use 7. */                                                  \
ACTION( STUMPLESS_FACILITY_LOCAL7, STUMPLESS_FACILITY_LOCAL7_VALUE )

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * All possible facility codes available to log entries.
 *
 * In versions prior to 2.0.0, these values were simply \#define symbols. They
 * have been changed to an enum to clearly convey proper usage.
 *
 * @since release v2.0.0.
 */
enum stumpless_facility {
  STUMPLESS_FOREACH_FACILITY( STUMPLESS_GENERATE_ENUM )
};

/**
 * Gets the string representation of the given facility.
 *
 * This is a string literal that should not be modified or freed by the caller.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0.
 *
 * @param facility The facility to get the string from.
 *
 * @return The string representation of the given facility.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_facility_string( enum stumpless_facility facility );

/**
 * Gets the enum value corresponding to the given facility string.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0.
 *
 * @param facility_string The facility name to get the enum from.
 * 
 *  Clears previous error on success.
 * 
 *  Raises STUMPLESS_INVALID_FACILITY on invalid input.
 *
 * @return The enum integer corresponding to the given facility or -1 if
 * the string is not a valid facility name.
 */
STUMPLESS_PUBLIC_FUNCTION
enum stumpless_facility
stumpless_get_facility_enum( const char *facility_string );

/**
 * Gets the enum value corresponding to the given facility string.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe.
 *
 * **Async Signal Safety: AS-Safe**
 * This function is safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function is safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.2.0.
 *
 * @param facility_string The facility name to get the enum from.
 * 
 * @param facility_buffer_length The length of the buffer
 * 
 *  Clears previous error on success.
 * 
 *  Raises STUMPLESS_INVALID_FACILITY on invalid input.
 *
 * @return The enum integer corresponding to the given facility or -1 if
 * the string is not a valid facility name.
 */
STUMPLESS_PUBLIC_FUNCTION
enum stumpless_facility
stumpless_get_facility_enum_from_buffer( const char *facility_string, size_t facility_buffer_length );

#  ifdef __cplusplus
} /* extern "C" */
#  endif

#endif /* __STUMPLESS_FACILITY_H */
