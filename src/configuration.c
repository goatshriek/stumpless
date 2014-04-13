#include <stdlib.h>

#include "private/configuration.h"
#include "private/output.h"
#include "private/status.h"
#include "private/type.h"
#include "private/value.h"

#include "private/formatter/text.h"

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
  configuration = malloc( sizeof( Configuration ) );
  if( configuration == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );

  size_t required_size = sizeof( FileConfiguration );
  configuration->default_file = malloc( required_size );
  if( configuration->default_file == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );

  required_size = sizeof( HTTPConfiguration );
  configuration->default_http = malloc( required_size );
  if( configuration->default_http == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  required_size = sizeof( ThreadingConfiguration );
  configuration->threading = malloc( required_size );
  if( configuration->threading == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  required_size = sizeof( SortingConfiguration );
  configuration->sorting = malloc( required_size );
  if( configuration->sorting == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  required_size = sizeof( StringConfiguration );
  configuration->string = malloc( required_size );
  if( configuration->string == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  configuration->string->buffer_size = 100;
  
  return NULL;
}

Status*
SetConfiguration( Configuration * new_configuration )
{
  if( configuration == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  configuration = new_configuration;
  return NULL;
}
