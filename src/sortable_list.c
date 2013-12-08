#include <stdlib.h>

#include "private/dictionary.h"
#include "private/list.h"
#include "private/sortable_list.h"
#include "private/sortable_list_static.h"
#include "private/type.h"

SortableList *
AddToSortableList
( SortableList * list, void * value )
{
  return NULL;
}

void *
BeginSortableList
( SortableList * list )
{
  return NULL;
}

SortableList *
CopySortableList
( SortableList * list )
{
  return NULL;
}

void
DestroySortableList
( SortableList * list )
{
  if( list != NULL && list->first != NULL )
    DestroyNode( list->first, list->first->neighbors );
  
  free( list );
  
  return;
}

SortableList *
MergeSortableLists
( SortableList * first, SortableList * second )
{
  return NULL;
}

void *
NextInSortableList
( SortableList * list )
{
  return NULL;
}

SortableList *
NewSortableList
()
{
  SortableList * list = malloc( sizeof( SortableList ) );
  if( list == NULL )
    return NULL;
  
  list->compare = NULL;
  list->current = NULL;
  list->first = NULL;
  list->last = NULL;
  list->options = NULL;
  list->previous = NULL;
  
  return list;
}

SortableList *
NewSortableListFromList
( List * list, short ( *compare )( const void *, const void *, Dictionary * ) )
{
  if( list == NULL || compare == NULL )
    return NULL;
  
  SortableList * sortable_list = malloc( sizeof( SortableList ) );
  if( sortable_list == NULL )
    return NULL;
  
  sortable_list->compare = compare;
  sortable_list->current = NULL;
  sortable_list->first = NULL;
  sortable_list->last = NULL;
  sortable_list->options = NULL;
  sortable_list->previous = NULL;
  
  void * value = BeginList( list );
  while( value != NULL ){
    if( AddToSortableList( sortable_list, value ) == NULL )
      return NULL;
    
    value = NextInList( list );
  }
  
  return sortable_list;
}

SortableList *
SetSortableListComparison
( SortableList * list, short ( *compare )( const void *, const void *, Dictionary * ) )
{
  if( list == NULL || compare == NULL )
    return NULL;
  
  list->compare = compare;
  return SortList( list );
}

SortableList *
SetSortableListOptions
( SortableList * list, Dictionary * options )
{
  if( list == NULL )
    return NULL;
  
  list->options = options;
  return SortList( list );
}

unsigned short
SortableListContains
( SortableList * list, void * value )
{
  return 0;
}

unsigned short
SortableListIsEmpty
( SortableList * list )
{
  return 0;
}

static
void
DestroyNode
( Node * node, intptr_t next )
{
  if( node == NULL )
    return;
  
  free( node );
  
  Node * next_node = ( Node * ) next;
  return DestroyNode( next_node, next_node->neighbors ^ ( intptr_t ) node );
}

static
SortableList *
SortList
( SortableList * list )
{
  return NULL;
}
