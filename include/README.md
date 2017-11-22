The include files within the project are split into two types: private and
public. Private headers are those that are only used within the source files for
the library and are not exposed in the installed headers.

The files in the `stumpless` directory as well as the `stumpless.h` include file
itself are installed with the project and can be used to call functions from the
library. These header files are compatible with both C and C++ compilers.
