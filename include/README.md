The include files within the project are split into two types: private and
public. Private headers are those that are only used within the source files for
the library and are not exposed in the installed headers. These headers are
contained in the `private` folder.

The files in the `stumpless` directory as well as the `stumpless.h` include file
itself are installed with the project and can be used to call functions from the
library. These header files are compatible with both C and C++ compilers.

Some headers are only used by tests for the project. These headers are kept in
the `test` subdirectory of the include directory.
