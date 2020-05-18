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
parameters. The following examples are for `GTEST_PATH`, but the same principles
apply for `BENCHMARK_PATH` as well.

This snippet shows how to download a fresh copy of Google Test via the hash,
unzip it, and build it.

```sh
wget https://github.com/google/googletest/archive/6f5fd0d7199b9a19faa9f499ecc266e6ae0329e7.zip
unzip 6f5fd0d7199b9a19faa9f499ecc266e6ae0329e7.zip
mv googletest-6f5fd0d7199b9a19faa9f499ecc266e6ae0329e7/ gtest/
cd gtest
cmake -Dgtest_force_shared_crt=ON -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release .
```

Note that this uses a few flags that mirror what Stumpless uses to build of a
freshly downloaded copy. The build type should match what you use in your own
builds of Stumpless, so if you need one Release and one for Debug, simply repeat
this process with two directories. `gtest` and `gtestd`, perhaps?

When you build Stumpless itself, simply pass in the `GTEST_PATH` parameter,
like so:

```sh
mkdir build && cd build
cmake -DGTEST_PATH=/path/to/built/gtest ../
```

As long as the correct libraries (`gtest`, `gtest_main`, and `gmock`) and
headers (`gtest/gtest.h` and `gmock/gmock.h`) are found at the given path, then
they will be used and gtest will not be downloaded and built again. If _any_ of
them are missing though, a fresh copy will be downloaded and used anyway, so
make sure everything is there!

If you don't want to download a version and build it yourself, you can copy the
result of a normal build out into a separate directory and use it going forward.
An example of this strategy would look like this:

```sh
mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..
make gtest # download and build gtest

# copy the built libraries
cp -r gtest/src/gtest-build/ ../../gtestd

# copy the required headers
cp -r gtest/src/gtest/googlemock/include/ ../../gtestd/googlemock/include/
cp -r gtest/src/gtest/googletest/include/ ../../gtestd/googletest/include/

# then, on your next build, you could do this instead:
mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DGTEST_PATH=../../gtestd ..
```
