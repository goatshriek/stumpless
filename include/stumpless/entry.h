
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

#ifndef __STUMPLESS_ENTRY_H
#  define __STUMPLESS_ENTRY_H

#  include <stddef.h>
#  include <stumpless/config.h>
#  include <stumpless/id.h>

#  ifdef __cplusplus
extern "C" {
#  endif

#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    include <syslog.h>

/* severity codes as set by syslog.h */
#    define STUMPLESS_SEVERITY_EMERG  LOG_EMERG
#    define STUMPLESS_SEVERITY_ALERT  LOG_ALERT
#    define STUMPLESS_SEVERITY_CRIT   LOG_CRIT
#    define STUMPLESS_SEVERITY_ERR    LOG_ERR
#    define STUMPLESS_SEVERITY_WARN   LOG_WARN
#    define STUMPLESS_SEVERITY_NOTICE LOG_NOTICE
#    define STUMPLESS_SEVERITY_INFO   LOG_INFO
#    define STUMPLESS_SEVERITY_DEBUG  LOG_DEBUG

#    define STUMPLESS_SEVERITY_MASK(severity) (LOG_MASK(severity))
#    define STUMPLESS_SEVERITY_MASK_UPTO(severity) (LOG_UPTO(severity))

/* facility codes as set by syslog.h */
#    define STUMPLESS_FACILITY_KERN   LOG_KERN
#    define STUMPLESS_FACILITY_USER   LOG_USER
#    define STUMPLESS_FACILITY_MAIL   LOG_MAIL
#    define STUMPLESS_FACILITY_NEWS   LOG_NEWS
#    define STUMPLESS_FACILITY_UUCP   LOG_UUCP
#    define STUMPLESS_FACILITY_DAEMON LOG_DAEMON
#    define STUMPLESS_FACILITY_AUTH   LOG_AUTH
#    define STUMPLESS_FACILITY_CRON   LOG_CRON
#    define STUMPLESS_FACILITY_LPR    LOG_LPR
#    define STUMPLESS_FACILITY_LOCAL0 LOG_LOCAL0
#    define STUMPLESS_FACILITY_LOCAL1 LOG_LOCAL1
#    define STUMPLESS_FACILITY_LOCAL2 LOG_LOCAL2
#    define STUMPLESS_FACILITY_LOCAL3 LOG_LOCAL3
#    define STUMPLESS_FACILITY_LOCAL4 LOG_LOCAL4
#    define STUMPLESS_FACILITY_LOCAL5 LOG_LOCAL5
#    define STUMPLESS_FACILITY_LOCAL6 LOG_LOCAL6
#    define STUMPLESS_FACILITY_LOCAL7 LOG_LOCAL7

/* options defined in syslog.h */
#    define STUMPLESS_OPTION_PID    LOG_PID
#    define STUMPLESS_OPTION_CONS   LOG_CONS
#    define STUMPLESS_OPTION_NDELAY LOG_NDELAY
#    define STUMPLESS_OPTION_ODELAY LOG_ODELAY
#    define STUMPLESS_OPTION_NOWAIT LOG_NOWAIT

#  else

/* severity codes as specified in RFC 5424 */
#    define STUMPLESS_SEVERITY_EMERG  0
#    define STUMPLESS_SEVERITY_ALERT  1
#    define STUMPLESS_SEVERITY_CRIT   2
#    define STUMPLESS_SEVERITY_ERR    3
#    define STUMPLESS_SEVERITY_WARN   4
#    define STUMPLESS_SEVERITY_NOTICE 5
#    define STUMPLESS_SEVERITY_INFO   6
#    define STUMPLESS_SEVERITY_DEBUG  7

#    define STUMPLESS_SEVERITY_MASK(severity) (1<<(severity))
#    define STUMPLESS_SEVERITY_MASK_UPTO(severity) ((1<<(severity+1))-1)

/* facility codes as specified in RFC 5424*/
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

/* options normally defined in syslog.h */
#    define STUMPLESS_OPTION_PID    1
#    define STUMPLESS_OPTION_CONS   (1<<1)
#    define STUMPLESS_OPTION_NDELAY (1<<2)
#    define STUMPLESS_OPTION_ODELAY (1<<3)
#    define STUMPLESS_OPTION_NOWAIT (1<<4)

#  endif

/* remaining facility codes specified in RFC 5424 */
#  define STUMPLESS_FACILITY_SYSLOG (5<<3)
#  define STUMPLESS_FACILITY_AUTH2  (10<<3)
#  define STUMPLESS_FACILITY_FTP    (11<<3)
#  define STUMPLESS_FACILITY_NTP    (12<<3)
#  define STUMPLESS_FACILITY_AUDIT  (13<<3)
#  define STUMPLESS_FACILITY_ALERT  (14<<3)
#  define STUMPLESS_FACILITY_CRON2  (15<<3)

  struct stumpless_param {
    char *name;
    size_t name_length;
    char *value;
    size_t value_length;
  };

  struct stumpless_element {
    char *name;
    size_t name_length;
    struct stumpless_param **params;
    size_t param_count;
  };

  struct stumpless_entry {
    stumpless_id_t id;
    int prival;
    char *app_name;
    size_t app_name_length;
    char *message;
    size_t message_length;
    char *msgid;
    size_t msgid_length;
    struct stumpless_element **elements;
    size_t element_count;
  };

  /* 
   * While the functions provided right now offer basic creation and deletion
   * capabilities, there will need to be many more added to make working with
   * the messages, elements, and params easier. For example, hash-style accessors
   * and assignments, as well as a clear memory management strategy.
   */

  struct stumpless_entry *stumpless_add_element( struct stumpless_entry *entry, struct stumpless_element
                                                 *element );
  struct stumpless_element *stumpless_add_param( struct stumpless_element
                                                 *element, struct stumpless_param
                                                 *param );
  struct stumpless_element *stumpless_new_element( const char *name );
  struct stumpless_entry *stumpless_new_entry( int severity, int facility,
                                               const char *app_name,
                                               const char *msgid,
                                               const char *message );
  struct stumpless_param *stumpless_new_param( const char *name,
                                               const char *value );
  void stumpless_destroy_element( struct stumpless_element *element );
  void stumpless_destroy_entry( struct stumpless_entry *entry );
  void stumpless_destroy_param( struct stumpless_param *param );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_ENTRY_H */
