TOPDIR = ../..
INCLUDEDIR = $(TOPDIR)/include
SRCDIR = $(TOPDIR)/src
LIBDIR = $(TOPDIR)/lib
SCRIPTSDIR = $(TOPDIR)/scripts
TESTDIR = $(TOPDIR)/test
CFLAGS = -Wall -g -O0 -I $(INCLUDEDIR)
CPPFLAGS = -Wall -g -O0 -I $(INCLUDEDIR)

all: stumpless.o stumplessd.o test-throughput.o target.o memory.o error.o
	mkdir -p ./bin
	gcc -o ./bin/stumplessd stumplessd.o
	ld -shared stumpless.o target.o memory.o error.o -o libstumpless.so

test: all test-function test-throughput
	./bin/stumplessd &
	./bin/test/throughput
	./bin/test/function/stumpless
	pkill --signal SIGINT stumplessd

error.o: $(SRCDIR)/error.c $(INCLUDEDIR)/stumpless/error.h $(INCLUDEDIR)/private/error.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/error.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/error.c

memory.o: $(SRCDIR)/memory.c $(INCLUDEDIR)/private/memory.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/memory.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/memory.c

target.o: $(SRCDIR)/target.c $(INCLUDEDIR)/private/target.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/target.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/target.c

stumpless.o: $(SRCDIR)/stumpless.c $(INCLUDEDIR)/stumpless.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/stumpless.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/stumpless.c

stumplessd.o: $(SRCDIR)/daemon/stumplessd.c $(INCLUDEDIR)/stumpless.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/daemon/stumplessd.c
	gcc $(CFLAGS) -c $(SRCDIR)/daemon/stumplessd.c

test-function: all test-function-stumpless

test-function-stumpless: all $(TESTDIR)/function/stumpless.cpp $(INCLUDEDIR)/stumpless.h
	mkdir -p ./bin/test/function
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/function/stumpless.cpp
	g++ $(TESTDIR)/function/stumpless.cpp -o ./bin/test/function/stumpless $(CPPFLAGS) -L. -lgtest -lstumpless -Wl,-rpath=.

test-throughput: test-throughput.o
	gcc throughput.o -o ./bin/test/throughput -L. -lstumpless -Wl,-rpath=.

test-throughput.o: $(TESTDIR)/performance/throughput.c
	$(SCRIPTSDIR)/headers_check.pl $(TESTDIR)/performance/throughput.c
	gcc $(CFLAGS) -c $(TESTDIR)/performance/throughput.c

swig: all
	mkdir -p ./lib/swig
	swig -python -I$(INCLUDEDIR) -o ./lib/swig/stumpless_python_wrap.c -outdir ./lib/swig $(LIBDIR)/swig/stumpless.i
	gcc ./lib/swig/stumpless_python_wrap.c -c -fPIC -I$(INCLUDEDIR) -I/usr/include/python2.7 -o ./lib/swig/stumpless_python_wrap.o
	ld ./lib/swig/stumpless_python_wrap.o -shared -L. -rpath-link . -rpath . -lstumpless -o ./lib/swig/_stumpless.so

swig-clean:
	rm -rf ./lib/swig/*_wrap.*
	rm -rf ./lib/swig/*.so
	rm -rf ./lib/swig/*.pyc
	rm -rf ./lib/swig/*.py
	if [ -e lib/swig ]; then rmdir --ignore-fail-on-non-empty -p lib/swig ; fi

swig-test: swig
	./bin/stumplessd &
	$(TESTDIR)/lib/swig/test-python.py
	pkill --signal SIGINT stumplessd
 
clean: swig-clean
	rm -f *.o
	rm -f *.so
	rm -f *.log
	rm -f *.csv
	rm -rf ./bin
	if [ -e /tmp/stumplesstestpipe ]; then unlink /tmp/stumplesstestpipe ; fi

.PHONY: clean swig-clean
