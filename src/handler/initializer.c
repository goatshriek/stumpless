#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/handler.h"
#include "private/handler/initializer.h"
#include "private/handler/stream.h"
#include "private/status.h"

#define ADD_HANDLER( name, function )                                          \
SetDictionaryValue( initializers, name, Initialize##function##Handler );

#define HANDLER_INITIALIZER_FUNCTION( handler_name, function_name )            \
Handler *                                                                      \
Initialize##function_name##Handler                                             \
( void )                                                                       \
{                                                                              \
  Handler * handler = malloc( sizeof( Handler ) );                             \
  if( !handler )                                                               \
    return NULL;                                                               \
                                                                               \
  handler->name = handler_name;                                                \
  handler->handle = Handle##function_name##Output;                             \
  handler->filters = NULL;                                                     \
  handler->options = NULL;                                                     \
                                                                               \
  return handler;                                                              \
}

static Dictionary * initializers = NULL;

Status *
InitializeHandlerByName
( const char *name )
{
  Handler *( *initializer )();

  if( !initializers ){

    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseStatus( "constructor failure" );

    ADD_HANDLER( "stream", Stream )
  }

  initializer = GetDictionaryValue( initializers, name );
  if( !initializer )
    return NULL;
  else
    return AddHandler( initializer() );
}

HANDLER_INITIALIZER_FUNCTION( "stream", Stream )
