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

Stumpless has a conventional way to handle dependencies in a portable way, which
can be used whenever the need for configuration-specific behavior arises. This
is based on the `config` family of headers, sources, and symbols.

## Config Headers and Wrappers

_describe the include/private/config and include/stumpless/config headers_

## Wrapper Headers and `#define`s

_describe the family of config functions and source files_

## Fallback Behavior

_describe the fallback convention_