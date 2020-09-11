## Localization
Stumpless implements a simple framework to support different languages for
human-readable output, such as error messages. This implementation is based on
the use of header files with definitions for the strings based on a specific
locale. A simple wrapper header, `private/config/locale/wrapper.h`, can then
be included by source files. This wrapper header chooses the correct locale
header based on the build configuration.

## Locale Headers
Locale headers are located in `private/config/locale` and are named after the
locale that they hold using the IETF Language Tag format defined in
[RFC 5646](https://tools.ietf.org/html/rfc5646). For example, the United
States English locale is in `private/config/locale/en-us.h`.

These header files all define the same set of preprocessor symbols, each
beginning with the prefix `L10N_`. These are string constants that will be
placed into the source code during compilation to customize the library for
the desired locale.

Some of these symbols may be functions that take string constants as
parameters and insert these into the appropriate location. An example of this
is the `L10N_NULL_ARG_ERROR_MESSAGE` function, which takes the name of the
argument that was null as a parameter so that it can insert it into the error
message that it generates. Different locales may use this value in different
places, or not at all.

## Defining a New Locale
Adding a new locale to the library only requires the addition of the new header
file and making sure that it can be used during build configuration. Adding
the header is straightforward: just copy any already existing header (this will
be easier if you understand the language of the original) and then change the
defined symbols to reflect your new locale. Be sure that the name of the new
header is a valid IETF Language Tag.
