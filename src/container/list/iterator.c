#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/iterator.h"

#include "static/container/list.h"

#include "static/container/list/iterator.h"

ListIterator *
CopyListIterator
( const ListIterator *iterator )
{
  if( !iterator )
    return NULL;

  ListIterator *copy = malloc( sizeof( ListIterator ) );
  if( !copy )
    return NULL;

  copy->list = iterator->list;
  copy->current = iterator->current;
  copy->previous = iterator->previous;

  return copy;
}

void
DestroyListIterator
( ListIterator *iterator )
{
  free( iterator );

  return;
}

unsigned short
ListIteratorHasNext
( const ListIterator *iterator )
{
  return iterator && iterator->current != NULL;
}

unsigned short
ListIteratorHasPrevious
( const ListIterator *iterator )
{
  return iterator && iterator->previous != NULL;
}

ListIterator *
NewListIterator
( List * list, int position )
{
  if( !list )
    return NULL;

  ListIterator *iterator = malloc( sizeof( ListIterator ) );
  if( !iterator )
    return NULL;

  iterator->list = list;

  int i, steps;
  Node *temp, *current, *previous=NULL;
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

void *
NextInListIterator
( ListIterator *iterator )
{
  if( !iterator || !iterator->current )
    return NULL;

  void *value = iterator->current->value;

  Node *temp = iterator->current;
  iterator->current = XORNODES( iterator->previous, temp->neighbors );
  iterator->previous = temp;

  return value;
}

void *
PreviousInListIterator
( ListIterator *iterator )
{
  if( !iterator || !iterator->previous )
    return NULL;

  void *value = iterator->previous->value;

  Node *temp = iterator->previous;
  iterator->previous = XORNODES( iterator->current, temp->neighbors );
  iterator->current = temp;

  return value;
}
