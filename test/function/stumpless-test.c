#include <stdlib.h>
#include <stdio.h>
#include "stumpless.h"

int main(void){
  if(stumpless("testing") >= 0){
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}
