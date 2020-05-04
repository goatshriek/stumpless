# C++ Bindings

While stumpless is written in C to keep it as lightweight and simple as
possible, it has been extended to C++ so that it can be used from the higher
level language with the same performance benefits.

These bindings go beyond simply calling C code from C++, however; the entire
library is exposed via an object-oriented API documented in full
[here](https://goatshriek.github.io/stumpless/cpp/). While the concepts of the
library are the same in this extension, the object oriented extensions offer
some useful advantages over the simple functional capabilities of C.

The C++ bindings are created using
[Wrapture](https://goatshriek.github.io/wrapture/).

## Stumpless Classes

Targets can be created and logged to using the various target classes that match
target types from the C library. The constructors take the same parameters as
the matching open target function in the C library. This example shows how to
open a file target.

Note that you will need to include the header for the class in order to use it.
There is currently no roll-up header for the entire C++ library, though this is
planned in an upcoming release in the project roadmap (see `docs/roadmap.md`).

```cpp
#include <FileTarget.hpp>

// ...

FileTarget file_logger( "logfile.log",
                        STUMPLESS_OPTION_NONE,
                        STUMPLESS_FACILITY_USER );
```

Entries, elements, and parameters are still created much the same way, again
using the class constructors instead of the raw functions. The following snippet
has the same effect as the snippets in the entry example:

```cpp
Entry entry( STUMPLESS_FACILITY_USER,
             STUMPLESS_SEVERITY_INFO,
             "my-app-name",
             "my-msgid",
             "user has logged a message");

Element element( "user" );
Param param( "username", username );
element.AddParam( param );
entry.AddElement( element );
file_logger.Log( entry );
```

If you would like to get the struct associated with one of these classes, you
can use the `equivalent` member of the class to get and use it as you would
with the underlying C library.

```cpp
struct stumpless_target *underlying = file_logger.equivalent;
std::cout << "using target: " << underlying->name << std::endl;
```

## Error Checking

Error checking is not as cumbersome as in the C library; an exception is thrown
whenever an error is detected in the underlying function. This allows code to
use try/catch blocks rather than check each return value.

```cpp
try {
  file_logger.AddMessage( NULL );
} catch( StumplessException *e ) {
  // will catch the exception (ArgumentEmpty)
}
```

## Constants and Configuration

If you need to check information about the configuration of your build of the
library, you can check the same constants as before for them, though you will
need to include the C header to do so.

```cpp
if( STUMPLESS_SOCKET_TARGETS_SUPPORTED ) {
  std::stdout << "logging to " << STUMPLESS_DEFAULT_SOCKET << " by default" << std::endl;
}
```

However, for some (but not all) constants there is a matching constant that puts
these constants into a namespace:

```cpp
// this check still has to use the C #define
if( STUMPLESS_SOCKET_TARGETS_SUPPORTED ) {
  std::stdout << "logging to " << SocketTarget::DEFAULT_SOCKET << " by default" << std::endl;
}
```
