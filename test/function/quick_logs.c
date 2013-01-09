#include <stdlib.h>

#include <stumpless.h>

int
main( void )
{
  StumplessStatusCode result = StumplessLogDebug( "testing" );
  if( result == STUMPLESS_SUCCESS )
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
