# C++ Bindings

While stumpless is written in C to keep it as lightweight and simple as
possible, it has been extended to C++ so that it can be used from the higher
level language with the same performance benefits.

These bindings go beyond simply calling C code from C++, however; the entire
library is exposed via an object-oriented API documented in full
(here)[https://goatshriek.github.io/stumpless/cpp/]. While the concepts of the
library are the same in this extension, the object oriented extensions offer
some useful advantages over the simple functional capabilities of C.

The C++ bindings are created using
(Wrapture)[https://goatshriek.github.io/wrapture/].

## Target Classes

Targets can be created and logged to using the various target classes that match
target types from the C library. The constructors take the same parameters as
the matching open target function in the C library. This example shows how to
open a file target.

```cpp
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

Error checking is not as cumbersome as it is in the C library; an exceptions is
thrown whenever an error is detected in the underlying function. This allows
code to simply use try/catch blocks rather than check each return value.

```cpp
try {
  file_logger.AddMessage( NULL );
} catch( StumplessException *e ) {
  // will catch an exception (ArgumentEmpty)
}
```


