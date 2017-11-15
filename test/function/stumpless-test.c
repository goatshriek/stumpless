#include <stdlib.h>
#include <stumpless.h>
#include <stumpless/error.h>

int main(void){
  if(stumpless("testing") != 0){
    return EXIT_FAILURE;
  }
  
  if(stumpless_get_error()){
    return EXIT_FAILURE;
  }
  
  // todo check the contents of the log file
  
  return EXIT_SUCCESS;
}
