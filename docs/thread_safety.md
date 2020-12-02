# Thread Safety in Stumpless
As of version 2.0, stumpless is completely thread safe. All functions
provided by the library are documented with their safety level using
safety attributes described in the POSIX standard and conditional safety
features described by some GNU libc manual (find the relevant section
[here](https://www.gnu.org/software/libc/manual/html_node/POSIX-Safety-Concepts.html#POSIX-Safety-Concepts)
).

In addition to thread safety, the async safety and async cancellation safety is
also documented. However, most functions are not safe in either of these
situations. You can look at any function documentation in the public header
files for examples of how this is formatted.

## Implementation Approach
There are a number of ways to achieve thread safety, and stumpless uses a
combination of them to balance performance and simplicity. You can find the
symbols for working with each of these types in the
`private/config/wrapper/thread_safety.h` include file.

### Mutexes
Most structs are protected with a mutex, which is used to coordinate reads
and writes to all members of the struct. Some targets also use a (separate)
mutex to coordinate writes, such as the file and stream targets. These locks
are held for as short of a time as possible. Especially try to avoid holding
a mutex during expensive operations like memory allocations.

Mutexes are defined by the typdef `config_mutex_t`, and there are four functions
for working with them. `config_lock_mutex` and `config_unlock_mutex` acquire
and release the mutex respectively. `config_init_mutex` sets up the mutex for
first use, and `config_destroy_mutex` cleans it up when it is no longer needed.
The init and destroy functions _must_ be called at the beginning and end of the
mutex's life. For a good example of how mutexes can be used, check out the slab
cache implementation in `src/cache.c` and `include/private/cache.h`, which uses
a mutex to make each cache thread safe.

### Thread Local Storage
Some structures do not necessarily need to be available to all threads all the
time, and can use more efficient safety mechanisms instead. Good examples of
this are the per-thread error structures and the cached entry struct used by
string-based logging functions like `stump`. These are place in thread-local
storage, and therefore no locking is needed on them. If you can use this
strategy, it is less susceptible to contention and will be faster in most cases.

You can declare any variable as thread-local using the
`CONFIG_THREAD_LOCAL_STORAGE` modifier in its definition. After doing this, the
variable will work just as normal and no other special work is needed.

### Atomic Types
Atomic values are the final strategy used in implementations. These can be used
to have a single field that can be read and written without a lock to
synchronize access. This synchronization method can be the most performant of
the options, but are also tricky to use correctly. The implementatin of
`stumpless_get_default_target` is a good example of this, requiring more logic
than a simple read and update in order to avoid a potential memory leak.

Atomic types are defined for each type needed, and come with functions for
reading, writing, and doing a compare and exchange operation. You will also
need to intialize the variable when it is defined, using the appropriate
initializer. The current and default target variables in `src/target.c` are
good examples of how to create and work with an atomic type.
