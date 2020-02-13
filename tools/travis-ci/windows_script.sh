echo `which make`
make all VERBOSE=1 2>&1
make CTEST_OUTPUT_ON_FAILURE=1 check
make examples
