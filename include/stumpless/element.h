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
 * Types and functions for creating and modifying elements.
 */

#ifndef __STUMPLESS_ELEMENT_H
#  define __STUMPLESS_ELEMENT_H

#  include <stddef.h>
#  include <stumpless/param.h>

#  ifdef __cplusplus
extern "C" {
#  endif

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
 * Note that the name will be NULL-terminated as of version 1.6.0. In earlier
 * versions it is _not_ NULL-terminated.
 *
 * If you need to access the name, use the stumpless_(g|s)et_element_name
 * functions. These will protect you from changes in the struct in future
 * versions.
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
 * Creates a new param and adds it to the given element.
 *
 * This is equivalent to calling stumpless_new_param and passing the result
 * directly stumpless_add_param.
 *
 * @since Release v1.6.0
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
struct stumpless_element *
stumpless_add_new_param( struct stumpless_element *element,
                         const char *param_name,
                         const char *param_value );

/**
 * Adds a param to an element.
 *
 * @param element The element to add the param to.
 *
 * @param param The param to add to element.
 *
 * @return The modified element if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_element *
stumpless_add_param( struct stumpless_element *element,
                     struct stumpless_param *param );

/**
 * An alias for stumpless_destroy_element_and_contents.
 *
 * @param element The element to destroy.
 */
void
stumpless_destroy_element( struct stumpless_element *element );

/**
 * Destroys an element as well as all params that it contains, freeing any
 * allocated memory.
 *
 * @param element The element to destroy.
 */
void
stumpless_destroy_element_and_contents( struct stumpless_element *element );

/**
 * Destroys an element, freeing any allocated memory. Associated params are left
 * untouched, and must be destroyed separately.
 *
 * @param element The element to destroy.
 */
void
stumpless_destroy_element_only( struct stumpless_element *element );

/**
 * Returns the name of the given element. The resulting character buffer must
 * not be altered or freed by the caller.
 *
 * @since Release v1.6.0
 *
 * @param element The element to get the name from.
 *
 * @return The name of the element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
const char *
stumpless_get_element_name( const struct stumpless_element *element );

/**
 * Returns the param in the given element at the specified index.
 *
 * @since Release v1.6.0
 *
 * @param element The element to get the param from.
 *
 * @param index The index of the param to retrieve.
 *
 * @return The param if no error is encountered. If an error is encountered,
 * then NULL is returned and an error code is set appropriately.
 */
struct stumpless_param *
stumpless_get_param_by_index( struct stumpless_element *element,
                              size_t index );

/**
 * Returns the first occurrence of a param with the given name in element, if it
 * is found.
 *
 * @since Release v1.6.0
 *
 * @param element The element to search.
 *
 * @param name The param name to search for.
 *
 * @return The param, if it is found in the element, NULL otherwise. If an error
 * was encountered, then NULL is returned and an error code is set
 * appropriately.
 */
struct stumpless_param *
stumpless_get_param_by_name( struct stumpless_element *element,
                             const char *name );

/**
 * Returns the number of params in the given element.
 *
 * @since Release v1.6.0
 *
 * @param element The element to get the param count of.
 *
 * @return The number of params element has. If there is an error, zero is
 * returned and an error code is set appropriately.
 */
size_t
stumpless_get_param_count( const struct stumpless_element *element );

/**
 * Gives the index of the first occurrence of a param with the given name in
 * the given element.
 *
 * Note that an element may contain as many instances of a param as desired
 * according to RFC 5424, and therefore there may be other param instances that
 * this function does hint at. If you simply need a count of params with a given
 * name, then you can use stumpless_get_param_name_count to find this. If you
 * need a reference to any other params, then you must loop through all params
 * in the element using stumpless_get_param_by_index, checking each name.
 *
 * @since Release v1.6.0
 *
 * @param element The element to search for params with the given name.
 *
 * @param name The name to search params for.
 *
 * @return The first instance of a param with name in element, if one exists. If
 * there is no such param or an error is encountered, NULL is returned and an
 * error code is set appropriately.
 */
size_t
stumpless_get_param_index( struct stumpless_element *element,
                           const char *name );

const char *
stumpless_get_param_name_by_index( struct stumpless_element *element,
                                   size_t index );

/**
 * Gives the number of params with the given name found in the given element.
 *
 * If you need to get a reference to any of these params beyond the first one,
 * then you will need to loop through all params in the element using
 * stumpless_get_param_by_index, checking each name.
 *
 * @since Release v1.6.0
 *
 * @param element The element to search for params.
 *
 * @param name The name to look for in params.
 *
 * @return The number of params found with the given name in the given element.
 * If an error is encountered, zero is returned and an error code is set
 * appropriately.
 */
size_t
stumpless_get_param_name_count( const struct stumpless_element *element,
                                const char *name );

const char *
stumpless_get_param_value_by_index( struct stumpless_element *element,
                                    size_t index );

const char *
stumpless_get_param_value_by_name( struct stumpless_element *element,
                                   const char *name );

/**
 * Creates a new element with the given name.
 *
 * @param name The name of the new element.
 *
 * @return The created element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code set appropriately.
 */
struct stumpless_element *
stumpless_new_element( const char *name );

/**
 * Sets the name of the given element.
 *
 * @since Release v1.6.0
 *
 * @param element The element to set the name of.
 *
 * @return The modified element, if no error is encountered. If an error is
 * encountered, then NULL is returned and an error code is set appropriately.
 */
struct stumpless_element *
stumpless_set_element_name( struct stumpless_element *element,
                            const char *name );

struct stumpless_element *
stumpless_set_param_by_index( struct stumpless_element *element,
                              size_t index,
                              struct stumpless_param *param );

struct stumpless_element *
stumpless_set_param_value_by_index( struct stumpless_element *element,
                                    size_t index,
                                    const char *value );

struct stumpless_element *
stumpless_set_param_value_by_name( struct stumpless_element *element,
                                   const char *name,
                                   const char *value );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif

#endif /* __STUMPLESS_ELEMENT_H */
