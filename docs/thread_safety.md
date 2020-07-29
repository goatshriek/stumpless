## Thread Safety in Stumpless

As of version 2.0, stumpless is designed to be completely thread safe. All
functions provided by the library are documented with their safety level using
safety attributes described in the POSIX standard and conditional safety
features described in the `attributes` man page for Linux, which describes
these POSIX safety concepts in detail. This is the example followed by the
documentation of stumpless thread safety.

## Implementation Approach

There are a number of ways to implement thread safety, and stumpless uses a
combination of them to balance performance and simplicity.

The primary goal of stumpless is to have a logging call that is as fast as
possible. For this reason the thread safety design is built around optimizing
calls to `stumpless_add_entry`, which is the function that ultimately handles
all logging requests. The implementation is therefore designed around making
this function _wait free_.

This is accomplished by keeping an immutable copy of each entry available
at all times. This copy is then grabbed at the beginning of the logging call,
which becomes the linearization point of the event. If any changes are made
to the entry after this copy is grabbed, they are linearized after this point.

The design of the entry, element, and param structs revolves around this method.
Updates to any of these structures requires an update to entries referring to
them so that the immutable copy is consistent. These updates are coordinated
using traditional locking mechanisms.
