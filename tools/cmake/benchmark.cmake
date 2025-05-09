FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/299e5928955cc62af9968370293b916f5130916f.zip # v1.9.3
  FIND_PACKAGE_ARGS NAMES benchmark
)

FetchContent_MakeAvailable(googlebenchmark)
