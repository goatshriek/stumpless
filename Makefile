all: stumpless.o stumplessd.o stumpless-test.o
	gcc -o stumpless-test stumpless.o stumpless-test.o
	gcc -o stumplessd stumplessd.o

test: all
	./stumpless-test

stumpless.o: src/stumpless.c include/stumpless.h
	gcc -Wall -I include -c src/stumpless.c

stumplessd.o: stumplessd.c include/stumpless.h
	gcc -Wall -I include -c stumplessd.c

stumpless-test.o: stumpless-test.c include/stumpless.h
	gcc -Wall -I include -c stumpless-test.c

clean:
	rm *.o
	rm -f stumplessd
	rm -f stumpless-test
