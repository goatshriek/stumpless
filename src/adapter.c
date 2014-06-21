#include <stdlib.h>

#include "private/adapter.h"
#include "private/adapter_initializer.h"
#include "private/container/dictionary.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary * adapters = NULL;

Status *
AddAdapter
( Adapter * adapter )
{
  if( adapter == NULL || adapter->name == NULL )
    return NULL;
  
  if( adapters == NULL ){
    adapters = NewDictionary();
    
    if( adapters == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  void * value = ( void * ) adapter;
  if( SetDictionaryValue( adapters, adapter->name, value ) == NULL )
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
( const char * name )
{
  if( !adapters ){
    adapters = NewDictionary();
    
    if( adapters == NULL )
      return NULL;
  }
  
  Adapter * adapter = GetDictionaryValue( adapters, name );
  
  if( adapter == NULL ){
    if( InitializeAdapterByName( name ) != NULL )
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
( Adapter * adapter, const char * option, void * value )
{
  if( adapter == NULL || option == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( adapter->options == NULL ){
    adapter->options = NewDictionary();
    
    if( adapter->options == NULL )
      return RaiseAbnormalStatus( "dictionary failure" );
  }
  
  Dictionary * result;
  result =  SetDictionaryValue( adapter->options, option, value );
  
  if( result == NULL )
    return RaiseAbnormalStatus( "dictionary failure" );
  else
    return NULL;
}
