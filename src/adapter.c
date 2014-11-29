#include <stdlib.h>

#include "private/adapter.h"
#include "private/adapter/initializer.h"
#include "private/container/dictionary.h"
#include "private/status.h"
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

Status *
AddAdapter
( Adapter *adapter )
{
  if( !adapter || !adapter->name )
    return NULL;

  if( !adapters ){
    adapters = NewDictionary();

    if( !adapters )
      return RaiseStatus( "constructor failure" );
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

Status *
SetAdapterOption
( Adapter *adapter, const char *option, void *value )
{
  Dictionary *result;

  if( !adapter || !option )
    return RaiseStatus( "empty argument" );

  if( !adapter->options ){
    adapter->options = NewDictionary();

    if( !adapter->options )
      return RaiseStatus( "dictionary failure" );
  }

  result =  SetDictionaryValue( adapter->options, option, value );

  if( !result )
    return RaiseStatus( "dictionary failure" );
  else
    return NULL;
}
