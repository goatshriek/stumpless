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
 * Types and functions for creating and modifying elements.
 */

#ifndef __STUMPLESS_ELEMENT_H
#  define __STUMPLESS_ELEMENT_H

#  include <stdbool.h>
#  include <stddef.h>
#  include <stumpless/config.h>
#  include <stumpless/entry.h>
#  include <stumpless/param.h>

/** The maximum length of an element name, as specified by RFC 5424. */
#  define STUMPLESS_MAX_ELEMENT_NAME_LENGTH 32

#  ifdef __cplusplus
extern "C" {
#  endif

// this is required due to the circular dependency with the entry header.
struct stumpless_entry;

#ifdef STUMPLESS_JOURNALD_TARGETS_SUPPORTED
/**
 * Gets the name to use for the journald field corresponding to this element.
 *
 * If the destination buffer is too small to hold the complete name, then
 * nothing should be done. Callers must be able to detect this by comparing
 * the return value to the value provided in the size argument. If the return
 * value is larger, then the name was not written into destination.
 *
 * **Thread Safety: MT-Unsafe**
 * This function need not be thread safe. It will be called when locks are
 * already held on the entry and element in question, and therefore should not
 * use any functions that will attempt to lock any of these as this will result
 * in deadlock.
 *
 * **Async Signal Safety: AS-Safe**
 * This function must be safe to call from signal handlers.
 *
 * **Async Cancel Safety: AC-Safe**
 * This function must be safe to call from threads that may be asynchronously
 * cancelled.
 *
 * @since release v2.1.0
 *
 * @param entry The entry that the param is part of.
 *
 * @param element_index The index of the element in the entry.
 *
 * @param destination The buffer to write the name to.
 *
 * @param size The maximum number of bytes to write to the destination
 * buffer.
 *
 * @return The number of bytes needed to write the complete name, not including
 * a NULL terminating character. If this is greater than size, then it
 * signifies that nothing was done.
 */
typedef
size_t
( *stumpless_element_namer_func_t )( const struct stumpless_entry *entry,
                                     size_t element_index,
                                     char *destination,
                                     size_t size );
#endif

/**
 * An element of structured data.
 *
 * Elements must have a name, but may or may not have any parameters. Their
 * components must comply with RFC 5424.
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
 * Note that the name will be NULL-terminated as of version 1.6.0. In earlier
 * versions it is _not_ NULL-terminated.
 *
 * If you need to access the name, use the stumpless_(g|s)et_element_name
 * functions. These will protect you from changes in the struct in future
 * versions.
 */
  char name[STUMPLESS_MAX_ELEMENT_NAME_LENGTH + 1];
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
#ifdef STUMPLESS_JOURNALD_TARGETS_SUPPORTED
/**
 * Gets the name to use for the journald field corresponding to this element.
 */
  stumpless_element_namer_func_t get_journald_name;
#endif
#ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * A pointer to a mutex which protects all element fields. The exact type of
 * this mutex depends on the build.
 */
  void *mutex;
#endif
};

