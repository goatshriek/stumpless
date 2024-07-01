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
#include <stumpless.h>
#include "test/helper/memory_counter.hpp"

NEW_MEMORY_COUNTER( prival_from_string )

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

BENCHMARK(PrivalFromString);
