# Building Stumpless

In order to compile Stumpless you will need cmake and a compatible build system
such as the GNU toolchain or Microsoft Visual Studio. Given these dependencies
building the library is very straightforward. The examples below show how to do
this in a build environment with `make`:

    mkdir build
    cd build
    cmake ..
    make all

Other environments should be built according to their normal style, for example
Visual Studio provides a CMake menu that will display all available targets.

If you want to run the test suite on the library before installing it, you can
use the `check` target to run all tests and display the results. If you're
concerned that the build may not work on your architecture, then this is the
best way to verify.

    make check

# Installing the Library

You can use the install target to install the library on your machine after the
build.

    make install
