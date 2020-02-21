#!/usr/bin/env sh

build-wrapper-linux-x86-64 --out-dir ../bw-output make all || make all
make CTEST_OUTPUT_ON_FAILURE=1 check
sudo --preserve-env make CTEST_OUTPUT_ON_FAILURE=1 check
make examples
