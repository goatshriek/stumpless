#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/adapter.h"
#include "private/adapter/base.h"
#include "private/adapter/initializer.h"
#include "private/container/dictionary.h"

#define ADAPTER_INITIALIZER_FUNCTION( adapter_name, function_name )            \
Adapter *                                                                      \
Initialize##function_name##Adapter                                             \
( void )                                                                       \
{                                                                              \
  Adapter *adapter = malloc( sizeof( Adapter ) );                              \
  if( !adapter )                                                               \
    return NULL;                                                               \
                                                                               \
  adapter->name = adapter_name;                                                \
  adapter->adapt = RecordThrough##function_name##Adapter;                      \
  adapter->filters = NULL;                                                     \
  adapter->options = NULL;                                                     \
                                                                               \
  return adapter;                                                              \
}

#define ADD_ADAPTER( name, function )                                          \
SetDictionaryValue( initializers, name, Initialize##function##Adapter );

static Dictionary *initializers = NULL;

Adapter *
InitializeAdapterByName
( const char *name )
{
  Adapter *( *initializer )();

  if( !initializers ){
    initializers = NewDictionary();
    if( !initializers )
      return NULL;

    ADD_ADAPTER( "context", Context )
    ADD_ADAPTER( "level", Level )
  }

  initializer = GetDictionaryValue( initializers, name );
  if( !initializer ){
    return NULL;
  } else {
    return AddAdapter( initializer() );
  }
}

ADAPTER_INITIALIZER_FUNCTION( "context", Context )

ADAPTER_INITIALIZER_FUNCTION( "level", Level )
