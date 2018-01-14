/*
 * Copyright 2018, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <gtest/gtest.h>
#include "test/function/utf8.hpp"

void TestUTF8Compliance(const char *str){
  // strip off the BOM if it exists
  if(*str == '\xef' && *(str+1) == '\xbb' && *(str+2) == '\xbf'){
    str += 3;
  }

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

  for(const char *c=str; *c != '\0'; c++){
    switch(current_state){
      case LEAD_CHAR:
        if((*c & '\xe0') == '\xc0'){
          current_state = TWO_CHAR;
          bytes[0] = *c & '\x1f';
          break;
        }
        if((*c & '\xf0') == '\xe0'){
          current_state = THREE_CHAR;
          bytes[0] = *c & '\x0f';
          char_count = 1;
          break;
        }
        if((*c & '\xf8') == '\xf0'){
          current_state = FOUR_CHAR;
          bytes[0] = *c & '\x07';
          char_count = 1;
          break;
        }
        if((*c & '\xfc') == '\xf8'){
          current_state = FIVE_CHAR;
          bytes[0] = *c & '\x03';
          char_count = 1;
          break;
        }
        if((*c & '\xfe') == '\xfc'){
          current_state = SIX_CHAR;
          bytes[0] = *c & '\x01';
          char_count = 1;
          break;
        }
        ASSERT_EQ(*c & '\x80', 0) << "invalid lead byte";
        break;

      case TWO_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80') << "invalid continuation byte";
        ASSERT_NE(bytes[0] & '\x1e', 0) << "non-shortest form not allowed";
        current_state = LEAD_CHAR;
        break;

      case THREE_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80') << "invalid continuation byte";
        bytes[char_count] = *c & '\x3f';
        char_count++;
        if(char_count == 3){
          ASSERT_NE(bytes[0] | (bytes[1] & '\x20'), 0) << "non-shortest form not allowed";
          current_state = LEAD_CHAR;
        }
        break;

      case FOUR_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80') << "invalid continuation byte";
        char_count++;
        if(char_count == 4){
          current_state = LEAD_CHAR;
        }
        break;


      case FIVE_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80') << "invalid continuation byte";
        char_count++;
        if(char_count == 5){
          current_state = LEAD_CHAR;
        }
        break;


      case SIX_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80') << "invalid continuation byte";
        char_count++;
        if(char_count == 6){
          current_state = LEAD_CHAR;
        }
        break;

      default:
        FAIL() << "invalid state reached during string parsing";
    }
  }
}
