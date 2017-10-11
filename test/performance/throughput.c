#include <stdlib.h>
#include <stdio.h>
#include <stumpless.h>
#include <sys/types.h>
#include <syslog.h>
#include <time.h>

int main(void){
  const unsigned message_count = 1000;
  clock_t start, finish;
  unsigned i;
  FILE *outfile;
  long double stumpless_result, syslog_result;

  outfile = fopen("throughput-results.csv", "w");
  if( !outfile ){
    perror("could not create outfile");
    return EXIT_FAILURE;
  }
  
  start = clock();
  for(i=0; i < message_count; i++){
    stumpless("testing");
  }
  finish = clock();
  stumpless_result = (finish-start)/(long double)CLOCKS_PER_SEC;

  start = clock();
  for(i=0; i < message_count; i++){
    syslog(LOG_INFO, "testing");
  }
  finish = clock();
  syslog_result = (finish-start)/(long double)CLOCKS_PER_SEC;
  fprintf(outfile, "%d,%Lf,%Lf\n", message_count, stumpless_result, syslog_result);

  fclose(outfile);
  
  return EXIT_SUCCESS;
}
