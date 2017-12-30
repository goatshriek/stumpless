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
  int prival, i=0;
  std::cmatch matches;
  std::regex rfcRegex(RFC_5424_REGEX_STRING);

  ASSERT_TRUE(std::regex_match(syslog_msg, matches, rfcRegex));

  prival = std::stoi(matches[1]);
  EXPECT_GE(prival, 0);
  EXPECT_LE(prival, 191);
  
  for(auto m=matches.begin(); m != matches.end(); ++m){
    std::cout << "match " << i++ << ": " << *m << "\n";
  }
}
