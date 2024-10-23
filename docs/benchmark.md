# Benchmark Testing with Stumpless

High performance and efficiency is a core pillar of stumpless design, and as
such a benchmarking framework is available to assist with this. This framework
uses the [Google Benchmark](https://github.com/google/benchmark) library to
measure execution time and other efficiency characteristics.

Performance tests are named `performance-test-<item>` for various pieces of the
library. You can use the `bench` target to build and execute all performance
tests at once, or the name of the executable prefixed with `run-` if you only
want to run a single module. These targets write their results to both the
standard output as well as a json file in the `performance-output` directory of
the build location, which you can use with the `compare.py` tool from the
benchmark library. There is an example of using this tool in the walkthrough
below. Of course, you can also directly execute the test executable itself if
you want to set the parameters yourself. This is also demonstrated in the
walkthrough.

Performance tests are NOT intended to be an absolute measurement of the
performance of a function or the library as a whole. They are only useful for
measuring the relative performance between two versions of code on the same
machine in the same environment. This is why you will not see performance
test results posted in any documentation. The results are only useful when
compared to one another, typically during development of some change.

Benchmarks are run during Release CI builds, but should not be used as
indicators of performance for this exact reason. They are only included in the
CI process to make sure that they are not broken.

## Walkthrough: Improving `stumpless_copy_element`

Walking through a benchmarking improvement change from beginning to end
demonstrates all of these principles and how they are used to implement an
actual improvement to the library. Let's analyze an improvement to the
performance of `stumpless_copy_element` to do this.

An early version of `stumpless_copy_element` iterated through all of the
params in the element, adding them to the copy one by one. The code for this
looked like this snippet, which has been abbreviated to focus on the performance
of the code:

```c
// first create a new element
copy = stumpless_new_element( stumpless_get_element_name( element ) );

// then handle all of the parameters
for( i = 0; i < element->param_count; i++ ) {
  // copy the parameter
  param_copy = stumpless_copy_param( element->params[i] );

  // and then add it
  stumpless_add_param( copy, param_copy );
}
```

While it is logical and easy to follow, this method is inefficient because
`stumpless_add_param` reallocates the underlying array each time it is called.
This means that the same piece of memory could be reallocated several times in
a single call, increasing execution time and putting pressure on the memory
manager. Let's change it to instead allocate the memory up front.

Before we make any changes to the code itself, let's implement a benchmark test
to measure the performance of the code as is. Our test code looks like this:

```cpp
static void CopyElement(benchmark::State& state){
  struct stumpless_element *element;
  const struct stumpless_element *result;

  INIT_MEMORY_COUNTER( copy_element );
  stumpless_set_malloc( copy_element_memory_counter_malloc );
  stumpless_set_realloc( copy_element_memory_counter_realloc );
  stumpless_set_free( copy_element_memory_counter_free );

  element = create_entry();

  for(auto _ : state){
    result = stumpless_copy_element( element );
    if( result <= 0 ) {
      state.SkipWithError("the element copy failed");
    } else {
      stumpless_destroy_element_and_contents( result );
    }
  }

  stumpless_destroy_element_and_contents( element );

  state.counters["CallsToAlloc"] = ( double ) copy_element_memory_counter.malloc_count;
  state.counters["MemoryAllocated"] = ( double ) copy_element_memory_counter.alloc_total;
  state.counters["CallsToRealloc"] = ( double ) copy_element_memory_counter.realloc_count;
  state.counters["CallsToFree"] = ( double ) copy_element_memory_counter.free_count;
  state.counters["MemoryFreed"] = ( double ) copy_element_memory_counter.free_total;
}
```

We can run this specific test with the following command, which will build the
test if necessary and then execute it.

```sh
make performance-test-element && ./performance-test-element --benchmark_filter=CopyElement

# sample output:
# 2020-07-27T14:40:33-04:00
# Running ./performance-test-element
# Run on (8 X 1498 MHz CPU s)
# Load Average: 0.52, 0.58, 0.59
# ----------------------------------------------------------------------
# Benchmark            Time             CPU   Iterations UserCounters...
# ----------------------------------------------------------------------
# CopyElement        633 ns          628 ns      1120000 CallsToAlloc=8.96001M CallsToFree=10.08M CallsToRealloc=2.24M MemoryAllocated=181.44M MemoryFreed=181.44M
```

If you got an error about the library being built as DEBUG, make sure that you
pass the `-DCMAKE_BUILD_TYPE=Release` argument to cmake when you are building
stumpless.

Great! We have an idea of the speed of the library, as well as the number of
calls that are made to various memory allocation routines. Next, let's make our
fix to `stumpless_copy_element`.

```c
// we still create a new element the same way
copy = stumpless_new_element( stumpless_get_element_name( element ) );

// now we manually allocate the array just once
copy->params = alloc_mem( element->param_count * sizeof( param_copy ) );

for( i = 0; i < element->param_count; i++ ) {
  param_copy = stumpless_copy_param( element->params[i] );

  // and then populate it with each copy
  copy->params[i] = param_copy;
  copy->param_count++;
}
```

Now that we've made this change, let's rebuild our performance test and run it!

```sh
make performance-test-element && ./performance-test-element --benchmark_filter=CopyElement

# sample output:
# 2020-07-27T14:45:05-04:00
# Running ./performance-test-element
# Run on (8 X 1498 MHz CPU s)
# Load Average: 0.52, 0.58, 0.59
# ----------------------------------------------------------------------
# Benchmark            Time             CPU   Iterations UserCounters...
# ----------------------------------------------------------------------
# CopyElement        542 ns          547 ns      1000000 CallsToAlloc=9.00001M CallsToFree=9.00001M CallsToRealloc=2 MemoryAllocated=162M MemoryFreed=162M
```

We immediately see that the number of calls to `realloc` dropped significantly,
and is clearly no longer tied to calls to CopyElement. The execution time is
also lower, so we can declare success!

If you run a number of benchmarks at once and want to compare all of the
results, manually comparing this output can get difficult. Google Benchmark
provides a python script in the `tools` folder that makes this much easier.
In a normal build tree this is in `benchmark/src/benchmark/tools/`, and it is
exported by the `export-benchmark` build target if you are using
`BENCHMARK_PATH` (see the
[development notes](https://github.com/goatshriek/stumpless/blob/latest/docs/development.md)
for details on this option).

Running the script is straightforward, as you simply need to export JSON output
from each benchmark execution and then compare the results. If you want more
detail, check out the full documentation
[here](https://github.com/google/benchmark/blob/master/docs/tools.md).

For this example, we'll assume that you've built stumpless twice, one based on
the `latest` branch in folder `build-latest`, and another based on a branch with
your changes in folder `build-element-copy`. The general flow is to build the
test, run it once with each library version, and then compare the results.

```sh
# in folder build-element-copy
make performance-test-element

# run the test with our changes
./performance-test-element --benchmark_filter=CopyElement --benchmark_out=new.json --benchmark_out_format=json

# and then swap out the library and run it again
rm libstumpless.so.2.0.0
cp ../build-latest/libstumpless.so.2.0.0 ./
./performance-test-element --benchmark_filter=CopyElement --benchmark_out=old.json --benchmark_out_format=json

# compare results with the Google Benchmark tool
cd benchmark/src/benchmark/tools
python3 compare.py benchmarks ../../../../old.json ../../../../new.json

# sample output:
# Comparing old.json to new.json
# Benchmark                     Time             CPU      Time Old      Time New       CPU Old       CPU New
# ----------------------------------------------------------------------------------------------------------
# CopyElement                -0.1791         -0.1747           663           545           663           547
```

This execution tells us that we have reduced the execution time of the function
by just over 17 percent. Note that the numbers are slightly different from our
previous executions, but that the general trend still holds true. This relative
nature is exactly why benchmark test results are only relevant when executed on
the same machine in the same environment, under the same load if at all 
possible.

You can also pass the compare script two performance test executables, if you
have them, and bypass the json output steps. However, if you implemented a new
benchmark for your change then the latest build tree may not have a test, and
you can simply rely on the above method.

This is a real example of an actual improvement made to stumpless, so if you
want to see any of the tests or code in detail you can simply look at them in
the source tree.
