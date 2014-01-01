#include <stdlib.h>

#include "private/list.h"
#include "private/static/list.h"
#include "private/type.h"

List *
AddSeparatorToList
( List * list, void * value )
{
  if( list == NULL || value == NULL )
    return NULL;
  
  if( list->first == NULL )
    return list;
  
  if( SeparateNodes( list->first, value ) == NULL )
    return NULL;
  
  return list;
}

List *
AppendLists
( List * first, const List * second )
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
( const List * list )
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
  if( list == NULL )
    return;
  
  DestroyNode( list->first );
  
  free( list );
  
  return;
}

ListIterator *
GetListIterator
( List * list )
{
  return NULL;
}

unsigned short
ListContains
( const List * list, const void * value )
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
( const List * list )
{
  return list == NULL || list->first == NULL;
}

unsigned
ListSize
( const List * list )
{
  if( list == NULL )
    return 0;
  
  unsigned size = 0;
  
  Node * node = list->first;
  while( node != NULL ){
    size++;
    node = node->next;
  }
  
  return size;
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

static
void *
SeparateNodes
( Node * node, void * value )
{
  if( node->next == NULL )
    return value;
  
  Node * separator = malloc( sizeof( Node ) );
  if( separator == NULL )
    return NULL;
  
  separator->value = value;
  separator->next = node->next;
  node->next = separator;
  
  return SeparateNodes( separator->next, value );
}
