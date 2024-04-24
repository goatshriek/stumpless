find_library(benchmark_lib
  NAMES benchmark benchmarkd
  PATHS ${BENCHMARK_PATH} "${BENCHMARK_PATH}/src" "${BENCHMARK_PATH}/src/${CMAKE_CFG_INTDIR}" "${BENCHMARK_PATH}/lib" "${BENCHMARK_PATH}/lib/${CMAKE_CFG_INTDIR}" "${BENCHMARK_PATH}/bin" "${BENCHMARK_PATH}/bin/${CMAKE_CFG_INTDIR}"
)

find_library(benchmark_main_lib
  NAMES benchmark_main benchmark_maind
  PATHS ${BENCHMARK_PATH} "${BENCHMARK_PATH}/src" "${BENCHMARK_PATH}/src/${CMAKE_CFG_INTDIR}" "${BENCHMARK_PATH}/lib" "${BENCHMARK_PATH}/lib/${CMAKE_CFG_INTDIR}" "${BENCHMARK_PATH}/bin" "${BENCHMARK_PATH}/bin/${CMAKE_CFG_INTDIR}"
)

find_path(benchmark_header_path
  NAMES "benchmark/benchmark.h"
  PATHS ${BENCHMARK_PATH} "${BENCHMARK_PATH}/include"
)

if(${benchmark_lib} STREQUAL "benchmark_lib-NOTFOUND" OR ${benchmark_main_lib} STREQUAL "benchmark_main_lib-NOTFOUND" OR ${benchmark_header_path} STREQUAL "benchmark_header_path-NOTFOUND")
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
    URL https://github.com/google/benchmark/archive/bc946b919cac6f25a199a526da571638cfde109f.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/benchmark
    CMAKE_ARGS -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_SH=${CMAKE_SH} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_CXX_FLAGS=${google_libs_cxx_flags}
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

  add_custom_target(export-benchmark
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${local_benchmark_binary_dir} ${BENCHMARK_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${local_benchmark_static_dir} ${BENCHMARK_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_dir}/include" ${BENCHMARK_PATH}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_dir}/tools" "${BENCHMARK_PATH}/tools"
    DEPENDS benchmark
  )
else()
  add_found_library(
    LIB_NAME "libbenchmark"
    LIB_PATH ${benchmark_lib}
    DLL_PATH "-NOTFOUND"
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  add_found_library(
    LIB_NAME "libbenchmarkmain"
    LIB_PATH ${benchmark_main_lib}
    DLL_PATH "-NOTFOUND"
    INTERFACE_LINK_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
  )

  include_directories(${benchmark_header_path})
endif()
