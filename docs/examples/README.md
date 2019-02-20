# Stumpless Examples

These examples demonstrate how to use features of the stumpless library. If you
aren't sure where to get started, this is the right place! If you're still
not quite sure, take a look at the [basic](basic/README.md) example as a good
starting place.

If you want to actually compile and run the examples, you'll need to have the
stumpless library available. If you don't want to install it on your system, you
can also use the `examples` build target. Note that some examples are built by
this target, but aren't actually executed. This is because these examples work
best after you modify them to suit your intentions. For example, the TCP example
is configured to send logs to `example.com`, which will fail as this is
obviously not a log server. You can either use the `examples` build target and
then run these afterwards, or you could use the `example-<examplename>` build
target to just build one at a time. For example, the `example-tcp` target will
build the TCP example, after which you can execute it manually.

If you want to see even more sample code after looking at the examples, you can
check out the test suites available in the `test` folder of the repository.
While the code in these suites is written with the primary goal of testing and
demonstrating (sometimes nuanced) functionality and performance, it can also be
a good place to find specific usage patterns and expected results.
