#!/usr/bin/env ruby

# as it is, this script makes several assumptions about the structure of the
# source code that it is analyzing, as well as where certain files are:
#  - ruby 2.0 is required due to use of the __dir__ variable
#  - any line containing '/*' starts a comment
#  - any line containing '*/' ends a comment

require 'yaml'

known_terms = Hash.new

default_manifests = ["c_standard_library.yml", "stumpless.yml"]
default_manifests.each do |filename|
  file_path = File.join(__dir__, filename)
  manifest_terms = YAML.load_file file_path
  known_terms.merge! manifest_terms
end

included_files = Array.new
used_terms = Array.new
skipping = false
ARGV.each do |source_filename|
  File.open(source_filename).each do |line|
    if line.include? '*/'
      skipping = false
      next
    end

    if skipping
      next
    end

    if line.include? '/*'
      skipping = true
      next
    end

    if line.strip.empty?
      next
    end

    line.match(/#\s*include\s*["<](.*)[">]/) do |include_match|
      included_files << include_match[1]
    end

    line.split(/\W/).each do |word|
      if known_terms.has_key?(word)
        used_terms << word
      end
    end
  end
end

included_files.uniq!

used_terms.uniq.each do |term|
  requirement = known_terms[term]

  if requirement.is_a? Array
    met_requirements = requirement & included_files
    if met_requirements.empty?
      puts "use of '#{term}' requires inclusion of at least one of #{requirement.join(', ')}"
    end
  else
    unless included_files.include? requirement
      puts "use of '#{term}' requires inclusion of '#{requirement}'"
    end
  end

  if requirement.is_a? Array
  end

end
