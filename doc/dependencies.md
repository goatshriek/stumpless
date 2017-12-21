## Build Environment
In order to compile the library, a standard suite of build tools must be
available. These tools are standard for building a C project and are listed
below:
 * `make` for build targets and orchestration
 * `gcc` for compilation of C source code

## Testing
The test suite for the project is written using the Google Test suite. The
headers and library must be installed on the system in order for the test suites
to build and execute successfully.

More information on the Google Test framework may be found on the project
[Github page](https://github.com/google/googletest).

Of course if you would like to test the generated wrappers for languages other
than C then you will need the language environment installed in order to run the
tests.

The performance test suite for the project uses the Google Benchmark suite. The
headers and library must be installed on the system in order for the benchmarks
to build and run.

More information on the Google Benchmark framework may be found on the project
[Github page](https://github.com/google/benchmark).

## Documentation
The specification for the Syslogv2 protocol is in an XML file that can be used
to generate an RFC-styled document outlining the details. In order to generate
text, HTML, or other RFC output you will need to use the `xml2rfc` tool,

## Simplified Wrapper Interface Generator (SWIG)
The SWIG project is used to expose the functionality of Stumpless to languages
beyond normal C. The `swig` executable must be available in order to build any
other language support (for example, Python). SWIG is not required for the base
library build, so if support for other languages is not needed then it does not
need to be installed on the base system.

More information on the SWIG project may be found on the project
[Github page](https://github.com/swig/swig).
