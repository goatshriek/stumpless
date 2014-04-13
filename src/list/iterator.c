#include <stdlib.h>

#include "private/type.h"

#include "private/list/iterator.h"

#include "static/list.h"

#include "static/list/iterator.h"

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
  if( !iterator )
    return 0;
  
  return iterator->current != NULL;
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
