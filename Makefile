all: stumpless.o stumplessd.o stumpless-test.o test-throughput.o
	gcc -o stumpless-test stumpless.o stumpless-test.o
	gcc -o test-throughput stumpless.o throughput.o
	gcc -o stumplessd stumplessd.o

test: all
	./test-throughput

stumpless.o: src/stumpless.c include/stumpless.h
	gcc -Wall -I include -c src/stumpless.c

stumplessd.o: stumplessd.c include/stumpless.h
	gcc -Wall -I include -c stumplessd.c

stumpless-test.o: test/stumpless-test.c include/stumpless.h
	gcc -Wall -I include -c test/stumpless-test.c

test-throughput.o: test/performance/throughput.c
	gcc -Wall -I include -c test/performance/throughput.c

clean:
	rm -f *.o
	rm -f stumplessd
	rm -f stumpless-test
	rm -f test-throughput
