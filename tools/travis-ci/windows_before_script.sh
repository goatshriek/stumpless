#!/usr/bin/env sh

cmake -G "MSYS Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DCOVERAGE=ON ${BUILD_ARGS} ..
