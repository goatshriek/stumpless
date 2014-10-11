#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/handler.h"
#include "private/status.h"
#include "private/type.h"

#include "private/handler/initializer.h"

static Dictionary * handlers = NULL;

Status *
AddHandler
( Handler * handler )
{
  if( handler == NULL || handler->name == NULL )
    return NULL;

  if( handlers == NULL ){
    handlers = NewDictionary();

    if( handlers == NULL )
      return RaiseStatus( "constructor failure" );
  }

  void * value = ( void * ) handler;
  if( SetDictionaryValue( handlers, handler->name, value ) == NULL )
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
( const char * name )
{
  if( handlers == NULL ){
    handlers = NewDictionary();

    if( handlers == NULL )
      return NULL;
  }

  Handler * handler = GetDictionaryValue( handlers, name );

  if( handler == NULL ){
    if( InitializeHandlerByName( name ) != NULL )
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
  if( handler == NULL || option == NULL )
    return RaiseStatus( "empty argument" );

  if( handler->options == NULL ){
    handler->options = NewDictionary();

    if( handler->options == NULL )
      return RaiseStatus( "dictionary failure" );
  }

  Dictionary * result;
  result =  SetDictionaryValue( handler->options, option, value );

  if( result == NULL )
    return RaiseStatus( "dictionary failure" );
  else
    return NULL;
}
