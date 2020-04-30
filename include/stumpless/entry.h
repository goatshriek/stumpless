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
 * Types and functions for creating and modifying entries. Facilities,
 * severities, and options are created to be compatible with the syslog.h
 * header if it is found on the system. Otherwise, they are defined as closely
 * as possible to the RFC 5424 standard.
 */

#ifndef __STUMPLESS_ENTRY_H
#  define __STUMPLESS_ENTRY_H

#  include <stumpless/config.h>

#  include <stdarg.h>
#  include <stddef.h>
#  include <stumpless/id.h>

#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include <windows.h>
#  endif

#  ifdef __cplusplus
extern "C" {
#  endif

#  ifdef STUMPLESS_SYSLOG_H_COMPATIBLE
#    include <syslog.h>


/* severity codes as set by syslog.h */

/** Emergency: system is unusable. */
#    define STUMPLESS_SEVERITY_EMERG    LOG_EMERG
/** Alert: action must be taken immediately. */
#    define STUMPLESS_SEVERITY_ALERT    LOG_ALERT
/** Critical: critical conditions. */
#    define STUMPLESS_SEVERITY_CRIT     LOG_CRIT
/** Error: error conditions. */
#    define STUMPLESS_SEVERITY_ERR      LOG_ERR
/** Warning: warning conditions. */
#    define STUMPLESS_SEVERITY_WARN     LOG_WARNING
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


/* facility codes as set by syslog.h */

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


/* options defined in syslog.h */
/* these don't have doxygen documentation as they are currently not supported
 * by the implementation */
#    define STUMPLESS_OPTION_PID    LOG_PID
#    define STUMPLESS_OPTION_CONS   LOG_CONS
#    define STUMPLESS_OPTION_NDELAY LOG_NDELAY
#    define STUMPLESS_OPTION_ODELAY LOG_ODELAY
#    define STUMPLESS_OPTION_NOWAIT LOG_NOWAIT

#  else

/* severity codes as specified in RFC 5424 */
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

/** Empty option mask for explicit 'no option' use. */
#  define STUMPLESS_OPTION_NONE 0

/**
 * A parameter within a structured data element.
 *
 * A parameter must have both a name and a value in compliance with RFC 5424.
 */
struct stumpless_param {
/**
 * The name of the parameter.
 *
 * The name must be between 1 and 32 characters long and consist only of ASCII
 * characters between '!' and '~', inclusive, with the exception of the '=',
 * ' ', ']', and '"' characters, which are not allowed.
 *
 * Note that the name will _not_ be NULL-terminated.
 */
  char *name;
/** The number of characters in name. */
  size_t name_length;
/**
 * The value may be any UTF-8 string.
 *
 * As specified in RFC 5424, the characters '"' (ABNF %d34), '\' (ABNF %d92),
 * and ']' (ABNF %d93) MUST be escaped by placing a backslash character '\'
 * directly before them.
 *
 * Unlike the name field, value will be NULL-terminated. This is done to support
 * their use for wel insertion strings.
 */
  char *value;
/** The number of characters in value. */
  size_t value_length;
};

/**
 * An element of structured data.
 *
 * Elements must have a name, but may not have any parameters. Their components
 * must comply with RFC 5424.
 */
struct stumpless_element {
/**
 * The name of the element.
 *
 * As specified in RFC 5424, the '=', ']', '"' characters are not allowed in
 * element names. In addition, the '@' character is only allowed in names that
 * are private. All other characters between '!' and '~', inclusive, are
 * allowed.
 *
 * According to the standard names must either be private (of the form
 * name@<private enterprise number>) or registered with the IANA. This library
 * assumes that you have done your due diligence and does not enforce the
 * registration requirement.
 *
 * Note that the name will _not_ be NULL-terminated.
 */
  char *name;
/** The number of characters in name. */
  size_t name_length;
/**
 * The parameters this element contains.
 *
 * This is an array of pointers to param structures. Use the param_count member
 * to iterate through the array if needed. This may be NULL if there are no
 * params in the element, but not necessarily - the param_count is the only way
 * to tell for sure.
 */
  struct stumpless_param **params;
/** The number of params in the array. */
  size_t param_count;
};

/**
 * A log entry.
 *
 * Entries are the basic element of logging within the library. Note that
 * although many of the members are character strings, they are not NULL
 * terminated and should not be used with standard string functions.
 */
struct stumpless_entry {
/** A unique identifier of this entry. */
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
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
  WORD wel_type;
  WORD wel_category;
  DWORD wel_event_id;
  WORD wel_insertion_count;
  LPCSTR *wel_insertion_strings;
  struct stumpless_param **wel_insertion_params;
#  endif
};

/*
 * While the functions provided right now offer basic creation and deletion
 * capabilities, there will need to be many more added to make working with
 * the messages, elements, and params easier. For example, hash-style accessors
 * and assignments, as well as a clear memory management strategy.
 */

struct stumpless_entry *
stumpless_add_element( struct stumpless_entry *entry,
                       struct stumpless_element *element );

struct stumpless_element *
stumpless_add_param( struct stumpless_element *element,
                     struct stumpless_param *param );

void
stumpless_destroy_element( struct stumpless_element *element );

void
stumpless_destroy_entry( struct stumpless_entry *entry );

void
stumpless_destroy_param( struct stumpless_param *param );

struct stumpless_element *
stumpless_new_element( const char *name );

/**
 * Creates a new entry with the given parameters.
 *
 * @param facility The facility code of the entry. This should be a
 * \c STUMPLESS_FACILITY value.
 *
 * @param severity The severity code of the entry. This should be a
 * \c STUMPLESS_SEVERITY value.
 *
 * @param app_name The app_name of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character).
 *
 * @param msgid The message id of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character).
 *
 * @param message The message in the entry. This message may contain any format
 * specifiers valid in \c printf. If this is NULL, then it will be blank in the
 * entry (no characters). This also means that characters such as % need to be
 * escaped as they would be in printf.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of specifiers
 * given.
 *
 * @return The created entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_new_entry( int facility,
                     int severity,
                     const char *app_name,
                     const char *msgid,
                     const char *message,
                     ... );

struct stumpless_param *
stumpless_new_param( const char *name,
                     const char *value );

struct stumpless_entry *
stumpless_set_entry_app_name( struct stumpless_entry *entry,
                              const char *app_name );

/**
 * Sets the message of a given entry.
 *
 * @param entry The entry to modify.
 *
 * @param message The new message to set on the entry. This message may contain
 * any format specifiers valid in \c printf. If this is NULL, then it will be
 * blank in the entry (no characters). This also means that characters such as %
 * need to be escaped as they would be in printf.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of specifiers
 * given.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_set_entry_message( struct stumpless_entry *entry,
                             const char *message,
                             ... );

/**
 * Creates a new entry with the given parameters.
 *
 * @param facility The facility code of the entry. This should be a
 * \c STUMPLESS_FACILITY value.
 *
 * @param severity The severity code of the entry. This should be a
 * \c STUMPLESS_SEVERITY value.
 *
 * @param app_name The app_name of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character).
 *
 * @param msgid The message id of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character).
 *
 * @param message The message in the entry. This message may contain any format
 * specifiers valid in \c printf. If this is NULL, then it will be blank in the
 * entry (no characters). This also means that characters such as % need to be
 * escaped as they would be in printf.
 *
 * @param subs Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given. This list must be started via \c va_start before being
 * used, and \c va_end should be called afterwards, as this function does not
 * call them.
 *
 * @return The created entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
vstumpless_new_entry( int facility,
                      int severity,
                      const char *app_name,
                      const char *msgid,
                      const char *message,
                      va_list subs );

/**
 * Sets the message of a given entry.
 *
 * @param entry The entry to modify.
 *
 * @param message The new message to set on the entry. This message may contain
 * any format specifiers valid in \c printf. If this is NULL, then it will be
 * blank in the entry (no characters). Characters such as % need to be escaped
 * as they would be in printf.
 *
 * @param subs Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of
 * specifiers given. This list must be started via \c va_start before being
 * used, and \c va_end should be called afterwards, as this function does not
 * call them.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
vstumpless_set_entry_message( struct stumpless_entry *entry,
                              const char *message,
                              va_list subs );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_ENTRY_H */
