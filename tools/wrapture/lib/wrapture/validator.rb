module Wrapture

  def self.normalize_spec(spec)
    return self.normalize_spec( spec.dup )
  end

  def self.normalize_spec!(spec)

    spec['classes'].each do |class_spec|

      if class_spec['equivalent-struct']['members'].nil?
        class_spec['equivalent-struct']['members'] = Array::new
      end

      if class_spec['functions'].nil?
        class_spec['functions'] = Array::new
      else
        class_spec['functions'].each do |function_spec|
          if function_spec['wrapped_function']['params'].nil?
            function_spec['wrapped_function']['params'] = Array::new
          end

          if function_spec['return']['includes'].nil?
            function_spec['return']['includes'] = Array::new
          end
        end
      end

      if class_spec['constants'].nil?
        class_spec['constants'] = Array::new
      else
        class_spec['constants'].each do |constant_spec|
          if constant_spec['includes'].nil?
            constant_spec['includes'] = Array::new
          end
        end
      end

    end

    return spec

  end

end
