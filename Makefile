test: stumpless.o stumpless-test.o
	gcc -o stumpless-test stumpless.o stumpless-test.o 
	./stumpless-test

stumpless.o: stumpless.c
	gcc -Wall -c stumpless.c

stumpless-test.o: stumpless-test.c
	gcc -Wall -c stumpless-test.c

clean:
	rm -f *.o
	rm -f stumpless-test
