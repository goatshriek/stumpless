#!/usr/bin/env ruby

# frozen_string_literal: true

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

# Adds a new localized string to all locale headers. Each new string is marked
# as needing translation. Expects the name of the new string (without the
# `L10N_` prefix) as the first argument, with all others being joined together
# with spaces to make the english value of the string.

if ARGV.length < 2
  puts 'usage: add_l10n_string.rb NAME_OF_STRING english [string words ...]'
  exit 1
end

define_name = 'L10N_' + ARGV[0]
english_str = ARGV.drop(1)

english_lines = ["\"#{english_str}\""]

# 80 characters minus the two quotes
if english_str.length > 78
  english_lines = []
  current_line = String.new

  english_str.split(' ').each do |word|
    if current_line.length + word.length > 77
      english_lines << "\"#{current_line}\" \\"
      current_line = String.new
    end

    current_line << " #{word}"
  end

  english_lines << "\"#{current_line}\""
end

root_dir = File.expand_path('..', __dir__)
locale_dir = File.join(root_dir, 'include', 'private', 'config', 'locale')
Dir.new(locale_dir).reject { |file| %w[wrapper.h . ..].include?(file) }.each do |file|
  new_lines = []

  File.open(file, 'r').each do |line|
    define_match = line.match(/#\s*define\s*L10N_(\w*)(\s|\()/)
    if define_match
      define_name = define_match[1]
      
    else
      
    end
  end
end
