# Stumpless C++

The Stumpless library for C++ lightly wraps the base C library with an object
model, and is intended to make logging feel more natural in C++. Of course,
users can also choose to use the C library directly from their code rather than
use the expanded C++ library. The library is generated using
[Wrapture](https://github.com/goatshriek/wrapture) with a collection of specs
defined in the `wrapture` directory of the source for Stumpless.

## Basic Usage
The following snippets show some usage patterns specific to C++. If you're
looking for basic usage of the C library, check out the main project
[readme](https://github.com/goatshriek/stumpless/blob/latest/README.md) for a
quick rundown of what you can do.

Targets and entries can be created by instantiating the appropriate class, just
as you might expect:

```cpp
FileTarget myLogFile( "logfile.log",
                      STUMPLESS_OPTION_NONE,
                      Facility::USER );

Entry processStarting( Facility::USER,
                       Severity::INFO,
                       "my-application",
                       "process-start-msgid",
                       "A new process is starting." );
```

And then logged to by using the `Log` function of the target:

```cpp
myLogFile.Log( processStarting );
```

The C++ library also puts functions and constants into a namespace and raises
exceptions when errors are encountered. For more information and examples on
what is possible, check out the
[documentation](https://goatshriek.github.io/stumpless/docs/cpp/latest) for the C++
bindings and the
[example code](https://goatshriek.github.io/stumpless/examples/cpp.html) in
`docs/examples/cpp`.
