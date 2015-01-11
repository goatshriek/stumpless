#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/adapter.h"
#include "private/adapter/initializer.h"
#include "private/container/dictionary.h"
#include "private/type.h"

static Dictionary *adapters = NULL;

Record *
AdaptRecord
( Adapter *adapter, Record *record )
{
  if( !adapter || !adapter->adapt )
    return record;

  if( !record )
    return NULL;

  return adapter->adapt( adapter, record );
}

Exception *
AddAdapter
( Adapter *adapter )
{
  if( !adapter || !adapter->name )
    return NULL;

  if( !adapters ){
    adapters = NewDictionary();

    if( !adapters )
      return RaiseException( "constructor failure" );
  }

  if( !SetDictionaryValue( adapters, adapter->name, adapter ) )
    return NULL;

  return NULL;
}

// todo implement
void
DestroyAdapter
( Adapter *adapter )
{
  return;
}

Adapter *
FindAdapterByName
( const char *name )
{
  Adapter *adapter;

  if( !adapters ){
    adapters = NewDictionary();

    if( !adapters )
      return NULL;
  }

  adapter = GetDictionaryValue( adapters, name );

  if( !adapter ){
    if( InitializeAdapterByName( name ) )
      return NULL;
    adapter = GetDictionaryValue( adapters, name );
  }

  return adapter;
}

void *
GetAdapterOption
( const Adapter * adapter, const char * option )
{
  if( adapter == NULL || option == NULL || adapter->options == NULL )
    return NULL;

  return GetDictionaryValue( adapter->options, option );
}

Exception *
SetAdapterOption
( Adapter *adapter, const char *option, void *value )
{
  Dictionary *result;

  if( !adapter || !option )
    return RaiseException( "empty argument" );

  if( !adapter->options ){
    adapter->options = NewDictionary();

    if( !adapter->options )
      return RaiseException( "dictionary failure" );
  }

  result =  SetDictionaryValue( adapter->options, option, value );

  if( !result )
    return RaiseException( "dictionary failure" );
  else
    return NULL;
}
