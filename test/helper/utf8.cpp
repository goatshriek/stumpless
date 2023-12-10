// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2023 Joel E. Anderson
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

#include <cstddef>
#include <string>
#include <gtest/gtest.h>
#include "test/helper/utf8.hpp"

void TestUTF8Compliance( const std::string &str ){
  enum utf8_state {
    LEAD_CHAR,
    TWO_CHAR,
    THREE_CHAR,
    FOUR_CHAR,
    FIVE_CHAR,
    SIX_CHAR
  };
  enum utf8_state current_state = LEAD_CHAR;
  size_t char_count;
  char bytes[6];

  auto it = str.cbegin();

  // strip off the BOM if it exists
  if( str[0] == '\xef' && str[1] == '\xbb' && str[2] == '\xbf' ){
    std::advance( it, 3 );
  }

  for( const char &c = *it; it != str.cend(); it++ ){
    switch(current_state){
      case LEAD_CHAR:
        if( (c & '\xe0') == '\xc0' ) {
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
        if( ( c & '\xfc' ) == '\xf8' ) {
          current_state = FIVE_CHAR;
          bytes[0] = c & '\x03';
          char_count = 1;
          break;
        }
        if( ( c & '\xfe' ) == '\xfc' ) {
          current_state = SIX_CHAR;
          bytes[0] = c & '\x01';
          char_count = 1;
          break;
        }
        ASSERT_EQ( c & '\x80', 0 ) << "invalid lead byte";
        break;

      case TWO_CHAR:
        ASSERT_EQ( c & '\xc0', '\x80' ) << "invalid continuation byte";
        ASSERT_NE( bytes[0] & '\x1e', 0 ) << "non-shortest form not allowed";
        current_state = LEAD_CHAR;
        break;

      case THREE_CHAR:
        ASSERT_EQ( c & '\xc0', '\x80' ) << "invalid continuation byte";
        bytes[char_count] = c & '\x3f';
        char_count++;
        if( char_count == 3 ) {
          ASSERT_NE( bytes[0] | ( bytes[1] & '\x20' ), 0 ) << "non-shortest form not allowed";
          current_state = LEAD_CHAR;
        }
        break;

      case FOUR_CHAR:
        ASSERT_EQ( c & '\xc0', '\x80' ) << "invalid continuation byte";
        bytes[char_count] = c & '\x3f';
        char_count++;
        if( char_count == 4 ) {
          ASSERT_NE( bytes[0] | ( bytes[1] & '\x30' ), 0 ) << "non-shortest form not allowed";
          current_state = LEAD_CHAR;
        }
        break;


      case FIVE_CHAR:
        ASSERT_EQ( c & '\xc0', '\x80' ) << "invalid continuation byte";
        bytes[char_count] = c & '\x3f';
        char_count++;
        if(char_count == 5){
          ASSERT_NE( bytes[0] | ( bytes[1] & '\x38' ), 0 ) << "non-shortest form not allowed";
          current_state = LEAD_CHAR;
        }
        break;


      case SIX_CHAR:
        ASSERT_EQ( c & '\xc0', '\x80' ) << "invalid continuation byte";
        bytes[char_count] = c & '\x3f';
        char_count++;
        if(char_count == 6){
          ASSERT_NE( bytes[0] | ( bytes[1] & '\x3c' ), 0 ) << "non-shortest form not allowed";
          current_state = LEAD_CHAR;
        }
        break;

      default:
        FAIL() << "invalid state reached during string parsing";
    }
  }
}
