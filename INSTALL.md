# Building Stumpless

In order to compile Stumpless you will need cmake and a compatible build system
such as the GNU toolchain or Microsoft Visual Studio. Given these dependencies
building the library is very straightforward. The examples below show how to do
this in a build environment using `make` from a fresh clone.

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
Visual Studio provides a CMake menu in the IDE that will display all available
targets.

If you're unsure of the build commands for the toolchain on your system, then
cmake can run these commands for you if you invoke it in build mode.

```sh
# build the `all` target using whatever toolchain cmake detected during the
# configuration stage
# the argument to the `--build` parameter is the root of the folder where we
# ran the original cmake configuration command
cmake --build . --target all

# build and run the test suite the same way
cmake --build . --target all
```

The type of build can be changed at configuation time by defining the
`CMAKE_BUILD_TYPE` symbol during configuration.

```sh
# benchmark testing should always be done using Release builds
cmake -DCMAKE_BUILD_TYPE=Release ../stumpless
```

However, some environments (Visual Studio being one) require the configuration
to be passed in during build steps. In the above example, builds would still use
the default build type, effectively ignoring the configuration step. To specify
the build type you will need to provide a config to use during build:

```sh
# explicitly use the Release configuration we have in our toolchain
cmake --build . --config x64-Release --target bench
```

In systems like this, it is easiest to use an IDE that does this work for you,
for example Visual Studio. For more information on these build topics, refer to
the CMake documentation on
[build mode](https://cmake.org/cmake/help/latest/manual/cmake.1.html#build-a-project)
and
[multi-config generators](https://cmake.org/cmake/help/latest/prop_gbl/GENERATOR_IS_MULTI_CONFIG.html).

The rest of this documentation uses make commands for simplicity, but for any
target you can build it using cmake build mode if you need truly portable
command line invocation.

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

A simple way to make sure that your install is working as you expected is to
compile one of the examples without using the built-in targets. If the target
builds but your own compilation doesn't, then there is something wrong with
your install.

```sh
# first we use the build target to make sure it works
make example-entry && ./example-entry

# next, we compile the same example manually
gcc docs/examples/entry/entry_example.c -lstumpless -omanual_entry_example
# this should work if everything was correct
./manual_entry_example
```

If you do have issues, there are a few simple things for you to check. An easy
issue is if the installed library is not in the system's library search path,
which will usually lead to an error message of `cannot find -lstumpless` or
similar. If you see this, check the current search path and if needed set
appropriate environment variables or add compilation flags to add the location
that stumpless was installed to the search path. Some examples are gcc's `-L`
option, the `LD_LIBRARY_PATH` environment variable on many Linux systems, and
the environment variable `LIBRARY_PATH` in Cygwin.

If you find that stumpless has installed to unexpected locations and you want
to modify this, use the `CMAKE_INSTALL_PREFIX` definition during the
configuration step of the build. You can always re-run cmake to update this in
an existing build tree if you need to change it.

```sh
# our initial build installed to /usr/local locations, which we didn't want
cat install_manifest.txt
# /usr/local/include/stumpless/target/network.h
# /usr/local/include/stumpless/target/socket.h
# /usr/local/lib/libstumpless.so.2.0.0
# /usr/local/lib/libstumpless.so
# /usr/local/include/stumpless.h
# <output truncated>

# re-run the configuration
cmake -DCMAKE_INSTALL_PREFIX=/usr ../stumpless

# re-do the install
sudo make install

# now we see things in the right place!
cat install_manifest.txt
# /usr/include/stumpless/target/network.h
# /usr/include/stumpless/target/socket.h
# /usr/lib/libstumpless.so.2.0.0
# /usr/lib/libstumpless.so
# /usr/include/stumpless.h
# /usr/include/stumpless/config.h
# <output truncated>
```

### Uninstalling

There is currently no uninstall target supported, so removal of the library
and its include files must be done manually if it is no longer needed. Please
submit an issue on the project's Github site if you feel that you need a build
target providing this feature. For the time being, you can run the contents
of the `install_manifest.txt` file (generated during the install) through `rm`
like this:

```sh
xargs rm < install_manifest.txt
```

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
# this will emit a warning and leave c++ disabled if wrapture cannot be found
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
