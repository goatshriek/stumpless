# Building Stumpless

In order to compile Stumpless you will need cmake and a compatible build system
such as the GNU toolchain or Microsoft Visual Studio. Given these dependencies
building the library is very straightforward. The examples below show how to do
this in a build environment using `make` from the root folder.

```sh
# cloning the latest version of the source tree
git clone git@github.com:goatshriek/stumpless.git

# creating a new build directory
mkdir build
cd build

# configuring the new build
cmake ../stumpless

# building the library itself
make all
```

Other environments should be built according to their normal style. For example
Visual Studio provides a CMake menu that will display all available targets.

## Verifying your Build

If you want to run the test suite on the library during development or as a
sanity check before installation, you can use the `check` target to run all
tests and display the results. If you're concerned that the build may not work
on your architecture, then this is the best way to verify.

```sh
make check
```

The `check` target will download and build the Google Test library in the build
folder to run the tests when it is invoked for the first time.

If you're curious about how the library will perform on your system, use the
`bench` target to run the performance benchmarks. Like the `check` target, this
will download and build the Google Benchmark library in order to run.

```sh
make bench
```

## Installing

You can use the install target to install the library on your machine after the
build.

```sh
make install

# if the above doesn't work, you might need sudo to install files into the
# correct system folders
sudo make install
```

There is not currently an uninstall target supported, so removal of the library
and its include files must be done manually if it is no longer needed. Please
submit an issue on the project's Github site if you feel that you need a build
target providing this feature.

## C++ Library

If you want to build, test, and install the C++ bindings for stumpless as well,
you will need to modify the above steps slightly.

As a prerequisite, you will also need to make sure that you have the Wrapture
gem installed for this to work. This can be done with a simple
`gem install wrapture`, or you can use the `Gemfile` included in stumpless and
simply do a `bundle install` to pull it in.

After you have wrapture available, building and testing the C++ library can
be done like this:

```sh
# in the build directory, modify the cmake to enable c++
cmake -DENABLE_CPP=ON ../stumpless

# the all target will now include the stumpless c++ library
make all

# to test the library, use the `check-cpp` target
make check-cpp

# when enabled, the C++ bindings are installed along with the library itself
# so the following command will install the c++ headers and library in addition
# to the c headers and library
make install
```
