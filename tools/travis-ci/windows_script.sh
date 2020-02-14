ls /c/ProgramData/chocolatey/bin
ls C:/ProgramData/chocolatey/bin
make all VERBOSE=1 2>&1
ls
#make CTEST_OUTPUT_ON_FAILURE=1 VERBOSE=1 check 2>&1
ls
make examples 2>&1
