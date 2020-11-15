# Thread Safety in Stumpless
As of version 2.0, stumpless is completely thread safe. All functions
provided by the library are documented with their safety level using
safety attributes described in the POSIX standard and conditional safety
features described by some GNU libc manual (find the relevant section
[here](https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html#POSIX-Safety-Concepts).

In addition to thread safety, the async safety and async cancellation safety is
also documented. However, most functions are not safe in either of these
situations.

## Implementation Approach
There are a number of ways to achieve thread safety, and stumpless uses a
combination of them to balance performance and simplicity.

Most structs are protected with a mutex, which is used to coordinate reads
and writes to all members of the struct. Some targets also use a (separate)
mutex to coordinate writes, such as the file and stream targets. These locks
are held for as short of a time as possible. Especially try to avoid holding
a mutex during expensive operations like memory allocations.

Some structures do not necessarily need to be available to all threads all the
time, and can use more efficient safety mechanisms instead.
