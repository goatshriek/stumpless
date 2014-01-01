#include <stdlib.h>

#include "private/list_iterator.h"
#include "private/static/list_iterator.h"
#include "private/type.h"

ListIterator *
CopyListIterator
( ListIterator * iterator )
{
  return NULL;
}

void
DestroyListIterator
( ListIterator * iterator )
{
  return;
}

unsigned short
ListIteratorHasNext
( ListIterator * iterator )
{
  return 0;
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
  return NULL;
}
