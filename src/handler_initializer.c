#include <stdlib.h>

#include "private/dictionary.h"
#include "private/handler.h"
#include "private/handler_initializer.h"
#include "private/status.h"

#define ADD_HANDLER( name, function )                                          \
SetDictionaryValue( initializers, name, Initialize##function##Handler );

static Dictionary * initializers = NULL;

Status *
InitializeHandlerByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_HANDLER( "stream", Stream )
  }
  
  Handler * ( *initializer )();
  initializer = GetDictionaryValue( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddHandler( initializer() );
}

Handler *
InitializeStreamHandler
( void )
{
  return NULL;
}
