#include <stdio.h>
#include <string.h>

#include "private/comparator_list.h"
#include "private/configuration.h"
#include "private/list.h"
#include "private/static/comparator_list.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendToComparatorList
( ComparatorList * list, Comparator * comparator )
{
  if( list == NULL || comparator == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, comparator );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

unsigned short
ComparatorListIsEmpty
( ComparatorList * list )
{
  return list == NULL || ListIsEmpty( list->list );
}

ComparatorList *
CopyComparatorList
( ComparatorList * list )
{
  if( list == NULL )
    return NULL;
  
  ComparatorList * copy = malloc( sizeof( ComparatorList ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyComparatorList
( ComparatorList * list )
{
  DestroyList( list->list );
  
  free( list );
  
  return;
}

ComparatorList *
NewComparatorList
( void )
{
  ComparatorList * list = malloc( sizeof( ComparatorList ) );
  if( list == NULL )
    return NULL;
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Status *
PrependToComparatorList
( ComparatorList * list, Comparator * comparator )
{
  if( list == NULL || comparator == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, comparator );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

short
RunComparatorList
( ComparatorList * list, const void * value_1, const void * value_2 )
{
  if( list == NULL )
    return 0;
  
  // todo finish
  
  return 0;
}