/**
 * Creates a new param and adds it to the given element.
 *
 * This is equivalent to calling stumpless_new_param() and passing the result
 * directly stumpless_add_param().
 *
 * **Thread Safety: MT-Safe race:param_name race:param_value**
 * This function is thread safe, of course assuming that the param name and
 * value or not changed by other threads during execution. A mutex is used to
 * coordinate updates to the element with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to create the new param.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param element The element to add the new param to.
 *
 * @param param_name The name of the new param.
 *
 * @param param_value The value of the new param.
 *
 * @return The modified element if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_add_new_param( struct stumpless_element *element,
                         const char *param_name,
                         const char *param_value );

/**
 * Adds a param to an element.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate updates to the
 * element with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions to adjust the array of params in the element.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @param element The element to add the param to.
 *
 * @param param The param to add to element.
 *
 * @return The modified element if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_add_param( struct stumpless_element *element,
                     struct stumpless_param *param );

/**
 * Creates a copy of an element.
 *
 * Copies of elements are 'deep' in that the copy also copies each of the params
 * that the original element has, if any. This means that even if the params of
 * the original element are destroyed, the equivalent ones in this element will
 * still be valid.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * element with other accesses and modifications.
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
 * @since release v1.6.0.
 *
 * @param element The element to copy.
 *
 * @return A new element that is a deep copy of the original. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_copy_element( const struct stumpless_element *element );

/**
 * Destroys an element as well as all params that it contains, freeing any
 * allocated memory.
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
 * @param e The element to destroy.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_destroy_element_and_contents( const struct stumpless_element *e );

/**
 * Destroys an element, freeing any allocated memory. Associated params are left
 * untouched, and must be destroyed separately.
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
 * @param element The element to destroy.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_destroy_element_only( const struct stumpless_element *element );

/**
 * True if the given element has a param with the given name, false otherwise.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed by
 * another thread during execution. A mutex is used to coordinate access to the
 * element with other accesses and modifications.
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
 * @param element The element to search for the param.
 *
 * @param name The name of the param to check for.
 *
 * @return True if no error is encountered and the param is found. If the
 * param is not found or an error is encountered, then false is returned and
 * an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
bool
stumpless_element_has_param( const struct stumpless_element *element,
                             const char *name );

/**
 * Returns name and params from element as a formatted string.
 * The character buffer should be freed when no longer is needed by the caller.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * element with other accesses and modifications.
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
 * @since release v2.2.0
 *
 * @param element The element to get the name and params from.
 *
 * @return The formatted string of name or name=[param1,...] if no error is encountered.
 * If an error is  encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_element_to_string( const struct stumpless_element *element );

/**
 * Returns the name of the given element. The character buffer must be freed by
 * the caller when it is no longer needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the name and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * element with other accesses and modifications.
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
 * @since release v1.6.0
 *
 * @param element The element to get the name from.
 *
 * @return The name of the element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_element_name( const struct stumpless_element *element );

/**
 * Returns the param in the given element at the specified index.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate access to the
 * element with other accesses and modifications.
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
 * @param element The element to get the param from.
 *
 * @param index The index of the param to retrieve.
 *
 * @return The param if no error is encountered. If an error is encountered,
 * then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_get_param_by_index( const struct stumpless_element *element,
                              size_t index );

/**
 * Returns the first occurrence of a param with the given name in element, if it
 * is found.
 *
 * Note that an element may contain as many instances of a param as desired
 * according to RFC 5424, and therefore there may be other param instances with
 * the same name. If you simply need a count of params with a given name, then
 * you can use stumpless_get_param_name_count to find this. If you
 * need a reference to any other params, then you must loop through all params
 * in the element using stumpless_get_param_by_index, checking each name.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed by
 * another thread during execution. A mutex is used to coordinate access to the
 * element with other accesses and modifications.
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
 * @param element The element to search.
 *
 * @param name The param name to search for.
 *
 * @return The param if it is found in the element, or NULL otherwise. If an
 * error was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_get_param_by_name( const struct stumpless_element *element,
                             const char *name );

/**
 * Returns the number of params in the given element.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate access to the
 * element with other accesses and modifications.
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
 * @param element The element to get the param count of.
 *
 * @return The number of params element has. If there is an error, zero is
 * returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_get_param_count( const struct stumpless_element *element );

/**
 * Gives the index of the first occurrence of a param with the given name in
 * the given element.
 *
 * Note that an element may contain as many instances of a param as desired
 * according to RFC 5424, and therefore there may be other param instances that
 * this function does not recognize. If you simply need a count of params with a
 * given name, then you can use stumpless_get_param_name_count to find this. If
 * you need a reference to any other params, then you must loop through all
 * params in the element using stumpless_get_param_by_index, checking each name.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed by
 * another thread during execution. A mutex is used to coordinate access to the
 * element with other accesses and modifications.
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
 * @param element The element to search for params with the given name.
 *
 * @param name The name to search params for.
 *
 * @return The first instance of a param with name in element, if one exists. If
 * there is no such param or an error is encountered, NULL is returned and an
 * error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_get_param_index( const struct stumpless_element *element,
                           const char *name );

/**
 * Gets the name of the param with the given index in this element. The
 * result character buffer must be freed by the caller when it is no longer
 * needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the name and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * element with other accesses and modifications.
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
 * @since release v1.6.0
 *
 * @param element The element to get the param and name from.
 *
 * @param index The index of the param to get the name from.
 *
 * @return The name of the param at the given index, if no error is encountered.
 * If an error is encountered, NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_param_name_by_index( const struct stumpless_element *element,
                                   size_t index );

/**
 * Gives the number of params with the given name found in the given element.
 *
 * If you need to get an actual reference to any of these params beyond the
 * first one, then you will need to loop through all params in the element using
 * stumpless_get_param_by_index, checking each name.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed by
 * another thread during execution. A mutex is used to coordinate access to the
 * element with other accesses and modifications.
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
 * @param element The element to search for params.
 *
 * @param name The name to look for in params.
 *
 * @return The number of params found with the given name in the given element.
 * If an error is encountered, zero is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_get_param_name_count( const struct stumpless_element *element,
                                const char *name );

/**
 * Returns the value of the param at the given index in the given element. The
 * result character buffer must be freed by the caller when it is no longer
 * needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the value and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * element with other accesses and modifications.
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
 * @since release v1.6.0
 *
 * @param element The element to retrieve the param and value from.
 *
 * @param index The index of the param to get the value from.
 *
 * @return The value of the param at the given index, if no error is
 * encountered. If an error is encountered, then NULL is returned and an error
 * code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_param_value_by_index( const struct stumpless_element *element,
                                    size_t index );

/**
 * Returns the value of the first param with the given name in the given
 * element. The result character buffer must be freed by the caller when it is
 * no longer needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the value and was not to be modified by the caller. This
 * behavior changed in v2.0.0 in order to avoid thread safety issues.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * element with other accesses and modifications.
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
 * If you need to get the value of a param with the given name beyond the first
 * one, then you will need to loop through all params in the element using
 * stumpless_get_param_by_index, checking each name.
 *
 * @since release v1.6.0
 *
 * @param element The element to retrieve the param and value from.
 *
 * @param name The name of the param to get the value from.
 *
 * @return The value of the first param with the given name, if no error is
 * encountered. If an error is encountered, then NULL is returned and an error
 * code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_param_value_by_name( const struct stumpless_element *element,
                                   const char *name );

/**
 * Loads a provided element with the given name.
 *
 * Does not call any memory allocation routines, and is faster than
 * stumpless_new_element as a result.
 *
 * An element loaded using this function must be unloaded with
 * stumpless_unload_element when it is no longer needed. Calling
 * stumpless_destroy_element or any function that does (such as
 * stumpless_destroy_entry_and_contents will result in memory corruption).
 *
 * **Thread Safety: MT-Safe race:element race:name**
 * This function is thread safe, assuming that the element and name are
 * not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe lock**
 * This function is not safe to call from signal handlers due to the use of
 * a mutex initialization routine. If STUMPLESS_THREAD_SAFETY_SUPPORTED is not
 * defined, then this function is AS-Safe.
 *
 * **Async Cancel Safety: AC-Unsafe lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a mutex initialization routine. If
 * STUMPLESS_THREAD_SAFETY_SUPPORTED is not defined, then this function is
 * AC-Safe.
 *
 * @since release v2.2.0
 *
 * @param element The struct to load.
 *
 * @param name The name of the element.
 *
 * @return A pointer to the loaded element, if no error is encountered. If an
 * error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_load_element( struct stumpless_element *element, const char *name );

/**
 * Creates a new element with the given name.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not changed
 * by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the new element.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @param name The new name of the element. Valid name should have printable
 * ASCII characters expect '=', ']' , '"' and should be 32 characters long
 *
 * @return The created element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_new_element( const char *name );

/**
 * Sets the name of the given element.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * element with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param element The element to set the name of.
 *
 * @param name The new name of the element. Valid name should have printable
 * ASCII characters expect '=', ']' , '"' and should be 32 characters long
 *
 * @return The modified element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_set_element_name( struct stumpless_element *element,
                            const char *name );

/**
 * Puts the param at the given index in the given element.
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
 * element with other accesses and modifications.
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
 * @param element The element to set the param on.
 *
 * @param index The index to set to param.
 *
 * @param param The param to set at the given index.
 *
 * @return The modified element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_set_param( struct stumpless_element *element,
                     size_t index,
                     struct stumpless_param *param );

/**
 * Sets the value of the param at the given index in the given element.
 *
 * **Thread Safety: MT-Safe race:value**
 * This function is thread safe, of course assuming that the value is not
 * changed during execution by another thread. A mutex is used to coordinate
 * changes to the element with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param element The element to set the param on.
 *
 * @param index The index of the param to set the value of.
 *
 * @param value The new value to set on the param.
 *
 * @return The modified element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_set_param_value_by_index( struct stumpless_element *element,
                                    size_t index,
                                    const char *value );

/**
 * Sets the value of the first param with the given name in the given element.
 *
 * If a param of the given name is not found in the element, one is created with
 * the supplied name and value and added to the end of the element.
 *
 * If you need to set the value of a param with this name other than the first
 * one, then you will need to loop through the params using
 * stumpless_get_param_by_index to find the params you want and then set the
 * value using stumpless_set_param_value.
 *
 * **Thread Safety: MT-Safe race:name race:value**
 * This function is thread safe, of course assuming that the name and value are
 * not changed during execution by another thread.. A mutex is used to
 * coordinate changes to the element with other accesses and modifications.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate access and the use of memory management
 * functions.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param element The element to set the param on.
 *
 * @param name The name of the param to set the value of (or create).
 *
 * @param value The new value to set on the param..
 *
 * @return The modified element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_element *
stumpless_set_param_value_by_name( struct stumpless_element *element,
                                   const char *name,
                                   const char *value );

/**
 * Unloads an element as well as all params that it contains.
 *
 * Either this function or stumpless_unload_element_only must be used to clean
 * up any element struct previously loaded with stumpless_load_element.
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
 * @param e The element to unload.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_unload_element_and_contents( const struct stumpless_element *e );

/**
 * Unloads an element, freeing any allocated memory. Associated params are left
 * untouched, and must be unloaded separately.
 *
 * Either this function or stumpless_unload_element_and_contents must be used to
 * clean up any element struct previously loaded with stumpless_load_element.
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
 * @param element The element to unload.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_unload_element_only( const struct stumpless_element *element );


#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif /* __STUMPLESS_ELEMENT_H */
