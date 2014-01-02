#include "private/adapter_list.h"
#include "private/configuration.h"
#include "private/entry.h"
#include "private/list.h"
#include "private/static/adapter_list.h"
#include "private/status.h"
#include "private/type.h"

unsigned short
AdapterListContains
( AdapterList * list, Adapter * adapter )
{
  return list != NULL && ListContains( list->list, adapter );
}

unsigned short
AdapterListIsEmpty
( AdapterList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

Status *
AppendToAdapterList
( AdapterList * list, Adapter * adapter )
{
  if( list == NULL || adapter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, adapter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

AdapterList *
CopyAdapterList
( AdapterList * list )
{
  if( list == NULL )
    return NULL;
  
  AdapterList * copy = malloc( sizeof( AdapterList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyAdapterList
( AdapterList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

AdapterList *
NewAdapterList
( void )
{
  AdapterList * list = malloc( sizeof( AdapterList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Status *
PrependToAdapterList
( AdapterList * list, Adapter * adapter )
{
  if( list == NULL || adapter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, adapter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Entry *
ValueThroughAdapterList
( AdapterList * list, Value * value )
{
  if( list == NULL || value == NULL )
    return NULL;
  
  Adapter * adapter = BeginAdapterList( list );
  Entry * entry = NULL;
  while( adapter != NULL ){
    entry = MergeEntries( entry, adapter->adapt( value, adapter->options ) );
    
    adapter = NextInAdapterList( list );
  }
  
  return entry;
}
