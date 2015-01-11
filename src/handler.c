#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/handler.h"
#include "private/type.h"

#include "private/handler/initializer.h"

static Dictionary *handlers = NULL;

Exception *
AddHandler
( Handler *handler )
{
  void *value;

  if( !handler || !handler->name )
    return NULL;

  if( !handlers ){
    handlers = NewDictionary();

    if( !handlers )
      return RaiseException( "constructor failure" );
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
  if( !handler || !option || !handler->options )
    return NULL;

  return GetDictionaryValue( handler->options, option );
}

Exception *
HandleOutput
( const Handler *handler, const Output *output )
{
  if( !handler || !handler->handle )
    return NULL;

  return handler->handle( handler, output );
}

Exception *
SetHandlerOption
( Handler * handler, const char * option, void * value )
{
  Dictionary *result;

  if( !handler || !option )
    return RaiseException( "empty argument" );

  if( handler->options == NULL ){
    handler->options = NewDictionary();

    if( handler->options == NULL )
      return RaiseException( "dictionary failure" );
  }

  result =  SetDictionaryValue( handler->options, option, value );

  if( !result )
    return RaiseException( "dictionary failure" );
  else
    return NULL;
}
