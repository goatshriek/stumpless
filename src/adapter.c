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

Adapter *
AddAdapter
( Adapter *adapter )
{
  if( !adapter || !adapter->name )
    return adapter;

  if( !adapters ){
    adapters = NewDictionary();

    // todo throw constructor failure error
    if( !adapters )
      return adapter;
  }

  SetDictionaryValue( adapters, adapter->name, adapter );

  return adapter;
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
  if( !adapter || !option || !adapter->options )
    return NULL;

  return GetDictionaryValue( adapter->options, option );
}

Adapter *
SetAdapterOption
( Adapter *adapter, const char *option, void *value )
{
  if( !adapter || !option )
    return adapter;

  if( !adapter->options ){
    adapter->options = NewDictionary();

    // todo throw dictionary constructor failure exception
    if( !adapter->options )
      return adapter;
  }

  SetDictionaryValue( adapter->options, option, value );

  return adapter;
}
