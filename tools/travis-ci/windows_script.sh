#!/usr/bin/env bash

mingw32-make all &&
mingw32-make CTEST_OUTPUT_ON_FAILURE=1 check &&
if [[ $BUILD_ARGS =~ "ENABLE_CPP=ON" ]]; then mingw32-make check-cpp; fi &&
if [[ $BUILD_ARGS =~ "CMAKE_BUILD_TYPE=Release" ]]; then mingw32-make bench; fi &&
mingw32-make examples
