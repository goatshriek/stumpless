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
#  include <stumpless/generator.h>

#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    include <syslog.h>
#  endif

/** Creates a severity mask for the provided severity. */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_MASK( SEVERITY ) ( LOG_MASK( SEVERITY ) )
#  else
#    define STUMPLESS_SEVERITY_MASK( SEVERITY ) ( 1 << ( SEVERITY ) )
#  endif

/** Creates a severity mask from EMERG up to the provided severity. */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_MASK_UPTO( SEVERITY ) ( LOG_UPTO( SEVERITY ) )
#  else
#    define STUMPLESS_SEVERITY_MASK_UPTO( SEVERITY ) \
( ( 1 << ( ( SEVERITY ) + 1 ) ) - 1 )
#  endif

/**
 * Severity code value for EMERG log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_EMERG_VALUE LOG_EMERG
#  else
#    define STUMPLESS_SEVERITY_EMERG_VALUE 0
#  endif

/**
 * Severity code value for ALERT log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_ALERT_VALUE LOG_ALERT
#  else
#    define STUMPLESS_SEVERITY_ALERT_VALUE 1
#  endif

/**
 * Severity code value for CRIT log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_CRIT_VALUE LOG_CRIT
#  else
#    define STUMPLESS_SEVERITY_CRIT_VALUE 2
#  endif

/**
 * Severity code value for ERR log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_ERR_VALUE LOG_ERR
#  else
#    define STUMPLESS_SEVERITY_ERR_VALUE 3
#  endif

/**
 * Severity code value for WARNING log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_WARNING_VALUE LOG_WARNING
#  else
#    define STUMPLESS_SEVERITY_WARNING_VALUE 4
#  endif

/**
 * Severity code value for NOTICE log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_NOTICE_VALUE LOG_NOTICE
#  else
#    define STUMPLESS_SEVERITY_NOTICE_VALUE 5
#  endif

/**
 * Severity code value for INFO log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_INFO_VALUE LOG_INFO
#  else
#    define STUMPLESS_SEVERITY_INFO_VALUE 6
#  endif

/**
 * Severity code value for DEBUG log entries.
 *
 * @since release v2.0.0.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_SEVERITY_DEBUG_VALUE LOG_DEBUG
#  else
#    define STUMPLESS_SEVERITY_DEBUG_VALUE 7
#  endif

/**
 * A macro function that runs the provided action once for each severity,
 * providing the symbol and value. The action must take two arguments, the
 * first being the symbol name of the severity, and the second the numeric
 * value of the severity.
 *
 * @since release v2.0.0.
 */
#  define STUMPLESS_FOREACH_SEVERITY( ACTION )                         \
/** Emergency: system is unusable. */                                  \
ACTION( STUMPLESS_SEVERITY_EMERG, STUMPLESS_SEVERITY_EMERG_VALUE )     \
/** Alert: action must be taken immediately. */                        \
ACTION( STUMPLESS_SEVERITY_ALERT, STUMPLESS_SEVERITY_ALERT_VALUE )     \
/** Critical: critical conditions. */                                  \
ACTION( STUMPLESS_SEVERITY_CRIT, STUMPLESS_SEVERITY_CRIT_VALUE )       \
/** Error: error conditions. */                                        \
ACTION( STUMPLESS_SEVERITY_ERR, STUMPLESS_SEVERITY_ERR_VALUE )         \
/** Warning: warning conditions. */                                    \
ACTION( STUMPLESS_SEVERITY_WARNING, STUMPLESS_SEVERITY_WARNING_VALUE ) \
/** Notice: normal but significant condition. */                       \
ACTION( STUMPLESS_SEVERITY_NOTICE, STUMPLESS_SEVERITY_NOTICE_VALUE )   \
/** Informational: informational messages. */                          \
ACTION( STUMPLESS_SEVERITY_INFO, STUMPLESS_SEVERITY_INFO_VALUE )       \
/** Debug: debug-level messages. */                                    \
ACTION( STUMPLESS_SEVERITY_DEBUG, STUMPLESS_SEVERITY_DEBUG_VALUE )

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * All possible severity codes available to log entries.
 *
 * In versions prior to 2.0.0, these values were simply #define symbols. They
 * have been changed to an enum to clearly convey proper usage.
 *
 * @since release v2.0.0.
 */
enum stumpless_severity {
  STUMPLESS_FOREACH_SEVERITY( STUMPLESS_GENERATE_ENUM )
};

#  ifdef __cplusplus
} /* extern "C" */
#  endif

#endif /* __STUMPLESS_SEVERITY_H */
