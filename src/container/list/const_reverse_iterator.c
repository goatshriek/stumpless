#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/const_reverse_iterator.h"

#include "static/container/list.h"

#include "static/container/list/const_reverse_iterator.h"

ListConstReverseIterator *
CopyListConstReverseIterator
( const ListConstReverseIterator * iterator )
{
  ListConstReverseIterator *copy;

  if( !iterator )
    return NULL;

  copy = malloc( sizeof( ListConstReverseIterator ) );
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
  Node *temp;
  const void *value;

  if( !iterator || !iterator->current )
    return NULL;

  value = iterator->current->value;

  temp = iterator->current;
  iterator->current = XORNODES( iterator->previous, iterator->current->neighbors );
  iterator->previous = temp;

  return value;
}

ListConstReverseIterator *
NewListConstReverseIterator
( const List *list, int position )
{
  int i;
  ListConstReverseIterator *iterator;
  Node *current, *previous = NULL, *temp;

  if( !list )
    return NULL;

  iterator = malloc( sizeof( ListConstReverseIterator ) );
  if( !iterator )
    return NULL;

  iterator->list = list;

  current = list->first;
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
