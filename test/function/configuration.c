#include <stdlib.h>
#include <stdio.h>

#include <stumpless.h>

int test_initialization( void );

int
main( void )
{
  return test_initialization();
}

int
test_initialization( void )
{
  StumplessConfiguration * result = StumplessGetConfiguration();
  if( result != NULL )
    return EXIT_FAILURE;
  
  StumplessLogInfo( "testing testing 1 2 3..." );
  
  if( result == NULL ){
    printf( "The configuration was not initialized.\n" );
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
