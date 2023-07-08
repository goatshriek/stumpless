#!/usr/bin/env ruby

# frozen_string_literal: true

# Copyright 2022-2023 Joel E. Anderson
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
#   - l10n strings marked as needing translation (via a preceding comment of
#     "// todo translate") have the english translation as their value. This
#     is only done if the english locale file is one of those checked.

errors = []
header_defines = {}
defaults_header = 'en-us.h'
defaults = nil
todo = false
todo_list = []

ARGV.each do |source_glob|
  Dir.glob(source_glob) do |source_filename|
    file_defines = {}
    last_l10n = ''
    current_l10n = nil
    str = String.new

    File.open(source_filename).each do |line|
      if line.rstrip.length > 80
        errors << "#{source_filename}: line `#{line}` is longer than 80 characters"
      end

      todo = true if line.rstrip.end_with?('// todo translate')

      str_match = line.match(/^L?((("(.*)")|\w+| )+)( \\)?/)
      if current_l10n && str_match
        str << str_match[1]

        unless line.rstrip.end_with?('\\')
          if (last_l10n <=> current_l10n) > 0
            errors << "#{source_filename}: #{current_l10n} not defined in alphabetic order"
          end

          todo_list << [source_filename, current_l10n] if todo

          file_defines[current_l10n] = str
          last_l10n = current_l10n
          current_l10n = nil
          str = String.new
          todo = false
        end
      end

      define_match = line.match(/#\s*define\s*L10N_(\w+)( |\()/)
      current_l10n = define_match[1] if define_match
    end

    header_defines[source_filename] = file_defines
    defaults = file_defines if source_filename.end_with?(defaults_header)
  end
end

header_defines.each_pair do |filename, file_defines|
  if file_defines.keys.sort != defaults.keys.sort
    missing_keys = file_defines.keys - defaults.keys
    unless missing_keys.empty?
      errors << "#{filename}: missing strings defined in #{defaults_header}: #{missing_keys}"
    end

    extra_keys = defaults.keys - file_defines.keys
    unless extra_keys.empty?
      errors << "#{filename}: extra strings defined in #{defaults_header}: #{extra_keys}"
    end
  end
end

todo_list.each do |todo_tuple|
  filename, define = *todo_tuple
  if header_defines[filename][define] != defaults[define]
    errors << "#{filename}: untranslated string #{define} not set to default value `#{defaults[define]}`"
  end
end

if errors.empty?
  exit 0
else
  puts "#{errors.size} errors found"
  errors.each { |err| puts err }
  exit errors.size
end
