#include <stdlib.h>

#include "private/list_iterator.h"
#include "private/static/list_iterator.h"
#include "private/type.h"

ListIterator *
CopyListIterator
( const ListIterator * iterator )
{
  if( iterator == NULL )
    return NULL;
  
  ListIterator * copy = malloc( sizeof( ListIterator ) );
  if( copy == NULL )
    return NULL;
  
  copy->list = iterator->list;
  copy->current = iterator->current;
  
  return copy;
}

void
DestroyListIterator
( ListIterator * iterator )
{
  free( iterator );
  
  return;
}

unsigned short
ListIteratorHasNext
( const ListIterator * iterator )
{
  if( iterator == NULL )
    return 0;
  
  return iterator->current != NULL;
}

ListIterator *
NewListIterator
( List * list )
{
  if( list == NULL )
    return NULL;
  
  ListIterator * iterator = malloc( sizeof( ListIterator ) );
  if( iterator == NULL )
    return NULL;
  
  iterator->list = list;
  iterator->current = list->first;
  
  return iterator;
}

void *
NextInListIterator
( ListIterator * iterator )
{
  if( iterator == NULL || iterator->current == NULL )
    return NULL;
  
  void * value = iterator->current->value;
  
  iterator->current = iterator->current->next;
  
  return value;
}
