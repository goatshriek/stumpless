#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_INHERITANCE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_INHERITANCE_H

#include <stdlib.h>

#include "private/type.h"

#include "private/container/list/iterator.h"

#define COPY_LIST_CONST_REVERSE_ITERATOR( type )                               \
type##ListConstReverseIterator *                                               \
Copy##type##ListConstReverseIterator                                           \
( const type##ListConstReverseIterator * iterator )                            \
{                                                                              \
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  type##ListConstReverseIterator * copy = malloc( sizeof( type##ListConstReverseIterator ) );\
  if( !copy )                                                                  \
    return NULL;                                                               \
                                                                               \
  copy->iterator = CopyListConstReverseIterator( iterator->iterator );         \
  if( !copy->iterator )                                                        \
    return NULL;                                                               \
                                                                               \
  return copy;                                                                 \
}

#define DESTROY_LIST_CONST_REVERSE_ITERATOR( type )                            \
void                                                                           \
Destroy##type##ListConstReverseIterator                                        \
( type##ListConstReverseIterator * iterator )                                  \
{                                                                              \
  if( !iterator )                                                              \
    return;                                                                    \
                                                                               \
  DestroyListConstReverseIterator( iterator->iterator );                       \
                                                                               \
  free( iterator );                                                            \
                                                                               \
  return;                                                                      \
}

#define LIST_CONST_REVERSE_ITERATOR_HAS_NEXT( type )                           \
unsigned short                                                                 \
type##ListConstReverseIteratorHasNext                                          \
( const type##ListConstReverseIterator * iterator )                            \
{                                                                              \
  if( !iterator )                                                              \
    return 0;                                                                  \
                                                                               \
  return ListConstReverseIteratorHasNext( iterator->iterator );                \
}
  
#define NEW_LIST_CONST_REVERSE_ITERATOR( type )                                \
type##ListConstReverseIterator *                                               \
New##type##ListConstReverseIterator                                            \
( const type##List * list, int position )                                      \
{                                                                              \
  type##ListConstReverseIterator * iterator = malloc( sizeof( type##ListConstReverseIterator ) );\
  if( !iterator )                                                              \
    return NULL;                                                               \
                                                                               \
  iterator->iterator = NewListConstReverseIterator( list->list, position );    \
  if( !iterator->iterator )                                                    \
    return NULL;                                                               \
                                                                               \
  return iterator;                                                             \
}

#define NEXT_IN_LIST_CONST_REVERSE_ITERATOR( type )                            \
const type *                                                                   \
NextIn##type##ListConstReverseIterator                                         \
( type##ListConstReverseIterator * iterator )                                  \
{                                                                              \
  return NextInListConstReverseIterator( iterator->iterator );                 \
}

#endif
