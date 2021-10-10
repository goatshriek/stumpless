/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020 Joel E. Anderson
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
#  define __STUMPLESS_PRIVATE_VALIDATE_H

#  include <stddef.h>
#  include <stdbool.h>
#  include "private/config/locale/wrapper.h"
#  include "private/error.h"

#  define VALIDATE_ARG_NOT_NULL( ARG_NAME )                         \
if( ARG_NAME == NULL ) {                                            \
  raise_argument_empty( L10N_NULL_ARG_ERROR_MESSAGE( #ARG_NAME ) ); \
  return NULL;                                                      \
}

/**
 * Checks the char length of msgid.
 *
 * @param the msgid.
 * 
 * @return True if the msgid is at or below the maximum allowed length, otherwise
 * it will return false and raise the appropriate error.
 */
bool validate_msgid_length(const char* msgid );

/**
 * Checks that the passed in app_name contains only ASCII characters (33 <= char <= 126).
 *
 * @param the app_name.
 *
 * @return True if the app_name has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool validate_printable_ascii( const char* str );

/**
 * Checks the length of app name.
 *
 * @param the app name
 *
 * @return True if the app name is less than allowed length 
 * (48 characters not including NULL terminating),otherwise
 * it will return false and raise STUMPLESS_ARGUMENT_TOO_BIG error.
 */
bool validate_app_name_length( const char* app_name);

/**
 * Checks that the passed in param name contains only ASCII characters and
 * also does not contain any of the following characters: '=',']','"'.
 *
 * @param the param name.
 *
 * @return True if the param name has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool validate_param_name( const char* str);

/**
 * Checks that the passed in element name contains only ASCII characters and
 * also does not contain any of the following characters: '=',']','"'.
 *
 * @param the element name(string).
 *
 * @return True if the element name has the correct format, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 */
bool validate_element_name( const char* str);

/**
 * Checks that the passed in element name is of valid length
 *
 * @param the element name(string).
 *
 * @return True if the element name is less than allowed length 
 * (32 characters not including NULL terminating),otherwise
 * it will return false and raise STUMPLESS_ARGUMENT_TOO_BIG error.
 */
bool validate_element_name_length( const char* str);
#endif /* __STUMPLESS_PRIVATE_VALIDATE_H */
