#include <stdlib.h>

#include "private/adapter.h"
#include "private/adapter_base.h"
#include "private/adapter_initializer.h"
#include "private/dictionary.h"
#include "private/status.h"
#include "private/stream_handler.h"

#define ADAPTER_INITIALIZER_FUNCTION( adapter_name, function_name )            \
Adapter *                                                                      \
Initialize##function_name##Adapter                                             \
( void )                                                                       \
{                                                                              \
  Adapter * adapter = malloc( sizeof( Adapter ) );                             \
  if( adapter == NULL )                                                        \
    return NULL;                                                               \
                                                                               \
  adapter->name = adapter_name;                                                \
  adapter->adapt = ValueThrough##function_name##Adapter;                       \
  adapter->filters = NULL;                                                     \
  adapter->options = NULL;                                                     \
                                                                               \
  return adapter;                                                              \
}

#define ADD_ADAPTER( name, function )                                          \
SetDictionaryValue( initializers, name, Initialize##function##Adapter );

static Dictionary * initializers = NULL;

ADAPTER_INITIALIZER_FUNCTION( "context", Context )

Status *
InitializeAdapterByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_ADAPTER( "context", Context )
  }
  
  Adapter * ( *initializer )();
  initializer = GetDictionaryValue( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddAdapter( initializer() );
}
