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

/** 
 *  Option to log to system console if writing to the 
 *  target stream fails.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_CONS   LOG_CONS
#  else
#    define STUMPLESS_OPTION_CONS   (1<<1)
#  endif

/** For all applicable targets, NDELAY semantics is the
 * default behavior.
 * 
 * NDELAY definition for each target:
 * 1. Buffer - Buffer created and passed by the user. Not applicable.
 * 2. File - Open the file in append mode.
 * 3. Function - Function created and passed by the user. Not applicable.
 * 4. Journald - Unix socket to journald opened by sd_journal_sendv. Not applicable.
 * 5. Network - Establish network connection with the destination.
 * 6. Socket - Open and bind the socket.
 * 7. Stream - Stream created and passed by the user. Not applicable.
 * 8. WEL - Execute RegisterEventSource.
 * 9. SQLITE3 - Connect to the database.
 * 10. Chain - Each target in the chain will have their own definition.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_NDELAY LOG_NDELAY
#  else
#    define STUMPLESS_OPTION_NDELAY (1<<2)
#  endif

/** Definitions for ODELAY remains the same for all targets as defined in NDELAY
 * with the only difference being that they will be executed when the first
 * message is logged.
 */
#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_ODELAY LOG_ODELAY
#  else
#    define STUMPLESS_OPTION_ODELAY (1<<3)
#  endif

/** No need to wait for the child processes that may have 
 *  been created while logging the messages.
 *  (Stumpless does not spawn child processes because it 
 *  slows down the process of logging, so essentially
 *  this option is always set)
 */

#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    define STUMPLESS_OPTION_NOWAIT LOG_NOWAIT
#  else
#    define STUMPLESS_OPTION_NOWAIT (1<<4)
#  endif

/** Log the message to the stderr as well as
 *  to the target
 */
# ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#   define STUMPLESS_OPTION_PERROR LOG_PERROR
# else
#   define STUMPLESS_OPTION_PERROR (1 << 5)
# endif

/** Empty option mask for explicit 'no option' use. */
#  define STUMPLESS_OPTION_NONE 0

#endif /* __STUMPLESS_OPTION_H */
