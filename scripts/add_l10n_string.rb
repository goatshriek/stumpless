#!/usr/bin/env ruby

# frozen_string_literal: true

# Copyright 2022-2024 Joel E. Anderson
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

# building the string literal
english_str = ARGV.drop(1).join(' ')
english_lines = ["\"#{english_str}\"\n"]
if english_str.length > 78 # 80 characters minus the two quotes
  english_lines = []
  current_line = String.new

  english_str.split(' ').each do |word|
    if current_line.length + word.length > 77
      english_lines << "\"#{current_line}\" \\\n"
      current_line = String.new
    end

    current_line << " #{word}"
  end

  english_lines << "\"#{current_line}\""
end
define_lines = ["#  define #{define_name} \\\n", english_lines].flatten

root_dir = File.expand_path('..', __dir__)
locale_dir = File.join(root_dir, 'include', 'private', 'config', 'locale')
Dir.new(locale_dir).each_child do |file|
  new_file_lines = []
  line_buffer = []
  inserted = false

  absolute_file = File.join(locale_dir, file)
  File.open(absolute_file, 'r').each do |line|
    line_buffer << line

    if line.strip.empty?
      new_file_lines.concat(line_buffer)
      line_buffer = []
    end

    unless inserted
      define_match = line.match(/#\s*define\s*(L10N_\w*)(\s|\()/)
      if define_match
        matched_define = define_match[1]
        if matched_define > define_name
          new_file_lines << "// todo translate\n" unless file == "en-us.h"
          new_file_lines.concat(define_lines)
          new_file_lines << "\n"
          inserted = true
        end
      end

      end_match = line.match(/\s*#\s*endif/)
      if end_match && !inserted
        new_file_lines << "// todo translate\n" unless file == "en-us.h"
        new_file_lines.concat(define_lines)
        new_file_lines << "\n"
        inserted = true
      end
    end
  end
  new_file_lines.concat(line_buffer)

  new_file = File.new(absolute_file, 'w')
  new_file_lines.each { |line| new_file.write(line) }
  new_file.close
end
