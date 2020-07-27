# Benchmark Testing with Stumpless

High performance and efficiency is a core pillar of stumpless design, and as
such a benchmarking framework is available to assist with this. This framework
uses the [Google Benchmark](https://github.com/google/benchmark) library to
measure execution time and other efficiency characteristics.

Performance tests are named `performance-test-<item>` for various pieces of the
library. You can use the `bench` target to build and execute all performance
tests at once, or just the name of the executable if you only want to measure
a single module.

## Walkthrough: Improving `stumpless_copy_element`

Walking through a benchmarking improvement change from beginning to end
demonstrates all of these principles and how they are used to implement an
actual improvement to the library. Let's analyze an improvement to the
performance of `stumpless_copy_element` to do this.
