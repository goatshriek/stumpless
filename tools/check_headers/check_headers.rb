#!/usr/bin/env ruby

# as it is, this script makes several assumptions about the structure of the
# source code that it is analyzing, where certain files are, and more:
#  - ruby 2.0 is required due to use of the __dir__ variable
#  - any line containing '/*' starts a comment
#  - any line containing '*/' ends a comment
#  - include statements are on their own lines
#  - the manifest files are in the same directory as this script
#  - for terms that may exist in more than one header, only one of those headers
#    will be included

require 'yaml'

known_terms = Hash.new

default_manifests = ["c_standard_library.yml", "cpp_standard_library.yml", "gtest.yml", "stumpless.yml"]
default_manifests.each do |filename|
  file_path = File.join(__dir__, filename)
  manifest_terms = YAML.load_file file_path
  known_terms.merge! manifest_terms
end

return_code = 0

ARGV.each do |source_glob|
  included_files = Array.new
  used_includes = Array.new
  used_terms = Array.new
  skipping = false

  Dir.glob(source_glob) do |source_filename|
    File.open(source_filename).each do |line|
      # we don't immediately start skipping lines in case this is a one-line comment
      if line.include? '/*'
        skipping = true
      end
  
      if line.include? '*/'
        skipping = false
        next
      end
  
      if skipping or line.match?(/\s*\\\\.*/)
        # skip if skippint or only a single-line comment
        next
      end
  
      if m = line.match(/#\s*include\s*["<](.*)[">]/)
        included_files << m[1]
        next # don't parse include filepaths for terms
      end
  
      line.split(/\W/).each do |word|
        if known_terms.has_key?(word)
          used_terms << word
        end
      end
    end
  
    included_files.uniq!
   
    used_terms.uniq.each do |term|
      requirement = known_terms[term]
    
      if requirement.is_a? Array
        met_requirements = requirement & included_files
        if met_requirements.empty?
          puts "#{source_filename}: use of '#{term}' requires inclusion of at least one of #{requirement.join(', ')}"
          return_code = 1
        else
          used_includes.concat met_requirements
        end
      else
        unless included_files.include? requirement
          puts "#{source_filename}: use of '#{term}' requires inclusion of '#{requirement}'"
          return_code = 1
        else
          used_includes << requirement
        end
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
