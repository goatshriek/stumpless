#include <stdlib.h>

#include "private/list.h"
#include "private/list_static.h"
#include "private/type.h"

List *
AddSeparatorToList
( List * list, void * value )
{
  if( list == NULL || value == NULL )
    return NULL;
  
  Node * current = list->first;
  Node * separator;
  while( current->next != NULL ){
    separator = malloc( sizeof( Node ) );
    if( separator == NULL )
      return NULL;
    
    separator->next = current->next;
    separator->value = value;
    current->next = separator;
    
    current = separator->next;
  }
  
  return list;
}

List *
AppendLists
( List * first, List * second )
{
  if( first == NULL )
    return NULL;
  
  void * value = StartList( second );
  while( value != NULL ){
    AppendToList( first, value );
    value = NextInList( second );
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

List *
CopyList
( List * list )
{
  if( list == NULL )
    return NULL;
  
  List * copy = NewList();
  void * value = StartList( list );
  while( value != NULL ){
    AppendToList( copy, value );
    value = NextInList( list );
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

void *
StartList
( List * list )
{
  if( list == NULL || list->first == NULL )
    return NULL;
  
  list->current = list->first;
  
  return list->current->value;
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
