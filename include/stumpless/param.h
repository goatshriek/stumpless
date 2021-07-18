/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2021 Joel E. Anderson
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

#  ifdef __cplusplus
extern "C" {
#  endif

// this is required due to the circular dependency with the entry header.
struct stumpless_entry;

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
  char *name;
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
  size_t ( *get_journald_name )( const struct stumpless_entry *,
                                 size_t,
                                 size_t,
                                 char *,
                                 size_t );
#  endif
#  ifdef STUMPLESS_THREAD_SAFETY_SUPPORTED
/*
 * In thread-safe builds the memory at the end of the param holds a mutex that
 * is used to coordinate access to the param. However the type info is not
 * included in the struct definition in the public headers as it is
 * configuration-specific and would complicate the public headers significantly
 * if they were to stay portable.
 */
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
const char *
stumpless_get_param_value( const struct stumpless_param *param );

/**
 * Creates a new param with the given name and value.
 *
 * **Thread Safety: MT-Safe race:name race:value**
 * This function is thread safe, of course assuming that name and value are not
 * changed by other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory management functions to create the new param.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, due to the use of memory management functions.
 *
 * @param name The name of the new param. Restricted to printable ASCII characters different from '=', ']' and '"'.
 *
 * @param value The value of the new param.
 *
 * @return The created param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code set appropriately.
 */
struct stumpless_param *
stumpless_new_param( const char *name, const char *value );

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
 * @param value The new name of param.
 *
 * @return The modified param, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
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
 * @return The formatted string of <name>: <value> if no error is encountered.
 * If an error is  encountered, then NULL is returned and an error code is set appropriately.
 */

const char *
stumpless_param_to_string( const struct stumpless_param *param );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif /* __STUMPLESS_PARAM_H */
