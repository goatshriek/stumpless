all: stumpless.o stumplessd.o stumpless-test.o
	gcc -o stumpless-test stumpless.o stumpless-test.o
	gcc -o stumplessd stumplessd.o

test: stumpless.o stumplessd.o stumpless-test.o
	./stumpless-test

stumpless.o: stumpless.c
	gcc -Wall -c stumpless.c

stumplessd.o: stumplessd.c
	gcc -Wall -c stumplessd.c

stumpless-test.o: stumpless-test.c
	gcc -Wall -c stumpless-test.c

clean:
	rm -f *.o
	rm -f stumplessd
	rm -f stumpless-test
