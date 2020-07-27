# Developing Stumpless

If you're going to work on the library itself, here are some helpful tips that
will make the experience a little smoother and faster.

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
make check
make bench

# to build the libraries and put them in the path for future builds, we just
# execute these two targets:
make export-gtest
make export-benchmark

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
make check
make bench
```

## Other development notes

For a detailed discussion of the performance testing framework used to gauge
the speed and efficiency of various calls, check out the
[benchmark](https://github.com/goatshriek/stumpless/blob/latest/docs/benchmark.md)
documentation for the basic strategy and a full walkthrough of an example.
