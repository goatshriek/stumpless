#!/usr/bin/env ruby

require 'fileutils'

Dir.glob('*.hpp') do |filename|
  new_filename = File.join(ARGV[0], filename)
  FileUtils.copy_file(filename, new_filename)
end
