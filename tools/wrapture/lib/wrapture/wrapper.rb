module Wrapture

  class Wrapper

    def self.wrap_class(class_spec)

      class_name = class_spec['name']
      struct_name = class_spec['equivalent-struct']['name']

      # generating constructor signatures
      unless class_spec['equivalent-struct']['members'].nil?
        members = Array.new
        class_spec['equivalent-struct']['members'].each do |member|
          members << "#{member['type']} #{member['name']}"
        end
        constructor_signature = "#{class_name}( #{members.join ', '} )"
      end

      # get the list of includes for declarations
      declaration_includes = class_spec['equivalent-struct']['includes'].dup
      unless class_spec['functions'].nil?
        class_spec['functions'].each do |function_spec|
          unless function_spec['return']['includes'].nil?
            declaration_includes.concat function_spec['return']['includes']
          end
        end
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
        file.puts "    struct #{struct_name} equivalent;"

        file.puts

        file.puts "  public:"
        file.puts "    #{constructor_signature};"
        file.puts "    #{class_name}( struct #{struct_name} equivalent );"
        file.puts "    #{class_name}( const struct #{struct_name} *equivalent );"

        unless class_spec['equivalent-struct']['members'].nil?
          class_spec['equivalent-struct']['members'].each do |member|
            file.puts "    #{member['type']} Get#{member['name'].capitalize}( void ) const;"
            file.puts "    void Set#{member['name'].capitalize}( #{member['type']} #{member['name']} );"
          end
        end

        unless class_spec['functions'].nil?
          class_spec['functions'].each do |function_spec|
            static_modifier = if function_spec['static'] then 'static ' else '' end
            file.puts "    #{static_modifier}#{function_spec['return']['type']} #{function_spec['name']}( void );"
          end
        end

        file.puts

        unless class_spec['constants'].nil?
          class_spec['constants'].each do |constant_spec|
            file.puts "    static const #{constant_spec['type']} #{constant_spec['name']};"
          end
        end

        file.puts '  };' # end of class
        file.puts '}' # end of namespace
        file.puts '#endif' # end of header guard
      end
  
      # get the complete list of includes for definitions
      definition_includes = Array.new
      definition_includes << "#{class_name}.hpp"
      unless class_spec['functions'].nil?
        class_spec['functions'].each do |function_spec|
          if not function_spec['return']['includes'].nil?
            definition_includes.concat function_spec['return']['includes']
          end
          definition_includes.concat function_spec['wrapped_function']['includes']
        end
      end

      unless class_spec['constants'].nil?
        class_spec['constants'].each do |constant_spec|
          unless constant_spec['includes'].nil?
            definition_includes.concat constant_spec['includes']
          end
        end
      end
      definition_includes.uniq!

      # generate the definition file
      File.open("#{class_name}.cpp", 'w') do |file|
        definition_includes.each do |include_file|
          file.puts "#include <#{include_file}>"
        end

        file.puts
        file.puts "namespace #{class_spec['namespace']} {"
        file.puts 

        # constants
        unless class_spec['constants'].nil?
          class_spec['constants'].each do |constant_spec|
            file.puts "  const #{constant_spec['type']} #{class_name}::#{constant_spec['name']} = #{constant_spec['value']};"
          end
        end

        # the basic construtor
        unless class_spec['equivalent-struct']['members'].nil?
          file.puts "  #{class_name}::#{constructor_signature} {"
          class_spec['equivalent-struct']['members'].each do |member|
            file.puts "    this->equivalent.#{member['name']} = #{member['name']};"
          end
          file.puts '  }' # end of the constructor

          file.puts

          file.puts "  #{class_name}::#{class_name}( struct #{struct_name} equivalent ) {"
          class_spec['equivalent-struct']['members'].each do |member|
            file.puts "    this->equivalent.#{member['name']} = equivalent.#{member['name']};"
          end
          file.puts '  }' # end of struct conversion

          file.puts

          file.puts "  #{class_name}::#{class_name}( const struct #{struct_name} *equivalent ) {"
          class_spec['equivalent-struct']['members'].each do |member|
            file.puts "    this->equivalent.#{member['name']} = equivalent->#{member['name']};"
          end
          file.puts '  }' # end of pointer conversion

          class_spec['equivalent-struct']['members'].each do |member|
            file.puts # line to separate from previous functions
            file.puts "  #{member['type']} #{class_name}::Get#{member['name'].capitalize}( void ) const {"
            file.puts "    return this->equivalent.#{member['name']};"
            file.puts '  }'
            file.puts
            file.puts "  void #{class_name}::Set#{member['name'].capitalize}( #{member['type']} #{member['name']} ) {"
            file.puts "    this->equivalent.#{member['name']} = #{member['name']};"
            file.puts '  }'
          end
        end

        unless class_spec['functions'].nil?
          class_spec['functions'].each do |function_spec|
            file.puts
            file.puts "  #{function_spec['return']['type']} #{class_name}::#{function_spec['name']}( void ) {"

            # the function body
            file.write "    return #{function_spec['return']['type']}( #{function_spec['wrapped_function']['name']}( "

            # building the parameters
            unless function_spec['wrapped_function']['params'].nil?
              wrapped_params = Array.new
              function_spec['wrapped_function']['params'].each do |param|
                case param['name']
                when "equivalent-struct"
                  wrapped_params << "this->equivalent"
                when "equivalent-struct-pointer"
                  wrapped_params << "&this->equivalent"
                else
                  wrapped_params << param['name']
                end
              end
              file.write(wrapped_params.join ', ')
            end

            file.puts ' ) );'
            file.puts '  }'
          end
        end

        file.puts # line after last function
        file.puts '}' # end of namespace
      end

    end

  end

end
