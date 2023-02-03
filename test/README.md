# Stumpless Testing
Test support for stumpless is divided at a high level into the areas of focus,
each of which is implemented and organized differently from the others so that
the specific focus can be effectively tested.


## Functionality Tests
The [`function`](./function) directory holds tests for basic functionality of
the library. There is a large suite of unit tests implemented using the Google
Test library. These tests are used to measure coverage as well, and check for
memory leaks, startup conditions, and error scenarios in addition to the basic
features of the library.


## Memory Leak Tests
Memory leaks are a concern for any application written in C, and so whenever a
leak is found or suspected a test for it is implemented and added here to
prevent regression. These tests are in the [`function/leak`](./function/leak)
directory and focus on causing the leak and detecting it. These tests do not
necessarily verify correct functionality around the potential leak, as that is
the focus of the more general functionality tests.


## Thread Safety Tests
Testing for thread safety is not as straightforward as for basic functionality,
and therefore these tests are separated from the standard unit testing suite in
the [`thread_safety`](./thread_safety) directory. These tests also use the
Google Test library, but are used to test for thread safety to the extent
possible.


## Performance Tests
Any changes that are made to the library in the name of improving performance
are measured by a performance test in the [`performance`](./performance)
directory. These tests are implemented using the Google Benchmark library and
measure execution time, memory consumption, and the number of calls to some
functions outside of the library (such as memory allocation routines).

For a detailed guide on how to implement your own benchmark test, check out
the documentation at [`docs/benchmark.md`](../docs/benchmark.md)


## Fuzzing Tests
In order to catch one class of security issues, there are a number of fuzzing
targets in the [`fuzz`](./fuzz) directory. These tests don't have a target to
run all of them at once, but you can build all of them with the `fuzz` target.
To run one of them, use the `run-fuzz-test-<name>` target, which will build the
fuzzer and run it with the proper corpus directories. The initial seed corpus is
the appropriate subdirectory of [`corpora`](./corpora), and a matching folder is
created in the build directory in a folder named `fuzz-corpora` to hold new
corpus files generated during fuzzing.

Fuzzers are only supported when Clang is the compiler, as they rely on
libFuzzer.


## Test Helper Modules
Of course there are some tasks that are needed in a number of tests and
therefore should not be duplicated in each of them. A good example of this is
the existence of a network server that can listen for messages when testing
the network logging targets. These implementations are kept in the
[`helper`](./helper) directory of the test suite.

