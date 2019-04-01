Gem::Specification.new do |s|
  s.name        =  'wrapture'
  s.version     =  '0.1.0'
  s.date        =  '2019-04-01'
  s.summary     =  'wrap C in C++'
  s.description =  'Wraps C code in C++.'
  s.authors     =  ['Joel Anderson']
  s.email       =  'joelanderson333@gmail.com'
  s.files       =  ['lib/wrapture.rb', 'lib/wrapture/cpp_wrapper.rb', 'lib/wrapture/wrapper.rb']
  s.executables << 'wrapture'
  s.homepage    =  'http://rubygems.org/gems/wrapture'
  s.license     =  'Apache-2.0'
end
