#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/handler.h"
#include "private/type.h"

#include "private/handler/initializer.h"

static Dictionary *handlers = NULL;

Handler *
AddHandler
( Handler *handler )
{
  if( !handler || !handler->name )
    return handler;

  if( !handlers ){
    handlers = NewDictionary();

    // todo throw an Exception and return a failure
    if( !handlers )
      return handler;
  }

  SetDictionaryValue( handlers, handler->name, ( void * ) handler );

  return handler;
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

const Handler *
HandleOutput
( const Handler *handler, const Output *output )
{
  if( !handler || !handler->handle )
    return NULL;

  return handler->handle( handler, output );
}

Handler *
SetHandlerOption
( Handler *handler, const char * option, void * value )
{
  Dictionary *result;

  if( !handler || !option )
    return handler;

  if( !handler->options ){
    handler->options = NewDictionary();

    // todo raise an exception here or be fault tolerant
    if( !handler->options )
      return handler;
  }

  result =  SetDictionaryValue( handler->options, option, value );

  // todo raise an Exception here or be fault tolerant
  if( !result )
    return NULL;
  else
    return handler;
}
