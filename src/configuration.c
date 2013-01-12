#include <stdlib.h>

#include <configuration.h>
#include <types.h>

StumplessConfiguration * stumpless_configuration = NULL;

StumplessConfiguration *
StumplessGetConfiguration( void )
{
  return stumpless_configuration;
}

StumplessStatusCode
StumplessInitializeConfiguration( void )
{
  stumpless_configuration = malloc( sizeof( StumplessConfiguration ) );
  
  // todo need to add initialization of struct members
  
  if( stumpless_configuration == NULL )
    return STUMPLESS_FAILURE;
  else
    return STUMPLESS_SUCCESS;
}

StumplessStatusCode
StumplessSetConfiguration( StumplessConfiguration * new_configuration )
{
  stumpless_configuration = new_configuration;
  if( stumpless_configuration == new_configuration )
    return STUMPLESS_SUCCESS;
  else
    return STUMPLESS_FAILURE;
}
