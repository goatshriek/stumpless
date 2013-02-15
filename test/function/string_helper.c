#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string_helper.h>

const char * test_is_empty( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_is_empty();
  if( result != NULL ){
    printf( "Is Empty Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_is_empty( void )
{
  unsigned short result = is_empty( " \f\n\r\t\v" );
  
  if( result == 0 )
    return "a string of all whitespace caharcters was not empty";
  
  if( result != 6 )
    return "the result of the call was not the length of the string";
  
  return NULL;
}
