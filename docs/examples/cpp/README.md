# C++ Bindings

While stumpless is written in C to keep it as lightweight and simple as
possible, it has been extended to C++ so that it can be used from the higher
level language with the same performance benefits.

These bindings go beyond simply calling C code from C++, however; the entire
library is exposed via an object-oriented API documented in full
[here](https://goatshriek.github.io/stumpless/docs/cpp/latest). While the concepts of the
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
                        Facility::USER );
```

Entries, elements, and parameters are still created much the same way, again
using the class constructors instead of the raw functions. The following snippet
has the same effect as the snippets in the entry example:

```cpp
Entry up_to_code( Facility::USER,
                  Severity::INFO,
                  "cpp-demo-app",
                  "up-to-code",
                  "is it up to code?" );

// makes an element named 'subject' and adds it to the entry
Element item( "subject" );
up_to_code.AddElement( item );

// adds a few parameters to the element
Param name( "name", "baked alaska" );
Param result( "result", "not-up-to-code" );

// most `Add` and `Set` methods can be chained together
item.AddParam( name ).AddParam( result );

// writing an entry to the log file
file_logger.Log( up_to_code );

// the resulting entry looks like this:
// 'Angus' is the name of the system this was logged on
// '10078' was the PID of the process that logged it
// <14>1 2020-05-05T19:55:48.368156Z Angus cpp-demo-app 10078 up-to-code [subject name="baked alaska" result="not-up-to-code"] is it up to code?
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
use try/catch blocks rather than check each return value. You can also check the
error id to see what the specific nature of the error was.

```cpp
try {
  file_logger.Log( NULL );
} catch( StumplessException *e ) {
  // will catch the exception
  if( e->GetErrorId() == ErrorId::ARGUMENT_EMPTY ) {
    std::cout << "the message was NULL!" << std::endl;
  }
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

## Running this Example

If you want to compile and run the example code here, then you'll need to
compile it with the correct include paths and library load paths. Or you can
simply compile it with the library specified if the C++ library has already
been installed.

```sh
g++ cpp_usage.cpp -lstumplesscpp -o cpp_usage
./cpp_usage
```
