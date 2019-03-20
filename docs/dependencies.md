## Build Environment
In order to compile the library, a standard suite of build tools must be
available. These tools are standard for building C projects and are listed
below:
 * `cmake` for build targets and orchestration
 * a toolchain that can be used by cmake (gcc, for example)

## Testing
The test suite for the project is written using the Google Test suite. It will
be downloaded and built on the system automatically if the test suites are run,
but if the build fails for some reason then test suites will not be available.

More information on the Google Test framework may be found on the project
[Github page](https://github.com/google/googletest).

Of course if you would like to test the generated wrappers for languages other
than C then you will need the language environment installed in order to run the
tests.

The performance test suite for the project uses the Google Benchmark suite. Like
the Google Test suite, build targets will automatically download and build the
library if it is needed.

More information on the Google Benchmark framework may be found on the project
[Github page](https://github.com/google/benchmark).

## Documentation
General documentation of how functions behave is included as block comments in
the public header files. Documentation can also be generated using `doxygen`.
This is done using the `docs` build target, which will only be available if
doxygen is detected on the build system.

You can avoid downloading the repo and building the documentation by visiting
the project Github Pages website, (code is in the `gh-pages` branch of the
repository). This contains several of the documents in the `docs` folder of the
repository in a prettier format, and also uses `m.css` to generate a more
appealing and mobile-friendly doxygen page. More information on `m.css` can be
found on the [m.css project page](https://mcss.mosra.cz/).

## Development
If you wish to develop within the stumpless project itself, you will need a few
additional tools:
 * `perl` for some of the development scripts
 * `indent` to format sources according to the project standard

## Simplified Wrapper Interface Generator (SWIG)
The SWIG project is used to expose the functionality of Stumpless to languages
beyond normal C. The `swig` executable must be available in order to build any
other language support (for example, Python). SWIG is not required for the base
library build, so if support for other languages is not needed then it does not
need to be installed on the base system.

More information on the SWIG project may be found on the project
[Github page](https://github.com/swig/swig).
