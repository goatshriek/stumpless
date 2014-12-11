#include <stdlib.h>

#include "private/type.h"
#include "private/container/list/const_iterator.h"
#include "static/container/list.h"
#include "static/container/list/const_iterator.h"

ListConstIterator *
CopyListConstIterator
( const ListConstIterator * iterator )
{
  ListConstIterator *copy;

  if( !iterator )
    return NULL;

  copy = malloc( sizeof( ListConstIterator ) );
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
  return iterator != NULL && iterator->current != NULL;
}

const void *
NextInListConstIterator
( ListConstIterator *iterator )
{
  Node *temp;
  const void *value;

  if( !iterator || !iterator->current )
    return NULL;

  value = iterator->current->value;

  temp = iterator->current;
  iterator->current = XORNODES( iterator->previous, temp->neighbors );
  iterator->previous = temp;

  return value;
}

ListConstIterator *
NewListConstIterator
( const List *list, int position )
{
  int i, steps;
  ListConstIterator *iterator;
  Node *current, *previous = NULL, *temp;

  if( !list )
    return NULL;

  iterator = malloc( sizeof( ListConstIterator ) );
  if( !iterator )
    return NULL;

  iterator->list = list;

  if( position >= 0 ){
    current = list->first;
    steps = position;
  } else {
    current = list->last;
    steps = -( position + 1 );
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
  iterator->previous = previous;
  return iterator;
}
