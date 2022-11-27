# Testing with Stumpless
Tests are an important part of any serious library. They provide assurance that
it behaves as expected, and also give some level of confidence to developers
that changes have not caused unexpected breakage. Stumpless uses tests for
exactly this purpose.

Stumpless uses the [Google Test](https://github.com/google/googletest) library
to create its unit tests. The rest of this document will walk through the
specifics of writiting and running tests for Stumpless, but if you have
questions about Google Test itself we recommend checking out the project's
own [guides](https://google.github.io/googletest/).


## Test Location and Structure
Tests are located in the `test` directory, of course! There is also a README in
this folder that details what types of tests are in each of these folders. Most
functionality is in the `test/function` directory, and if you're looking for the
test for a particular function this is the best place to start.

Tests are for the most part organized in a way that mirrors the structure of the
source code for stumpless. For example, tests for a function implemented
in `src/entry.c` will probably be located in `test/function/entry.cpp`. There
are some exceptions to this. For example, memory leak testing is in the
`test/function/leak` directory, and tests that must have a clean state are in
in the `test/function/startup` directory. But when looking for a test, the best
place to start is just `test/function`.

Individual tests should be focused on specific functionality of a single library
feature. This focus is important to allow issues to be quickly identified when a
test fails. Ideally the category and name of the test should reveal exactly
what went wrong, and if not then going to the assertion that has failed should
make it immediately obvious. For example, write separate tests for different
functions even if the input and expected behavior are exactly the same so that a
failure immediately indicates which function has broken.

There are two types of tests in Google Test, simple tests and fixture tests.
Simple tests have two levels of names, the first is a category, and the second
is the specific test. For example, for a test regarding setting params with a
NULL value, you would write `TEST( SetParam, NullValue )`.

Fixture tests use `TEST_F` instead, and are paired with a class with `SetUp`
and `TearDown` methods that are run before and after each test, along with
other instance variables that can be used during the test. If you have a number
of tests that need common setup and cleanup, this is the way to go.

For examples of the various test styles and idioms, have a look at the
`test/function/entry.cpp` module, which uses each of these techniques.


## Common Test Code
As with any development project, the need to write code that can be used across
many tests will arise. The helper test modules exist for this purpose and are
found in the `test/helper` directory of the project, with headers in the
`include/test/helper` directory. There are already a number of utilities in
these folders for tasks like adding custom assertions, tracking memory
allocations and deallocations for leak testing, running network services, and
so on. If you find yourself writing something for your tests that would be
useful for more than just one test suite, consider putting it here for reuse.


## Adding Tests to the Build
Stumpless uses CMake to build, and so adding new tests is as simple as adding
them to the `CMakeLists.txt` file. There are a number of CMake functions
provided that take care of creating runner targets and adding tests to the
appropriate aggregation targets like `check`. You'll find examples of each of
these in the project already that you can use for specific examples. They are:
 * `add_function_test` to create a unit test and add it to the `check` target
 * `add_performance_test` to create a test and add it to the `bench` target
 * `add_thread_safety_test` to create a test and add it to the
   `check-thread-safety` target
 * `add_cpp_test` to create a test for C++ functionality and add it to the
   `check-cpp` target (examples in `tools/cmake/cpp.cmake`)


## Running Tests
The easiest way to run all tests is to use the `check` target. You can run this
target through whatever build system you're using, for example `make check` in a
makefile-based build. You can also use cmake to run the target using your build
system in a more portable way like this: `cmake --build . --target check`. The
tests themselves run pretty quickly, but may take a while to build, so be sure
to use whatever parallel build processes you can to speed this up, for example
the `-j` parameter for make.

Using the `check` target prints a quick summary of the pass/fail status of
all of the tests that ran. However, if you have failures you'll probably want to
investigate exactly what failed. The output from the entire run will be written
to `Testing/Temporary/LastTest.log`, so you can go through this to find the test
that failed and start figuring out why.

If you don't want to run the entire test suite every time you want to run a
test, you can use the specific target for that test. These are named
`function-test-<module>`, for example `function-test-entry` for the entry
module. If you want to be even MORE focused, you can pass the `gtest_filter`
option to the executable. For example, to run all `SetParam` tests, you could do
`./function-test-entry --gtest_filter=SetParam*`.

There are special targets that group other types of tests as well.
 * `check-cpp` runs the C++ bindings test suite
 * `check-thread-safety` runs the thread safety test suite
 * `run-thread-safety-test-<name>` builds and runs the thread safety test with
   the given name
 * `run-performance-test-<name>` builds and runs the benchmark with the given
   name


## Test Coverage
Stumpless uses test coverage to make sure that most of the lines in the code
base are executed at least once during testing. While stumpless does not strive
to reach 100% code coverage, you should try to cover all of your own code, only
leaving out things that are difficult to recreate during a test.

Coverage information is collected automatically on pull requests during the
continuous integration testing, and
[Codecov](https://app.codecov.io/gh/goatshriek/stumpless) will helpfully
generate a report for the pull request or branch in question. This may be enough
if you are confident that you have already covered everything and just need to
double-check upon opening the pull request.

However, if you'd like to test coverage yourself locally, you'll need to
generate the report yourself. This isn't complicated, but does require a few key
steps to make possible. There are multiple ways to generate reports from
coverage data; we'll use `gcovr` on a Linux build here, but if you have another
tool and/or environment you prefer you can use that instead.

First, make sure you turn the `COVERAGE` flag on during the cmake configuration
step, and use a Debug build to keep source-code alignment intact. So your cmake
invocation would look something like this:

```sh
cmake -DCMAKE_BUILD_TYPE=Debug -DCOVERAGE=ON /path/to/stumpless
```

When you run the test suite, coverage data will be generated and placed
alongside the object files. You can run individual tests if you want to see what
they cover by themselves, but the easiest way to get a full report is to just
invoke the `check` target, like this:

```sh
# you can change the  -j flag to build and run more/less threads in parallel
make -j 4 check
```

You can then find coverage data in the form of `.gcda` and `.gcno` files in the
`CMakeFiles/stumpless.dir/src` folder and subfolders. If you are using another
generation tool, you can point it at these to do what you need. For `gcovr`, we
don't need to worry about this though, since it can figure it out. We instead
just need to pass the path to stumpless in to the `-r` flag, and ask for a
detailed html report:

```sh
gcovr -r /path/to/stumpless --object-directory . -o coverage.html --html --html-details .
```

This will generate a report file `coverage.html` that you can open in your
browser to see overall percentage reports and inspect coverage of specific files
in detail.

There are a few caveats to keep in mind with coverage testing. First, it can
slow down the test suite considerably due to the instrumentation inserted into
the binaries. Don't default to enabling coverage with `-DCOVERAGE=ON` in all of
your builds: only do this when you need to check coverage. The easiest way to do
this is to have a separate build directory such as `build-coverage` that you go
to when you need to run a coverage test.

Second, note that the `clean` build target will _not_ remove coverage files from
the build directory. If you have made changes and need to make sure that
previously covered lines are still being covered, you will need to remove these
yourself, either by manually deleting them or starting a fresh build directory
entirely.
