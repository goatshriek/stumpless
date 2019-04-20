# Check Headers Tool

This tool provides a way to perform some basic checks against C/C++ source and
header file include statements. Its primary use case is to make sure that the
files have these two properties:

 * all necessary headers are included, without relying on header files to
   include other files themselves
 * there are no headers included that are not needed

These properties are meant to keep compile times manageable while avoiding
potentially complicated header interdependencies.

The tool uses manifest files to determine what headers are needed for various
terms. For example, the `c_standard_library.yml` manifest file lists the terms
that may be used from the C and C++ standard libraries, and what headers are
needed for each of them. For example, the ever-popular `NULL` term is defined
in `stddef.h`, and so this tool will check for that include in any source file
that contains it.

There are several subtle details and limitations of this tool, as it does not
implement language parsing and is meant to be as simple as possible. To see a
list of assumptions and quirks, look at the `check_headers.rb` script itself.
