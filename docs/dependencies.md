## Build Environment
In order to compile the library, a standard suite of build tools must be
available. These tools are standard for building C projects and are listed
below:
 * `cmake` for build targets and orchestration
 * a toolchain that can be used by cmake (gcc, for example)

If you want to build the C++ language bindings, you will need `wrapture`
installed. It is available on rubygems.org as a packaged gem. You can also
use bundler to install it with the project Gemfile (`bundle install`), but note
that this is intended for development and may install some other gems that you
do not need if you just want to build and install the library.

## Testing
The test suite for the project is written using the Google Test suite. It will
be found and/or downloaded and built on the system automatically if testing is
enabled, which it is by default.

More information on the Google Test framework may be found on the project
[Github page](https://github.com/google/googletest).

Of course if you would like to test the generated wrappers for languages other
than C then you will need the language environment installed in order to run the
tests.

The performance test suite for the project uses the Google Benchmark suite. Like
the Google Test suite, it will automatically be found and/or downloaded and
built if benchmarking is enabled.

More information on the Google Benchmark framework may be found on the project
[Github page](https://github.com/google/benchmark).

Valgrind is used to check for memory leaks and perform other sanity tests for
the library. These tests are invoked in the continuous integration tests for
the Linux debug build, but can also be performed manually as needed.

More information on Valgrind can be found on the project's
[home page](https://valgrind.org/).

## Documentation
General documentation of how functions behave is included as block comments in
the public header files. Documentation can also be generated using `doxygen`.
This is done using the `docs` build target, which will only be available if
doxygen is detected on the build system.

If you only want to see the docs, you can avoid downloading the repo and
building it by visiting the project
[website](https://goatshriek.github.io/stumpless/), which has documentation for
C and C++ for the latest release.

## Development
If you wish to develop within the stumpless project itself, you will need a few
additional tools:
 * `ruby` for some of the development scripts. If you have bundler, you can use
   the Gemfile (run `bundle install` from the project root) to install all the
   gems you might need at once.

## Simplified Wrapper Interface Generator (SWIG)
The SWIG project is used to expose the functionality of Stumpless to languages
beyond normal C. The `swig` executable must be available in order to build any
other language support (for example, Python). SWIG is not required for the base
library build, so if support for other languages is not needed then it does not
need to be installed on the base system.

More information on the SWIG project may be found on the project
[Github page](https://github.com/swig/swig).
