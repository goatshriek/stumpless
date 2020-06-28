#!/usr/bin/env bash

ls /c/ProgramData/chocolatey/bin &&
which gcov &&
mingw32-make all &&
mingw32-make CTEST_OUTPUT_ON_FAILURE=1 check &&
if [[ $BUILD_ARGS =~ "ENABLE_CPP=ON" ]]; then mingw32-make check-cpp; fi &&
mingw32-make examples
