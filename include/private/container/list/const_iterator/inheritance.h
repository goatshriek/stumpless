#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_INHERITANCE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_INHERITANCE_H

#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/iterator.h"

#define COPY_LIST_CONST_ITERATOR( type )                                       \
type##ListConstIterator *                                                      \
Copy##type##ListConstIterator                                                  \
( const type##ListConstIterator * iterator )                                   \
{                                                                              \
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  type##ListConstIterator * copy = malloc( sizeof( type##ListConstIterator ) );\
  if( !copy )                                                                  \
    return NULL;                                                               \
                                                                               \
  copy->iterator = CopyListConstIterator( iterator->iterator );                \
  if( !copy->iterator )                                                        \
    return NULL;                                                               \
                                                                               \
  return copy;                                                                 \
}

#define DESTROY_LIST_CONST_ITERATOR( type )                                    \
void                                                                           \
Destroy##type##ListConstIterator                                               \
( type##ListConstIterator * iterator )                                         \
{                                                                              \
  if( !iterator )                                                              \
    return;                                                                    \
                                                                               \
  DestroyListConstIterator( iterator->iterator );                              \
                                                                               \
  free( iterator );                                                            \
                                                                               \
  return;                                                                      \
}

#define LIST_CONST_ITERATOR_HAS_NEXT( type )                                   \
unsigned short                                                                 \
type##ListConstIteratorHasNext                                                 \
( const type##ListConstIterator * iterator )                                   \
{                                                                              \
  if( !iterator )                                                              \
    return 0;                                                                  \
                                                                               \
  return ListConstIteratorHasNext( iterator->iterator );                       \
}

#define NEW_LIST_CONST_ITERATOR( type )                                        \
type##ListConstIterator *                                                      \
New##type##ListConstIterator                                                   \
( const type##List *list, int position )                                       \
{                                                                              \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  type##ListConstIterator * iterator = malloc( sizeof( type##ListConstIterator ) );\
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  iterator->iterator = NewListConstIterator( list->list, position );           \
  if( !iterator->iterator )                                                    \
    return NULL;                                                               \
                                                                               \
  return iterator;                                                             \
}

#define NEXT_IN_LIST_CONST_ITERATOR( type )                                    \
const type *                                                                   \
NextIn##type##ListConstIterator                                                \
( type##ListConstIterator *iterator )                                          \
{                                                                              \
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  return NextInListConstIterator( iterator->iterator );                        \
}

#endif
