/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2024 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_VALIDATE_H
#define __STUMPLESS_PRIVATE_VALIDATE_H

#include <stddef.h>
#include <stdbool.h>
#include <stumpless/error.h>
#include "private/config.h"
#include "private/config/wrapper/locale.h"
#include "private/error.h"

/**
 * Checks to see if the variable with the provided name is NULL, and if it is
 * then raises an argument empty error and returns NULL.
 */
#  define VALIDATE_ARG_NOT_NULL( ARG_NAME )                                    \
if( unlikely( ( ARG_NAME ) == NULL ) ) {                                       \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) );            \
  return NULL;                                                                 \
}

/**
 * Checks to see if the variable with the provided name is NULL, and if it is
 * then raises an argument empty error and returns -STUMPLESS_ARGUMENT_EMPTY.
 *
 * This is nearly identical to VALIDATE_ARG_NOT_NULL, but is suitable for use in
 * functions where the return value is an integer instead of a pointer, and a
 * negative value is needed to signify failure.
 */
#  define VALIDATE_ARG_NOT_NULL_INT_RETURN( ARG_NAME )                         \
if( unlikely( ( ARG_NAME ) == NULL ) ) {                                       \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) );            \
  return -STUMPLESS_ARGUMENT_EMPTY;                                            \
}

/**
 * Checks to see if the variable with the provided name is NULL, and if it is
 * then raises an argument empty error and returns 0.
 *
 * This is nearly identical to VALIDATE_ARG_NOT_NULL, but is suitable for use in
 * functions where the return value is an unsigned integer instead of a pointer,
 * and zero is needed to signify failure.
 */
#  define VALIDATE_ARG_NOT_NULL_UNSIGNED_RETURN( ARG_NAME )                    \
if( unlikely( ( ARG_NAME ) == NULL ) ) {                                       \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) );            \
  return 0;                                                                    \
}

/**
 * Checks to see if the variable with the provided name is NULL, and if it is
 * then raises an argument empty error and returns.
 *
 * This is nearly identical to VALIDATE_ARG_NOT_NULL, but is suitable for use in
 * functions where the return type is void.
 *
 * @since release v2.2.0
 */
#  define VALIDATE_ARG_NOT_NULL_VOID_RETURN( ARG_NAME )                        \
if( unlikely( ( ARG_NAME)  == NULL ) ) {                                       \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) );            \
  return;                                                                      \
}

/**
 * Checks that the passed in app name is of the appropriate length and
 * contains only printable ASCII characters.
 *
 * @param str The app name to validate.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the app name has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool
validate_app_name( const char *str, size_t *length );

/**
 * Checks the length of app name.
 *
 * @param app_name the app name
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the app name is less than allowed length
 * (48 characters not including NULL terminating),otherwise
 * it will return false and raise STUMPLESS_ARGUMENT_TOO_BIG error.
 */
bool
validate_app_name_length( const char *app_name, size_t *length );

/**
 * Checks that the passed in element name contains only ASCII characters and
 * also does not contain any of the following characters: '=',']','"'.
 *
 * @param str The element name to validate.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the element name has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool
validate_element_name( const char *str, size_t *length );

/**
 * Checks that the passed in element name is of valid length
 *
 * @param the element name(string).
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the element name is less than allowed length
 * (32 characters not including NULL terminating),otherwise
 * it will return false and raise an STUMPLESS_ARGUMENT_TOO_BIG error.
 */
bool
validate_element_name_length( const char *str, size_t *length );

/**
 * Checks a hostname for validity.
 *
 * @param hostname The hostname.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the hostname is valid. If the hostname is not valid then
 * false is returned and an appropriate error is raised.
 */
bool
validate_hostname( const char *hostname, size_t *length );

/**
 * Checks the length of a hostname.
 *
 * @param hostname The hostname.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the hostname is at or below the maximum allowed length,
 * otherwise it will return false and raise the appropriate error.
 */
bool
validate_hostname_length( const char *hostname, size_t *length );

/**
 * Checks that the passed in msgid is of the appropriate length and
 * contains only printable ASCII characters.
 *
 * @param str The msgid to validate.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the msgid has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool
validate_msgid( const char *str, size_t *length );

/**
 * Checks the char length of msgid.
 *
 * @param msgid The msgid.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the msgid is at or below the maximum allowed length,
 * otherwise it will return false and raise the appropriate error.
 */
bool
validate_msgid_length( const char *msgid, size_t *length );

/**
 * Checks that the passed in string contains only ASCII characters
 * (33 <= char <= 126) and not '=', ']', or '"' characters.
 *
 * @param str The string to validate.
 *
 * @param length The length of the string to validate.
 *
 * @return True if the string has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool
validate_name_chars( const char *str, size_t length );

/**
 * Checks that the passed in param name contains only ASCII characters and
 * also does not contain any of the following characters: '=',']','"'.
 *
 * @param str The param name to validate.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the param name has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool
validate_param_name( const char *str, size_t *length );

/**
 * Checks that the passed in param name is of valid length.
 *
 * @param the param name(string).
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the param name is less than allowed length
 * (32 characters not including NULL terminating), otherwise
 * it will return false and raise STUMPLESS_ARGUMENT_TOO_BIG error.
 */
bool
validate_param_name_length( const char *str, size_t *length );

/**
 * Checks that the passed in param value is valid UTF-8 string.
 *
 * @param str The param value(string).
 *
 * @param length The length of the string to validate.
 *
 * @return True if the param name is valid UTF-8 string, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool
validate_param_value( const char *str, size_t length );

/**
 * Checks that the passed in string contains only ASCII characters
 * (33 <= char <= 126).
 *
 * @param str The string to validate.
 *
 * @param length The length of the string to validate.
 *
 * @return True if the string has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool
validate_printable_ascii( const char *str, size_t length );

/**
 * Checks a procid for validity.
 *
 * @param procid The procid to validate.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the procid is valid. If the procid is not valid then
 * false is returned and an appropriate error is raised.
 */
bool
validate_procid( const char *procid, size_t *length );

/**
 * Checks the char length of procid.
 *
 * @param procid The procid.
 *
 * @param length A pointer to a variable that will be set to the length
 * of the string. Must not be NULL.
 *
 * @return True if the procid is at or below the maximum allowed length,
 * otherwise it will return false and raise the appropriate error.
 */
bool
validate_procid_length( const char *procid, size_t *length );

#endif /* __STUMPLESS_PRIVATE_VALIDATE_H */
