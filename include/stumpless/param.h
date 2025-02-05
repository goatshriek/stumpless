/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2022 Joel E. Anderson
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
 * Types and functions for creating and modifying params.
 */

#ifndef __STUMPLESS_PARAM_H
#  define __STUMPLESS_PARAM_H

#  include <stddef.h>
#  include <stumpless/config.h>
#  include <stumpless/entry.h>

/** The maximum length of a parameter name, as specified by RFC 5424. */
#  define STUMPLESS_MAX_PARAM_NAME_LENGTH 32

#  ifdef __cplusplus
extern "C" {
#  endif

// this is required due to the circular dependency with the entry header.
struct stumpless_entry;

#ifdef STUMPLESS_JOURNALD_TARGETS_SUPPORTED
/**
 * Gets the name to use for the journald field corresponding to this param.
 *
 * If the destination buffer is too small to hold the complete name, then
 * nothing should be done. Callers must be able to detect this by comparing
 * the return value to the value provided in the size argument. If the return
 * value is larger, then the name was not written into destination.
 *
 * **Thread Safety: MT-Unsafe**
 * This function need not be thread safe. It will be called when locks are
 * already held on the entry, element, and param in question, and therefore
 * should not use any functions that will attempt to lock any of these as this
 * will result in deadlock.
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
 * @param param_index The index of the param within the element.
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
( *stumpless_param_namer_func_t )( const struct stumpless_entry *entry,
                                   size_t element_index,
                                   size_t param_index,
                                   char *destination,
                                   size_t size );
#endif

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
 * Note that the name will be NULL-terminated as of version 1.6.0. In earlier
 * versions it is _not_ NULL-terminated.
 *
 * If you need to access the name, use the stumpless_(g|s)et_param_name
 * functions. These will protect you from changes in the struct in future
 * versions.
 */
  char name[STUMPLESS_MAX_PARAM_NAME_LENGTH + 1];
/** The number of characters in name (not including the NULL character). */
  size_t name_length;
/**
 * The value may be any UTF-8 string.
 *
 * As specified in RFC 5424, the characters '"' (ABNF %d34), '\' (ABNF %d92),
 * and ']' (ABNF %d93) MUST be escaped by placing a backslash character '\'
 * directly before them.
 *
 * Unlike the name field, value will always be NULL-terminated. This is done to
 * support their use for wel insertion strings.
 *
 * If you need to access the value, use the stumpless_(g|s)et_param_value
 * functions. These will protect you from changes in the struct in future
 * versions.
 */
  char *value;
/** The number of characters in value (not including the NULL character). */
  size_t value_length;
#  ifdef STUMPLESS_JOURNALD_TARGETS_SUPPORTED
/** Gets the name to use for the journald field corresponding to this param. */
  stumpless_param_namer_func_t get_journald_name;
#  endif
#  ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/**
 * A pointer to a mutex which protects all target fields. The exact type of
 * this mutex depends on the build.
 */
  void *mutex;
#  endif
};

