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
these folders for tasks like adding customr assertions, tracking memory
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
