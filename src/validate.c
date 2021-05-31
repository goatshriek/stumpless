// SPDX-License-Identifier: Apache-2.0

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

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stumpless/entry.h>
#include "private/error.h"
#include "private/config/locale/wrapper.h"

bool validate_msgid_length(const char* msgid ) {
  size_t msgid_char_length = strlen( msgid );
  bool validation_status = true;

  if( msgid_char_length > STUMPLESS_MAX_MSGID_LENGTH ) {
    raise_argument_too_big( L10N_STRING_TOO_LONG_ERROR_MESSAGE,
                            msgid_char_length,
                            L10N_STRING_LENGTH_ERROR_CODE_TYPE );

    validation_status = false;
  }

  return validation_status;
}

bool validate_printable_ascii( const char* str ) {
  size_t str_length = strlen( str );

  for (size_t i = 0; i < str_length; i++) {
    if (str[i] < 33 || str[i] > 126) {
      raise_invalid_encoding(L10N_FORMAT_ERROR_MESSAGE("app name"));
      return false;
    }
  }

  return true;
}


bool validate_app_name_length( const char* app_name ) {
    size_t app_name_char_length = strlen( app_name );
    bool validation_status = true;

    if ( app_name_char_length > STUMPLESS_MAX_APP_NAME_LENGTH ) {
      raise_argument_too_big( L10N_STRING_TOO_LONG_ERROR_MESSAGE,
                              app_name_char_length,
                              L10N_STRING_LENGTH_ERROR_CODE_TYPE );

      validation_status = false;
    }

    return validation_status;
}
