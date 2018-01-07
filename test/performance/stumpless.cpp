#include <benchmark/benchmark.h>
#include <stumpless/target/socket.h>

static void StumplessString(benchmark::State& state){
  for(auto _ : state){
    stumpless("testing");
  }
}

BENCHMARK(StumplessString);

BENCHMARK_MAIN();
