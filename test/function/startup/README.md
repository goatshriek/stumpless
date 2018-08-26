# Startup Tests

Because many of the internals of stumpless are lazily initialized, it's
difficult to write tests that catch these initializations because they often
occur during earlier tests. Therefore, it's necessary to write test suites with
single or only a few tests that can carefully control the internal state and
cover failure scenarios that can occur during initialization, most commonly
memory allocation failures.
