#!/usr/bin/env ruby

# Copyright 2019-2023 Joel E. Anderson
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

# as it is, this script makes several assumptions about the structure of the
# source code that it is analyzing, where certain files are, and more:
#  - ruby 2.0 is required due to use of the __dir__ variable
#  - any line containing '/*' starts a comment
#  - any line containing '*/' ends a comment
#  - include statements are on their own lines
#  - terms do not contain spaces, unless they are prefixed with 'struct ' or
#    'enum '
#  - string literals do not have escaped double quotes
#  - the manifest files are in the same directory as this script
#  - for terms that may exist in more than one header, only one of those headers
#    will be included

require 'yaml'

# script globals
$header_alternates = {}
$deprecated_terms = []

def load_manifest(filename, term_hash)
  file_path = File.join(__dir__, filename)
  manifest_terms = YAML.load_file(file_path)

  if manifest_terms.key?('header-alternates')
    $header_alternates.merge!(manifest_terms['header-alternates'])
    manifest_terms.delete('header-alternates')
  end

  if manifest_terms.key?('deprecated-terms')
    $deprecated_terms.concat(manifest_terms['deprecated-terms'])
    manifest_terms.delete('deprecated-terms')
  end

  term_hash.merge!(manifest_terms)
end

common_known_terms = {}
%w[benchmark.yml standard_library.yml gtest.yml stumpless.yml
   stumpless_private.yml stumplesscpp.yml sqlite.yml].each do |filename|
  load_manifest(filename, common_known_terms)
end

c_only_terms = {}
%w[c_standard_library.yml].each do |filename|
  load_manifest(filename, c_only_terms)
end

cpp_only_terms = {}
%w[cpp_standard_library.yml].each do |filename|
  load_manifest(filename, cpp_only_terms)
end

return_code = 0

ARGV.each do |source_glob|
  Dir.glob(source_glob) do |source_filename|
    next if source_filename.match?(%r{windows_wrapper\.h})
    next if source_filename.match?(%r{stumpless\.h})
    next if source_filename.match?(%r{locale})

    file_terms = if source_filename.match?(%r{\.(h|c)$})
                   common_known_terms.merge(c_only_terms)
                 else
                   common_known_terms.merge(cpp_only_terms)
                 end

    used_includes = []
    used_terms = []
    skipping = false

    included_files = []
    source_filename.match(%r{include/(.*\.h(pp)?)}) do |this_include|
      included_files << this_include[1]
    end

    File.open(source_filename).each do |line|
      # we don't immedately skip in case this is a one-line comment
      skipping = true if line.include? '/*'

      if line.include? '*/'
        skipping = false
        next
      end

      if skipping || line.match?(/^\s*\/\/.*/)
        # skip if in skipping mode or only a single-line comment
        next
      end

      if (m = line.match(/#\s*include\s*["<](.*)[">]/))
        included_files << m[1]
        next # don't parse include filepaths for terms
      end

      line_terms = line.gsub(/"[^"]*"/, '*').split(/\W|(struct \w+)|(enum \w+)/)
      line_terms.each do |word|
        used_terms << 'L10N_' if word.start_with?('L10N_')
        used_terms << word if file_terms.key?(word)

        if $deprecated_terms.include?(word)
          puts "warning: deprecated term #{word} used in #{source_filename}"
        end
      end
    end

    included_files.uniq!

    used_terms.uniq.each do |term|
      possible_includes = [file_terms[term]]
      possible_includes.flatten!

      alternates = []
      $header_alternates.each_pair do |pattern, alternate|
        possible_includes.each do |include_file|
          alternates << alternate if include_file.match?(pattern)
        end
      end
      possible_includes.concat alternates

      actual_includes = possible_includes & included_files
      if actual_includes.empty?
        missing = if possible_includes.count > 1
                    "at least one of #{possible_includes.join(', ')}"
                  else
                    possible_includes[0]
                  end

        puts "#{source_filename}: '#{term}' requires inclusion of #{missing}"
        return_code = 1

      else
        used_includes.concat actual_includes

      end
    end

    unused_includes = included_files - used_includes
    unused_includes.each do |include_file|
      puts "#{source_filename}: unused include #{include_file}"
      return_code = 1
    end
  end
end

exit return_code
