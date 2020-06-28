#!/usr/bin/env bash

ls /c/ProgramData/chocolatey/bin &&
which gcov &&
gcov --version &&
make all &&
make CTEST_OUTPUT_ON_FAILURE=1 check &&
if [[ $BUILD_ARGS =~ "ENABLE_CPP=ON" ]]; then make check-cpp; fi &&
make examples
