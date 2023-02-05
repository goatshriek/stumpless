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

#include <regex>
#include <stdlib.h>
#include <string>
#include <gtest/gtest.h>
#include "test/helper/rfc5424.hpp"
#include "test/helper/utf8.hpp"

void TestRFC5424Compliance(const char *syslog_msg){
  std::cmatch matches;
  std::regex rfcRegex(RFC_5424_REGEX_STRING);
  if( !std::regex_match(syslog_msg, matches, rfcRegex) ) {
    FAIL(  ) << "message does not match RFC 5424 regex: " << syslog_msg;
  }

  int prival = std::stoi(matches[RFC_5424_PRIVAL_MATCH_INDEX]);
  EXPECT_GE(prival, RFC_5424_PRIVAL_MIN);
  EXPECT_LE(prival, RFC_5424_PRIVAL_MAX);
 
  EXPECT_EQ(matches[2], "1");

  int year = std::stoi(matches[RFC_5424_DATE_FULLYEAR_MATCH_INDEX]);
  EXPECT_GE(year, 0);

  int month = std::stoi(matches[RFC_5424_DATE_MONTH_MATCH_INDEX]);
  int day = std::stoi(matches[RFC_5424_DATE_MDAY_MATCH_INDEX]);
  EXPECT_GE(day, 1);
  switch(month){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      EXPECT_LE(day, 31);
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      EXPECT_LE(day, 30);
      break;
    case 2:
      if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        EXPECT_LE(day, 29);
      } else {
        EXPECT_LE(day, 28);
      }
      break;
    default:
      ADD_FAILURE() << "DATE-MONTH was not a value between 1 and 12";
  }

  TestRFC5424StructuredData(matches.str(RFC_5424_STRUCTURED_DATA_MATCH_INDEX).c_str());
 
  std::string msg_string = matches.str(RFC_5424_MSG_MATCH_INDEX);
  char *msg = (char *)malloc(msg_string.length() + 1);
  msg_string.copy( msg, msg_string.length() );
  msg[msg_string.length()] = '\0';
  if(msg[0] == '\xef' && msg[1] == '\xbb' && msg[2] == '\xbf'){
    TestUTF8Compliance(msg);
  }
  free(msg);
}

void TestRFC5424StructuredData(const char *structured_data){
  enum sd_state {
    INIT_STATE,
    SD_ELEMENT_EMPTY,
    SD_ELEMENT_BEGIN,
    SD_ID_NAME,
    SD_ID_ENTERPRISE_NUMBER,
    SD_PARAM_NAME,
    SD_PARAM_VALUE_BEGIN,
    SD_PARAM_VALUE,
    SD_PARAM_VALUE_END
  };
  enum sd_state current_state = INIT_STATE;
  bool backslash_preceded = false;
  std::string paramValue;

  for(const char *c=structured_data; *c != '\0'; c++){
    switch(current_state){
      case INIT_STATE:
        if(*c == '-'){
          current_state = SD_ELEMENT_EMPTY;
        } else if( *c == '['){
          current_state = SD_ID_NAME;
        }
        break;

      case SD_ELEMENT_EMPTY:
        FAIL() << "an empty STRUCTURED-DATA had more than a '-' character";
        break;

      case SD_ELEMENT_BEGIN:
        ASSERT_EQ(*c, '[');
        current_state = SD_ID_NAME;
        break;

      // todo validate with RFC
      case SD_ID_NAME:
        if(*c == '@'){
          current_state = SD_ID_ENTERPRISE_NUMBER;
          break;
        }
        if(*c == ']'){
          current_state = SD_ELEMENT_BEGIN;
          break;
        }
        if(*c == ' '){
          current_state = SD_PARAM_NAME;
          break;
        }
        ASSERT_GT(*c, 32);
        ASSERT_LT(*c, 127);
        ASSERT_NE(*c, '=');
        ASSERT_NE(*c, '"');
        break;

      // todo validate with registry
      case SD_ID_ENTERPRISE_NUMBER:
        if(*c == ']'){
          current_state = SD_ELEMENT_BEGIN;
          break;
        }
        if(*c == ' '){
          current_state = SD_PARAM_NAME;
          break;
        }
        ASSERT_GE(*c, '0');
        ASSERT_LE(*c, '9');
        break;

      case SD_PARAM_NAME:
        if(*c == '='){
          current_state = SD_PARAM_VALUE_BEGIN;
          break;
        }
        ASSERT_GT(*c, 32);
        ASSERT_LT(*c, 127);
        ASSERT_NE(*c, ' ');
        ASSERT_NE(*c, ']');
        ASSERT_NE(*c, '"');
        break;

      case SD_PARAM_VALUE_BEGIN:
        ASSERT_EQ(*c, '"');
        current_state = SD_PARAM_VALUE;
        paramValue = std::string();
        break;

      case SD_PARAM_VALUE:
        paramValue.push_back(*c);
        if(backslash_preceded){
          backslash_preceded = false;
          break;
        } else {
          if(*c == '"'){
            current_state = SD_PARAM_VALUE_END;
            break;
          }
          ASSERT_NE(*c, '=');
          ASSERT_NE(*c, ']');
        }

        if(*c == '\\'){
          backslash_preceded = true;
        }
        break;

      case SD_PARAM_VALUE_END:
        TestUTF8Compliance(paramValue.c_str());
        if(*c == ' '){
          current_state = SD_PARAM_NAME;
          break;
        }
        if(*c == ']'){
          current_state = SD_ELEMENT_BEGIN;
          break;
        }
        FAIL() << "invalid ending of PARAM-VALUE";
        break;

      default:
        FAIL() << "invalid state reached during SD-ELEMENT parsing";
    }
  }
}
