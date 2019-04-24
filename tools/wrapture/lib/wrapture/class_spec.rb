module Wrapture
  class ClassSpec
    def initialize(spec)
      @spec = ClassSpec.normalize_spec_hash(spec)
    end

    def generate_wrappers
      generate_declaration_file
      generate_definition_file
    end

    def self.normalize_spec_hash(spec)
      normalized_spec = spec.dup

      if normalized_spec['constructors'].nil?
        normalized_spec['constructors'] = Array.new
      end

      if normalized_spec['equivalent-struct']['members'].nil?
        normalized_spec['equivalent-struct']['members'] = Array.new
      end

      if normalized_spec['functions'].nil?
        normalized_spec['functions'] = Array.new
      else
        normalized_spec['functions'].each do |function_spec|
          if function_spec['params'].nil?
            function_spec['params'] = Array.new
          end

          if function_spec['wrapped-function']['params'].nil?
            function_spec['wrapped-function']['params'] = Array.new
          end

          if function_spec['return'].nil?
            function_spec['return'] = Hash.new
            function_spec['return']['type'] = 'void'
          end

          if function_spec['return']['includes'].nil?
            function_spec['return']['includes'] = Array.new
          end
        end
      end

      if normalized_spec['constants'].nil?
        normalized_spec['constants'] = Array.new

      else
        normalized_spec['constants'].each do |constant_spec|
          if constant_spec['includes'].nil?
            constant_spec['includes'] = Array.new
          end
        end
      end

      return normalized_spec
    end

    private

    def header_guard
      "__#{@spec['name'].upcase}_HPP"
    end

    def declaration_includes
      includes = Array.new

      includes.concat @spec['equivalent-struct']['includes']

      @spec['functions'].each do |function_spec|
        includes.concat function_spec['return']['includes']
      end

      includes.uniq!
    end

    def pointer_wrapper?
      @spec['constructors'].each do |constructor_spec|
        if constructor_spec['wrapped-function']['return']['type'] == 'equivalent-struct-pointer'
          return true
        end
      end

      return false
    end

    def equivalent_name
      if pointer_wrapper?
        '*equivalent'
      else
        'equivalent'
    end

    def generate_declaration_file
      file = File.open("#{@spec['name']}.hpp", 'w')

      file.puts "#ifndef #{header_guard}"
      file.puts "#define #{header_guard}"

      file.puts unless declaration_includes.empty?
      declaration_includes.each do |include_file|
        file.puts "#include <#{include_file}"
      end

      file.puts "namespace #{@spec['namespace']} {"
      file.puts "  class #{@spec['name']} {"
      file.puts '  public:'

      file.puts unless @spec['constants'].empty?
      @spec['constants'].each do |constant_spec|
        file.puts "    static sont #{constant['type']} #{constant['name']}"
      end

      file.puts
      file.puts "    struct #{@spec['equivalent-struct']['name']} #{equivalent_name}"

      file.puts '  };' # end of class
      file.puts '}' # end of namespace

      file.close
    end

    def generate_definition_file
    end
  end
end