/**
 * Creates a copy of a param.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate the read of the
 * param with other accesses and modifications.
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
 * @param param The param to copy.
 *
 * @return A new param that is a copy of the original. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_copy_param( const struct stumpless_param *param );

/**
 * Destroys a param, freeing any allocated memory.
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
 * @param param The param to destroy.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_destroy_param( const struct stumpless_param *param );

/**
 * Returns the name of the given param. The character buffer must be freed by
 * the caller when it is no longer needed to avoid memory leaks.
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
 * @since release v1.6.0
 *
 * @param param The param to get the name from.
 *
 * @return The name of param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_param_name( const struct stumpless_param *param );

/**
 * Returns the value of the given param. The character buffer must be freed by
 * the caller when it is no longer needed to avoid memory leaks.
 *
 * In versions prior to v2.0.0, the returned pointer was to the internal buffer
 * used to store the value and was not to be modified by the caller. This
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
 * @since release v1.6.0
 *
 * @param param The param to get the value from.
 *
 * @return The value of param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_get_param_value( const struct stumpless_param *param );

/**
 * Loads a provided param with the given values.
 *
 * This function will allocate less memory than stumpless_new_param, but will
 * still allocate memory for the value of the param, which may be of variable
 * length.
 *
 * A param loaded using this function must be unloaded with
 * stumpless_unload_param when it is no longer needed. Calling
 * stumpless_destroy_param or any function that does (such as
 * stumpless_destroy_entry_and_contents will result in memory corruption).
 *
 * **Thread Safety: MT-Safe race:param race:name race:value**
 * This function is thread safe, assuming that the param, name, and value are
 * not changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap lock**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the param's value as well as the use of
 * a mutex initialization routine.
 *
 * **Async Cancel Safety: AC-Unsafe heap lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions and a mutex
 * initialization routine.
 *
 * @since release v2.2.0
 *
 * @param param The struct to load with the given values.
 *
 * @param name The name of the param.
 *
 * @param value The value of the param. This pointer will be stored and used
 * over the lifetime of the param, and must be valid until
 * `stumpless_unload_param` is called on this loaded param.
 *
 * @return A pointer to the loaded param, if no error is encountered. If an
 * error is encountered, then NULL is returned and an error code is set
 * appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_load_param( struct stumpless_param *param,
                      const char *name,
                      const char *value );

/**
 * Creates a new param with the given name and value.
 *
 * **Thread Safety: MT-Safe race:name race:value**
 * This function is thread safe, of course assuming that name and value are not
 * changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap lock**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the new param as well as the use of
 * a mutex initialization routine.
 *
 * **Async Cancel Safety: AC-Unsafe heap lock**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions and a mutex
 * initialization routine.
 *
 * @param name The name of the new param. Restricted to printable ASCII
 * characters different from '=', ']' and '"'.
 *
 * @param value The value of the new param. The value must be UTF-8 string.
 *
 * @return The created param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_new_param( const char *name, const char *value );

/**
 * Creates a new param given a string by parsing the string and calling stumpless_new_param.
 *
 * **Thread Safety: MT-Safe
 * This function is thread safe, assuming the the given string is not changed
 * by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers since it calls
 * stumpless_new_param() which has usage of memory management functions.
 *
 * **Async Cancel Safety: AC_Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, since it calls stumpless_new_param() which has usage of
 * memory management functions.
 *
 * @since release v2.2.0
 *
 * @param string The string to create the stumpless_param from.
 *
 * @return The created param, if no error is encountered. If an error is
 * encountered, NULL is returned and an error code set appropriately.
 */
  
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_new_param_from_string( const char *string );

/**
 * Sets the name of the given param.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * param while it is being modified.
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
 * @since release v1.6.0
 *
 * @param param The param to set the name of.
 *
 * @param name The new name of param. Restricted to printable ASCII characters different from '=', ']' and '"'.
 *
 * @return The modified param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_set_param_name( struct stumpless_param *param, const char *name );

/**
 * Sets the value of the given param.
 *
 * **Thread Safety: MT-Safe**
 * This function is thread safe. A mutex is used to coordinate changes to the
 * param while it is being modified.
 *
 * **Async Signal Safety: AS-Unsafe lock heap**
 * This function is not safe to call from signal handlers due to the use of a
 * non-reentrant lock to coordinate changes and the use of memory management
 * functions to create the new value and free the old one.
 *
 * **Async Cancel Safety: AC-Unsafe lock heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of a lock that could be left locked as well as
 * memory management functions.
 *
 * @since release v1.6.0
 *
 * @param param The param to set the value of.
 *
 * @param value The new name of param. The value must be UTF-8 string.
 *
 * @return The modified param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_param *
stumpless_set_param_value( struct stumpless_param *param, const char *value );


/**
 * Returns the name and the value from param as a formatted string.
 * The character buffer should be freed when no longer is needed by the caller.
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
 * @since release v2.0.0
 *
 * @param param The param to get the name and the value from.
 *
 * @return The formatted string of "param_name=param_value" if no error is
 * encountered. If an error is  encountered, then NULL is returned and an
 * error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
const char *
stumpless_param_to_string( const struct stumpless_param *param );

/**
 * Copies the name and the value from param to a buffer string.
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
 * @since release v3.0.0
 *
 * @param param The param to get the name and the value from.
 *
 * @return The size written to the buffer string if no error is
 * encountered. If error code 'STUMPLESS_ARGUMENT_TOO_SMALL' is encountered, 
 * then minimum required size of the buffer is returned. If a NULL argument is 
 * encountered, 0 is returned.
 */
STUMPLESS_PUBLIC_FUNCTION
size_t
stumpless_param_into_string( const struct stumpless_param *param, char *str, size_t max_size );

/**
 * Unloads a param.
 *
 * Either this function, stumpless_unload_element_and_contents, or
 * stumpless_unload_entry_and_contents must be used to clean up any param struct
 * previously loaded with stumpless_load_param.
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
 * @param param The param to unload.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_unload_param( const struct stumpless_param *param );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif /* __STUMPLESS_PARAM_H */
