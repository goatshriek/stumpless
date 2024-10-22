# Portability in Stumpless
Stumpless is built to be compact and efficient, making it an excellent option in
embedded scenarios. This means that portability is a key factor of the design:
in order to work in constrained environments it must be able to handle a variety
of situations that don't arise in standard desktop or server environments.

Stumpless follows a few key design principles in order to be feature-rich and
easy to maintain while remaining as portable as possible:
 * **No `#ifdef` directives are allowed in source (`.c`) files.**
   Source code with preprocesor directives that add, alter, or remove
   functionality are easy to add, but scatter configuration-specific behavior
   and build environment dependencies across source files, and make it harder to
   understand program flow. These snippets should instead be factored into
   separate config source modules that keep portability handling code away from
   other logic and easy to find, understand, and modify.
 * **Have default behavior to handle missing dependencies.**
   This doesn't mean that you need to re-implement other libraries, but you
   should provide some sane fallback behavior that will function in their
   absence. This can be as simple as raising a target unsupported error or
   filling in an unknown value with a reasonable guess.


# Conventions
Stumpless has conventions for handling dependencies in a portable way, which can
be used whenever the need for configuration-specific behavior arises. This is
based on the `config` family of headers, sources, and symbols.


## Config Headers and Wrappers
Great care is taken to keep the impacts of configuration separate from other
functionality within the library. There are two headers where information on
the build is located: one for the information that describes features and other
variables that affect functionality, and another for factors that only affect
internal code.

The `stumpless/config.h` header is installed along with the library, and can
be referenced from code that includes it or `stumpless.h`. For example, the
version of stumpless is found in this header, `STUMPLESS_VERSION` for a string
literal and `STUMPLESS_MAJOR_VERSION`, `STUMPLESS_MINOR_VERSION`, and
`STUMPLESS_PATCH_VERSION` with integer values for each portion. Whether or not
certain target types are support is also available, for example if the
`STUMPLESS_SOCKET_TARGETS_SUPPORTED` symbol is defined, then Unix sockets are
available in this build. A complete list of the symbols in this header can be
found in the
[documentation](https://goatshriek.github.io/stumpless/docs/c/latest/).

However, this header does not include information needed to make some internal
code decisions. For example, the public header will not indicate whether a
particular header was available during the system build. For this type of
information there is a second configuration file, `private/config.h`, which
gives details about headers and symbols that are available in the build
environment. One such case is the `HAVE_WINSOCK2_H` symbol, which is defined
when the build system has `winsock2.h` available.

These two headers can be used whenever this information is needed in the source
code of Stumpless itself. But, to adhere to the first principle outlined above,
they are only used in header files to conditionally define other symbols that
can then be referenced in source code without needing to worry about `#ifdef`
symbols or use other preprocessor directives. In fact, there is another
established convention for how to do this: the wrapper headers and `config`
family of functions.


## The Wrapper Header and `config` Functions
One header in particular in the private include file list deserves special
mention: `private/config/wrapper.h`. This file contains definitions of a number
of functions and symbols all starting with `config_` that wrap configuration
specific functionality. This header is then all that library code needs to
include in order to use this functionality, without needing to check all
possible configuration combinations.

This is easier to understand with an example. Let's look at the code used to
determine whether Microsoft's "safe" version of the `fopen` library call should
be used, or just the regular `fopen` call provided by Linux systems. The snippet
of the wrapper header that handles this looks like this:

```c
#ifdef HAVE_FOPEN_S
#  include "private/config/have_fopen_s.h"
#  define config_fopen fopen_s_fopen
#else
#  include <stdio.h>
#  define config_fopen fopen
#endif
```

The `HAVE_FOPEN_S` symbol is defined in the `private/config.h` header, and is
defined on systems where the symbol is detected during CMake's execution. If the
symbol is found, the configuration header with the declaration of the function
that will use the `fopen_s` function is included, and `config_fopen` is defined
to be an alias for this function. If it isn't, `config_fopen` is instead simply
defined as an alias for the `fopen` library call. Any library code that needs
`fopen` functionality will then simply use `config_fopen` without needing to
know which underlying call is being provided.

The header files and functions within follow a naming convention to make it
clear which configuration element they correlate to.

 * `have_xxx_.h` designates that the header or function named `xxx` is assumed
   to be present in the code within it. Functions in headers named this way
   always start with a prefix of `xxx_` where xxx is the name of the header or
   function that is used.
 * Headers of the form `no_xxx.h` are the opposite of the previous case: they
   assume that the header or function is _not_ available for use. These
   functions are named with a prefix of `no_xxx_`, again where xxx is the name
   of the symbol that is available.
 * `xxx_supported.h` headers contain code that assumes that there is platform
   and/or library support for a given feature. For example, abstract sockets
   can only be used on Linux systems. Another case are network targets, which
   may be disabled in some builds. Functions in these headers start with a
   prefix of `xxx_` with xxx substituted with the feature name. Note that
   sometimes this prefix is the entire name of the function (without the
   trailing underscore of course), if the supported feature is the function
   itself.
 * Predictably, `xxx_unsupported.h` headers contain code to deal with the case
   where a feature is not available. Functions in these headers start with the
   prefix of `no_xxx_` with xxx filled in as the feature name.

For all of these functions, the prefix designated is replaced with `config_` by
the wrapper that designates the chosen one. Functions that don't have or need
a `config_` wrapper function do not necessarily follow this naming convention.
Public functions fall into this category, as they start with a prefix of
`stumpless_` to conform to the overall library standard, and are not wrapped
by any config header.

The config header and source files may not necessarily live in the config
directory if there is a better place. The most prominent example of this are
target types that may not be available in a given configuration. These source
files exist in the target directory along with the other target-related files
rather than in the config directory.


## Other Wrapper Headers
There are other wrapper headers that hide configuration-related details beyond
`private/config/wrapper.h`. The most prominent of these is
`private/config/wrapper/locale.h` which includes the correct set of localized
string definitions based on the locale chosen during the build configuration.
Another example is `private/windows_wrapper.h` which includes Windows-related
header files only if they are found and in the correct order.


## Fallback Behavior
Stumpless is designed to work in a variety of environments, and can typically
find a way to accomplish what it needs to if there is a possibility. However,
in some environments the necessary capabilities are simply missing, and the
library must fail in the most friendly way possible.

In these scenarios, the `fallback` family of config functions comes into play.
These should be defined whenever there is a possibility that some configuration
option is not available, but stumpless should still operate. This keeps
configuration-specific behavior in easy to find locations instead of requiring
the platform independent library code to implement its own fallback code.

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
fallback function will not be needed most of the time. However it is possible
that neither is available, as has been seen on some Cygwin builds (see Github
issue [#60](https://github.com/goatshriek/stumpless/issues/60) for more info).
For cases like these, the fallback function is used, which has a simple and
configuration-independent implementation:

```c
size_t
fallback_getpagesize( void ) {
  return 4096;
}

```

Fallback functions must be completely independent of any configuration-based
assumptions, and should make sense in the context they intend to be used. This
example uses a fallback memory page size of 4 KiB, a common size and reasonable
guess.

Fallback functions are free to raise errors if there is no natural "default"
behavior, but this should only be done in cases where the other configuration
options might also raise errors. Extra error handling should not be introduced
solely for the sake of avoiding extra work in the fallback option.
