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

  for(const char *c=str; *c != '\0'; c++){
    switch(current_state){
      case LEAD_CHAR:
        if((*c & '\xe0') == '\xc0'){
          current_state = TWO_CHAR;
          break;
        }
        if((*c & '\xf0') == '\xe0'){
          current_state = THREE_CHAR;
          char_count = 1;
          break;
        }
        if((*c & '\xf8') == '\xf0'){
          current_state = FOUR_CHAR;
          char_count = 1;
          break;
        }
        if((*c & '\xfc') == '\xf8'){
          current_state = FIVE_CHAR;
          char_count = 1;
          break;
        }
        if((*c & '\xfe') == '\xfc'){
          current_state = SIX_CHAR;
          char_count = 1;
          break;
        }
        ASSERT_EQ(*c & '\x80', 0);
        break;

      case TWO_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80');
        current_state = LEAD_CHAR;
        break;

      case THREE_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80');
        char_count++;
        if(char_count == 3){
          current_state = LEAD_CHAR;
        }
        break;

      case FOUR_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80');
        char_count++;
        if(char_count == 4){
          current_state = LEAD_CHAR;
        }
        break;


      case FIVE_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80');
        char_count++;
        if(char_count == 5){
          current_state = LEAD_CHAR;
        }
        break;


      case SIX_CHAR:
        ASSERT_EQ(*c & '\xc0', '\x80');
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
