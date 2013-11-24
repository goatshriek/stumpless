#include "private/configuration.h"
#include "private/entry_attribute_list.h"
#include "private/entry_attribute_list_static.h"
#include "private/list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToEntryAttributeList
( EntryAttributeList * list, EntryAttribute * attribute )
{
  if( list == NULL || attribute == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, attribute );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

EntryAttribute *
BeginEntryAttributeList
( EntryAttributeList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
}

EntryAttributeList *
CopyEntryAttributeList
( EntryAttributeList * list )
{
  if( list == NULL )
    return NULL;
  
  EntryAttributeList * copy = malloc( sizeof( EntryAttributeList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyEntryAttributeList
( EntryAttributeList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

unsigned short
EntryAttributeListIsEmpty
( EntryAttributeList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

EntryAttributeList *
NewEntryAttributeList
( void )
{
  EntryAttributeList * list = malloc( sizeof( EntryAttributeList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

EntryAttribute *
NextInEntryAttributeList
( EntryAttributeList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
}

Status *
PrependToEntryAttributeList
( EntryAttributeList * list, EntryAttribute * attribute )
{
  if( list == NULL || attribute == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, attribute );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}
