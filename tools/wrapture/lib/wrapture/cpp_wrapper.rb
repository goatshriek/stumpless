module CppWrapper
  def wrap_class(class_description)
    output_filename = class_description["name"] + ".cpp"

    cpp_templates = YAML::load_file("/home/angel/code/stumpless/tools/wrapture/data/cpp.yml")

    # open file

    # build parameter

    # build function

    # build class

    # print to file

    # close file
  end
end
