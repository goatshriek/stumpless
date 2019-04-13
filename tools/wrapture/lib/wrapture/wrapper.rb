module Wrapture

  def self.wrap_class(class_spec)

    class_name = class_spec['name']
    struct_name = class_spec['equivalent-struct']['name']

    # generating constructor signatures
    constructor_signatures = Array::new
    equivalent_name = 'equivalent'
    equivalent_struct = 'this->equivalent'
    equivalent_struct_pointer = '&this->equivalent'
    member_operator = '.'

    class_spec['constructors'].each do |constructor_spec|
      if constructor_spec['wrapped-function']['return']['type'] == 'equivalent-struct-pointer'
        equivalent_name = '*equivalent'
        equivalent_struct = '*(this->equivalent)'
        equivalent_struct_pointer = 'this->equivalent'
        member_operator = '->'
      end

      params = Array::new
      constructor_spec['wrapped-function']['params'].each do |param|
        params << "#{param['type']} #{param['name']}"
      end

      constructor_signatures << "#{class_name}( #{params.join ', '} )"
    end

    members = Array.new
    class_spec['equivalent-struct']['members'].each do |member|
      members << "#{member['type']} #{member['name']}"
    end

    member_constructor_signature = "#{class_name}( #{members.join ', '} )"
    struct_constructor_signature = "#{class_name}( struct #{struct_name} equivalent )"
    pointer_constructor_signature = "#{class_name}( const struct #{struct_name} *equivalent )"

    # get the list of includes for declarations
    declaration_includes = class_spec['equivalent-struct']['includes'].dup
    class_spec['functions'].each do |function_spec|
      declaration_includes.concat function_spec['return']['includes']
    end
    declaration_includes.uniq!

    # generate the header file
    File.open("#{class_name}.hpp", 'w') do |file|
      # header guard
      file.puts "#ifndef __#{class_name.upcase}_HPP"
      file.puts "#define __#{class_name.upcase}_HPP"

      file.puts

      declaration_includes.each do |include_file|
        file.puts "#include <#{include_file}>"
      end

      file.puts

      file.puts "namespace #{class_spec['namespace']} {"
      file.puts "  class #{class_name} {"
      file.puts "  private:"
      file.puts "    struct #{struct_name} #{equivalent_name};"

      file.puts

      file.puts "  public:"
      constructor_signatures.each do |signature|
        file.puts "    #{signature};"
      end

      file.puts "    #{member_constructor_signature};"
      file.puts "    #{struct_constructor_signature};"
      file.puts "    #{pointer_constructor_signature};"

      class_spec['equivalent-struct']['members'].each do |member|
        file.puts "    #{member['type']} Get#{member['name'].capitalize}( void ) const;"
        file.puts "    void Set#{member['name'].capitalize}( #{member['type']} #{member['name']} );"
      end

      class_spec['functions'].each do |function_spec|
        static_modifier = if function_spec['static'] then 'static ' else '' end
        file.puts "    #{static_modifier}#{function_spec['return']['type']} #{function_spec['name']}( void );"
      end

      file.puts

      class_spec['constants'].each do |constant_spec|
        file.puts "    static const #{constant_spec['type']} #{constant_spec['name']};"
      end

      file.puts '  };' # end of class
      file.puts '}' # end of namespace
      file.puts '#endif' # end of header guard
    end

    # get the complete list of includes for definitions
    definition_includes = Array.new
    definition_includes << "#{class_name}.hpp"
    class_spec['functions'].each do |function_spec|
      definition_includes.concat function_spec['return']['includes']
      definition_includes.concat function_spec['wrapped_function']['includes']
    end

    class_spec['constants'].each do |constant_spec|
      definition_includes.concat constant_spec['includes']
    end
    definition_includes.uniq!

    # generate the definition file
    File.open("#{class_name}.cpp", 'w') do |file|
      definition_includes.each do |include_file|
        file.puts "#include <#{include_file}>"
      end

      file.puts
      file.puts "namespace #{class_spec['namespace']} {"

      # constants
      class_spec['constants'].each do |constant_spec|
        file.puts
        file.puts "  const #{constant_spec['type']} #{class_name}::#{constant_spec['name']} = #{constant_spec['value']};"
      end

      # construtors

      class_spec['constructors'].each_index do |i|
        wrapped_function = class_spec['constructors'][i]['wrapped-function']
        function_params = Array::new
        wrapped_function['params'].each do |param|
          function_params << param['name']
        end

        file.puts
        file.puts "  #{class_name}::#{constructor_signatures[i]} {"
        file.puts "    #{wrapped_function['name']}( #{function_params.join ', '} );"
        file.puts '  }'
      end

      file.puts

      file.puts "  #{class_name}::#{member_constructor_signature} {"
      class_spec['equivalent-struct']['members'].each do |member|
        file.puts "    this->equivalent#{member_operator}#{member['name']} = #{member['name']};"
      end
      file.puts '  }' # end of the constructor

      file.puts

      file.puts "  #{class_name}::#{struct_constructor_signature} {"
      class_spec['equivalent-struct']['members'].each do |member|
        file.puts "    this->equivalent#{member_operator}#{member['name']} = equivalent.#{member['name']};"
      end
      file.puts '  }' # end of struct conversion

      file.puts

      file.puts "  #{class_name}::#{pointer_constructor_signature} {"
      class_spec['equivalent-struct']['members'].each do |member|
        file.puts "    this->equivalent#{member_operator}#{member['name']} = equivalent->#{member['name']};"
      end
      file.puts '  }' # end of pointer conversion

      class_spec['equivalent-struct']['members'].each do |member|
        file.puts # line to separate from previous functions
        file.puts "  #{member['type']} #{class_name}::Get#{member['name'].capitalize}( void ) const {"
        file.puts "    return this->equivalent#{member_operator}#{member['name']};"
        file.puts '  }'
        file.puts
        file.puts "  void #{class_name}::Set#{member['name'].capitalize}( #{member['type']} #{member['name']} ) {"
        file.puts "    this->equivalent#{member_operator}#{member['name']} = #{member['name']};"
        file.puts '  }'
      end

      class_spec['functions'].each do |function_spec|
        file.puts
        file.puts "  #{function_spec['return']['type']} #{class_name}::#{function_spec['name']}( void ) {"

        # the function body
        file.write "    return #{function_spec['return']['type']}( #{function_spec['wrapped_function']['name']}( "

        # building the parameters
        wrapped_params = Array.new
        function_spec['wrapped_function']['params'].each do |param|
          case param['name']
          when "equivalent-struct"
            wrapped_params << equivalent_struct
          when "equivalent-struct-pointer"
            wrapped_params << equivalent_struct_pointer
          else
            wrapped_params << param['name']
          end
        end
        file.write(wrapped_params.join ', ')

        file.puts ' ) );'
        file.puts '  }'
      end

      file.puts # line after last function
      file.puts '}' # end of namespace
    end

  end

end
