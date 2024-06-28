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
 * Types and functions for creating and modifying entries.
 */

#ifndef __STUMPLESS_ENTRY_H
#  define __STUMPLESS_ENTRY_H

#  include <stdarg.h>
#  include <stdbool.h>
#  include <stddef.h>
#  include <stumpless/config.h>
#  include <stumpless/element.h>
#  include <stumpless/facility.h>
#  include <stumpless/id.h>
#  include <stumpless/param.h>
#  include <stumpless/severity.h>

/** The maximum length of a procid, as specified by RFC 5424. */
#define STUMPLESS_MAX_PROCID_LENGTH 128

/** The maximum length of a hostname, as specified by RFC 5424. */
#define STUMPLESS_MAX_HOSTNAME_LENGTH 255

/** The maximum length of an app name, as specified by RFC 5424. */
#  define STUMPLESS_MAX_APP_NAME_LENGTH 48

/** The maximum length of a msgid, as specified by RFC 5424. */
#  define STUMPLESS_MAX_MSGID_LENGTH 32

#  ifdef __cplusplus
extern "C" {
#  endif

/**
 * A log entry.
 *
 * Entries are the basic element of logging within the library. Note that
 * although many of the members are character strings, they are not
 * guaranteed to be NULL terminated and should not be used with standard
 * string functions.
 */
struct stumpless_entry {
/** A unique identifier of this entry. */
  stumpless_id_t id;
/**
 * The procid of this entry, as a NULL-terminated string.
 *
 * @since release v2.1.0
 */
  char procid[STUMPLESS_MAX_PROCID_LENGTH + 1];
/**
 * The length of the procid of this entry (in bytes), without a NULL terminator.
 * If this is zero, then the default procid will be used.
 *
 * @since release v2.1.0
 */
  size_t procid_length;
/**
 * The hostname of this entry, as a NULL-terminated string.
 *
 * @since release v2.1.0
 */
  char hostname[STUMPLESS_MAX_HOSTNAME_LENGTH + 1];
/**
 * The length of the hostname of this entry (in bytes), without a NULL
 * terminator. If this is zero, then the default hostname will be used.
 *
 * @since release v2.1.0
 */
  size_t hostname_length;
/**
 * The prival of this entry. This is a combination of the facility and severity
 * of the event, combined using a bitwise or.
 */
  int prival;
/** The app name of this entry, as a NULL-terminated string. */
  char app_name[STUMPLESS_MAX_APP_NAME_LENGTH + 1];
/** The length of the app name, without the NULL terminator. */
  size_t app_name_length;
/**
 * The message of this entry, as a NULL-terminated string. This may be NULL
 * if the entry does not have a message set.
 */
  char *message;
/** The length of the message in bytes, without the NULL terminator. */
  size_t message_length;
/** The message id of this entry, as a NULL-terminated string. */
  char msgid[STUMPLESS_MAX_MSGID_LENGTH + 1];
/** The length of the message id, without the NULL terminator. */
  size_t msgid_length;
/** An array holding the elements of this entry. */
  struct stumpless_element **elements;
/** The number of elements in this entry. */
  size_t element_count;
#  ifdef STUMPLESS_WINDOWS_EVENT_LOG_TARGETS_SUPPORTED
/** A pointer to a wel_data structure. */
  void *wel_data;
#  endif
#  ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * A pointer to a mutex which protects all entry fields. The exact type of
 * this mutex depends on the build.
 */
  void *mutex;
#  endif
};

/**
 * Adds an element to an entry. The element is appended to the end of the list
 * of elements in this entry.
 *
 * Note that duplicate elements are not allowed in RFC 5424, and as such
 * attempts to add an element to an entry already having one with the same name
 * will result in a STUMPLESS_DUPLICATE_ELEMENT error.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry to add the element to.
 *
 * @param element The element to add to the entry.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_add_element( struct stumpless_entry *entry,
                       struct stumpless_element *element );

/**
 * Creates a new element with the given name and adds it to this entry.
 *
 * Note that duplicate elements are not allowed in RFC 5424, and as such
 * attempts to add an element to an entry already having one with the same name
 * will result in a STUMPLESS_DUPLICATE_ELEMENT error.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to add the new element to.
 *
 * @param name The name of the new element.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_add_new_element( struct stumpless_entry *entry,
                           const char *name );

/**
 * Creates a new param and adds it to the given element in the given entry. If
 * an element with the given name does not exist in the given entry, then one
 * will be created with the new param added to it.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to add the new param to.
 *
 * @param element_name The name of the element to add the param to. If an
 * element with this name is not found, it will be created. Valid name should
 * have printable ASCII characters expect '=', ']' , '"' and should be 32
 * characters long.
 *
 * @param param_name The name of the new param to add.
 *
 * @param param_value The value of the new param to add.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_add_new_param_to_entry( struct stumpless_entry *entry,
                                  const char *element_name,
                                  const char *param_name,
                                  const char *param_value );

/**
 * Creates a copy of an entry.
 *
 * Copies of entries are 'deep' in that the copy also copies each of the
 * elements that the original entry has, if any. This means that even if the
 * elements or params of the original entry are destroyed, the equivalent ones
 * in this entry will still be valid.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the copy.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry to copy.
 *
 * @return A new entry that is a deep copy of the original. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_copy_entry( const struct stumpless_entry *entry );

/**
 * Destroys an entry as well as all elements and params that it contains,
 * freeing any allocated memory.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @param entry The entry to destroy.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_destroy_entry_and_contents( const struct stumpless_entry *entry );

/**
 * Destroys an entry, freeing any allocated memory. Associated elements and
 * params are left untouched, and must be destroyed separately.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @param entry The entry to destroy.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_destroy_entry_only( const struct stumpless_entry *entry );

/**
 * True if the given entry has an element with the given name, false otherwise.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed by
 * another thread during execution. A mutex is used to coordinate access to the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to search for the element.
 *
 * @param name The name of the element to check for.
 *
 * @return True if no error is encountered and the element is found. If the
 * element is not found or an error is encountered, then false is returned and
 * an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
bool
stumpless_entry_has_element( const struct stumpless_entry *entry,
                             const char *name );

/**
 * Returns the element at the given index in this Entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate access to the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to search.
 *
 * @param index The index of the element to get.
 *
 * @return The element if it is found in the entry, or NULL otherwise. If an
 * error was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_get_element_by_index( const struct stumpless_entry *entry,
                                size_t index );

/**
 * Returns the element with the given name in this entry, if it is found.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed by
 * another thread during execution. A mutex is used to coordinate access to the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to search.
 *
 * @param name The name of the element to search for.
 *
 * @return The element if it is found in the entry, or NULL otherwise. If an
 * error was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_get_element_by_name( const struct stumpless_entry *entry,
                               const char *name );

/**
 * Returns the number of elements in the given entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the entry.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.0.0
 *
 * @param entry The entry to get the element count of.
 *
 * @return The number of elements entry has. If there is an error, zero is
 * returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_get_element_count( const struct stumpless_entry *entry );

/**
 * Returns the index of the element with the given name in this entry, if it
 * is found.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed by
 * another thread during execution. A mutex is used to coordinate access to the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to search.
 *
 * @param name The name of the element to search for.
 *
 * @return The index of the element if it is found in the entry. If an error
 * was encountered or the element does not exist in the entry, then 0 is
 * returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_get_element_index( const struct stumpless_entry *entry,
                             const char *name );

/**
 * Returns the app name of the given entry. The character buffer returned must
 * be freed by the caller when it is no longer needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the name and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * param with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the app name of.
 *
 * @return The app name of the entry if no error is encountered. If an error
 * was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_entry_app_name( const struct stumpless_entry *entry );

/**
 * Returns the facility code of the given entry.
 *
 * In versions prior to v2.0.0, this function returned an int, and -1 in the
 * event of an error.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the entry.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the facility of.
 *
 * @return The facility of the entry if no error is encountered. If an error
 * was encountered, then an invalid facility is returned and an error code is
 * set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
enum stumpless_facility
stumpless_get_entry_facility( const struct stumpless_entry *entry );

/**
 * Returns the hostname of a given entry. If hostname is not set it will return
 * the machine hostname. The result character buffer must be freed by the caller
 * when it is no longer needed to avoid memory leaks.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to get the hostname of.
 *
 * @return The hostname of the entry if no error is encountered. If an error
 * was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_entry_hostname( const struct stumpless_entry *entry );

/**
 * Returns the message of the given entry. The character buffer returned must
 * be freed by the caller when it is no longer needed to avoid memory leaks.
 *
 * Note that if this message was originally set using format specifiers, the
 * result will have them substituted, instead of the original placeholders.
 *
 * It is also important to note that the message may be NULL if the entry
 * does not have one. This differs from other fields like the app id or msgid,
 * which will be an RFC 5424 NILVALUE '-' if they have not been set.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the name and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * param with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the message of.
 *
 * @return The message of the entry (which may be NULL). If an error was
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_entry_message( const struct stumpless_entry *entry );

/**
 * Returns the msgid of the given entry. The character buffer returned must
 * be freed by the caller when it is no longer needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the name and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * param with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the result.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the msgid of.
 *
 * @return The msgid of the entry if no error is encountered. If an error
 * was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_entry_msgid( const struct stumpless_entry *entry );

/**
 * Gets the param from the element at the given index in an entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate access to the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the param from.
 *
 * @param element_index The index of the element to get the param from.
 *
 * @param param_index The index of the param to get from the element.
 *
 * @return The param at the given index if no error is encountered. If an error
 * is encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_get_entry_param_by_index( const struct stumpless_entry *entry,
                                    size_t element_index,
                                    size_t param_index );

/**
 * Gets the first param from the element with the given name in an entry.
 *
 * Note that an element may contain as many instances of a param as desired
 * according to RFC 5424, and therefore there may be other param instances with
 * the same name. If you need a reference to other params with the same name in
 * the element, then you must loop through all params using
 * stumpless_get_entry_param_by_index, checking each name.
 *
 * **Thread Safety: MT-Safe race:element_name race:param_name**
 * This function is thread safe, of course assuming that the names are not
 * changed by another thread during execution. A mutex is used to coordinate
 * access to the entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the param from.
 *
 * @param element_name The name of the element to get the param from.
 *
 * @param param_name The name of the param to get from the element.
 *
 * @return The first param with the given name if no error is encountered. If
 * an error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_get_entry_param_by_name( const struct stumpless_entry *entry,
                                   const char *element_name,
                                   const char *param_name );

/**
 * Gets the value of the param from the element at the given index in an entry.
 * The result character buffer must be freed by the caller when it is no longer
 * needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the value and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate access to the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the param from.
 *
 * @param element_index The index of the element to get the param from.
 *
 * @param param_index The index of the param to get the value of.
 *
 * @return The value of the param at the given index if no error is encountered.
 * If an error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_entry_param_value_by_index( const struct stumpless_entry *entry,
                                          size_t element_index,
                                          size_t param_index );

/**
 * Gets the value of the first param from the element with the given name in an
 * entry. The result character buffer must be freed by the caller when it is no
 * longer needed to avoid memory leaks.
 *
 * Note that an element may contain as many instances of a param as desired
 * according to RFC 5424, and therefore there may be other param instances with
 * the same name. If you need the value of other params with the same name in
 * the element, then you must loop through all params using
 * stumpless_get_entry_param_by_index, checking each name.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the value and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe race:element_name race:param_name**
 * This function is thread safe, of course assuming that the names are not
 * changed by another thread during execution. A mutex is used to coordinate
 * access to the entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the param from.
 *
 * @param element_name The name of the element to get the param from.
 *
 * @param param_name The name of the param to get from the element.
 *
 * @return The value of the first param with the given name if no error is
 * encountered. If an error is encountered, then NULL is returned and an error
 * code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_entry_param_value_by_name( const struct stumpless_entry *entry,
                                         const char *element_name,
                                         const char *param_name );

/**
 * Returns the prival of the given entry, as defined in RFC 5424.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the entry.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to get the prival of.
 *
 * @return The prival of the entry if no error is encountered. If an error
 * was encountered, then -1 is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
int
stumpless_get_entry_prival( const struct stumpless_entry *entry );

/**
 * Returns the procid of a given entry. If procid is not set it will return the
 * ProcessID. The result character buffer must be freed by the caller when it is
 * no longer needed to avoid memory leaks.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to get the procid of.
 *
 * @return The procid of the entry if no error is encountered. If an error
 * was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_entry_procid( const struct stumpless_entry *entry );

/**
 * Returns the severity code of the given entry.
 *
 * In versions prior to v2.0.0, this function returned an int, and -1 in the
 * event of an error.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being read.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate the read of the entry.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0
 *
 * @param entry The entry to get the severity of.
 *
 * @return The severity of the entry if no error is encountered. If an error
 * was encountered, then an invalid severity is returned and an error code is
 * set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
enum stumpless_severity
stumpless_get_entry_severity( const struct stumpless_entry *entry );

/**
 * Loads an entry struct with the given characteristics.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumpless_load_entry_str instead.
 *
 * This function has the same behavior as stumpless_new_entry, except it does
 * not create a new entry, instead loading an existing struct.
 *
 * @since release v2.2.0
 *
 * @param entry The struct to load.
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
 * specifiers valid in \c printf. This also means that characters such as % need
 * to be escaped as they would be in printf. If this is NULL, then it will be
 * blank in the entry (no characters). This must be a valid UTF-8 string in
 * shortest form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of specifiers
 * given.
 *
 * @return The loaded entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_load_entry( struct stumpless_entry *entry,
                      enum stumpless_facility facility,
                      enum stumpless_severity severity,
                      const char *app_name,
                      const char *msgid,
                      const char *message,
                      ... );

/**
 * Creates a new entry with the given characteristics.
 *
 * This function has the same behavior as stumpless_load_entry_str, except it
 * does not create a new entry, instead loading an existing struct.
 *
 * @since release v2.2.0
 *
 * @param entry The entry structure to load with the given fields.
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
 * @param message The message in the entry. If this is NULL, then it will be
 * blank in the entry (no characters). This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return The loaded entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_load_entry_str( struct stumpless_entry *entry,
                          enum stumpless_facility facility,
                          enum stumpless_severity severity,
                          const char *app_name,
                          const char *msgid,
                          const char *message );

/**
 * Creates a new entry with the given characteristics.
 *
 * In versions prior to 2.0.0, the facility and severity parameters were int
 * types instead of enums.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumpless_new_entry_str instead.
 *
 * **Thread Safety: MT-Safe race:app_name race:msgid race:message**
 * This function is thread safe, of course assuming that the string arguments
 * are not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the new element.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
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
 * specifiers valid in \c printf. This also means that characters such as % need
 * to be escaped as they would be in printf. If this is NULL, then it will be
 * blank in the entry (no characters). This must be a valid UTF-8 string in
 * shortest form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of specifiers
 * given.
 *
 * @return The created entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_new_entry( enum stumpless_facility facility,
                     enum stumpless_severity severity,
                     const char *app_name,
                     const char *msgid,
                     const char *message,
                     ... );

/**
 * Creates a new entry with the given characteristics.
 *
 * **Thread Safety: MT-Safe race:app_name race:msgid race:message**
 * This function is thread safe, of course assuming that the string arguments
 * are not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the new element.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @since release v2.1.0
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
 * @param message The message in the entry. If this is NULL, then it will be
 * blank in the entry (no characters). This must be a valid UTF-8 string in
 * shortest form.
 *
 * @return The created entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_new_entry_str( enum stumpless_facility facility,
                         enum stumpless_severity severity,
                         const char *app_name,
                         const char *msgid,
                         const char *message );

/**
 * Puts the element at the given index in the given entry.
 *
 * The element previously at this position will be removed from the entry,
 * but it is NOT destroyed by this call. Callers must clean up this element
 * separately.
 *
 * An element cannot be set at an index position that does not already hold
 * one. If this is attempted, then a STUMPLESS_INDEX_OUT_OF_BOUNDS error
 * is raised.
 *
 * Note that duplicate elements are not allowed in RFC 5424, and as such
 * attempts to set an element of an entry which already contains another element
 * with the same name will result in a STUMPLESS_DUPLICATE_ELEMENT error.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0
 *
 * @param entry The entry to set the element on.
 *
 * @param index The index to set to element.
 *
 * @param element The element to set at the given index.
 *
 * @return The modified entry, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_element( struct stumpless_entry *entry,
                       size_t index,
                       struct stumpless_element *element );

/**
 * Sets the app name for an entry.
 *
 * **Thread Safety: MT-Safe race:app_name**
 * This function is thread safe, of course assuming that the name is not changed
 * by any other threads during execution. A mutex is used to coordinate changes
 * to the entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new name and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry for which the app name will be set.
 *
 * @param app_name A NULL-terminated string holding the new app_name for the
 * entry. This will be copied in to the entry, and therefore may be modified
 * or freed after this call without affecting the entry. If this is NULL, then
 * a single '-' character will be used, as specified as the NILVALUE in RFC
 * 5424. The app name length is restricted to be 48 characters or less.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_app_name( struct stumpless_entry *entry,
                              const char *app_name );

/**
 * Sets the facility of an entry.
 *
 * In versions prior to 2.0.0, the facility parameter was an int type instead
 * of an enum.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to set the facility of.
 *
 * @param facility The new facility of the entry. This must be a valid value
 * according to RFC 5424, available as STUMPLESS_FACILITY constants.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_facility( struct stumpless_entry *entry,
                              enum stumpless_facility facility );

/**
 * Sets the hostname of a given entry. If hostname is NULL it will set hostname to
 * be the Machine hostname.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to modify.
 *
 * @param hostname The new hostname to set on the entry.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_hostname( struct stumpless_entry *entry,
                              const char *hostname );

/**
 * Sets the message of a given entry.
 *
 * The message must be a valid format specifier string provided along with the
 * appropriate number of variable arguments afterwards. This means that it
 * should not be a user-controlled value under any circumstances. If you need a
 * safer alternative without the risks of format strings, use
 * \c stumpless_set_entry_message_str instead.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new message and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param entry The entry to modify.
 *
 * @param message The new message to set on the entry. This message may contain
 * any format specifiers valid in \c printf. If this is NULL, then it will be
 * blank in the entry (no characters). This also means that characters such as %
 * need to be escaped as they would be in printf. This must be a valid UTF-8
 * string in shortest form.
 *
 * @param ... Substitutions for any format specifiers provided in message. The
 * number of substitutions provided must exactly match the number of specifiers
 * given.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_message( struct stumpless_entry *entry,
                             const char *message,
                             ... );

/**
 * Sets the message of a given entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new message and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to modify.
 *
 * @param message The new message to set on the entry. If this is NULL, then it
 * will be blank in the entry (no characters). This must be a valid UTF-8 string
 * in shortest form.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_message_str( struct stumpless_entry *entry,
                                 const char *message );

/**
 * Sets the message of a given entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new message and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v2.2.0
 *
 * @param entry The entry to modify.
 *
 * @param message The new message to set on the entry. If this is NULL, then it
 * will be blank in the entry (no characters). This must be a valid UTF-16 string
 * in shortest form.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_message_str_w( struct stumpless_entry *entry,
                                   const wchar_t *message );

/**
 * Sets the msgid for an entry.
 *
 * **Thread Safety: MT-Safe race:msgid**
 * This function is thread safe, of course assuming that the msgid is not
 * changed by any other threads during execution. A mutex is used to coordinate
 * changes to the entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new msgid and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry for which the msgid will be set.
 *
 * @param msgid A NULL-terminated string holding the new msgid for the entry.
 * The string must be in the ASCII printable range 33 <= character <= 126 as
 * specified in RFC5424. This will be copied in to the entry, and therefore
 * may be modified or freed after this call without affecting the entry. If
 * this is NULL, then a single '-' character will be used, as specified as
 * the NILVALUE in RFC 5424.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_msgid( struct stumpless_entry *entry,
                           const char *msgid );

/**
 * Puts the param in the element at the given index of an entry.
 *
 * The parameter previously at this position will be removed from the element,
 * but it is NOT destroyed by this call. Callers must clean up this param
 * separately.
 *
 * A param cannot be set at an index position that does not already hold a
 * param. If this is attempted, then a STUMPLESS_INDEX_OUT_OF_BOUNDS error
 * is raised.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param entry The entry to set the param on.
 *
 * @param element_index The index of the element to have the param.
 *
 * @param param_index The index to put the param at in the chosen element.
 *
 * @param param The param to set.
 *
 * @return The modified entry, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_param_by_index( struct stumpless_entry *entry,
                                    size_t element_index,
                                    size_t param_index,
                                    struct stumpless_param *param );

/**
 * Sets the value of the param in the element at the given index of an entry.
 *
 * **Thread Safety: MT-Safe race:value**
 * This function is thread safe, of course assuming that value is not changed
 * by any other threads during execution. A mutex is used to coordinate changes
 * to the entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param entry The entry to set the param value on.
 *
 * @param element_index The index of the element having the param to modify.
 *
 * @param param_index The index of the param to set the value of.
 *
 * @param value The new value to set on the param.
 *
 * @return The modified entry, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_param_value_by_index( struct stumpless_entry *entry,
                                          size_t element_index,
                                          size_t param_index,
                                          const char *value );

/**
 * Sets the value of the first param in the named element an entry.
 *
 * If an element with the given name is not found in the entry, one is created
 * with the supplied name and added to the end of the entry.
 *
 * If a param of the given name is not found in the named element, one is
 * created with the supplied name and value and added to the end of the element.
 *
 * If you need to set the value of a param with this name other than the first
 * one, then you will need to loop through the params using
 * stumpless_get_entry_param_by_index to find the params you want and then
 * set the value using stumpless_set_entry_param_value_by_index.
 *
 * **Thread Safety: MT-Safe race:element_name race:param_name race:value**
 * This function is thread safe, of course assuming that the names and value
 * are not changed by any other threads during execution. A mutex is used to
 * coordinate changes to the entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param entry The entry to set the param value on.
 *
 * @param element_name The name of the element having the param to modify.
 *
 * @param param_name The name of the param to set the value of.
 *
 * @param value The new value to set on the param.
 *
 * @return The modified entry, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_param_value_by_name( struct stumpless_entry *entry,
                                         const char *element_name,
                                         const char *param_name,
                                         const char *value );

/**
 * Sets the facility and severity of an entry.
 *
 * In versions prior to 2.0.0, the facility and severity parameters were int
 * types instead of enums.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to set the priority values of.
 *
 * @param facility The new facility of the entry. This must be a valid value
 * according to RFC 5424, available as STUMPLESS_FACILITY constants.
 *
 * @param severity The new severity of the entry. This must be a valid value
 * according to RFC 5424, available as STUMPLESS_SEVERITY constants.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_priority( struct stumpless_entry *entry,
                              enum stumpless_facility facility,
                              enum stumpless_severity severity );

/**
 * Sets the prival of an entry, as defined in RFC 5424.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to set the prival of.
 *
 * @param prival The new prival of the entry, as defined in RFC 5424. Only the
 * first 8 bits of prival are considered: the rest are discarded after
 * extracting the effective facility and severity.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_prival( struct stumpless_entry *entry,
                            int prival );

/**
 * Sets the procid of a given entry. If procid is NULL it will set procid to
 * be the ProcessID.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v2.1.0
 *
 * @param entry The entry to modify.
 *
 * @param procid The new procid to set on the entry.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_procid( struct stumpless_entry *entry, const char *procid );

/**
 * Sets the severity of an entry.
 *
 * In versions prior to 2.0.0, the severity parameter was an int type instead
 * of an enum.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked.
 *
 * @since release v1.6.0.
 *
 * @param entry The entry to set the severity of.
 *
 * @param severity The new severity of the entry. This must be a valid value
 * according to RFC 5424, available as STUMPLESS_SEVERITY constants.
 *
 * @return The modified entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
stumpless_set_entry_severity( struct stumpless_entry *entry,
                              enum stumpless_severity severity );

/**
 * Unloads an entry as well as all elements that it contains.
 *
 * Either this function or stumpless_unload_entry_only must be used to clean
 * up any entry struct previously loaded with stumpless_load_entry.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @param entry The entry to unload.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_unload_entry_and_contents( const struct stumpless_entry *entry );

/**
 * Unloads an entry, freeing any allocated memory. Associated elements are left
 * untouched, and must be unloaded separately.
 *
 * Either this function or stumpless_unload_entry_and_contents must be used to
 * clean up any entry struct previously loaded with stumpless_load_entry.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this struct.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the destruction
 * of a lock that may be in use as well as the use of the memory deallocation
 * function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the cleanup of the lock may not be completed, and the memory
 * deallocation function may not be AC-Safe itself.
 *
 * @since release v2.2.0
 *
 * @param entry The entry to unload.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_unload_entry_only( const struct stumpless_entry *entry );

/**
 * Creates a new entry with the given parameters.
 *
 * This function has the same behavior as vstumpless_new_entry, except it does
 * not create a new entry, instead loading an existing struct.
 *
 * @since release v2.2.0
 *
 * @param entry The struct to load.
 *
 * @param facility The facility code of the entry. This should be a
 * \c STUMPLESS_FACILITY value.
 *
 * @param severity The severity code of the entry. This should be a
 * \c STUMPLESS_SEVERITY value.
 *
 * @param app_name The app_name of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The app name length is restricted
 * to be 48 characters or less.
 *
 * @param msgid The message id of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The string must be in the
 * ASCII printable range 33 <= character <= 126 as specified in RFC5424.
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
 * @return The loaded entry if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
vstumpless_load_entry( struct stumpless_entry *entry,
                       enum stumpless_facility facility,
                       enum stumpless_severity severity,
                       const char *app_name,
                       const char *msgid,
                       const char *message,
                       va_list subs );

/**
 * Creates a new entry with the given parameters.
 *
 * In versions prior to 2.0.0, the facility and severity parameters were int
 * types instead of enums.
 *
 * **Thread Safety: MT-Safe race:app_name race:msgid race:message**
 * This function is thread safe, of course assuming that the string arguments
 * are not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the new element.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @param facility The facility code of the entry. This should be a
 * \c STUMPLESS_FACILITY value.
 *
 * @param severity The severity code of the entry. This should be a
 * \c STUMPLESS_SEVERITY value.
 *
 * @param app_name The app_name of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The app name length is restricted
 * to be 48 characters or less.
 *
 * @param msgid The message id of the entry. If this is NULL, then it will be
 * blank in the entry (a single '-' character). The string must be in the
 * ASCII printable range 33 <= character <= 126 as specified in RFC5424.
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
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
vstumpless_new_entry( enum stumpless_facility facility,
                      enum stumpless_severity severity,
                      const char *app_name,
                      const char *msgid,
                      const char *message,
                      va_list subs );

/**
 * Sets the message of a given entry.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * entry while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new message and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
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
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_entry *
vstumpless_set_entry_message( struct stumpless_entry *entry,
                              const char *message,
                              va_list subs );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_ENTRY_H */
