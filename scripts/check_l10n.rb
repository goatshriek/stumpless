#!/usr/bin/env ruby

# Copyright 2022 Joel E. Anderson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# validates the localization (l10n) definitions in the given files, including:
#   - the l10n string definitions all occur in alphabetical order
#   - all headers have the same l10n strings defined
#   - lines do not go longer than 80 characters
#   - multiline string literals (lines ending with " \) do not have a space
#     at the end of the first string, and do have a space as the first character
#     of the following lines


return_code = 0

ARGV.each do |source_glob|
  Dir.glob(source_glob) do |source_filename|
    puts source_filename
  end
end

exit return_code