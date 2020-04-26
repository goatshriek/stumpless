#!/usr/bin/env sh

mingw32-make all &&
mingw32-make CTEST_OUTPUT_ON_FAILURE=1 check &&
mingw32-make examples
