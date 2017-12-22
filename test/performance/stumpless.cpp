#include <benchmark/benchmark.h>
#include <stumpless.h>

static void StumplessString(benchmark::State& state){
  for(auto _ : state){
    stumpless("testing");
  }
}

BENCHMARK(StumplessString);

BENCHMARK_MAIN();
