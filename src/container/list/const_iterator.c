#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/const_iterator.h"

#include "static/container/list.h"

#include "static/container/list/const_iterator.h"

ListConstIterator *
CopyListConstIterator
( const ListConstIterator * iterator )
{
  if( !iterator )
    return NULL;
  
  ListConstIterator * copy = malloc( sizeof( ListConstIterator ) );
  if( !copy )
    return NULL;
  
  copy->list = iterator->list;
  copy->current = iterator->current;
  copy->previous = iterator->previous;
  
  return copy;
}

void
DestroyListConstIterator
( ListConstIterator * iterator )
{
  free( iterator );
  
  return;
}

unsigned short
ListConstIteratorHasNext
( const ListConstIterator * iterator )
{
  if( !iterator )
    return 0;
  
  return iterator->current != NULL;
}

const void *
NextInListConstIterator
( ListConstIterator * iterator )
{
  if( !iterator || !iterator->current )
    return NULL;
  
  const void * value = iterator->current->value;
  
  Node * temp = iterator->current;
  iterator->current = XORNODES( iterator->previous, iterator->current->neighbors );
  iterator->previous = temp;
  
  return value;
}

ListConstIterator *
NewListConstIterator
( const List * list, int position )
{
  if( !list )
    return NULL;
  
  ListConstIterator * iterator = malloc( sizeof( ListConstIterator ) );
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
