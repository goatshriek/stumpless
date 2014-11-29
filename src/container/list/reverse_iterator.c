#include <stdlib.h>

#include "private/container/list/reverse_iterator.h"
#include "private/type.h"
#include "static/container/list.h"
#include "static/container/list/reverse_iterator.h"

ListReverseIterator *
CopyListReverseIterator
( const ListReverseIterator *iterator )
{
  ListReverseIterator *copy;

  if( !iterator )
    return NULL;

  copy = malloc( sizeof( ListReverseIterator ) );
  if( !copy )
    return NULL;

  copy->list = iterator->list;
  copy->current = iterator->current;
  copy->previous = iterator->previous;

  return copy;
}

void
DestroyListReverseIterator
( ListReverseIterator *iterator )
{
  free( iterator );

  return;
}

unsigned short
ListReverseIteratorHasNext
( const ListReverseIterator *iterator )
{
  return iterator && iterator->current != NULL;
}

void *
NextInListReverseIterator
( ListReverseIterator *iterator )
{
  Node *temp;
  void *value;

  if( !iterator || !iterator->current )
    return NULL;

  value = iterator->current->value;

  temp = iterator->current;
  iterator->current = XORNODES( iterator->previous, temp->neighbors );
  iterator->previous = temp;

  return value;
}

ListReverseIterator *
NewListReverseIterator
( List *list, int position )
{
  int i, steps;
  ListReverseIterator *iterator;
  Node *current, *previous = NULL, *temp;

  if( !list )
    return NULL;

  iterator = malloc( sizeof( ListReverseIterator ) );
  if( !iterator )
    return NULL;

  iterator->list = list;

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

void *
PreviousInListReverseIterator
( ListReverseIterator *iterator )
{
  Node *temp;
  void *value;

  if( !iterator || !iterator->current )
    return NULL;

  value = iterator->previous->value;

  temp = iterator->previous;
  iterator->previous = XORNODES( iterator->current, temp->neighbors );
  iterator->current = temp;

  return value;
}
