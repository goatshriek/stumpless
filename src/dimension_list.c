#include "private/configuration.h"
#include "private/dimension_list.h"
#include "private/dimension_list_static.h"
#include "private/list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToDimensionList
( DimensionList * list, Dimension * dimension )
{
  if( list == NULL || dimension == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, dimension );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Dimension *
BeginDimensionList
( DimensionList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
}

DimensionList *
CopyDimensionList
( DimensionList * list )
{
  if( list == NULL )
    return NULL;
  
  DimensionList * copy = malloc( sizeof( DimensionList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyDimensionList
( DimensionList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

unsigned short
DimensionListIsEmpty
( DimensionList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

DimensionList *
MergeDimensionLists
( DimensionList * primary, DimensionList * secondary )
{
  if( primary == NULL )
    return secondary;
  
  if( secondary == NULL )
    return primary;
  
  Dimension * primary_dimension = BeginDimensionList( primary );
  Dimension * secondary_dimension = BeginDimensionList( secondary );
  while( secondary_dimension != NULL ){
    EventAttribute * secondary_event = secondary_dimension->event_dimension;
    unsigned short matched = 0;
    while( primary_dimension != NULL ){
      EventAttribute * primary_event = primary_dimension->event_dimension;
      if( primary_event == secondary_event ){
        matched = 1;
        break;
      }
      
      primary_dimension = NextInDimensionList( primary );
    }
    if( !matched )
      AppendToDimensionList( primary, secondary_dimension );
    
    secondary_dimension = NextInDimensionList( secondary );
  }
  
  return primary;
}

DimensionList *
NewDimensionList
( void )
{
  DimensionList * list = malloc( sizeof( DimensionList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Dimension *
NextInDimensionList
( DimensionList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
}

Status *
PrependToDimensionList
( DimensionList * list, Dimension * dimension )
{
  if( list == NULL || dimension == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, dimension );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}
