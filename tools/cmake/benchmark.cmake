set(local_benchmark_binary_dir "${CMAKE_CURRENT_BINARY_DIR}/benchmark/src/benchmark-build")
set(local_benchmark_static_dir "${local_benchmark_binary_dir}/src")

if(MINGW OR CYGWIN OR NOT WIN32)
  set(local_benchmark_static "${local_benchmark_static_dir}/libbenchmark.a")
  set(local_benchmark_main_static "${local_benchmark_static_dir}/libbenchmark_main.a")
else()
  set(local_benchmark_static "${local_benchmark_static_dir}/benchmark.lib")
  set(local_benchmark_main_static "${local_benchmark_static_dir}/benchmark_main.lib")
endif()

set(local_benchmark_byproducts
  ${local_benchmark_static}
  ${local_benchmark_main_static}
)

ExternalProject_Add(benchmark
  URL https://github.com/google/benchmark/archive/df7c7ee1d37dda0fb597586b4624515166a778d0.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/benchmark
  CMAKE_ARGS -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_SH=${CMAKE_SH} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  INSTALL_COMMAND ""
  BUILD_BYPRODUCTS ${local_benchmark_byproducts}
)

set_target_properties(benchmark
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
)

ExternalProject_Get_Property(benchmark source_dir binary_dir)

add_library(libbenchmark IMPORTED STATIC GLOBAL)
add_dependencies(libbenchmark benchmark)

set_target_properties(libbenchmark PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  IMPORTED_LOCATION "${local_benchmark_static}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libbenchmarkmain IMPORTED STATIC GLOBAL)
add_dependencies(libbenchmarkmain benchmark)

set_target_properties(libbenchmarkmain PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  IMPORTED_LOCATION "${local_benchmark_main_static}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/include")
