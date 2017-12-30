/*
 * Copyright 2017, Joel Anderson.
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

#include <regex>
#include <gtest/gtest.h>
#include "test/function/rfc5424.hpp"

void TestRFC5424Compliance(const char *syslog_msg){
  int prival, year, month, day, i=0;
  std::cmatch matches;
  std::regex rfcRegex(RFC_5424_REGEX_STRING);

  ASSERT_TRUE(std::regex_match(syslog_msg, matches, rfcRegex));

  prival = std::stoi(matches[1]);
  EXPECT_GE(prival, RFC_5424_PRIVAL_MIN);
  EXPECT_LE(prival, RFC_5424_PRIVAL_MAX);
 
  EXPECT_EQ(matches[2], "1");

  year = std::stoi(matches[RFC_5424_DATE_FULLYEAR_MATCH_INDEX]);
  ASSERT_GE(year, 0);

  month = std::stoi(matches[RFC_5424_DATE_MONTH_MATCH_INDEX]);
  day = std::stoi(matches[RFC_5424_DATE_MDAY_MATCH_INDEX]);
  EXPECT_GE(day, 1);
  switch(month){
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
    case 11:
      EXPECT_LE(day, 31);
      break;
    case 4:
    case 6:
    case 8:
    case 10:
    case 12:
      EXPECT_LE(day, 30);
      break;
    case 2:
      if(month % 4 == 0){
        EXPECT_LE(day, 29);
      } else {
        EXPECT_LE(day, 28);
      }
      break;
    default:
      FAIL() << "DATE-MONTH was not a value between 1 and 12";
  }
  
  for(auto m=matches.begin(); m != matches.end(); ++m){
    std::cout << "match " << i++ << ": " << *m << "\n";
  }
}
