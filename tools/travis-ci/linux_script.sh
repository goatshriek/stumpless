#!/usr/bin/env sh

build-wrapper-linux-x86-64 --out-dir ../bw-output make -j 2 all || make -j 2 all &&
make CTEST_OUTPUT_ON_FAILURE=1 -j 2 check &&
sudo --preserve-env make CTEST_OUTPUT_ON_FAILURE=1 -j 2 check &&
make -j 2 examples
