#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/handler.h"
#include "private/status.h"
#include "private/type.h"

#include "private/handler/initializer.h"

static Dictionary *handlers = NULL;

Status *
AddHandler
( Handler *handler )
{
  void *value;

  if( !handler || !handler->name )
    return NULL;

  if( !handlers ){
    handlers = NewDictionary();

    if( !handlers )
      return RaiseStatus( "constructor failure" );
  }

  value = ( void * ) handler;
  if( !SetDictionaryValue( handlers, handler->name, value ) )
    return NULL;

  return NULL;
}

// todo implement
void
DestroyHandler
( Handler *handler )
{
  return;
}

Handler *
FindHandlerByName
( const char *name )
{
  Handler *handler;

  if( !handlers ){
    handlers = NewDictionary();

    if( !handlers )
      return NULL;
  }

  handler = GetDictionaryValue( handlers, name );

  if( !handler ){
    if( InitializeHandlerByName( name ) )
      return NULL;
    handler = GetDictionaryValue( handlers, name );
  }

  return handler;
}

void *
GetHandlerOption
( const Handler * handler, const char * option )
{
  if( handler == NULL || option == NULL || handler->options == NULL )
    return NULL;

  return GetDictionaryValue( handler->options, option );
}

Status *
HandleOutput
( const Handler *handler, const Output *output )
{
  if( !handler || !handler->handle )
    return NULL;

  return handler->handle( handler, output );
}

Status *
SetHandlerOption
( Handler * handler, const char * option, void * value )
{
  Dictionary *result;

  if( !handler || !option )
    return RaiseStatus( "empty argument" );

  if( handler->options == NULL ){
    handler->options = NewDictionary();

    if( handler->options == NULL )
      return RaiseStatus( "dictionary failure" );
  }

  result =  SetDictionaryValue( handler->options, option, value );

  if( !result )
    return RaiseStatus( "dictionary failure" );
  else
    return NULL;
}
