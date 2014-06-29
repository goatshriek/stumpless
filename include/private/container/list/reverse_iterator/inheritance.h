#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_INHERITANCE_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_INHERITANCE_H

#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/iterator.h"

#define COPY_LIST_REVERSE_ITERATOR( type )                                     \
type##ListReverseIterator *                                                    \
Copy##type##ListReverseIterator                                                \
( const type##ListReverseIterator * iterator )                                 \
{                                                                              \
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  type##ListReverseIterator * copy = malloc( sizeof( type##ListReverseIterator ) );\
  if( !copy )                                                                  \
    return NULL;                                                               \
                                                                               \
  copy->iterator = CopyListReverseIterator( iterator->iterator );              \
  if( !copy->iterator )                                                        \
    return NULL;                                                               \
                                                                               \
  return copy;                                                                 \
}

#define DESTROY_LIST_REVERSE_ITERATOR( type )                                  \
void                                                                           \
Destroy##type##ListReverseIterator                                             \
( type##ListReverseIterator * iterator )                                       \
{                                                                              \
  if( !iterator )                                                              \
    return;                                                                    \
                                                                               \
  DestroyListReverseIterator( iterator->iterator );                            \
                                                                               \
  free( iterator );                                                            \
                                                                               \
  return;                                                                      \
}

#define LIST_REVERSE_ITERATOR_HAS_NEXT( type )                                 \
unsigned short                                                                 \
type##ListReverseIteratorHasNext                                               \
( const type##ListReverseIterator * iterator )                                 \
{                                                                              \
  if( !iterator )                                                              \
    return 0;                                                                  \
                                                                               \
  return ListReverseIteratorHasNext( iterator->iterator );                     \
}

#define NEW_LIST_REVERSE_ITERATOR( type )                                      \
type##ListReverseIterator *                                                    \
New##type##ListReverseIterator                                                 \
( type##List * list, int position )                                            \
{                                                                              \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  type##ListReverseIterator * iterator = malloc( sizeof( type##ListReverseIterator ) );\
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  iterator->iterator = NewListReverseIterator( list->list, position );         \
  if( !iterator->iterator )                                                    \
    return NULL;                                                               \
                                                                               \
  return iterator;                                                             \
}

#define NEXT_IN_LIST_REVERSE_ITERATOR( type )                                  \
type *                                                                         \
NextIn##type##ListReverseIterator                                              \
( type##ListReverseIterator *iterator )                                        \
{                                                                              \
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  return NextInListReverseIterator( iterator->iterator );                      \
}

#endif
