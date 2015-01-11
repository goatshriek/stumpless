#include <stdlib.h>

#include <stumpless/exception.h>
#include <stumpless/formatter/text.h>
#include <stumpless/value.h>

#include "private/configuration.h"
#include "private/output.h"
#include "private/type.h"

static Configuration * configuration = NULL;

Configuration *
GetConfiguration( void )
{
  if( configuration == NULL && InitializeConfiguration() != NULL )
    return NULL;

  return configuration;
}

Exception *
InitializeConfiguration( void )
{
  size_t required_size;

  configuration = malloc( sizeof( Configuration ) );
  if( !configuration )
    return RaiseException( "memory allocation failure" );

  required_size = sizeof( FileConfiguration );
  configuration->file = malloc( required_size );
  if( !configuration->file )
    return RaiseException( "memory allocation failure" );

  required_size = sizeof( HTTPConfiguration );
  configuration->http = malloc( required_size );
  if( !configuration->http )
    return RaiseException( "memory allocation failure" );

  required_size = sizeof( ThreadingConfiguration );
  configuration->threading = malloc( required_size );
  if( configuration->threading == NULL )
    return RaiseException( "memory allocation failure" );

  required_size = sizeof( SortingConfiguration );
  configuration->sorting = malloc( required_size );
  if( configuration->sorting == NULL )
    return RaiseException( "memory allocation failure" );

  required_size = sizeof( StringConfiguration );
  configuration->string = malloc( required_size );
  if( configuration->string == NULL )
    return RaiseException( "memory allocation failure" );
  configuration->string->buffer_size = 200;

  return NULL;
}

Exception*
SetConfiguration( Configuration * new_configuration )
{
  if( !configuration )
    return RaiseException( "empty argument" );

  configuration = new_configuration;
  return NULL;
}
