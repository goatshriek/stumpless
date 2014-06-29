#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/reverse_iterator.h"

#include "static/container/list.h"

#include "static/container/list/reverse_iterator.h"

ListReverseIterator *
CopyListReverseIterator
( const ListReverseIterator * iterator )
{
  if( !iterator )
    return NULL;

  ListReverseIterator * copy = malloc( sizeof( ListReverseIterator ) );
  if( !copy )
    return NULL;

  copy->list = iterator->list;
  copy->current = iterator->current;
  copy->previous = iterator->previous;

  return copy;
}

void
DestroyListReverseIterator
( ListReverseIterator * iterator )
{
  free( iterator );

  return;
}

unsigned short
ListReverseIteratorHasNext
( const ListReverseIterator * iterator )
{
  if( !iterator )
    return 0;

  return iterator->current != NULL;
}

void *
NextInListReverseIterator
( ListReverseIterator * iterator )
{
  if( !iterator || !iterator->current )
    return NULL;

  void * value = iterator->current->value;

  Node * temp = iterator->current;
  iterator->current = XORNODES( iterator->previous, iterator->current->neighbors );
  iterator->previous = temp;

  return value;
}

ListReverseIterator *
NewListReverseIterator
( List * list, int position )
{
  if( !list )
    return NULL;

  ListReverseIterator * iterator = malloc( sizeof( ListReverseIterator ) );
  if( !iterator )
    return NULL;

  iterator->list = list;

  int i, steps;
  Node * temp;
  Node * previous = NULL;
  Node * current;
  if( position >= 0 ){
    current = list->last;
    steps = position;
  } else {
    current = list->first;
    steps = -position;
  }

  for( i = 0; i < steps; i++ ){
    temp = current;
    current = XORNODES( previous, current->neighbors );
    if( !current ){
      current = temp;
      break;
    }
    previous = temp;
  }

  iterator->current = current;
  return iterator;
}
