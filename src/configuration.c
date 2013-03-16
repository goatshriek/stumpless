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

  size_t required_size = sizeof( StumplessFileConfiguration );
  stumpless_configuration->file = malloc( required_size );
  if( stumpless_configuration->file == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;

  required_size = sizeof( StumplessHTTPConfiguration );
  stumpless_configuration->http = malloc( required_size );
  if( stumpless_configuration->http == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( StumplessMultithreadingConfiguration );
  stumpless_configuration->multithreading = malloc( required_size );
  if( stumpless_configuration->multithreading == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( StumplessSortingConfiguration );
  stumpless_configuration->sorting = malloc( required_size );
  if( stumpless_configuration->sorting == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  required_size = sizeof( StumplessStringConfiguration );
  stumpless_configuration->string = malloc( required_size );
  if( stumpless_configuration->sorting == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  stumpless_configuration->string->buffer_size = 100;

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
