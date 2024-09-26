// SPDX-License-Identifier: Apache-2.0

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

#include <benchmark/benchmark.h>
#include <string>
#include <cstdlib>
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( prival_from_string )
NEW_MEMORY_COUNTER( get_prival_string )

static void PrivalFromString(benchmark::State& state) {
  // Create a list of priorities.
  std::vector<std::string> priority_list = { "191",
                                             "user.emerg",
                                             "uucp.err",
                                             "local7.debug" };

  INIT_MEMORY_COUNTER( prival_from_string );

  // Measure the time it takes to call the function.
  for (auto _ : state) {
    for (const auto& priority : priority_list) {
      int result = stumpless_prival_from_string(priority.c_str());
      if ( result< 0) {
        state.SkipWithError("could not get the prival from the string");
      }
    }
  }
  SET_STATE_COUNTERS( state, prival_from_string );
}

static void GetPrivalString(benchmark::State& state) {
  std::vector<int> prival_list =
      { STUMPLESS_SEVERITY_ALERT | STUMPLESS_FACILITY_USER,
        STUMPLESS_SEVERITY_CRIT | STUMPLESS_FACILITY_MAIL, 
        STUMPLESS_SEVERITY_ERR | STUMPLESS_FACILITY_AUTH2,
        STUMPLESS_SEVERITY_WARNING | STUMPLESS_FACILITY_FTP,
        STUMPLESS_SEVERITY_NOTICE | STUMPLESS_FACILITY_NTP };

  const char *result;
  INIT_MEMORY_COUNTER( get_prival_string );

  for (auto _ : state) {
    for (auto prival: prival_list ) {
      result = stumpless_get_prival_string( prival );
      free( ( void * ) result );
    }
  }
  SET_STATE_COUNTERS( state, get_prival_string );
}

BENCHMARK(PrivalFromString);
BENCHMARK(GetPrivalString);
