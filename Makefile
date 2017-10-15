INCLUDEDIR = include
CFLAGS = -Wall -g -I $(INCLUDEDIR)/stumpless -I $(INCLUDEDIR)

all: stumpless.o stumplessd.o stumpless-test.o test-throughput.o target.o
	gcc -o stumpless-test stumpless.o target.o stumpless-test.o
	gcc -o test-throughput stumpless.o target.o throughput.o
	gcc -o stumplessd stumplessd.o

test: all
	./stumplessd &
	./test-throughput
	./stumpless-test
	pkill stumplessd

target.o: src/target.c $(INCLUDEDIR)/target.h
	scripts/headers_check.pl src/target.c
	gcc $(CFLAGS) -c src/target.c

stumpless.o: src/stumpless.c $(INCLUDEDIR)/stumpless/stumpless.h
	scripts/headers_check.pl src/stumpless.c
	gcc $(CFLAGS) -c src/stumpless.c

stumplessd.o: src/daemon/stumplessd.c $(INCLUDEDIR)/stumpless/stumpless.h
	scripts/headers_check.pl src/daemon/stumplessd.c
	gcc $(CFLAGS) -c src/daemon/stumplessd.c

stumpless-test.o: test/stumpless-test.c $(INCLUDEDIR)/stumpless/stumpless.h
	scripts/headers_check.pl test/stumpless-test.c
	gcc $(CFLAGS) -c test/stumpless-test.c

test-throughput.o: test/performance/throughput.c
	scripts/headers_check.pl test/performance/throughput.c
	gcc $(CFLAGS) -c test/performance/throughput.c

clean:
	rm -f *.o
	rm -f *.log
	rm -f *.csv
	rm -f stumplessd
	rm -f stumpless-test
	rm -f test-throughput
