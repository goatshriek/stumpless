mkfile_path := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

TOPDIR = $(abspath $(mkfile_path)../..)
INCLUDEDIR = $(TOPDIR)/include
SRCDIR = $(TOPDIR)/src
LIBDIR = $(TOPDIR)/lib
SCRIPTSDIR = $(TOPDIR)/scripts
TESTDIR = $(TOPDIR)/test
CC = gcc
CXX = g++
CFLAGS = -Wall -g -O0 -I $(INCLUDEDIR)
CPPFLAGS = -std=c++11 -Wall -g -O0 -I $(INCLUDEDIR)
LDFLAGS = -shared

all: libstumpless.so bin/stumplessd

bin/stumplessd: stumplessd.o
	mkdir -p ./bin
	$(CC) -o ./bin/stumplessd stumplessd.o

libstumpless.so: stumpless.o target.o memory.o error.o socket.o buffer.o formatter.o entry.o version.o
	ld $(LDFLAGS) stumpless.o target.o memory.o error.o socket.o buffer.o formatter.o entry.o version.o -o libstumpless.so

error.o: $(SRCDIR)/error.c $(INCLUDEDIR)/stumpless/error.h $(INCLUDEDIR)/private/error.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/error.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/error.c

entry.o: $(SRCDIR)/entry.c $(INCLUDEDIR)/stumpless/entry.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/entry.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/entry.c

formatter.o: $(SRCDIR)/formatter.c $(INCLUDEDIR)/stumpless/target.h $(INCLUDEDIR)/private/memory.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/formatter.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/formatter.c

memory.o: $(SRCDIR)/memory.c $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/private/memory.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/memory.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/memory.c

target.o: $(SRCDIR)/target.c $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/stumpless/target.h $(INCLUDEDIR)/private/target/buffer.h $(INCLUDEDIR)/private/target/socket.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/target.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/target.c

version.o: $(SRCDIR)/version.c $(INCLUDEDIR)/stumpless.h $(INCLUDEDIR)/stumpless/version.h $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/private/memory.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/version.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/version.c

socket.o: $(SRCDIR)/target/socket.c $(INCLUDEDIR)/stumpless.h $(INCLUDEDIR)/stumpless/target.h $(INCLUDEDIR)/stumpless/target/socket.h $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/private/memory.h $(INCLUDEDIR)/private/target/socket.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/target/socket.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/target/socket.c

buffer.o: $(SRCDIR)/target/buffer.c $(INCLUDEDIR)/stumpless.h $(INCLUDEDIR)/stumpless/target.h $(INCLUDEDIR)/stumpless/target/buffer.h $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/private/memory.h $(INCLUDEDIR)/private/target/buffer.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/target/buffer.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/target/buffer.c

stumpless.o: $(SRCDIR)/stumpless.c $(INCLUDEDIR)/stumpless.h $(INCLUDEDIR)/stumpless/target.h $(INCLUDEDIR)/stumpless/target/socket.h $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/private/memory.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/stumpless.c
	$(CC) $(CFLAGS) -c -fPIC $(SRCDIR)/stumpless.c

stumplessd.o: $(SRCDIR)/daemon/stumplessd.c $(INCLUDEDIR)/stumpless.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/daemon/stumplessd.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/daemon/stumplessd.c

test: bin/stumplessd bin/test/function/stumpless bin/test/function/target/buffer bin/test/performance/stumpless
	./bin/stumplessd &
	./bin/test/function/stumpless
	./bin/test/function/target/buffer
	./bin/test/performance/stumpless
	pkill --signal SIGINT stumplessd

test-function: bin/stumplessd bin/test/function/stumpless bin/test/function/target/buffer
	./bin/stumplessd &
	./bin/test/function/stumpless
	./bin/test/function/target/buffer
	pkill --signal SIGINT stumplessd

bin/test/function/stumpless: libstumpless.so $(TESTDIR)/function/stumpless.cpp $(INCLUDEDIR)/stumpless.h
	mkdir -p ./bin/test/function
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/function/stumpless.cpp
	$(CXX) $(TESTDIR)/function/stumpless.cpp -o ./bin/test/function/stumpless $(CPPFLAGS) -L. -lgtest -lstumpless -lpthread -Wl,-rpath=.

bin/test/function/target/buffer: libstumpless.so test/function/target/buffer.o rfc5424.o
	mkdir -p ./bin/test/function/target
	$(CXX) ./test/function/target/buffer.o rfc5424.o $(CPPFLAGS) -L. -lgtest -lstumpless -lpthread -Wl,-rpath=. -o ./bin/test/function/target/buffer

test/function/target/buffer.o: $(TESTDIR)/function/target/buffer.cpp $(INCLUDEDIR)/test/function/rfc5424.hpp
	mkdir -p ./test/function/target
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/function/target/buffer.cpp
	$(CXX) $(TESTDIR)/function/target/buffer.cpp $(CPPFLAGS) -c -o ./test/function/target/buffer.o

rfc5424.o: $(TESTDIR)/function/rfc5424.cpp $(INCLUDEDIR)/test/function/rfc5424.hpp
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/function/rfc5424.cpp
	$(CXX) $(TESTDIR)/function/rfc5424.cpp $(CPPFLAGS) -c

test-performance: bin/stumplessd bin/test/performance/stumpless
	./bin/stumplessd &
	./bin/test/performance/stumpless
	pkill --signal SIGINT stumplessd

bin/test/performance/stumpless: libstumpless.so $(TESTDIR)/performance/stumpless.cpp
	mkdir -p ./bin/test/performance
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/performance/stumpless.cpp
	$(CXX) $(TESTDIR)/performance/stumpless.cpp -o ./bin/test/performance/stumpless $(CPPFLAGS) -L. -lbenchmark -lstumpless -lpthread -Wl,-rpath=.

swig: lib/swig/_stumpless.so

lib/swig/_stumpless.so: libstumpless.so $(LIBDIR)/swig/stumpless.i
	mkdir -p ./lib/swig
	swig -python -I$(INCLUDEDIR) -o ./lib/swig/stumpless_python_wrap.c -outdir ./lib/swig $(LIBDIR)/swig/stumpless.i
	$(CC) ./lib/swig/stumpless_python_wrap.c -c -fPIC -I$(INCLUDEDIR) -I/usr/include/python2.7 -o ./lib/swig/stumpless_python_wrap.o
	ld $(LDFLAGS) ./lib/swig/stumpless_python_wrap.o -L. -rpath-link . -rpath . -lstumpless -o ./lib/swig/_stumpless.so

swig-test: bin/stumplessd lib/swig/_stumpless.so $(TESTDIR)/lib/swig/python-version.py
	./bin/stumplessd &
	$(TESTDIR)/lib/swig/python-version.py
	pkill --signal SIGINT stumplessd
 
clean:
	-pkill --signal SIGINT stumplessd
	if [ -e /tmp/stumplesstestpipe ]; then unlink /tmp/stumplesstestpipe ; fi
	rm -f ./stumplessd-out.log
	rm -rf ./lib/swig/*_wrap.*
	rm -rf ./lib/swig/*.so
	rm -rf ./lib/swig/*.pyc
	rm -rf ./lib/swig/*.py
	if [ -e lib/swig ]; then rmdir --ignore-fail-on-non-empty -p lib/swig ; fi
	rm -f ./test/function/*.o
	rm -f *.o
	rm -f *.so
	rm -f *.log
	rm -f *.csv
	rm -rf ./bin

.PHONY: all clean swig-test swig test test-function test-performance
