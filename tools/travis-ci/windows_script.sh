make all VERBOSE=1 2>&1
ls
make CTEST_OUTPUT_ON_FAILURE=1 check 2>&1
ls
make examples 2>&1
