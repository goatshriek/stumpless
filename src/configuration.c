#include <stdlib.h>

#include <stumpless/formatter/text.h>
#include <stumpless/type.h>
#include <stumpless/value.h>

#include "private/configuration.h"
#include "private/exception/thrower.h"
#include "private/output.h"

static Configuration *configuration = NULL;

Configuration *
GetConfiguration( void )
{
  if( !configuration && !InitializeConfiguration() )
    return NULL;

  return configuration;
}

Configuration *
InitializeConfiguration( void )
{
  size_t required_size;

  configuration = malloc( sizeof( Configuration ) );
  if( !configuration ){
    ThrowMemoryAllocationException();
    return NULL;
  }

  required_size = sizeof( FileConfiguration );
  configuration->file = malloc( required_size );
  if( !configuration->file ){
    ThrowMemoryAllocationException();
    return NULL;
  }

  required_size = sizeof( HTTPConfiguration );
  configuration->http = malloc( required_size );
  if( !configuration->http ){
    ThrowMemoryAllocationException();
    return NULL;
  }

  required_size = sizeof( ThreadingConfiguration );
  configuration->threading = malloc( required_size );
  if( !configuration->threading ){
    ThrowMemoryAllocationException();
    return NULL;
  }

  required_size = sizeof( SortingConfiguration );
  configuration->sorting = malloc( required_size );
  if( !configuration->sorting ){
    ThrowMemoryAllocationException();
    return NULL;
  }

  required_size = sizeof( StringConfiguration );
  configuration->string = malloc( required_size );
  if( !configuration->string ){
    ThrowMemoryAllocationException();
    return NULL;
  }
  configuration->string->buffer_size = 200;

  return configuration;
}

Configuration *
SetConfiguration
( Configuration *new_configuration )
{
  return configuration = new_configuration;
}
