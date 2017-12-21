#include <benchmark/benchmark.h>
#include <stumpless.h>

static void string_bm(benchmark::State& state){
  for(auto _ : state){
    stumpless("testing");
  }
}

BENCHMARK(string_bm);

BENCHMARK_MAIN();
