## Thread Safety in Stumpless

As of version 2.0, stumpless is designed to be completely thread safe. All
functions provided by the library are documented with their safety level using
safety attributes described in the POSIX standard and conditional safety
features described in the `attributes` man page for Linux, which describes
these POSIX safety concepts in detail. This is the example followed by the
documentation of stumpless thread safety.
