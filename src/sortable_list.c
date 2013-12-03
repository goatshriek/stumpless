#include <stdlib.h>

#include "private/sortable_list.h"
#include "private/sortable_list_static.h"
#include "private/type.h"

SortableList *
AppendSortableLists
( SortableList * first, SortableList * second )
{
  if( first == NULL )
    return NULL;
  
  Node * node = second->first;
  while( node != NULL ){
    AppendToSortableList( first, node->value );
    
    node = node->next;
  }
  
  return first;
}

SortableList *
AppendToSortableList
( SortableList * list, void * value )
{
  if( list == NULL )
    return NULL;
  
  Node * node = malloc( sizeof( Node ) );
  if( node == NULL )
    return NULL;
  
  node->next = NULL;
  node->value = value;
  
  if( list->last == NULL ){
    list->first = list->last = node;
  } else {
    list->last->next = node;
    list->last = node;
  }
  
  return list;
}

void *
BeginSortableList
( SortableList * list )
{
  if( list == NULL || list->first == NULL )
    return NULL;
  
  list->current = list->first;
  
  return list->current->value;
}

SortableList *
CopySortableList
( SortableList * list )
{
  if( list == NULL )
    return NULL;
  
  SortableList * copy = NewSortableList();
  Node * node = list->first;
  while( node != NULL ){
    AppendToSortableList( copy, node->value );
    node = node->next;
  }
  
  return copy;
}

void
DestroySortableList
( SortableList * list )
{
  DestroyNode( list->first );
  
  free( list );
  
  return;
}

void *
NextInSortableList
( SortableList * list )
{
  if( list == NULL || list->current == NULL )
    return NULL;
  
  list->current = list->current->next;
  
  if( list->current == NULL )
    return NULL;
  else
    return list->current->value;
}

SortableList *
NewSortableList
()
{
  SortableList * list = malloc( sizeof( SortableList ) );
  if( list == NULL )
    return NULL;
  
  list->first = list->current = list->last = NULL;
  
  return list;
}

SortableSortableList *
NewSortableListFromList
( SortableList * list, unsigned short ( *compare )( void *, void *, Dictionary * ) )
{
  return NULL;
}

SortableList *
PrependToSortableList
( SortableList * list, void * value )
{
  if( list == NULL || value == NULL )
    return NULL;
  
  Node * node = malloc( sizeof( Node ) );
  if( node == NULL )
    return NULL;
  
  node->next = list->first;
  node->value = value;
  
  list->first = node;
  
  if( list->last == NULL )
    list->last = node;
  
  return list;
}

SortableList *
SetSortableListComparison
( SortableList *, unsigned short ( *compare )( void *, void *, Dictionary * ) )
{
  return NULL;
}

unsigned short
SortableListContains
( SortableList * list, void * value )
{
  if( list == NULL )
    return 0;
  
  Node * node = list->first;
  while( node != NULL ){
    if( node->value == value )
      return 1;
    
    node = node->next;
  } 
  
  return 0;
}

unsigned short
SortableListIsEmpty
( SortableList * list )
{
  return list == NULL || list->first == NULL;
}

static
void
DestroyNode
( Node * node )
{
  if( node == NULL )
    return;
  
  Node * next = node->next;
  free( node );
  
  DestroyNode( next );
}
