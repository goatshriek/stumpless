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
  if( AddValueToDictionary( handlers, handler->name, value ) == NULL )
    return NULL;
  
  return NULL;
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
  
  Handler * handler = GetValueFromDictionary( handlers, name );
  
  if( handler == NULL ){
    if( InitializeHandlerByName( name ) != NULL )
      return NULL;
    handler = GetValueFromDictionary( handlers, name );
  }
  
  return handler;
}
