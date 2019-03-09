set(my_benchmark_binary_dir "${CMAKE_CURRENT_BINARY_DIR}/benchmark/src/benchmark-build")

if(WIN32)
  set(benchmark_imported_location "${my_benchmark_binary_dir}/src/benchmark.lib")
  set(benchmark_main_imported_location "${my_benchmark_binary_dir}/src/benchmark_main.lib")
else()
  set(benchmark_imported_location "${my_benchmark_binary_dir}/src/libbenchmark.a")
  set(benchmark_main_imported_location "${my_benchmark_binary_dir}/src/libbenchmark_main.a")
endif(WIN32)

ExternalProject_Add(benchmark
  URL https://github.com/google/benchmark/archive/df7c7ee1d37dda0fb597586b4624515166a778d0.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/benchmark
  CMAKE_ARGS -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  INSTALL_COMMAND ""
  BUILD_BYPRODUCTS "${benchmark_imported_location}" "${benchmark_main_imported_location}"
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
  IMPORTED_LOCATION "${benchmark_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libbenchmarkmain IMPORTED STATIC GLOBAL)
add_dependencies(libbenchmarkmain benchmark)

set_target_properties(libbenchmarkmain PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  IMPORTED_LOCATION "${benchmark_main_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/include")
