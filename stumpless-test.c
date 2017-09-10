#include <stdlib.h>
#include <stdio.h>
#include "stumpless.h"

int main(void){
  if(stumpless("testing") >= 0){
    printf("success\n");
    return EXIT_SUCCESS;
  } else {
    printf("failure\n");
    return EXIT_FAILURE;
  }
}
