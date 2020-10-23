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
message. Different locales may use this value in different places, or not at
all.


## Adding New Strings
If you are making a change that requires a new error message or other string
that needs to be localized, you will need to add it to all defined locales. It
is _required_ that the `en-us` locale include a meaningful definition of the
symbol. Others may be added as a placeholder value, for later translation by
someone with the necessary knowledge. The conventional placeholder for this
situation is a string containing the name of the symbol, minus the `L10N_`
prefix and with spaces instead of underscores. For example, for the
`L10N_INVALID_SEVERITY_ERROR_MESSAGE` symbol this would be
`"INVALID SEVERITY ERROR MESSAGE"`.


## Defining a New Locale
Adding a new locale to the library only requires the addition of the new header
file and making sure that it can be used during build configuration. Adding
the header is straightforward: just copy any already existing header (this will
be easier if you understand the language of the original) and then change the
defined symbols to reflect your new locale. Be sure that the name of the new
header is a valid IETF Language Tag in all lowercase letters.

After adding the header itself, you will need to tie it in to the build system
by updating the `CMakeList.txt` file, the `include/private/config.h.in`
header template, and the locale wrapper
`include/private/config/locale/wrapper.h`. In the CMake script, add an `elseif`
block to the chain of conditionals responsible for determining the locale (do a
search for `STUMPLESS_LANGUAGE` to quickly find this) following the pattern of
the others that are already there. Next, in the private config header template,
add a definition for the locale symbol for the new locale. This symbol should
be of the form `USE_LOCALE_XXX` where the last portion is the RFC 5646 language
tag in all caps with underscore separators. Again, reference the already defined
locales to see what this should look like. Finally, in the locale wrapper header
add an `#elseif` statement for the new locale symbol in the same order as it
appears in the CMake build script to include the new header.

The last step is to add new CI builds for the new locale to make sure that
there are no immediate problems and catch any future ones that arise. This is
done by updating the `.travis.yml` and `appveyor.yml` configuration files with
a build profile for the new language.

Updating the Travis CI build is simple: just copy the builds of a locale that
is already defined and change the name and variables to match the new one. Be
sure to add one for both Linux and Mac OS.

The Appveyor configuration requires a little more attention. You will need to
add an entry to the environment matrix first. However, since we only want to add
one more test build for this language, you'll also need to add a number of
exclusions for the build matrix. You can find examples of these in the exclusion
portion of the configuration for other languages.

Finally, add a flag for the new locale to the project README (in the Key
Features section) to show off your hard work to everyone else!
