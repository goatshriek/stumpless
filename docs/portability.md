# Portability in Stumpless

Stumpless is built to be compact and efficient, which makes it an excellent
option in embedded scenarios. However, this means that portability is equally
important to the design, as in order to work in constrained environments it must
be able to handle a variety of situations that don't arise in standard desktop
or server environments.

Stumpless follows a few key principles in its design in order to be feature-rich
and easy to maintain while remaining as portable as possible:
 * **no `#ifdef` directives in source files**
   Source code with preprocesor directives that add, alter, or remove
   functionality are easy to add, but hide configuration-specific behavior and
   build environment dependencies across source code, and can make it harder to
   understand program flow. These snippets should instead be factored into
   separate config source modules that keep portability handling code away from
   other logic and easy to find, understand, and modify.
 * **have default behavior that handle missing dependencies**
   This doesn't mean that you need to re-implement other libraries, but you
   should provide some sane fallback behavior that will function in their
   absence. This can be as simple as raising a target unsupported error or
   filling in an unknown value with a reasonable guess.

# Conventions

Stumpless has conventions for handling dependencies in a portable way, which can
be used whenever the need for configuration-specific behavior arises. This is
based on the `config` family of headers, sources, and symbols.

## Config Headers and Wrappers

_describe the include/private/config and include/stumpless/config headers_

## Wrapper Headers and `#define`s

_describe the family of config functions and source files_

## Fallback Behavior

Stumpless is designed to work in a variety of environments, and can typically
find a way to accomplish what it needs to if there is a possibility. However,
in some environments the necessary capabilities are simply missing, and the
library must fail in the most friendly way possible.

In these scenarios, the `fallback` family of config functions should be used.
These should be defined whenever there is a possibility that some configuration
option is not available. This keeps configuration-specific behavior in easy to
find locations instead of requiring the platform independent library cod to
implement its own fallback code.

A good example of this convention can be found in the call to get the memory
page size of the system, which is used to make the slab caches used for some of
the internal data structures more efficient. This call is defined in the wrapper
header as described above, like this:

```c
#ifdef HAVE_UNISTD_H
#  include "private/config/have_unistd.h"
#  define config_getpagesize unistd_getpagesize
#elif HAVE_WINDOWS_H
#  include "private/config/have_windows.h"
#  define config_getpagesize windows_getpagesize
#else
#  include "private/config/fallback.h"
#  define config_getpagesize fallback_getpagesize
#endif
```

Most systems will have either `unistd.h` or `windows.h` available, so the
fallback function will not be needed. However it is possible that neither is
available, as has been seen on some Cygwin builds (see Github issue #60 for
more info). For cases like these, the fallback function is used, which has a
very simple and configuration-independent implementation:

```c
size_t
fallback_getpagesize( void ) {
  return 4096;
}

```

Fallback functions must be completely independent of any configuration-based
assumptions, and should make sense in the context they intend to be used. This
example uses a page size of 4 KiB, a common page size.

Fallback functions can throw errors if there is no natural "default" behavior,
but this should only be done in cases where the other configuration options are
also able to raise errors. Extra error handling should not be introduced simply
for the sake of avoiding extra work in the fallback option.
