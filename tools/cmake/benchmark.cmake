ExternalProject_Add(benchmark
  URL https://github.com/google/benchmark/archive/eee8b05c97d7b832bf67d6e000958d012ab30165.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/benchmark
  CMAKE_ARGS -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  INSTALL_COMMAND ""
)

set_target_properties(benchmark
  PROPERTIES
  EXCLUDE_FROM_ALL TRUE
)

ExternalProject_Get_Property(benchmark source_dir binary_dir)

add_library(libbenchmark IMPORTED STATIC GLOBAL)
add_dependencies(libbenchmark benchmark)

if(WIN32)
  set(benchmark_imported_location "${binary_dir}/src/benchmark.lib")
else()
  set(benchmark_imported_location "${binary_dir}/src/libbenchmark.a")
endif(WIN32)

set_target_properties(libbenchmark PROPERTIES
  EXCLUDE_FROM_ALL TRUE
  IMPORTED_LOCATION "${benchmark_imported_location}"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/include")
