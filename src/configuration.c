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
  if( stumpless_configuration == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

  stumpless_configuration->file = malloc( sizeof( StumplessFileConfiguration ) );
  if( stumpless_configuration->file == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

  stumpless_configuration->http = malloc( sizeof( StumplessHTTPConfiguration ) );
  if( stumpless_configuration->http == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  stumpless_configuration->multithreading = malloc( sizeof( StumplessMultithreadingConfiguration ) );
  if( stumpless_configuration->multithreading == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  stumpless_configuration->sorting = malloc( sizeof( StumplessSortingConfiguration ) );
  if( stumpless_configuration->sorting == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

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
