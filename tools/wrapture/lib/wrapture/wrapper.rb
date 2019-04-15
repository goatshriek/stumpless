module Wrapture

  def self.wrap_class( class_spec )

    spec = ClassSpec.new class_spec
    spec.generate_wrappers

    class_name = class_spec['name']
    struct_name = class_spec['equivalent-struct']['name']

    # generating constructor signatures
    constructor_signatures = Array.new
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

      params = Array.new
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

      file.puts unless declaration_includes.empty?

      file.puts "namespace #{class_spec['namespace']} {"
      file.puts "  class #{class_name} {"
      file.puts '  public:'

      class_spec['constants'].each do |constant_spec|
        file.puts "    static const #{constant_spec['type']} #{constant_spec['name']};"
      end
      file.puts unless class_spec['constants'].empty?

      file.puts "    struct #{struct_name} #{equivalent_name};"
      file.puts

      constructor_signatures.each do |signature|
        file.puts "    #{signature};"
      end

      unless members.empty?
        file.puts "    #{member_constructor_signature};"
      end

      file.puts "    #{struct_constructor_signature};"
      file.puts "    #{pointer_constructor_signature};"

      class_spec['equivalent-struct']['members'].each do |member|
        file.puts "    #{member['type']} Get#{member['name'].capitalize}( void ) const;"
        file.puts "    void Set#{member['name'].capitalize}( #{member['type']} #{member['name']} );"
      end

      class_spec['functions'].each do |function_spec|
        static_modifier = if function_spec['static'] then 'static ' else '' end
        file.write "    #{static_modifier}#{function_spec['return']['type']} #{function_spec['name']}( "

        wrapped_params = Array.new
        function_spec['params'].each do |param|
          wrapped_params << "#{param['type']} #{param['name']}"
        end
        file.write(wrapped_params.join ', ')

        file.puts ' );'
      end

      # destructor
      unless class_spec['destructor'].nil?
        file.puts "    ~#{class_name}( void );"
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
      definition_includes.concat function_spec['wrapped-function']['includes']
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

      # constructors
      class_spec['constructors'].each_index do |i|
        wrapped_function = class_spec['constructors'][i]['wrapped-function']
        function_params = Array.new
        wrapped_function['params'].each do |param|
          function_params << param['name']
        end

        file.puts
        file.puts "  #{class_name}::#{constructor_signatures[i]} {"
        file.write('    ')
        case wrapped_function['return']['type']
        when 'equivalent-struct'
          file.write(equivalent_struct)
        when 'equivalent-struct-pointer'
          file.write(equivalent_struct_pointer)
        end
        file.puts " = #{wrapped_function['name']}( #{function_params.join ', '} );"
        file.puts '  }'
      end

      unless members.empty?
        file.puts
        file.puts "  #{class_name}::#{member_constructor_signature} {"
        class_spec['equivalent-struct']['members'].each do |member|
          file.puts "    this->equivalent#{member_operator}#{member['name']} = #{member['name']};"
        end
        file.puts '  }' # end of the member constructor
      end

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
        file.write "  #{function_spec['return']['type']} #{class_name}::#{function_spec['name']}( "

        wrapped_params = Array.new
        function_spec['params'].each do |param|
          wrapped_params << "#{param['type']} #{param['name']}"
        end
        file.write(wrapped_params.join ', ')

        file.puts ' ) {'

        # the function body
        if function_spec['return']['type'] == 'void'
          file.write "    #{function_spec['wrapped-function']['name']}( "
        else
          file.write "    return #{function_spec['return']['type']}( #{function_spec['wrapped-function']['name']}( "
        end

        # building the parameters
        wrapped_params = Array.new
        function_spec['wrapped-function']['params'].each do |param|
          case param['name']
          when 'equivalent-struct'
            wrapped_params << equivalent_struct
          when 'equivalent-struct-pointer'
            wrapped_params << equivalent_struct_pointer
          else
            wrapped_params << param['name']
          end
        end
        file.write(wrapped_params.join ', ')

        if function_spec['return']['type'] == 'void'
          file.puts ' );'
        else
          file.puts ' ) );'
        end
        file.puts '  }'
      end

      # destructor
      unless class_spec['destructor'].nil?
        file.puts
        file.puts "  #{class_name}::~#{class_name}( void ) {"
        file.write("    #{class_spec['destructor']['wrapped-function']['name']}( ")
        wrapped_params = Array.new
        class_spec['destructor']['wrapped-function']['params'].each do |param|
          case param['name']
          when 'equivalent-struct'
            wrapped_params << equivalent_struct
          when 'equivalent-struct-pointer'
            wrapped_params << equivalent_struct_pointer
          else
            wrapped_params << param['name']
          end
        end
        file.write(wrapped_params.join ', ')
        file.puts ' );'
        file.puts '  }'
      end

      file.puts # line after last function
      file.puts '}' # end of namespace
    end

  end

end
