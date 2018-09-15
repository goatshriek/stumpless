ExternalProject_Add(benchmark
    URL https://github.com/google/benchmark/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/benchmark
    CMAKE_ARGS -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=RELEASE
    INSTALL_COMMAND ""
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
  IMPORTED_LOCATION "${binary_dir}/src/libbenchmark.a"
  IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)
include_directories("${source_dir}/include")
