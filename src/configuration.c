#include <stdlib.h>

#include <stumpless/formatter/text.h>
#include <stumpless/value.h>

#include "private/configuration.h"
#include "private/output.h"
#include "private/status.h"
#include "private/type.h"

static Configuration * configuration = NULL;

Configuration *
GetConfiguration( void )
{
  if( configuration == NULL && InitializeConfiguration() != NULL )
    return NULL;

  return configuration;
}

Status *
InitializeConfiguration( void )
{
  size_t required_size;

  configuration = malloc( sizeof( Configuration ) );
  if( !configuration )
    return RaiseStatus( "memory allocation failure" );

  required_size = sizeof( FileConfiguration );
  configuration->file = malloc( required_size );
  if( !configuration->file )
    return RaiseStatus( "memory allocation failure" );

  required_size = sizeof( HTTPConfiguration );
  configuration->http = malloc( required_size );
  if( !configuration->http )
    return RaiseStatus( "memory allocation failure" );

  required_size = sizeof( ThreadingConfiguration );
  configuration->threading = malloc( required_size );
  if( configuration->threading == NULL )
    return RaiseStatus( "memory allocation failure" );

  required_size = sizeof( SortingConfiguration );
  configuration->sorting = malloc( required_size );
  if( configuration->sorting == NULL )
    return RaiseStatus( "memory allocation failure" );

  required_size = sizeof( StringConfiguration );
  configuration->string = malloc( required_size );
  if( configuration->string == NULL )
    return RaiseStatus( "memory allocation failure" );
  configuration->string->buffer_size = 100;

  return NULL;
}

Status*
SetConfiguration( Configuration * new_configuration )
{
  if( configuration == NULL )
    return RaiseStatus( "empty argument" );

  configuration = new_configuration;
  return NULL;
}
