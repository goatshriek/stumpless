#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_INHERITANCE_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_INHERITANCE_H

#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/iterator.h"

#define COPY_LIST_ITERATOR( type )                                             \
type##ListIterator *                                                           \
Copy##type##ListIterator                                                       \
( const type##ListIterator * iterator )                                        \
{                                                                              \
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  type##ListIterator * copy = malloc( sizeof( type##ListIterator ) );          \
  if( !copy )                                                                  \
    return NULL;                                                               \
                                                                               \
  copy->iterator = CopyListIterator( iterator->iterator );                     \
  if( !copy->iterator )                                                        \
    return NULL;                                                               \
                                                                               \
  return copy;                                                                 \
}

#define DESTROY_LIST_ITERATOR( type )                                          \
void                                                                           \
Destroy##type##ListIterator                                                    \
( type##ListIterator * iterator )                                              \
{                                                                              \
  if( !iterator )                                                              \
    return;                                                                    \
                                                                               \
  DestroyListIterator( iterator->iterator );                                   \
                                                                               \
  free( iterator );                                                            \
                                                                               \
  return;                                                                      \
}

#define LIST_ITERATOR_HAS_NEXT( type )                                         \
unsigned short                                                                 \
type##ListIteratorHasNext                                                      \
( const type##ListIterator * iterator )                                        \
{                                                                              \
  if( !iterator )                                                              \
    return 0;                                                                  \
                                                                               \
  return ListIteratorHasNext( iterator->iterator );                            \
}
  
#define NEW_LIST_ITERATOR( type )                                              \
type##ListIterator *                                                           \
New##type##ListIterator                                                        \
( type##List * list, int position )                                            \
{                                                                              \
  type##ListIterator * iterator = malloc( sizeof( type##ListIterator ) );      \
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  iterator->iterator = NewListIterator( list->list, position );                \
  if( !iterator->iterator )                                                    \
    return NULL;                                                               \
                                                                               \
  return iterator;                                                             \
}

#define NEXT_IN_LIST_ITERATOR( type )                                          \
type *                                                                         \
NextIn##type##ListIterator                                                     \
( type##ListIterator *iterator )                                               \
{                                                                              \
  return NextInListIterator( iterator->iterator );                             \
}

#endif
