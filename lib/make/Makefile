TOPDIR = ../..
INCLUDEDIR = $(TOPDIR)/include
SRCDIR = $(TOPDIR)/src
LIBDIR = $(TOPDIR)/lib
SCRIPTSDIR = $(TOPDIR)/scripts
TESTDIR = $(TOPDIR)/test
CFLAGS = -Wall -g -O0 -I $(INCLUDEDIR)
CPPFLAGS = -Wall -g -O0 -I $(INCLUDEDIR)

all: stumpless.o stumplessd.o test-throughput.o target.o error.o
	mkdir -p ./bin
	gcc -o ./bin/stumplessd stumplessd.o
	ld -shared stumpless.o target.o error.o -o libstumpless.so

test: all test-function test-throughput
	./bin/stumplessd &
	./bin/test/throughput
	./bin/test/function/stumpless
	pkill --signal SIGINT stumplessd

error.o: $(SRCDIR)/error.c $(INCLUDEDIR)/stumpless/error.h $(INCLUDEDIR)/private/error.h
	$(SCRIPTSDIR)/headers_check.pl $(SRCDIR)/error.c
	gcc $(CFLAGS) -c -fPIC $(SRCDIR)/error.c

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
	swig -python -I$(INCLUDEDIR)/stumpless -o stumpless_python_wrap.c -outdir . $(LIBDIR)/swig/stumpless.i
	gcc -c -fPIC -I$(INCLUDEDIR)/stumpless -I/usr/include/python2.7 ./stumpless_python_wrap.c
	ld -shared -L. -rpath-link . -rpath . -lstumpless stumpless_python_wrap.o -o ./_stumpless.so

swig-clean:
	rm -rf *_wrap.*
	rm -rf *.so
	rm -rf *.pyc
	rm -rf *.py
  
clean: swig-clean
	rm -f *.o
	rm -f *.so
	rm -f *.log
	rm -f *.csv
	rm -rf ./bin
	if [ -e /tmp/stumplesstestpipe ]; then unlink /tmp/stumplesstestpipe ; fi

.PHONY: clean
