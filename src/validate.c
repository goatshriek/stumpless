// SPDX-License-Identifier: Apache-2.0

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

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stumpless/entry.h>
#include <stumpless/param.h>
#include "private/error.h"
#include "private/validate.h"
#include "private/config/wrapper/locale.h"

/**
 * Validates that a provide string is less than or equal to the maximum length
 * provided. An error is raised if the validation fails.
 *
 * @param str The string to check the length of.
 *
 * @param max_length The maximum length allowed for the string. Must not be
 * NULL.
 *
 * @param length A pointer to a variable that will be set to the computed length
 * of the string, in bytes.
 */
static
bool
validate_string_length( const char *str, size_t max_length, size_t *length ) {
  *length = strlen( str );
  if( *length > max_length ) {
    raise_argument_too_big( L10N_STRING_TOO_LONG_ERROR_MESSAGE,
                            *length,
                            L10N_STRING_LENGTH_ERROR_CODE_TYPE );
    return false;
  } else {
    return true;
  }
}

bool
validate_app_name( const char *str, size_t *length ) {
  return validate_app_name_length( str, length ) &&
         validate_printable_ascii( str, *length );
}

bool
validate_app_name_length( const char *app_name, size_t *length ) {
  return validate_string_length( app_name,
                                 STUMPLESS_MAX_APP_NAME_LENGTH,
                                 length );
}

bool
validate_element_name( const char *str, size_t *length ) {
  return validate_element_name_length( str, length ) &&
         validate_name_chars( str, *length );
}

bool
validate_element_name_length( const char *name, size_t *length ) {
  return validate_string_length( name,
                                 STUMPLESS_MAX_ELEMENT_NAME_LENGTH,
                                 length );
}

bool
validate_hostname( const char *hostname, size_t *length ) {
  return validate_hostname_length( hostname, length ) &&
         validate_printable_ascii( hostname, *length );
}

bool
validate_hostname_length( const char *hostname, size_t *length ) {
  return validate_string_length( hostname,
                                 STUMPLESS_MAX_HOSTNAME_LENGTH,
                                 length );
}

bool
validate_msgid( const char *str, size_t *length ) {
  return validate_msgid_length( str, length ) &&
         validate_printable_ascii( str, *length );
}

bool
validate_msgid_length( const char *msgid, size_t *length ) {
  return validate_string_length( msgid,
                                 STUMPLESS_MAX_MSGID_LENGTH,
                                 length );
}

bool
validate_name_chars( const char *str, size_t length ) {
  size_t i;

  for( i = 0; i < length; i++ ) {
    if( str[i] < 33 ||
        str[i] > 126 ||
        str[i] == '=' ||
        str[i] == ']' ||
        str[i] == '"' ) {
      raise_invalid_encoding( L10N_FORMAT_ERROR_MESSAGE( "identifier" ) );
      return false;
    }
  }

  return true;
}

bool
validate_param_name( const char *str, size_t *length ) {
  return validate_param_name_length( str, length ) &&
         validate_name_chars( str, *length );
}

bool
validate_param_name_length( const char *name, size_t *length ) {
  return validate_string_length( name,
                                 STUMPLESS_MAX_PARAM_NAME_LENGTH,
                                 length );
}

/**
 * Validates that a provided string is UTF-8 compliance.
 *
 * @param str The string to validate.
 *
 * @param length The length of the string.
 * 
 * @return True if the string is valid UTF-8 string, otherwise
 * it will return false and raise STUMPLESS_INVALID_ENCODING error.
 * 
 * @note This implementation is ported from the function
 * TestUTF8Compliance in test/helper/utf8.cpp.
 */
static
bool
validate_utf8_compliance( const char *str, size_t length ) {
  enum utf8_state {
    LEAD_CHAR,
    TWO_CHAR,
    THREE_CHAR,
    FOUR_CHAR,
  };

  enum utf8_state current_state = LEAD_CHAR;
  size_t i;
  size_t char_count;
  char bytes[6];

  // strip off the BOM if it exists
  if( length >= 3 && str[0] == '\xef' && str[1] == '\xbb' && str[2] == '\xbf' ) {
    str += 3;
    length -= 3;
  }

  for( i = 0; i < length; i++ ) {
    #define VALIDATE_CONTINUATION_BYTE( continuation_byte ) \
      if( ( ( continuation_byte ) & '\xc0' ) != '\x80' ) { \
        raise_invalid_encoding( L10N_FORMAT_ERROR_MESSAGE( "UTF-8 continuation byte" ) ); \
        return false; \
      }

    #define VALIDATE_SHORTEST_FORM( surplus_most_significant_bits ) \
      if( ( surplus_most_significant_bits ) == 0 ) { \
        raise_invalid_encoding( L10N_FORMAT_ERROR_MESSAGE( "UTF-8 shortest form" ) ); \
        return false; \
      }

    const char c = str[i];
    switch( current_state ) {
      case LEAD_CHAR:
        if( ( c & '\xe0' ) == '\xc0' ) {
          current_state = TWO_CHAR;
          bytes[0] = c & '\x1f';
          break;
        }
        if( ( c & '\xf0' ) == '\xe0' ) {
          current_state = THREE_CHAR;
          bytes[0] = c & '\x0f';
          char_count = 1;
          break;
        }
        if( ( c & '\xf8' ) == '\xf0' ) {
          current_state = FOUR_CHAR;
          bytes[0] = c & '\x07';
          char_count = 1;
          break;
        }
        if( ( c & '\x80' ) != 0 ) {
          raise_invalid_encoding( L10N_FORMAT_ERROR_MESSAGE( "UTF-8 lead byte" ) );
          return false;
        }
        break;

      case TWO_CHAR:
        VALIDATE_CONTINUATION_BYTE( c );
        VALIDATE_SHORTEST_FORM( bytes[0] & '\x1e' )
        current_state = LEAD_CHAR;
        break;

      case THREE_CHAR:
        VALIDATE_CONTINUATION_BYTE( c );
        bytes[char_count] = c & '\x3f';
        char_count++;
        if( char_count == 3 ) {
          VALIDATE_SHORTEST_FORM( bytes[0] | ( bytes[1] & '\x20' ) );
          current_state = LEAD_CHAR;
        }
        break;

      case FOUR_CHAR:
        VALIDATE_CONTINUATION_BYTE( c );
        bytes[char_count] = c & '\x3f';
        char_count++;
        if( char_count == 4 ) {
          VALIDATE_SHORTEST_FORM( bytes[0] | ( bytes[1] & '\x30' ) );
          current_state = LEAD_CHAR;
        }
        break;

      default:
        raise_invalid_encoding( L10N_INVALID_STATE_DURING_UTF8_PARSING );
        return false;
    }

    #undef VALIDATE_SHORTEST_FORM
    #undef VALIDATE_CONTINUATION_BYTE
  }

  return true;
}

bool
validate_param_value( const char *str, size_t length ) {
  return validate_utf8_compliance( str, length );
}

bool
validate_printable_ascii( const char *str, size_t length ) {
  size_t i;

  for( i = 0; i < length; i++ ) {
    if( str[i] < 33 || str[i] > 126 ) {
      raise_invalid_encoding( L10N_FORMAT_ERROR_MESSAGE( "printable ascii" ) );
      return false;
    }
  }

  return true;
}

bool
validate_procid( const char *procid, size_t *length ) {
  return validate_procid_length( procid, length ) &&
         validate_printable_ascii( procid, *length );
}

bool
validate_procid_length( const char *procid, size_t *length ) {
  return validate_string_length( procid,
                                 STUMPLESS_MAX_PROCID_LENGTH,
                                 length );
}
