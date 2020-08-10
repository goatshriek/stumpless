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

## Test Helper Modules
Of course there are some tasks that are needed in a number of tests and
therefore should not be duplicated in each of them. A good example of this is
the existence of a network server that can listen for messages when testing
the network logging targets. These implementations are kept in the
[`helper`](./helper) directory of the test suite.
