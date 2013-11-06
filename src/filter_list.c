#include <stdio.h>
#include <string.h>

#include "private/configuration.h"
#include "private/filter_list.h"
#include "private/filter_list_static.h"
#include "private/list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToFilterList
( FilterList * list, Filter * filter )
{
  if( list == NULL || filter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, filter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Filter *
BeginFilterList
( FilterList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
}

FilterList *
CopyFilterList
( FilterList * list )
{
  if( list == NULL )
    return NULL;
  
  FilterList * copy = malloc( sizeof( FilterList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyFilterList
( FilterList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

unsigned short
EntryThroughFilterList
( FilterList * list, Entry * entry )
{
  return 0;
}

unsigned short
FilterListIsEmpty
( FilterList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

FilterList *
NewFilterList
( void )
{
  FilterList * list = malloc( sizeof( FilterList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Filter *
NextInFilterList
( FilterList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
}

unsigned short
OutputThroughFilterList
( FilterList * list, Output * output )
{
  return 0;
}

Status *
PrependToFilterList
( FilterList * list, Filter * filter )
{
  if( list == NULL || filter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, filter );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

unsigned short
ValueThroughFilterList
( FilterList * list, Value * value )
{
  return 0;
}
