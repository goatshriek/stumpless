# C++ Bindings
While stumpless is written in C to keep it as lightweight and simple as
possible, it has been extended to C++ so that it can be used from the higher
level language with nearly the same performance benefits.

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

```cpp
#include <stumpless.hpp>

// ...

FileTarget file_logger( "logfile.log" );
```

Logging to the target is done with the `Log` function, which has a few forms
depending on how much information you provide:

```cpp
// logs the given message to the file
file_logger.Log( "she just made ANOTHER u-turn" );
// the entry will look like this:
// <14>1 2020-05-15T16:28:56.266031Z Angus - 4484 - - she just made ANOTHER u-turn
// 'Angus' is the name of the system this was logged on
// the three '-' characters are the app name, the message id, and the structured data,
// which were all empty here
// '4484' is PID of the process that logged this message

// logs the given message to the file at the given priority
file_logger.Log( Facility::NEWS, Severity::EMERGENCY,
                 "Helen's lost again!!!" );
// the entry will look like this:
// <56>1 2020-05-15T16:28:56.267113Z Angus - 4484 - - Helen's lost again!!!

// logs the given message and format strings to the file
// you can use format strings with the previous forms as well if you want to
file_logger.Log( "she has gotten lost %d times in the last %d days", 25, 3 );
// the entry will look like this:
// <14>1 2020-05-15T16:28:56.267128Z Angus - 4484 - - she has gotten lost 25 times in the last 3 days
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
// <14>1 2020-05-05T19:55:48.368156Z Angus cpp-demo-app 4484 up-to-code [subject name="baked alaska" result="not-up-to-code"] is it up to code?
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
  file_logger.SetDefaultAppName( NULL );
} catch( StumplessException *e ) {
  // will catch the exception
  if( e->GetErrorId() == ErrorId::ARGUMENT_EMPTY ) {
    std::cout << "the app name was NULL!" << std::endl;
  }
}
```


## Constants and Configuration
If you need to check information about the configuration of your build of the
library, you can check the same constants as before for them, though you will
need to include the C header to do so.

```cpp
#ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
  std::stdout << "logging to " << STUMPLESS_DEFAULT_SOCKET << " by default" << std::endl;
#endif
```

However, for some (but not all) constants there is a matching constant that puts
these constants into a namespace:

```cpp
// this check still has to use the C #define
#ifdef STUMPLESS_SOCKET_TARGETS_SUPPORTED
  // this one has a constant that can be used instead
  std::stdout << "logging to " << SocketTarget::DEFAULT_SOCKET << " by default" << std::endl;
#endif
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
