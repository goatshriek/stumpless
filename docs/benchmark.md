# Benchmark Testing with Stumpless

High performance and efficiency is a core pillar of stumpless design, and as
such a benchmarking framework is available to assist with this. This framework
uses the [Google Benchmark](https://github.com/google/benchmark) library to
measure execution time and other efficiency characteristics.

Performance tests are named `performance-test-<item>` for various pieces of the
library. You can use the `bench` target to build and execute all performance
tests at once, or just the name of the executable if you only want to measure
a single module.

Performance tests are NOT intended to be an absolute measurement of the
performance of a function or the library as a whole. They are only useful for
measuring the relative performance between two versions of code on the same
machine in the same environment. This is why you will not see performance
test results posted in any documentation. The results are only useful when
compared to one another, typically during development of some change.

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

  element = stumpless_new_element( "copy-element-perf" );
  stumpless_add_new_param( element, "param-1", "value-1" );
  stumpless_add_new_param( element, "param-2", "value-2" );

  for(auto _ : state){
    result = stumpless_copy_element( element );
    if( result <= 0 ) {
      state.SkipWithError( "could not send an entry to the target" );
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

# sample output

```

If you got an error about the library being built as DEBUG, make sure that you
pass the `-DCMAKE_BUILD_TYPE=Release` argument to cmake when you are building
stumpless.

This is a real example of an actual improvement made to stumpless, so if you
want to see any of the tests or code in detail you can simply look at them in
the source tree.
