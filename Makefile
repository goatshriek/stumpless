INCLUDEDIR = include
CFLAGS = -Wall -g -I $(INCLUDEDIR)/stumpless -I $(INCLUDEDIR)

all: stumpless.o stumplessd.o stumpless-test.o test-throughput.o
	gcc -o stumpless-test stumpless.o stumpless-test.o
	gcc -o test-throughput stumpless.o throughput.o
	gcc -o stumplessd stumplessd.o

test: all
	./test-throughput

stumpless.o: src/stumpless.c $(INCLUDEDIR)/stumpless/stumpless.h
	gcc $(CFLAGS) -c src/stumpless.c

stumplessd.o: src/daemon/stumplessd.c $(INCLUDEDIR)/stumpless/stumpless.h
	gcc $(CFLAGS) -c src/daemon/stumplessd.c

stumpless-test.o: test/stumpless-test.c $(INCLUDEDIR)/stumpless/stumpless.h
	gcc $(CFLAGS) -c test/stumpless-test.c

test-throughput.o: test/performance/throughput.c
	gcc $(CFLAGS) -c test/performance/throughput.c

clean:
	rm -f *.o
	rm -f stumplessd
	rm -f stumpless-test
	rm -f test-throughput
