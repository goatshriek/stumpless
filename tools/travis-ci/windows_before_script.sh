echo `which gcc`
echo `which g++`
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER="gcc" -DCMAKE_CXX_COMPILER="g++" -DCOVERAGE=ON ${BUILD_ARGS} ..
