# Developing Stumpless

If you're going to work on the library itself, here are some helpful tips that
will make the experience a little smoother and faster.

## Getting Started

Stumpless is configured using the popular [CMake](https://cmake.org/) build
platform. In order to build it from the source you will need this tool
available, as well as any of a number of supported build systems.
[GNU Make](https://www.gnu.org/software/make/) is one of the most well-known
ones, and so most if not all examples you will find in stumpless
documentation use it. If you prefer to use something else, there is plenty of
support for CMake in other build systems. For example, Visual Studio has CMake
support built in so that you can build targets in a CMake project easily within
the IDE itself.

The `CMakeLists.txt` file contains the build specification for stumpless, and is
worth browsing through if you are curious about where configuration checks,
source and test files, and other build targets are specified.

There are a number of other dependencies for working on stumpless, but they are
less noteworth as you may not find yourself interacting with them. For example,
the Google Test and Benchmark libraries are needed, but they are downloaded and
built dynamically during the build process, so you do not need to worry about
providing them. Ruby is also used for some development and testing scripts, but
the basic builds and tests will succeed without it. For a more detailed rundown
of the dependencies you might encounter, check out the
[dependencies documentation](dependencies.md).

A typical development workflow involves an initial configuration and build,
followed by re-running the test suite after making some changes. This might
look like this:

```sh
# first, the initial setup:

# cloning the latest version of the source tree
git clone git@github.com:goatshriek/stumpless.git

# creating a new build directory
mkdir build
cd build

# configuring the new build
cmake ../stumpless

# after the above initial commands, a normal development cycle would be:

# update a few files (your favorite editor - here we use vim)
vim ../stumpless/src/target.c

# build and run the test suite
# change the number of threads with the j parameter to make things faster
# your processor's core count is a good starting place
make -j 4 check

# if you want to build a single test, you can do this using the executable
# name, which for functionality tests is function-test-<name>
make -j 4 function-test-target && ./function-test-target
```

More details about building the library are available in the
[INSTALL.md](../INSTALL.md) file. However, if you plan to be developing
stumpless itself it is recommended that you avoid using the `install` target
described there. Instead, simply work off of the version of the library in your
build folder, which will make it easier to work with different builds without
worrying about the installed library being used by accident.

A few other documents may be helpful for newcomers to glance through:
 * [Contributing Guidelines](CONTRIBUTING.md) If you have not read these yet,
   definitely do this soon. This document contains basic getting started info
   about different ways to contribute to stumpless, including a discussion of
   the branching scheme.
 * [docs/acronyms.md](acronyms.md) lists acronyms and initialisms used in the
   source of stumpless.
 * [docs/style.md](style.md) has a basic set of style guidelines to follow when
   working on the source code itself.
 * [docs/portability.md](portability.md) describes the framework used in
   stumpless to deal with differences between environments. If you are going
   to be working on something that may behave differently depending on the
   platform, or that may be missing on some, then this document holds
   important information for you. If you need to work with a function starting
   with `config_`, this is also a good indication you should read this doc.
 * [docs/benchmark.md](benchmark.md) has a detailed walkthrough of the
   performance testing framework set up in stumpless. If you're looking to
   make a performance improvement that will otherwise be transparent, this
   document describes the steps for this in detail with a full example.
 * [docs/localization.md](localization.md) describes how localization is
   implemented in detail and how to add new locales.

## Error Handling

Stumpless has a framework for handling errors that happen at runtime. If you
are writing new functionality or extending something that already exists
then you will need to make sure that this framework is used whenever an
operation stops prematurely after encountering a problem.

All possible errors are specified in `stumpless/error.h` as part of the
`STUMPLESS_FOREACH_ERROR` macro function. This function lists all possible
errors and their integral id values, along with their documentation. If you
need to add a new error, it will get added to the end of this list (_not_
in alphabetical order) with the next available integer assigned as the id.

Each error has an internal `raise` function associated with it, declared in
`include/private/error.h` and defined in `src/error.c`. These functions set
the stumpless error id and error messages, and are intended to keep error
handling in stumpless readable and expressive. If you need to add a new error,
you will need to implement one of these to raise it as well.

For example, if a public function detects that a provided index is out of
bounds, then `raise_index_out_of_bounds` should be called with a localized
string describing the error, something like
`L10N_INVALID_INDEX_ERROR_MESSAGE( "element" )`, and the invalid index that
was passed in. This is a common pattern that can be seen throughout the
library code.

All error messages must be localized so that they can be understood by those
who will troubleshoot them. More information about handling localization can
be found in the [localization documentation](localization.md).

Often `raise` functions include information to help with troubleshooting. The
`raise_index_out_of_bounds` is a good example of this: in addition to a string
describing the invalid access it also takes the index that was out of bounds.
This is then made available in the resulting error to the user as the `code`
of the struct, along with a localized string description of what the value is in
`code_type`. The code of an error can be different across errors and even in
the same error when thrown from a different context.

Note that if you are calling another internal function and checking its result
for an error, you do not need to raise an error if this function already does
so. A good example of this is the memory allocation function `alloc_mem` which
will raise the appropriate error if it encounters a problem. Functions that
detect a failure of `alloc_mem` can simply return, without needing to raise an
error of their own first (since this would overwrite the original error).

Any public function must clear the error if there was no issue. This is so that
a user can tell if their last call succeeded by checking for the presence of an
error. Most public functions do this by calling `clear_error` directly before
returning from their non-error path, which handles this cleanup. Some do not
explicitly call `clear_error`, but instead rely on a call to another public
function to clear it for them if it succeeds. The only functions that do not
need to clear the error code are destructors and any error handling functions.

There is error handling code everywhere, but if you want a singular place to
look we recommend `stumpless_set_entry_param_value_by_index` in `src/entry.c`.
This function demonstrates how to detect errors in parameters and internal
function calls, call the appropriate `raise` functions when needed, and simply
return when the error comes from a different function.

Errors raised in stumpless can be accessed by the various error handling
functions provided for the user. Some of the common useful ones are:
 * `stumpless_get_error` gets the current error struct if there was an error on
   the last call
 * `stumpless_has_error` is true if the last call failed, false if it succeeded
 * `stumpless_perror` prints the current error if there is one

## Adding new functions

If you're adding a new function to stumpless, here are a few notes that will
help you along the way.

First, always make sure that you have documented your function, especially if it
is public facing. Stumpless uses [doxygen](https://www.doxygen.nl/index.html) to
generate its documentation from the header files. You can use the `docs` build
target to generate them, provided that doxygen was installed when you ran cmake.

In order to support being built as a DLL, stumpless has a `.def` file at
`src/windows/stumpless.def`. If you are adding a new public function to
stumpless, you will need to make sure to add it to the `.def` file so that the
DLL will include it. Failing to do so will result in tests failing on Windows
builds with a note that your new function is not defined. The AppVeyor CI builds
typically catch this issue.

Stumpless uses a custom tool to make sure that all required headers are included
in a source file without any extras. The tool is called `check_headers` and is
stored in the `tools/check_headers` folder. You can run this manually if you
wish, by simply executing the script and passing it your source file (or files)
as parameters. You will need Ruby to run it. It is also run as a part of Travis
CI builds, so you can wait for it to run there instead of doing it yourself. For
a one-liner command to catch issues, you can run the tool like this:

```sh
tools/check_headers/check_headers.rb "src/**/*.c" "include/**/*.h*" "test/**/*.cpp"
```

However, if you have added a new function and you see Travis CI builds failing
as a result of this tool claiming that an include file is unnecessary, then you
probably need to add your function to the manifest that powers it. This is a
simple YAML file at `tools/check_headers/stumpless.yml` with entries for each
function. Adding your function and the associated header it is declared in will
remove this error as the tool will now know why the include is required.

## Continuous Integration Tools

Stumpless uses a number of CI tools to test builds and monitor code coverage
and quality. These tools each have badges in the project
[README](../README.md) that link to their respective pages.

[Travis CI](https://travis-ci.com/github/goatshriek/stumpless) and
[AppVeyor](https://ci.appveyor.com/project/goatshriek/stumpless) build the
library in a variety of environments and with a variety of build options.
They ensure that changes are portable and that no tests are failing. They also
perform a number of other tests such as header checks and ensuring that the
`install` target works. These must be passing on a change before it will be
merged to the library.

[Codecov](https://codecov.io/gh/goatshriek/stumpless) provides a way to
review and analyze code coverage from the test suite. It is fed by Travis CI
builds, and will check pull requests for diff and total coverage. In some
cases this gate may be failing and code will still be merged, but this is only
in situations where coverage is not reasonably obtainable. For example if the
only way to cover a failure branch is a very specific chain of memory or
system call failures, then the coverage requirement may be relaxed.

[Sonarcloud](https://sonarcloud.io/dashboard?id=stumpless) provides code quality
reviews and static analysis. Changes should avoid introducing any new issues in
Sonarcloud. Changes that do introduce new issues will likely not be accepted.

If you are making a documentation change or other update that won't affect the
output of any of these tools, you may include `[skip ci]` in your commit message
to bypass their builds and save some electricity. Travis CI and AppVeyor also
support the targeted skip messages `[skip travis]` and `[skip appveyor]`,
respectively.

## Caching Google Test and Benchmark

If you are going to be repeatedly building the library from scratch, for example
to ensure nothing is cached between builds or to try different configurations,
it will quickly become tedious to wait for the Google Test and/or Benchmark
libraries to download and build each time as well. As an alternative, you can
put a build of the libraries in some other location and simply tell the build
process to use those instead using the `GTEST_PATH` and `BENCHMARK_PATH` build
parameters.

You could download and build the library yourself, which may be the best course
of action if you plan to re-use the build for other projects. If you do this,
you just need to make sure that the correct libraries (in the case of gtest,
`gtest`, `gtest_main`, and `gmock`) and headers (`gtest/gtest.h` and
`gmock/gmock.h`) are found at the given path. If they are, then they will be
used and gtest will not be downloaded and built again. If _any_ of them are
missing though, a fresh copy will be downloaded and used anyway, so make sure
everything is there!

Since downloading and building can be a pain, especially multiple times for 
different build types, stumpless provides two build targets that will export
built libraries for you to the path. This way, all you need to do is build
stumpless as you would normally, and then use the `export-gtest` and/or
`export-benchmark` targets to populate the path for future builds. This would
look something like this (if you're using a `make` build system):

```sh
# from the directory above your repo
# just adjust the paths accordingly if you build somewhere else

# first we set up our folders to hold the libraries
mkdir gtest
mkdir benchmark

# next, we build the library as normal
mkdir biuld
cd build
cmake -DGTEST_PATH=../gtest -DBENCHMARK_PATH=../benchmark ../stumpless

# in this build Google Test and Benchmark will be downloaded and built since
# the paths we provided don't have anything in them
make check
make bench

# to build the libraries and put them in the path for future builds, we just
# execute these two targets:
make export-gtest
make export-benchmark

# these list commands show that the folders are now populated!
ls ../gtest
ls ../benchmark

# next time, you can use the exact same cmake command to use the previously
# built versions instead of downloading fresh

# if you want to try it out immediately:
cd ..

# clear out the previous build
rm -rf build

# and redo it!
mkdir biuld
cd build
cmake -DGTEST_PATH=../gtest -DBENCHMARK_PATH=../benchmark ../stumpless

# running the test suite or benchmark suite won't download the libraries this
# time - it will go straight to compiling the tests and linking them against
# the libraries in the PATH variables
make check
make bench
```

## Other development notes

For a detailed discussion of the performance testing framework used to gauge
the speed and efficiency of various calls, check out the
[benchmark](benchmark.md) documentation for the basic strategy and a full
walkthrough of an example.
