#include <stdlib.h>
#include "stumpless.h"

int main(void){
  if(stumpless("testing") != 0){
    return EXIT_FAILURE;
  }
  
  // todo check the error state of the library
  
  // todo check the contents of the log file
  
  return EXIT_SUCCESS;
}
