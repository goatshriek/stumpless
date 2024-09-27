# Developing Stumpless
If you're going to work on the library itself, here are some helpful tips that
will make the experience a little smoother and faster.


## Getting Started
Stumpless is configured using the popular [CMake](https://cmake.org/) build
platform. In order to build it from the source you will need this tool
available, as well as any of a number of supported build systems.
[GNU Make](https://www.gnu.org/software/make/) is one of the most well-known
ones, and many examples you will find online use it. If you prefer to use
something else, there is plenty of support for CMake in other build systems.
For example, Visual Studio has CMake support built in so that you can build
targets in a CMake project easily within the IDE itself.

The `CMakeLists.txt` file contains the build specification for stumpless, and is
worth browsing through if you are curious about where configuration checks,
source and test files, and other build targets are specified.

There are a number of other dependencies for working on stumpless, but they are
less noteworth as you may not find yourself interacting with them. For example,
the Google Test and Benchmark libraries are needed, but they are downloaded and
built dynamically during the build process, so you do not need to worry about
providing them. Ruby is also used for some development and testing scripts, but
the basic builds and tests will succeed without it. For a more detailed rundown
of the dependencies you might encounter, check out the
[dependencies documentation](dependencies.md).

A typical development workflow involves an initial configuration and build,
followed by re-running the test suite after making some changes. This might
look like this:

```sh
# first, the initial setup:

# cloning the latest version of the source tree
git clone git@github.com:goatshriek/stumpless.git

# creating a new build directory
mkdir build
cd build

# configuring the new build
cmake ../stumpless

# after the above initial commands, a normal development cycle would be:

# update a few files with your favorite editor - here we use vim
vim ../stumpless/src/target.c

# build and run the test suite
# add a parallel argument to make things faster
# your processor's core count is a good starting place
cmake --build . --parallel 4 --target check

# for multi-config systems like Visual Studio, you'll also need to add a config
# argument to every build command to use the intended config
cmake --build . --parallel 4 --config x64-Debug --target check

# you can be more specific to your own environment if you'd like
# for example, if you're using make as your build system, you could just do:
# make -j 4 check

# if you want to build a single test, you can do this using the executable
# name, which for functionality tests is function-test-<name>
cmake --build . --target --parallel 4 function-test-target && ./function-test-target
```

More details about building the library are available in the
[INSTALL.md](../INSTALL.md) file. However, if you plan to be developing
stumpless itself it is recommended that you avoid using the `install` target
described there. Instead, simply work off of the version of the library in your
build folder, which will make it easier to work with different builds without
worrying about the installed library being used by accident.

A few other documents may be helpful for newcomers to glance through:
 * [Contributing Guidelines](CONTRIBUTING.md) If you have not read these yet,
   definitely do this soon. This document contains basic getting started info
   about different ways to contribute to stumpless, including a discussion of
   the branching scheme.
 * [docs/acronyms.md](acronyms.md) lists acronyms and initialisms used in the
   source of stumpless.
 * [docs/style.md](style.md) has a basic set of style guidelines to follow when
   working on the source code itself, including formatting and naming
   conventions the project follows.
 * [docs/test.md](test.md) describes the testing framework used in stumpless to
   write and run unit tests. This is important to understand if you're
   implementing any new functionality, which will need tests to confirm it works
   (and continues to work) correctly.
 * [docs/portability.md](portability.md) describes the framework used in
   stumpless to deal with differences between environments. If you are going
   to be working on something that may behave differently depending on the
   platform, or that may be missing on some, then this document holds
   important information for you. If you need to work with a function starting
   with `config_`, this is also a good indication you should read this doc.
 * [docs/benchmark.md](benchmark.md) has a detailed walkthrough of the
   performance testing framework set up in stumpless. If you're looking to
   make a performance improvement that will otherwise be transparent, this
   document describes the steps for this in detail with a full example.
 * [docs/localization.md](localization.md) describes how localization is
   implemented in detail and how to add new locales.
 * [docs/thread_safety.md](thread_safety.md) describes the thread safety
   implementation approach. Be sure that you follow the principles outlined
   here for any new functionality you implement.


## Error Handling
Stumpless has a framework for handling errors that happen at runtime. If you
are writing new functionality or extending something that already exists
then you will need to make sure that this framework is used whenever an
operation stops prematurely after encountering a problem.

All possible errors are specified in `stumpless/error.h` as part of the
`STUMPLESS_FOREACH_ERROR` macro function. This function lists all possible
errors and their integral id values, along with their documentation. If you
need to add a new error, it will get added to the end of this list (_not_
in alphabetical order) with the next available integer assigned as the id.

Each error has an internal `raise` function associated with it, declared in
`include/private/error.h` and defined in `src/error.c`. These functions set
the stumpless error id and error messages, and are intended to keep error
handling in stumpless readable and expressive. If you need to add a new error,
you will need to implement one of these to raise it as well.

For example, if a public function detects that a provided index is out of
bounds, then `raise_index_out_of_bounds` should be called with a localized
string describing the error, something like
`L10N_INVALID_INDEX_ERROR_MESSAGE( "element" )`, and the invalid index that
was passed in. This is a common pattern that can be seen throughout the
library code.

All error messages must be localized so that they can be understood by those
who will troubleshoot them. More information about handling localization can
be found in the [localization documentation](localization.md).

Often `raise` functions include information to help with troubleshooting. The
`raise_index_out_of_bounds` is a good example of this: in addition to a string
describing the invalid access it also takes the index that was out of bounds.
This is then made available in the resulting error to the user as the `code`
of the struct, along with a localized string description of what the value is in
`code_type`. The code of an error can be different across errors and even in
the same error when thrown from a different context.

Note that if you are calling another internal function and checking its result
for an error, you do not need to raise an error if this function already does
so. A good example of this is the memory allocation function `alloc_mem` which
will raise the appropriate error if it encounters a problem. Functions that
detect a failure of `alloc_mem` can simply return, without needing to raise an
error of their own first (since this would overwrite the original error).

Any public function must clear the error if there was no issue. This is so that
a user can tell if their last call succeeded by checking for the presence of an
error. Most public functions do this by calling `clear_error` directly before
returning from their non-error path, which handles this cleanup. Some do not
explicitly call `clear_error`, but instead rely on a call to another public
function to clear it for them if it succeeds. The only functions that do not
need to clear the error code are destructors and any error handling functions.

There is error handling code everywhere, but if you want a singular place to
look we recommend `stumpless_set_entry_param_value_by_index` in `src/entry.c`.
This function demonstrates how to detect errors in parameters and internal
function calls, call the appropriate `raise` functions when needed, and simply
return when the error comes from a different function.

Errors raised in stumpless can be accessed by the various error handling
functions provided for the user. Some of the common useful ones are:
 * `stumpless_get_error` gets the current error struct if there was an error on
   the last call
 * `stumpless_has_error` is true if the last call failed, false if it succeeded
 * `stumpless_perror` prints the current error if there is one


## Adding new functions
If you're adding a new function to stumpless, here are a few notes that will
help you along the way.

First, always make sure that you have documented your function, especially if it
is public facing. Stumpless uses [doxygen](https://www.doxygen.nl/index.html) to
generate its documentation from the header files. You can use the `docs` build
target to generate them, provided that doxygen was installed when you ran cmake.
Be sure to include an `@since` tag with the current version (the project version
at the top of `CMakeLists.txt`) so that when it was introduced is clear.

As you look at other functions, you will see that each function documents its
thread and async safety attributes in addition to its functionality. There is
more detail about this in the [thread safety documentation](thread_safety.md),
as well as the tools that are available to you to implement thread safety. While
async safety and async cancellation safety are optional, you _must_ make your
implementation thread safe. Look at other functions as examples, and don't be
afraid to ask for help on the project
[Gitter](https://gitter.im/stumpless/community) if you get stuck.

If your function is public facing, be sure to use the
`STUMPLESS_PUBLIC_FUNCTION` macro before its declaration to ensure that it is
included in the resulting library. If you forget to do this, you'll see errors
about undefined references when trying to use the library, for example during
tests.

In order to support being built as a DLL, stumpless has a `.def` file at
`src/windows/stumpless.def` in addition to the public function macro. If you
are adding a new public function to stumpless, you will need to make sure to
add it to the `.def` file so that the DLL will include it. Failing to do so
will result in tests failing on Windows builds with a note that your new
function is not defined. The Windows CI builds typically catch this issue.

Finally, be sure that you've added your new function to the appropriate header
check tool YAML file. To find out what that is, see the next section below!


## Header Checks
Stumpless uses a custom tool to make sure that all required headers are included
in a source file without any extras. The tool is called `check_headers` and is
stored in the `tools/check_headers` folder. You can run this manually if you
wish, by simply executing the script and passing it your source file (or files)
as parameters. You will need Ruby to run it. It is also run during Github
Actions builds, so you can wait for it to run there instead of doing it
yourself. For a one-liner command to catch issues, you can run the tool like
this:

```sh
tools/check_headers/check_headers.rb "src/**/*.c" "include/**/*.h*" "test/**/*.cpp"
```

However, if you have added a new function and you see build jobs failing in the
Check Headers stage claiming that an include file is unnecessary, then you
probably need to add your function to the manifest that powers it. There are a
few simple YAML files named `tools/check_headers/stumpless.yml` and
`tools/check_headers/stumpless_private.yml` with entries for each function. The
first has functions and symbols that are publicly provided by the library, and
the second has functions and symbols that are only used internally. Adding your
function and the associated header it is declared in to the correct manifest
will resolve this error as the tool will now know why the include is required.


## Continuous Integration Tools
Stumpless uses a number of CI tools to test builds and monitor code coverage
and quality. These tools each have badges in the project
[README](../README.md) that link to their respective pages.

[Github Actions](https://github.com/goatshriek/stumpless/actions) are used to
build the library in a variety of environments and with a variety of build
options. They ensure that changes are portable and that no tests are failing.
These must be passing on a change before it will be merged to the library. The
[build](https://github.com/goatshriek/stumpless/actions?query=workflow%3Abuild)
workflow runs these.

[Codecov](https://codecov.io/gh/goatshriek/stumpless) provides a way to
review and analyze code coverage from the test suite. It is fed by the Github
Actions builds, and will check pull requests for diff and total coverage. In
some cases this gate may be failing and code will still be merged, but this is
only in situations where coverage is not reasonably obtainable. For example if
the only way to cover a failure branch is a very specific chain of memory or
system call failures, then the coverage requirement may be relaxed. See the
[testing](test.md) documentation for more information on test coverage and
how to check this locally before opening a pull request to trigger Codecov.

[Sonarcloud](https://sonarcloud.io/dashboard?id=stumpless) provides code quality
reviews and static analysis. Changes should avoid introducing any new issues in
Sonarcloud. Changes that do introduce new issues will likely not be accepted,
unless it can be shown that they are false positives. Unfortunately due to
limitations with this tool it will likely not run for pull requests from forks
of the project, so if you don't see an analysis of your requests this is likely
the reason. Requests will _not_ be rejected simply because they do not have this
scan (since the CodeQL analysis will still run) so this is no reason to worry.
But if you notice that a previous change (yours or someone else's) has
introduced an issue, please consider submitting a fix.

[CodeQL](https://github.com/goatshriek/stumpless/security/code-scanning) is a
github tool that provides static code scanning services. This service is similar
to the Sonarcloud analysis and is used in the same manner; changes that
introduce new issues will likely not be accepted. Fortunately this service will
be run on requests from forks of the project (unlike Sonarcloud), and as such
there is no risk of finding out an issue has been introduced after the fact.

If you are making a documentation change or other update that won't affect the
output of any of these tools, consider temporarily removing the
`.github/workflows/build.yml` file from the project while you work on it, and
adding it back before creating a pull request. This conserves build resources
and may allow your pull request to pass its checks faster.


## Caching Google Test and Benchmark
If you are going to be repeatedly building the library from scratch, for example
to ensure nothing is cached between builds or to try different configurations,
it will quickly become tedious to wait for the Google Test and/or Benchmark
libraries to download and build each time as well. As an alternative, you can
put a build of the libraries in some other location and simply tell the build
process to use those instead using the `GTEST_PATH` and `BENCHMARK_PATH` build
parameters.

You could download and build the library yourself, which may be the best course
of action if you plan to re-use the build for other projects. If you do this,
you just need to make sure that the correct libraries (in the case of gtest,
`gtest`, `gtest_main`, and `gmock`) and headers (`gtest/gtest.h` and
`gmock/gmock.h`) are found at the given path. If they are, then they will be
used and gtest will not be downloaded and built again. If _any_ of them are
missing though, a fresh copy will be downloaded and used anyway, so make sure
everything is there!

Since downloading and building can be a pain, especially multiple times for 
different build types, stumpless provides two build targets that will export
built libraries for you to the path. This way, all you need to do is build
stumpless as you would normally, and then use the `export-gtest` and/or
`export-benchmark` targets to populate the path for future builds. This would
look something like this (if you're using a `make` build system):

```sh
# from the directory above your repo
# just adjust the paths accordingly if you build somewhere else

# first we set up our folders to hold the libraries
mkdir gtest
mkdir benchmark

# next, we build the library as normal
mkdir biuld
cd build
cmake -DGTEST_PATH=../gtest -DBENCHMARK_PATH=../benchmark ../stumpless

# in this build Google Test and Benchmark will be downloaded and built since
# the paths we provided don't have anything in them
cmake --build . --target check
cmake --build . --target bench

# to build the libraries and put them in the path for future builds, we just
# execute these two targets:
cmake --build . --target export-gtest
cmake --build . --target export-benchmark

# these list commands show that the folders are now populated!
ls ../gtest
ls ../benchmark

# next time, you can use the exact same cmake command to use the previously
# built versions instead of downloading fresh

# if you want to try it out immediately:
cd ..

# clear out the previous build
rm -rf build

# and redo it!
mkdir biuld
cd build
cmake -DGTEST_PATH=../gtest -DBENCHMARK_PATH=../benchmark ../stumpless

# running the test suite or benchmark suite won't download the libraries this
# time - it will go straight to compiling the tests and linking them against
# the libraries in the PATH variables
cmake --build . --target check
cmake --build . --target bench
```


## Common Mistakes
The project team sees a few types of issues happen more commonly than others.
Here are a few tips that will help you get your contribution accepted faster by
avoiding some back-and-forth change requests.
 * **Forgetting to run header checks**
   By far, missing headers are the most common cause of CI failure in new
   contributions. Taking the extra time to run the
   [header checks](#header-checks) locally before you open a pull request can
   make the difference between a pull request being accepted and changes being
   requested.
 * **Force Pushing**
   It's common (and expected) for changes to be requested on contributions. When
   this happens, the best thing you can do is address these in a single commit
   and push the new commit to your pull request branch. This makes it easy to
   follow what changes were made, and speeds up the review process. While it
   might seem cleaner to amend or squash your changes into a single new commit
   and force-push it, please don't do this! It means that the entire
   contribution must be reviewed again, and can make it harder to track comments
   on individual lines of the commit. Most contributions are squashed into a
   single commit when they are accepted, so never fear: the project team will
   make sure that the end result of your hard work will be clean and neat!
