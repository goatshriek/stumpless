#include <stdlib.h>

#include "private/sortable_list.h"
#include "private/sortable_list_static.h"
#include "private/type.h"

List *
AppendLists
( List * first, List * second )
{
  if( first == NULL )
    return NULL;
  
  Node * node = second->first;
  while( node != NULL ){
    AppendToList( first, node->value );
    
    node = node->next;
  }
  
  return first;
}

List *
AppendToList
( List * list, void * value )
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
BeginList
( List * list )
{
  if( list == NULL || list->first == NULL )
    return NULL;
  
  list->current = list->first;
  
  return list->current->value;
}

List *
CopyList
( List * list )
{
  if( list == NULL )
    return NULL;
  
  List * copy = NewList();
  Node * node = list->first;
  while( node != NULL ){
    AppendToList( copy, node->value );
    node = node->next;
  }
  
  return copy;
}

void
DestroyList
( List * list )
{
  DestroyNode( list->first );
  
  free( list );
  
  return;
}

unsigned short
ListContains
( List * list, void * value )
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
ListIsEmpty
( List * list )
{
  return list == NULL || list->first == NULL;
}

void *
NextInList
( List * list )
{
  if( list == NULL || list->current == NULL )
    return NULL;
  
  list->current = list->current->next;
  
  if( list->current == NULL )
    return NULL;
  else
    return list->current->value;
}

List *
NewList
()
{
  List * list = malloc( sizeof( List ) );
  if( list == NULL )
    return NULL;
  
  list->first = list->current = list->last = NULL;
  
  return list;
}

List *
PrependToList
( List * list, void * value )
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
