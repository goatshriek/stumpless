module Wrapture

  def self.normalize_spec(spec)

    normalized_spec = Hash.new
    normalized_spec['classes'] = Array.new

    spec['classes'].each do |class_spec|
      normalized_spec['classes'] << ClassSpec.normalize_spec(class_spec)
    end

    return normalized_spec

  end

end
