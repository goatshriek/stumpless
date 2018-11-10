# Building Stumpless

In order to compile Stumpless you will need cmake and a compatible build system
such as the GNU toolchain or Microsoft Visual Studio. Given these dependencies
building the library is very straightforward. The examples below show how to do
this in a build environment with `make`:

    mkdir build
    cd build
    cmake ..
    make all

Other environments should be built according to their normal style. For example
Visual Studio provides a CMake menu that will display all available targets.

## Verifying your Build

If you want to run the test suite on the library before installation, you can
use the `check` target to run all tests and display the results. If you're
concerned that the build may not work on your architecture, then this is the
best way to verify:

    make check

If you're curious about how the library will perform on your system, use the
`bench` target to run the performance benchmarks:

    make bench

## Installing

You can use the install target to install the library on your machine after the
build.

    make install

There is not currently an uninstall target supported, so removal of the library
and its include files must be done manually if it is no longer needed.
