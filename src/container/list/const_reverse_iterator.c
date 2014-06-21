#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/const_reverse_iterator.h"

#include "static/container/list.h"

#include "static/container/list/const_reverse_iterator.h"

ListConstReverseIterator *
CopyListConstReverseIterator
( const ListConstReverseIterator * iterator )
{
  if( !iterator )
    return NULL;
  
  ListConstReverseIterator * copy = malloc( sizeof( ListConstReverseIterator ) );
  if( !copy )
    return NULL;
  
  copy->list = iterator->list;
  copy->current = iterator->current;
  copy->previous = iterator->previous;
  
  return copy;
}

void
DestroyListConstReverseIterator
( ListConstReverseIterator * iterator )
{
  free( iterator );
  
  return;
}

unsigned short
ListConstReverseIteratorHasNext
( const ListConstReverseIterator * iterator )
{
  if( !iterator )
    return 0;
  
  return iterator->current != NULL;
}

const void *
NextInListConstReverseIterator
( ListConstReverseIterator * iterator )
{
  if( !iterator || !iterator->current )
    return NULL;
  
  const void * value = iterator->current->value;
  
  Node * temp = iterator->current;
  iterator->current = XORNODES( iterator->previous, iterator->current->neighbors );
  iterator->previous = temp;
  
  return value;
}

ListConstReverseIterator *
NewListConstReverseIterator
( const List * list, int position )
{
  if( !list )
    return NULL;
  
  ListConstReverseIterator * iterator = malloc( sizeof( ListConstReverseIterator ) );
  if( !iterator )
    return NULL;
  
  iterator->list = list;
  
  int i;
  Node * temp;
  Node * previous = NULL;
  Node * current = list->first;
  if( position >= 0 ){
    current = list->first;
    for( i = 0; i < position; i++ ){
      temp = current;
      current = XORNODES( previous, current->neighbors );
      previous = temp;
    }
  } else {
    current = list->last;
    for( i = 0; i > position; i-- ){
      temp = current;
      current = XORNODES( previous, current->neighbors );
      previous = temp;
    }
  }
  
  iterator->current = current;
  
  return iterator;
}
