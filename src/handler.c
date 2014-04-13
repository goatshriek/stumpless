#include <stdlib.h>

#include "private/dictionary.h"
#include "private/handler.h"
#include "private/handler_initializer.h"
#include "private/status.h"
#include "private/type.h"

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
      return RaiseAbnormalStatus( "constructor failure" );
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
SetHandlerOption
( Handler * handler, const char * option, void * value )
{
  if( handler == NULL || option == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( handler->options == NULL ){
    handler->options = NewDictionary();
    
    if( handler->options == NULL )
      return RaiseAbnormalStatus( "dictionary failure" );
  }
  
  Dictionary * result;
  result =  SetDictionaryValue( handler->options, option, value );
  
  if( result == NULL )
    return RaiseAbnormalStatus( "dictionary failure" );
  else
    return NULL;
}
