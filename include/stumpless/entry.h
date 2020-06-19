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
 * Types and functions for creating and modifying entries.
 */

#ifndef __STUMPLESS_ENTRY_H
#  define __STUMPLESS_ENTRY_H

#  include <stdarg.h>
#  include <stddef.h>
#  include <stumpless/element.h>
#  include <stumpless/id.h>
#  include <stumpless/param.h>

#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
#    include <windows.h>
#  endif

/* included for compatability with all 1.x releases */
#  ifndef STUMPLESS_FACILITY_USER
#    include <stumpless/facility.h>
#  endif
#  ifndef STUMPLESS_OPTION_NONE
#    include <stumpless/option.h>
#  endif
#  ifndef STUMPLESS_SEVERITY_INFO
#    include <stumpless/severity.h>
#  endif

#  ifdef __cplusplus
extern "C" {
#  endif

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
/**
 * The prival of this entry. This is a combination of the facility and severity
 * of the event, combined using a bitwise or.
 */
  int prival;
/** The app name of this entry, as a NULL-terminated string. */
  char *app_name;
/** The length of the app name, without the NULL terminator. */
  size_t app_name_length;
/** The message of this entry. */
  char *message;
/** The length of the message, without the NULL terminator. */
  size_t message_length;
/** The message id of this entry, as a NULL-terminated string. */
  char *msgid;
/** The length of the message id, without the NULL terminator. */
  size_t msgid_length;
/** An array holding the elements of this entry. */
  struct stumpless_element **elements;
/** The number of elements in this entry. */
  size_t element_count;
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
/** The type of this entry, for use with Windows Event Log calls. */
  WORD wel_type;
/** The category of this entry, for use with Windows Event Log calls. */
  WORD wel_category;
/** The event id of this entry, for use with Windows Event Log calls. */
  DWORD wel_event_id;
/** The number of insertion strings this entry has. */
  WORD wel_insertion_count;
/** An array of the insertion strings this entry will use. */
  LPCSTR *wel_insertion_strings;
/**
 * An array of params of which the values can be used as insertion strings with
 * Windows Event Log calls..
 */
  struct stumpless_param **wel_insertion_params;
#  endif
};

/**
 * Adds an element to an entry. The element is appended to the end of the list
 * of elements in this entry.
 *
 * @param entry The entry to add the element to.
 *
 * @param element The element to add to the entry.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_add_element( struct stumpless_entry *entry,
                       struct stumpless_element *element );

struct stumpless_entry *
stumpless_add_new_element( struct stumpless_entry *entry,
                           const char *name );

struct stumpless_entry *
stumpless_add_new_param_to_entry( struct stumpless_entry *entry,
                                  const char *element_name,
                                  const char *param_name,
                                  const char *param_value );

struct stumpless_entry *
stumpless_copy_entry( const struct stumpless_entry *entry );

/**
 * An alias for stumpless_destroy_entry_and_contents.
 *
 * @param entry The entry to destroy.
 */
void
stumpless_destroy_entry( struct stumpless_entry *entry );

/**
 * Destroys an entry as well as all elements and params that it contains,
 * freeing any allocated memory.
 *
 * @param entry The entry to destroy.
 */
void
stumpless_destroy_entry_and_contents( struct stumpless_entry *entry );

/**
 * Destroys an entry, freeing any allocated memory. Associated elements and
 * params are left untouched, and must be destroyed separately.
 *
 * @param entry The entry to destroy.
 */
void
stumpless_destroy_entry_only( struct stumpless_entry *entry );

struct stumpless_element *
stumpless_get_element_by_index( struct stumpless_entry *entry,
                                size_t index );

struct stumpless_element *
stumpless_get_element_by_name( struct stumpless_entry *entry,
                               const char *name );

size_t
stumpless_get_element_index( struct stumpless_entry *entry,
                             const char *name );

const char *
stumpless_get_entry_app_name( const struct stumpless_entry *entry );

int
stumpless_get_entry_facility( const struct stumpless_entry *entry );

const char *
stumpless_get_entry_msgid( const struct stumpless_entry *entry );

int
stumpless_get_entry_prival( const struct stumpless_entry *entry );

int
stumpless_get_entry_severity( const struct stumpless_entry *entry );

struct stumpless_param *
stumpless_get_param_by_index_from_entry( struct stumpless_entry *entry,
                                         size_t element_index,
                                         size_t param_index );

struct stumpless_param *
stumpless_get_param_by_name_from_entry( struct stumpless_entry *entry,
                                        const char *element_name,
                                        const char *param_name );

const char *
stumpless_get_param_value_by_index_from_entry( struct stumpless_entry *entry,
                                               size_t element_index,
                                               size_t param_index );

const char *
stumpless_get_param_value_by_name_from_entry( struct stumpless_entry *entry,
                                              const char *element_name,
                                              const char *param_name );

/**
 * Creates a new entry with the given characteristics.
 *
 * @param facility The facility code of the event this entry describes. This
 * should be a \c STUMPLESS_FACILITY value.
 *
 * @param severity The severity code of the event this entry describes. This
 * should be a \c STUMPLESS_SEVERITY value.
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

/**
 * Sets the app name for an entry.
 *
 * @param entry The entry for which the app name will be set.
 *
 * @param app_name A NULL-terminated string holding the new app_name for the
 * entry. This will be copied in to the entry, and therefore may be modified
 * or freed after this call without affecting the entry.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_entry *
stumpless_set_entry_app_name( struct stumpless_entry *entry,
                              const char *app_name );

struct stumpless_entry *
stumpless_set_entry_facility( struct stumpless_entry *entry, int facility );

struct stumpless_entry *
stumpless_set_entry_msgid( struct stumpless_entry *entry,
                           const char *msgid );

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

struct stumpless_entry *
stumpless_set_entry_priority( struct stumpless_entry *entry,
                              int facility,
                              int severity );

struct stumpless_entry *
stumpless_set_entry_prival( struct stumpless_entry *entry,
                            int prival );

struct stumpless_entry *
stumpless_set_entry_severity( struct stumpless_entry *entry, int severity );

struct stumpless_entry *
stumpless_set_element( struct stumpless_entry *entry,
                       size_t index,
                       struct stumpless_element *element );

struct stumpless_entry *
stumpless_set_param_by_index_from_entry( struct stumpless_entry *entry,
                                         size_t element_index,
                                         size_t param_index,
                                         struct stumpless_param *param );

struct stumpless_entry *
stumpless_set_param_value_by_index_from_entry( struct stumpless_entry *entry,
                                               size_t element_index,
                                               size_t param_index,
                                               const char *param_value );

struct stumpless_entry *
stumpless_set_param_value_by_name_from_entry( struct stumpless_entry *entry,
                                              const char *element_name,
                                              const char *param_name,
                                              const char *param_value );

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
