#include <stdlib.h>
#include <stdio.h>
#include <stumpless.h>
#include <sys/types.h>
#include <time.h>

int main(void){
  const unsigned message_count = 1000;
  clock_t start, finish;
  unsigned i;


  start = clock();
  for(i=0; i < message_count; i++){
    stumpless("testing");
  }
  finish = clock();

  printf("time to run: %Lf seconds\n", ((finish-start)/(long double)CLOCKS_PER_SEC));

  return EXIT_SUCCESS;
}
