# Testing with Stumpless
Tests are an important part of any serious library. They provide assurance that
it behaves as expected, and also gives some level of confidence to developers
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
source code for stumpless. For example, tests related to a function implemented
in `src/entry.c` will probably be located in `test/function/entry.cpp`. There
are some exceptions to this. For example, memory leak testing is in the
`test/function/leak` directory, and tests that must be the first test run in a
module are in the `test/function/startup` directory. But when looking for a
test, the best place to start is just `test/function`.

Individual tests should be focused on specific functionality of a given library
feature. This focus is important to allow issues to be quickly identified when a
test fails. Ideally, the category and name of the test should reveal exactly
what has gone wrong, and if not then going to the assertion that has failed
should make it immediately obvious. For example, write separate tests for
functions even if the input and expected behavior is exactly the same so that
a failure immediately points at which function has broken.

There are two types of tests in Google Test, simple tests and fixture tests.
Simple tests have two levels of names, the first is a category, and the second
is the specific test. For example, for a test regarding setting params with a
NULL value, you would use `TEST( SetParam, NullValue )`.

Fixture tests use `TEST_F` instead, and are paired with a class with `SetUp`
and `TearDown` functions that are run before and after each test, along with
other instance variables that can be used during the test. If you have a number
of tests that need common setup, this is the best way to go.

For a good example of the various test styles, have a look at the
`test/function/entry.cpp` module, which uses each of these techniques.


## Running Tests
The easiest way to run all tests is to use the `check` target. You can run this
target through whatever build system you're using, for example `make check` in a
makefile-based build. You can also use cmake to run the target using your build
system in a more portable way like this: `cmake --build . --target check`.

If you don't want to run the entire test suite every time you want to run a
test, you can use the specific target for that test. These are named
`function-test-<module>`, for example `function-test-entry` for the entry
module. If you want to be even MORE focused, you can pass the `gtest_filter`
option to the executable. For example, to run all `SetParam` tests, you could do
`./function-test-entry --gtest_filter=SetParam`.
