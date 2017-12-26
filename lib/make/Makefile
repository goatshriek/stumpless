mkfile_path := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

TOPDIR = $(abspath $(mkfile_path)../..)
INCLUDEDIR = $(TOPDIR)/include
SRCDIR = $(TOPDIR)/src
LIBDIR = $(TOPDIR)/lib
SCRIPTSDIR = $(TOPDIR)/scripts
TESTDIR = $(TOPDIR)/test
CFLAGS = -Wall -g -O0 -I $(INCLUDEDIR)
CPPFLAGS = -std=c++11 -Wall -g -O0 -I $(INCLUDEDIR)
LDFLAGS = -shared

all: libstumpless.so bin/stumplessd

bin/stumplessd: stumplessd.o
	mkdir -p ./bin
	gcc -o ./bin/stumplessd stumplessd.o

libstumpless.so: stumpless.o target.o memory.o error.o socket.o buffer.o
	ld $(LDFLAGS) stumpless.o target.o memory.o error.o socket.o buffer.o -o libstumpless.so

error.o: $(SRCDIR)/error.c $(INCLUDEDIR)/stumpless/error.h $(INCLUDEDIR)/private/error.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/error.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/error.c

memory.o: $(SRCDIR)/memory.c $(INCLUDEDIR)/private/memory.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/memory.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/memory.c

target.o: $(SRCDIR)/target.c $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/stumpless/target.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/target.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/target.c

socket.o: $(SRCDIR)/target/socket.c $(INCLUDEDIR)/stumpless.h $(INCLUDEDIR)/stumpless/target.h $(INCLUDEDIR)/private/error.h $(INCLUDEDIR)/private/memory.h $(INCLUDEDIR)/private/target/socket.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/target/socket.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/target/socket.c

buffer.o: $(SRCDIR)/target/buffer.c
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/target/buffer.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/target/buffer.c

stumpless.o: $(SRCDIR)/stumpless.c $(INCLUDEDIR)/stumpless.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/stumpless.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/stumpless.c

stumplessd.o: $(SRCDIR)/daemon/stumplessd.c $(INCLUDEDIR)/stumpless.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/daemon/stumplessd.c
	gcc $(CFLAGS) -c $(SRCDIR)/daemon/stumplessd.c

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
	g++ $(TESTDIR)/function/stumpless.cpp -o ./bin/test/function/stumpless $(CPPFLAGS) -L. -lgtest -lstumpless -Wl,-rpath=.

bin/test/function/target/buffer: libstumpless.so
	mkdir -p ./bin/test/function/target
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/function/target/buffer.cpp
	g++ $(TESTDIR)/function/target/buffer.cpp -o ./bin/test/function/target/buffer $(CPPFLAGS) -L. -lgtest -lstumpless -Wl,-rpath=.

test-performance: bin/stumplessd bin/test/performance/stumpless
	./bin/stumplessd &
	./bin/test/performance/stumpless
	pkill --signal SIGINT stumplessd

bin/test/performance/stumpless: libstumpless.so $(TESTDIR)/performance/stumpless.cpp
	mkdir -p ./bin/test/performance
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/performance/stumpless.cpp
	g++ $(TESTDIR)/performance/stumpless.cpp -o ./bin/test/performance/stumpless $(CPPFLAGS) -L. -lbenchmark -lstumpless -lpthread -Wl,-rpath=.

swig: lib/swig/_stumpless.so

lib/swig/_stumpless.so: libstumpless.so $(LIBDIR)/swig/stumpless.i
	mkdir -p ./lib/swig
	swig -python -I$(INCLUDEDIR) -o ./lib/swig/stumpless_python_wrap.c -outdir ./lib/swig $(LIBDIR)/swig/stumpless.i
	gcc ./lib/swig/stumpless_python_wrap.c -c -fPIC -I$(INCLUDEDIR) -I/usr/include/python2.7 -o ./lib/swig/stumpless_python_wrap.o
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
	rm -f *.o
	rm -f *.so
	rm -f *.log
	rm -f *.csv
	rm -rf ./bin

.PHONY: all clean swig-test swig test test-function test-performance
